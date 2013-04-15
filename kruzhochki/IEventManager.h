#ifndef KRUZHOCHKI_IEVENTMANAGER_H
#define KRUZHOCHKI_IEVENTMANAGER_H

#include "IEventHandler.h"

namespace kruz {
  /// Event manager interface.
  /// Event manager contains a list of event handlers and and sends the event to them then events occurs.
  class IEventManager
  {
  public:
    virtual ~IEventManager()
    {
    }

    /// Add the handler.
    virtual void addEventHandler(IEventHandler* handler) = 0;
    /// Remove the handler.
    virtual void removeEventHandler(IEventHandler* handler) = 0;
    /// Clear the handlers.
    virtual void removeAllEventHandlers() = 0;
  };

} // namespace kruz

#endif // KRUZHOCHKI_IEVENTMANAGER_H
