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
    if (event.mouseInput.input == MI_RIGHT_PRESSED)
    {
      kruzDebug(mName << ": Right button pressed. Exit.");
      mRoot->terminate(0);
      return;
    }
  }
}

void IntroState::update()
{
  //TODO: Create and/or move the circles
}

void IntroState::render()
{
  IGfxManager* gfx = mRoot->getGfxManager();

  gfx->setColor(0.5f, 1.0f, 0.25f);
  gfx->drawText("KUZHOCHKI, the game.", 100, 24 * 5);
  gfx->setColor(0.8f, 0.8f, 0.8f);
  gfx->drawText("Test job for Social Quantum.", 100, 24 * 6);
  
  gfx->setColor(1.0f, 1.0f, 1.0f);
  gfx->drawText("START: Left Mouse Button", 100, 24 * 10);
  gfx->drawText("EXIT: Right Mouse Button", 100, 24 * 11);

  gfx->setColor(0.8f, 0.8f, 0.8f);
  gfx->drawText("Game controls:", 100, 24 * 15);
  gfx->drawText("SHOOT: Left Mouse Button", 140, 24 * 16);
  gfx->drawText("PAUSE/MAIN MENU: Right Mouse Button", 140, 24 * 17);
}
