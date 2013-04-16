#include "CWinapiEventManager.h"
#include "Event.h"
//#include <algorithm>

namespace kruz
{

  CWinapiEventManager::CWinapiEventManager() :
    mEventHandlers(NULL)
  {
    mEventHandlers = new std::list<IEventHandler*>();
  }


  CWinapiEventManager::~CWinapiEventManager()
  {
    removeAllEventHandlers();
    delete mEventHandlers;
  }

  void CWinapiEventManager::addEventHandler(IEventHandler* handler)
  {
    if (handler && mEventHandlers)
    {
      mEventHandlers->push_back(handler);
    }
  }

  void CWinapiEventManager::removeEventHandler(IEventHandler* handler)
  {
    if (handler && mEventHandlers)
    {
      auto it = mEventHandlers->begin();
      while (it != mEventHandlers->end())
      {
        if ((*it) == handler)
        {
          break;
        }
        ++it;
      }
      mEventHandlers->erase(it);
    }
  }

  void CWinapiEventManager::removeAllEventHandlers()
  {
    if (mEventHandlers && !mEventHandlers->empty())
    {
      mEventHandlers->clear();
    }
  }
  
  void CWinapiEventManager::raiseEvent(const Event& event)
  {
    kruzDebug("Raising the event!");

    // Temporary copy of handlers list stored here to prevent the iterator corruption
    // in case of actual list will be changed by handleEvent handler's method.
    std::list<IEventHandler*> tmp((*mEventHandlers));
    
    // Iterating through temporary copy of actual list.
    for (auto it = tmp.begin(); it != tmp.end(); ++it)
    {
      // Passing the event to handler.
      (*it)->handleEvent(event);
    }
  }

  // 
  void CWinapiEventManager::processWinapiEvent(UINT msg, WPARAM wParam, LPARAM lParam)
  {
    Event event;
    switch (msg)
    {
    case WM_CLOSE:
      //Raising the kruz::Event corresponding to native WM_CLOSE event
      event.type = ET_SYSTEM_EVENT;
      SystemEvent se;
      se.event = SE_WINDOW_CLOSE;
      event.systemEvent = se;
      raiseEvent(event);
      break;
    case WM_LBUTTONDOWN:
      {
        event.type = ET_MOUSE_INPUT;
        MouseInput mi;
        mi.input = MI_LEFT_PRESSED;
        mi.x = LOWORD(lParam);
        mi.y = HIWORD(lParam);
        event.mouseInput = mi;
        raiseEvent(event);
      }
      break;
    case WM_RBUTTONDOWN:
      {
        event.type = ET_MOUSE_INPUT;
        MouseInput mi;
        mi.input = MI_RIGHT_PRESSED;
        mi.x = LOWORD(lParam);
        mi.y = HIWORD(lParam);
        event.mouseInput = mi;
        raiseEvent(event);
      }
      break;
    default:
      break;
    }
  }

} // namesapce kruz
