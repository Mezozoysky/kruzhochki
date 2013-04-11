#ifndef KRUZHOCHKI_CWINAPIEVENTMANAGER_H
#define KRUZHOCHKI_CWINAPIEVENTMANAGER_H

#include "IEventManager.h"
#include <windows.h>
#include <set>

namespace kruz
{

  class CWinapiEventManager :
    public IEventManager
  {
  public:
    CWinapiEventManager();
    virtual ~CWinapiEventManager();

    // Add the new handler to the list.
    void addEventHandler(IEventHandler* handler);
    // Remove the specified handler from the list.
    void removeEventHandler(IEventHandler* handler);
    // Clear the handlers' list.
    void removeAllEventHandlers();

  private:
    friend class CWinapiRoot; //For calling processWinapiEvent() from CWinapiRoot.run() (main loop)
    // Converts WinAPI event into Kruzhochki event and passes it to each linked eventHandler.
    void processWinapiEvent(UINT msg, WPARAM wParam, LPARAM lParam);

  private:
    std::set<IEventHandler*>* mEventHandlers;
  };

} // namespace kruz

#endif // KRUZHOCHKI_CWINAPIEVENTMANAGER_H
