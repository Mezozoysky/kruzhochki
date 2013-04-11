#include "CGameStateManager.h"

namespace kruz
{

  CGameStateManager::CGameStateManager()
  {
  }


  CGameStateManager::~CGameStateManager()
  {
    if (!mStack.empty())
    {
      mStack.top()->deactivate();
      while (!mStack.empty())
      {
        mStack.pop();
      }
    }
    if (!mStates.empty())
    {
      mStates.clear();
    }
  }

  std::string CGameStateManager::getStartState () const
  {
    return mStartState;
  }

  void CGameStateManager::setStartState(const std::string& stateName)
  {
    mStartState = stateName;
  }

  void CGameStateManager::update()
  {
    if (!mStack.empty())
    {
      mStack.top()->update();
    }
  }

  void CGameStateManager::render()
  {
    if (!mStack.empty())
    {
      mStack.top()->render();
    }
  }

  void CGameStateManager::registerState(IGameState* state)
  {
    //TODO:: Force unique states registering or use <set>
    mStates[state->getName()] = state;
  }

  void CGameStateManager::changeState(const std::string& stateName)
  {
    if (!mStack.empty())
    {
      mStack.top()->deactivate();
      mStack.pop();
    }

    mStack.push(mStates.at(stateName));
    mStack.top()->activate();
  }

  void CGameStateManager::pushState(const std::string& stateName)
  {
    if (!mStack.empty())
    {
      mStack.top()->pause();
    }

    mStack.push(mStates.at(stateName));
    mStack.top()->activate();
  }

  void CGameStateManager::popState()
  {
    if (!mStack.empty())
    {
      mStack.top()->deactivate();
    }

    if (!mStack.empty())
    {
      mStack.top()->resume();
    }
  }

} // namespace kruz
