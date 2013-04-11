#ifndef KRUZHOCHKI_IEVENTMANAGER_H
#define KRUZHOCHKI_IEVENTMANAGER_H

#include "IEventHandler.h"

namespace kruz {

  class IEventManager
  {
  public:
    virtual ~IEventManager()
    {
    }

    virtual void addEventHandler(IEventHandler* handler) = 0;
    virtual void removeEventHandler(IEventHandler* handler) = 0;
    virtual void removeAllEventHandlers() = 0;
  };

} // namespace kruz

#endif // KRUZHOCHKI_IEVENTMANAGER_H
