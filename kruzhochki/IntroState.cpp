#include "IntroState.h"
#include <iostream>

using namespace std;
using namespace kruz;

IntroState::IntroState(IRoot* root, const string& name) :
  mName(name),
  mRoot(root)
{
}


IntroState::~IntroState()
{
}

string IntroState::getName() const
{
  return mName;
}

void IntroState::activate()
{
  mRoot->getEventManager()->addEventHandler(this);
  kruzDebug(mName << ": Activated.");
}

void IntroState::deactivate()
{
  mRoot->getEventManager()->removeEventHandler(this);
  kruzDebug(mName << ": Deactivated.");
}

void IntroState::pause()
{
  kruzDebug(mName << ": Paused.");
}

void IntroState::resume()
{
  kruzDebug(mName << ": Resumed.");
}

void IntroState::handleEvent(const Event& event)
{
  if (event.type == ET_SYSTEM_EVENT)
  {
    if (event.systemEvent.event == SE_WINDOW_CLOSE)
    {
      kruzDebug( mName << ": 'Window close' system event received. terminating.");
      mRoot->terminate(0);
      return;
    }
  }
  else if (event.type == ET_MOUSE_INPUT)
  {
    if (event.mouseInput.input == MI_LEFT_PRESSED)
    {
      kruzDebug(mName << ": Left mouse button is pressed. Starting the game.");
      mRoot->getStateManager()->changeState("kruzhochki");
    }
  }
}

void IntroState::update()
{
  //TODO: Create and/or move the circles
}

void IntroState::render()
{
  //TODO: Draw all we need with Gfx Manager
}
