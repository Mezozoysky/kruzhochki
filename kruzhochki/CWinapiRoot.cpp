#include "CWinapiRoot.h"
#include "CWinapiEventManager.h"
#include "CGameStateManager.h"
#include "COpenglGfxManager.h"
#include <gl/GL.h>
#include <cstdio>

namespace kruz
{
  CWinapiRoot* CWinapiRoot::createOnce(
    HINSTANCE appInstance,
    bool fullscreen,
    unsigned short width,
    unsigned short height
  )
  {
    if (!smInstance)
    {
      smInstance = new CWinapiRoot(appInstance, fullscreen, width, height);
    }
    return smInstance;
  }

  CWinapiRoot::CWinapiRoot(
    HINSTANCE appInstance,
    bool fullscreen,
    unsigned short width,
    unsigned short height
  ) :
    mIsRunning(true),
    mErrorCode(0),
    mWindowWidth(width),
    mWindowHeight(height),
    mFullscreen(fullscreen),
    mWindow(NULL),
    mDeviceContext(NULL),
    mGLContext(NULL),
    mStateManager(NULL),
    mEventManager(NULL),
    mGfxManager(NULL),
    mFontListsBase(-1)
  {
    smAppInstance = appInstance;
    mStateManager = new CGameStateManager();
    mEventManager = new CWinapiEventManager();
    mGfxManager = new COpenglGfxManager(this); //TODO: GfxManager needs a pointer to to root for using root's glPrintText. Optimize in future.
  }

  CWinapiRoot::CWinapiRoot(const CWinapiRoot& copySrc)
  {
  }

  CWinapiRoot& CWinapiRoot::operator=(const CWinapiRoot& src)
  {
    return *this;
  }

  CWinapiRoot::~CWinapiRoot()
  {
    kruzDebug("Root destructor called.");

    if (mEventManager)
    {
      kruzDebug("Root destructor: clearing event handlers from manager.");
      mEventManager->removeAllEventHandlers();
    }

    if (mStateManager)
    {
      kruzDebug("Root destructor: clearing the states from the manager.");
      mStateManager->clearStates();
    }

    //TODO: delete states here.

    if (mStateManager)
    {
      kruzDebug("Root destructor: deleting state manager.");
      delete mStateManager;
    }

    if (mEventManager)
    {
      kruzDebug("Root destructor: deleting event manager.");
      delete mEventManager;
    }

    if (mGfxManager)
    {
      kruzDebug("Root destructor: deleting GGX manager.");
      delete mGfxManager;
    }

    // Deleting the font lists
    kruzDebug("Root destructor: deleting font lists.");
    glDeleteLists(mFontListsBase, 128);

    // Restoring the mouse cursor.
    ShowCursor(true);

    //TODO: Delete the window resources, etc.
    if (mFullscreen)
    {
      ChangeDisplaySettings(NULL, 0); // ack to the desktop mode.
    }
    if (mGLContext)
    {
      if (!wglMakeCurrent(NULL, NULL)) // Releasing GL context.
      {
        std::cout << "Could not release GLRC context." << std::endl;
      }

      if (!wglDeleteContext(mGLContext)) // Deleting GL context.
      {
        std::cout << "Could not delete GLRC context." << std::endl;
      }
      mGLContext = NULL;
    }
    if (mDeviceContext)
    {
      if (!ReleaseDC(mWindow, mDeviceContext)) // Releasing device context.
      {
        std::cout << "Could not release device context." << std::endl;
      }
      mDeviceContext = NULL;
    }
    if (mWindow)
    {
      if (!DestroyWindow(mWindow)) // Destroing the main window.
      {
        std::cout << "Could not release window." << std::endl;
      }
      mWindow = NULL;
    }

    if (!UnregisterClass(smClassName, smAppInstance)) // Unregister the window class.
    {
      std::cout << "Could not unregister window class." << std::endl;
    }
    smAppInstance = NULL;

    kruzDebug("Root is destructed.");
  }

  IGameStateManager* CWinapiRoot::getStateManager() const
  {
    return mStateManager;
  }

  IEventManager* CWinapiRoot::getEventManager() const
  {
    return mEventManager;
  }

  IGfxManager* CWinapiRoot::getGfxManager() const
  {
    return mGfxManager;
  }

  int CWinapiRoot::run()
  {
    // Creating the main window.
    createWindow();
    // Switching to the starting game state.
    if (mStateManager)
    {
      mStateManager->changeState(mStateManager->getStartState());
    }
    else
    {
      mErrorCode = EC_NULL_STATE_MANAGER;
      mIsRunning = false;
    }

    MSG msg;
    msg.message = ~WM_QUIT;

    //TODO: Control the idle time!
    mIsRunning = true;
    while (mIsRunning)
    {
      if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if (msg.message == WM_QUIT)
        {
          mIsRunning = false;
        }
      }

      if (mStateManager) //TODO: Optimize! Excrescent test.
      {
        // Update the scene.
        mStateManager->update();
          
        glClear(GL_COLOR_BUFFER_BIT);
        glPushMatrix();
        glLoadIdentity();
        glEnable(GL_BLEND); // Blending is needed for semitransparent counter drawing.
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
          
          // Render the scene.
          mStateManager->render();
          // Drawing the custom cursor.
          glDrawCursor();
        glDisable(GL_BLEND);
        glPopMatrix();
        glFlush();
        SwapBuffers(mDeviceContext);
      }
    }

