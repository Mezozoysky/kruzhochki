#ifndef KRUZHOCHKI_CWINAPIEVENTMANAGER_H
#define KRUZHOCHKI_CWINAPIEVENTMANAGER_H

#include "Kruzhochki.h"
#include <windows.h>
#include <list>

namespace kruz
{
  /// Winapi implementation of event manager interface.
  class CWinapiEventManager :
    public IEventManager
  {
  public:
    CWinapiEventManager();
    virtual ~CWinapiEventManager();

    /// Add the new handler to the list.
    void addEventHandler(IEventHandler* handler);
    /// Remove the specified handler from the list.
    void removeEventHandler(IEventHandler* handler);
    /// Clear the handlers' list.
    void removeAllEventHandlers();

  private:
    /// Passes event to all the eventHandlers.
    void raiseEvent(const Event& event);

    friend class CWinapiRoot; //For calling processWinapiEvent() from CWinapiRoot.run() (main loop)
    /// Called from main loop. Converts WinAPI event into Kruzhochki event and passes it to each linked eventHandler.
    void processWinapiEvent(UINT msg, WPARAM wParam, LPARAM lParam);

  private:
    std::list<IEventHandler*>* mEventHandlers; ///< Actual list of registered handlers.
  };

} // namespace kruz

#endif // KRUZHOCHKI_CWINAPIEVENTMANAGER_H
