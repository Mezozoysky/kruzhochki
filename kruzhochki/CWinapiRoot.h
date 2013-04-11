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
    CWinapiRoot(
      unsigned short width,
      unsigned short height,
      bool fullscreen,
      IGameStateManager* stateManager,
      IEventManager* eventManager,
      IGfxManager* gfxManager
    );
    virtual ~CWinapiRoot();

    IGameStateManager* getStateManager() const;
    IEventManager* getEventManager() const;
    IGfxManager* getGfxManager() const;

    /// Main loop of the application
    int run();
    /// By calling terminate() root application will stop after the current loop iteration.
    inline void terminate(int errorCode = 0);

  private:
    /// Creates the main and only window
    void createWindow();
    /// Window procedure; Calling when a message for this window is dispatched.
    static LRESULT CALLBACK wndProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);
    /// Calling by wndProc() in order to recalculate window parameters according to the new size.
    void handleSizeEvent(GLsizei width, GLsizei height);

  private:
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
  };

} // namespace kruz

#endif // KRUZHOCHKI_CWINAPIROOT_H
