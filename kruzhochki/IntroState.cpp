#include "IntroState.h"
#include <iostream>

using namespace std;
using namespace kruz;

IntroState::IntroState(const string& name, IRoot* root) :
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
  //TODO: Write/draw something
}

void IntroState::deactivate()
{
  mRoot->getEventManager()->removeEventHandler(this);
}

void IntroState::pause()
{
}

void IntroState::resume()
{
}

void IntroState::handleEvent(const Event& event)
{
  if (event.type == ET_SYSTEM_EVENT)
  {
    if (event.systemEvent.event == SE_WINDOW_CLOSE)
    {
      cout << mName << ": 'Window close' system event received. terminating." << endl;
      mRoot->terminate(0);
      return;
    }
  }
  else if (event.type == ET_MOUSE_INPUT)
  {
    if (event.mouseInput.input == MI_LEFT_PRESSED)
    {
      cout << mName << ": Left mouse button is pressed. Starting the game." << endl;
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
