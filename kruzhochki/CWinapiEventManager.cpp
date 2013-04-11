#include "CWinapiEventManager.h"

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
  
  void CWinapiEventManager::processWinapiEvent(UINT msg, WPARAM wParam, LPARAM lParam)
  {
    switch (msg)
    {
    case WM_CLOSE:
      break;
    case WM_SIZE:
      break;
    case WM_LBUTTONDOWN:
      break;
    case WM_RBUTTONDOWN:
      break;
    default:
      break;
    }
  }

} // namesapce kruz
