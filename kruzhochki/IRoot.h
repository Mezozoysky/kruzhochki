#ifndef KRUZHOCHKI_IROOT_H
#define KRUZHOCHKI_IROOT_H

#include "IGameStateManager.h"
#include "IEventManager.h"
#include "IGfxManager.h"

namespace kruz
{
  /// Root object interface.
  /// Root object is an application kernel. 
  class IRoot
  {
  public:
    virtual ~IRoot()
    {
    }

    /// Get the state manager pointer.
    virtual IGameStateManager* getStateManager() const = 0;
    /// Get the event manager pointer.
    virtual IEventManager* getEventManager() const = 0;
    /// Get the graphics manager pointer
    virtual IGfxManager* getGfxManager() const = 0;

    /// Get the main window width in pixels.
    virtual unsigned short getWindowWidth() const = 0;
    /// Get the main window height in pixels.
    virtual unsigned short getWindowHeight() const = 0;

    /// Creating window, doing some handy job and, finally, starting the main loop.
    virtual int run() = 0;
    /// Switching root object to terminate main loop. errorCode will be returned by run().
    virtual void terminate(int errorCode) = 0;

    /// This is where in order to avoid writing the special manager for text rendering. I'm sorry.
    virtual void glPrintText(const std::string& text, unsigned short x, unsigned short y) = 0;
  };

} // namespace kruz

#endif // KRUZHOCHKI_IROOT_H
