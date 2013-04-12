#include "CWinapiEventManager.h"
#include "Event.h"
//#include <algorithm>

namespace kruz
{

  CWinapiEventManager::CWinapiEventManager() :
    mEventHandlers(NULL)
  {
    mEventHandlers = new std::set<IEventHandler*>();
  }


  CWinapiEventManager::~CWinapiEventManager()
  {
    removeAllEventHandlers();
    if (mEventHandlers)
    {
      delete mEventHandlers;
    }
  }

  void CWinapiEventManager::addEventHandler(IEventHandler* handler)
  {
    if (handler && mEventHandlers)
    {
      mEventHandlers->insert(handler);
    }
  }

  void CWinapiEventManager::removeEventHandler(IEventHandler* handler)
  {
    if (handler && mEventHandlers)
    {
      mEventHandlers->erase(handler);
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
    for (std::set<IEventHandler*>::iterator it = mEventHandlers->begin(); it != mEventHandlers->end(); ++it)
    {
      (*it)->handleEvent(event);
    }
  }

  void CWinapiEventManager::processWinapiEvent(UINT msg, WPARAM wParam, LPARAM lParam)
  {
    Event event;
    switch (msg)
    {
    case WM_CLOSE:
      //Raising the kruz::Event corresponding to native WM_CLOSE event
      event.type = ET_SYSTEM_EVENT;
      SystemEvent se;
      se.event = SYSTEM_EVENT::SE_WINDOW_CLOSE;
      event.systemEvent = se;
      raiseEvent(event);
      break;
    case WM_LBUTTONDOWN:
      event.type = ET_MOUSE_INPUT;
      MouseInput mi;
      mi.input = MOUSE_INPUT::MI_LEFT_PRESSED;
      mi.x = 0;
      mi.y = 0;
      event.mouseInput = mi;
      raiseEvent(event);
      break;
    case WM_RBUTTONDOWN:
      event.type = ET_MOUSE_INPUT;
      MouseInput mi;
      mi.input = MOUSE_INPUT::MI_RIGHT_PRESSED;
      mi.x = 0;
      mi.y = 0;
      event.mouseInput = mi;
      raiseEvent(event);
      break;
    default:
      break;
    }
  }

} // namesapce kruz
