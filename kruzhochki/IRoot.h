#ifndef KRUZHOCHKI_IROOT_H
#define KRUZHOCHKI_IROOT_H

#include "IGameStateManager.h"
#include "IEventManager.h"
#include "IGfxManager.h"

namespace kruz
{

  class IRoot
  {
  public:
    virtual ~IRoot()
    {
    }

    virtual IGameStateManager* getStateManager() const = 0;
    virtual IEventManager* getEventManager() const = 0;
    virtual IGfxManager* getGfxManager() const = 0;

    virtual int run() = 0;
    virtual void terminate(int errorCode) = 0;
  };

} // namespace kruz

#endif // KRUZHOCHKI_IROOT_H
