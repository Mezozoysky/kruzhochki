#ifndef KRUZHOCHKI_CWINAPIROOT_H
#define KRUZHOCHKI_CWINAPIROOT_H

#include "Kruzhochki.h"
#include <Windows.h>

namespace kruz
{
  /// CWindowRoot error codes
  enum
  {
    EC_NO_ERROR,
    EC_FULLSCREEN_FAILED,
    EC_CREATE_WINDOW_FAILED,
    EC_CREATE_CONTEXT_FAILED,
    EC_CHOOSE_PIXELFORMAT_FAILED,
    EC_SET_PIXELFORMAT_FAILED,
    EC_CREATE_GLCONTEXT_FAILED,
    EC_MAKE_GLCONTEXT_CURRENT_FAILED
  };

  /// WinAPI implementation of the IRoot `interface`.
  class CWinapiRoot : //TODO: Make it a singleton
    public IRoot
  {
  public:
    /// Event if all the arguments are specified, they make sence only on the first call.
    /// During subsequent calls all arguments will be ignored.
    static CWinapiRoot* createOnce(
      HINSTANCE appInstance,
      bool fullscreen = false,
      unsigned short width = 800,
      unsigned short height = 600
    );

    //We make a singleton, so where is a private section for constructors and assignment operator
  private:
    CWinapiRoot(
      HINSTANCE appInstance,
      bool fullscreen,
      unsigned short width,
      unsigned short height
    ); // Private constructor
    CWinapiRoot(const CWinapiRoot& sopySrc); // Private copy constructor
    CWinapiRoot& operator=(const CWinapiRoot& src); // Private assignment

  public:
    virtual ~CWinapiRoot();

    IGameStateManager* getStateManager() const;
    IEventManager* getEventManager() const;
    IGfxManager* getGfxManager() const;

    /// Main loop of the application
    int run();
    /// By calling terminate() root application will stop after the current loop iteration.
    inline void terminate(int errorCode = 0);

    /// Print the line of up to 256 chars over OpenGL window.
    void glPrintText(const std::string& text, unsigned short x, unsigned short y);

    /// Get the actual window width.
    inline unsigned short getWindowWidth() const;
    /// Get the actual window height.
    inline unsigned short getWindowHeight() const;


  private:
    /// Creates the main and only window
    void createWindow();
    /// Window procedure; Calling when a message for this window is dispatched.
    static LRESULT CALLBACK wndProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);
    /// Calling by wndProc() in order to recalculate window parameters according to the new size.
    void handleSizeEvent(GLsizei width, GLsizei height);
    /// Calling by createWindow() after creating the actual window in order to initialize OpenGL and build the font for it.
    void initOpenGL();
    /// Draw the custom mouse cursor.
    void glDrawCursor();

  private:
    static CWinapiRoot* smInstance;
    static HINSTANCE smAppInstance;
    static const char* smClassName;

    bool mIsRunning;
    int mErrorCode;
    IGameStateManager* mStateManager;
    IEventManager* mEventManager;
    IGfxManager* mGfxManager;

    unsigned short mWindowWidth;
    unsigned short mWindowHeight;
    bool mFullscreen;
    HWND mWindow;
    HDC mDeviceContext;
    HGLRC mGLContext;

    bool fullscreen;

    GLuint mFontListsBase; ///< Nubfer of the first display list of sequence of lists used for drawing text.
  };

} // namespace kruz

#endif // KRUZHOCHKI_CWINAPIROOT_H