    kruzDebug("Main Loop is terminated.");
    return mErrorCode;
  }

  void CWinapiRoot::terminate(int errorCode)
  {
    mErrorCode = errorCode;
    mIsRunning = false;
  }

  void CWinapiRoot::createWindow()
  {
    // Registering the window class
    WNDCLASS wc;
    wc.style = 0;
    wc.lpfnWndProc = &CWinapiRoot::wndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(NULL); // We dont'care about hIstance fot that time
    wc.hIcon = NULL; // We don't care about the icon.
    wc.hCursor = 0;
    wc.hbrBackground = 0;
    wc.lpszMenuName = NULL; // Don't care about menu
    wc.lpszClassName = smClassName;

    RegisterClass(&wc);

    // Window boundaries
    RECT windowRect;
    windowRect.top = 0;
    windowRect.left = 0;
    windowRect.right = mWindowWidth;
    windowRect.bottom = mWindowHeight;

    // Window style + extended style.
    // Will be initiated later.
    DWORD style;
    DWORD styleEx;

    if (mFullscreen)
    {
      // Creating the device mode for fullscreen window
      DEVMODE screenDevMode;
      memset(&screenDevMode, 0, sizeof(screenDevMode));
      screenDevMode.dmSize = sizeof(screenDevMode);
      screenDevMode.dmPelsWidth = mWindowWidth;
      screenDevMode.dmPelsHeight = mWindowHeight;
      screenDevMode.dmBitsPerPel = 32;
      screenDevMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

      // Set fullscreen mode of terminate the application if failed.
      if (ChangeDisplaySettings(&screenDevMode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
      {
        terminate(EC_FULLSCREEN_FAILED);
        return;
      }

      // Styles for fullscreen mode
      style = WS_POPUP;
      styleEx = WS_EX_APPWINDOW;

      //ShowCursor(false);
      //TODO: Make the sexy custom cursor!
    }
    else
    {
      // Styles for windowed mode.
      style = WS_OVERLAPPEDWINDOW;
      styleEx = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    }

    // Adjusting window boundaries with the given size and styles.
    AdjustWindowRectEx(&windowRect, style, false, styleEx);

    // Creating the main (and only) window.
    mWindow = CreateWindowEx(
      styleEx,
      TEXT(wc.lpszClassName),
      TEXT("Kruzhochki"), // Window title
      WS_CLIPSIBLINGS | WS_CLIPCHILDREN | style,
      0,
      0,
      windowRect.right - windowRect.left,
      windowRect.bottom - windowRect.top,
      NULL,
      NULL,
      GetModuleHandle(NULL), // Don't care about the instance handle.
      this // User data: putting the pointer to CWinapiRoot instance into.
    );

    if (mWindow == NULL)
    {
      terminate(EC_CREATE_WINDOW_FAILED);
      return;
    }

    // Creating the device context.
    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1; //TODO: Figure out what this version does.
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | // Draws to window
                  PFD_SUPPORT_OPENGL | // Supports OpenGL
                  PFD_DOUBLEBUFFER;    // Supports doublebuffering
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;

    mDeviceContext = GetDC(mWindow);

    if (mDeviceContext == NULL)
    {
      terminate(EC_CREATE_CONTEXT_FAILED);
      return;
    }

    // Setting the pixel format
    int pixelFormat = ChoosePixelFormat(mDeviceContext, &pfd);
    if (!pixelFormat)
    {
      terminate(EC_CHOOSE_PIXELFORMAT_FAILED);
      return;
    }

    if (!SetPixelFormat(mDeviceContext, pixelFormat, &pfd))
    {
      terminate(EC_SET_PIXELFORMAT_FAILED);
      return;
    }

    // Creating the OpenGL context
    mGLContext = wglCreateContext(mDeviceContext);
    if (mGLContext == NULL)
    {
      terminate(EC_CREATE_GLCONTEXT_FAILED);
      return;
    }

    // Activating the OpenGL context
    if (!wglMakeCurrent(mDeviceContext, mGLContext))
    {
      terminate(EC_MAKE_GLCONTEXT_CURRENT_FAILED);
      return;
    }

    // Initializing OpenGL
    initOpenGL();
 
    // Raising the window up
    ShowWindow(mWindow, SW_SHOW);
    ShowCursor(false);

    //Force calling it here in order to prevent the loss of calling after than OpenGL is initialized.
    handleSizeEvent(mWindowWidth, mWindowHeight);
  }

  LRESULT CWinapiRoot::wndProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
  {
    if (msg == WM_NCCREATE) // WM_NCCREATE event is raising before WM_CREATE event
    {
      // Obtain the window creating params struct (pointer to the our CWinapiRoot instance is inside of).
      CREATESTRUCT* createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
      // And set CWinapiRoot pointer as the user data of window handle.
      SetWindowLongPtr(
        window,
        GWLP_USERDATA,
        reinterpret_cast<long>(createStruct->lpCreateParams) // lpCreateParams field stores our pointer.
      );
    }

    // Obtain the pointer to CWinapiRoot instance stored in the window handle user data.
    CWinapiRoot* rootInstance = reinterpret_cast<CWinapiRoot*>(GetWindowLongPtr(window, GWLP_USERDATA));
    if (rootInstance)
    {
      if (msg == WM_SIZE)
      {
        //Perform the window resizing
        rootInstance->handleSizeEvent(LOWORD(lParam), HIWORD(lParam));
      }

      if (rootInstance->mEventManager)
      {
        (static_cast<CWinapiEventManager*>(rootInstance->mEventManager))->processWinapiEvent(msg, wParam, lParam);
      }
    }

    return DefWindowProc(window, msg, wParam, lParam);
  }

  void CWinapiRoot::handleSizeEvent(unsigned short width, unsigned short height)
  {
    mWindowWidth = width;
    mWindowHeight = height;
    // Window-wide viewport for OpenGL.
    glViewport(0, 0, width, height);

    // Projection mode.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Orthographic projection.
    glOrtho(0.0, width, height, 0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
  }

  void CWinapiRoot::initOpenGL()
  {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Color using to clear the color buffer.

    //TODO: Is it for textures only?
    //glEnable(GL_ALPHA_TEST); // Alpha test ON.
    //glAlphaFunc(GL_EQUAL, 0.0f); // Skip pixels which alpha is equal to 0.

    HFONT font;
    HFONT oldFont; // Old font to keeping.

    GLuint listsBase = glGenLists(128); // Number of the first of 96 display lists, each correcsponding to one character.

    font = CreateFont(  // Creating GDI font.
      -24, // Font height. Minus means that we need the font based on the charated height instead of cell-height-based.
      0, // Font cell width. 0 means use default value.
      0, // Angle of escapement. We don't rotate text, so don't care.
      0, // Orientation angle. Don't care.
      FW_BOLD, /*FW_DONTCARE,*/ // Font weight.
      0, // Italic.
      0, // Underline.
      0, // Strikeout.
      ANSI_CHARSET, // Default charset (I guess, it's OK for ASCII).
      OUT_TT_PRECIS, // Optput precision. This one means use TrueType if possible.
      CLIP_DEFAULT_PRECIS, // Use default clipping precision.
      ANTIALIASED_QUALITY, // Output quality. Use antialiasing.
      FF_DONTCARE | DEFAULT_PITCH, // Font Family - we don't care; Pitch - don't care.
      "Calibri" // Font name
    );

    oldFont = (HFONT)SelectObject(mDeviceContext, font); // Select the new font (and keep the old one).
    wglUseFontBitmaps(mDeviceContext, 0, 128, listsBase); // Build 96 characters starting at 32th.
    // font is no more needed.
    SelectObject(mDeviceContext, oldFont); // Give back the old font.
    DeleteObject(font); // And deleted the one we've used.
  }

  void CWinapiRoot::glDrawCursor()
  {
    POINT pos;
    GetCursorPos(&pos);
    ScreenToClient(mWindow, &pos);
    if (pos.x >= 0 && pos.x < mWindowWidth && pos.y >= 0 && pos.y < mWindowHeight)
    {
      float x = (float)pos.x;
      float y = (float)pos.y;

      mGfxManager->setColor(1.0f, 1.0f, 1.0, 0.7f);
      mGfxManager->drawCircle(x, y, 5.0f);
    }
  }

  void CWinapiRoot::glPrintText(const std::string& text, unsigned short x, unsigned short y)
  {
    char line[256]; // We'll print lines of up to 256 chars.
    sprintf_s(line, "%s", text.c_str()); // Obtaining the line.
    line[255] = '\0'; // be on the safe side

    //TODO: Translate the window coords into GL-coords.

    //glColor3f(1.0f, 1.0f,1.0f); // White color for whole the printing text.

    glPushMatrix();
      glLoadIdentity();
      glRasterPos2f((GLfloat)x, (GLfloat)y);
      glPushAttrib(GL_LIST_BIT); // Push the list bit. Preventing glListBase from affecting "wrong" display lists.
      glListBase(mFontListsBase + 2); // I don't understand why, but char codes seems to be moved forward by 2, i'm doing the same.
      glCallLists(strlen(line), GL_UNSIGNED_BYTE, line); // Draw the display lists.
      glPopAttrib();
    glPopMatrix();
  }

  unsigned short CWinapiRoot::getWindowWidth() const
  {
    return mWindowWidth;
  }

  unsigned short CWinapiRoot::getWindowHeight() const
  {
    return mWindowHeight;
  }

  CWinapiRoot* CWinapiRoot::smInstance = NULL;
  HINSTANCE CWinapiRoot::smAppInstance = NULL;
  const char* CWinapiRoot::smClassName = "Kruzhochki-Window-Class";

} // namespace kruz
