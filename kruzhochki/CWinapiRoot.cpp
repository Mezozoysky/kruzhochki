#include "CWinapiRoot.h"
#include "CWinapiEventManager.h"

namespace kruz
{

  CWinapiRoot::CWinapiRoot(
      unsigned short width,
      unsigned short height,
      bool fullscreen,
      IGameStateManager* stateManager,
      IEventManager* eventManager,
      IGfxManager* gfxManager
  ) :
    mIsRunning(true),
    mErrorCode(0),
    mWindowWidth(width),
    mWindowHeight(height),
    mFullscreen(fullscreen),
    mWindow(NULL),
    mDeviceContext(NULL),
    mGLContext(NULL),
    mStateManager(stateManager),
    mEventManager(eventManager),
    mGfxManager(gfxManager)
  {
  }


  CWinapiRoot::~CWinapiRoot()
  {
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
    mStateManager->changeState(mStateManager->getStartState());

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
      else
      {
        if (mStateManager) //TODO: Optimize! Excrescent test.
        {
          mStateManager->update();
          mStateManager->render();
        }
      }
    }

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
    wc.lpszClassName = "Kruzhochki-Window-Class";

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
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Color using to clear the color buffer.
    //TODO: Is it for textures only?
    //glEnable(GL_ALPHA_TEST); // Alpha test ON.
    //glAlphaFunc(GL_EQUAL, 0.0f); // Skip pixels which alpha is equal to 0.

    // Raising the window up
    ShowWindow(mWindow, SW_SHOW);

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

} // namespace kruz
