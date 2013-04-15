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
  // Subsribe for events incoming with with event manager.
  mRoot->getEventManager()->addEventHandler(this);
  kruzDebug(mName << ": Activated.");
}

void IntroState::deactivate()
{
  // Unsubscribe from events.
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
  if (event.type == ET_SYSTEM_EVENT) // System event
  {
    if (event.systemEvent.event == SE_WINDOW_CLOSE) // Window close event
    {
      kruzDebug( mName << ": 'Window close' system event received. terminating.");
      // Terminate the main loop.
      mRoot->terminate(0);
      return;
    }
  }
  else if (event.type == ET_MOUSE_INPUT) // Mouse input event
  {
    if (event.mouseInput.input == MI_LEFT_PRESSED) // Left button
    {
      kruzDebug(mName << ": Left mouse button is pressed. Starting the game.");
      // Start the game.
      mRoot->getStateManager()->changeState("kruzhochki");
    }
    if (event.mouseInput.input == MI_RIGHT_PRESSED) // Right button
    {
      kruzDebug(mName << ": Right button pressed. Exit.");
      // Terminate the main loop.
      mRoot->terminate(0);
      return;
    }
  }
}

void IntroState::update()
{
  //Do nothing
}

void IntroState::render()
{
  // Obtain the graphics manager from the root object.
  IGfxManager* gfx = mRoot->getGfxManager();

  // Draw title.
  gfx->setColor(0.5f, 1.0f, 0.25f);
  gfx->drawText("KUZHOCHKI, the game.", 100, 24 * 5);
  gfx->setColor(0.8f, 0.8f, 0.8f);
  gfx->drawText("Test job for Social Quantum.", 100, 24 * 6);
  
  // Draw start menu options
  gfx->setColor(1.0f, 1.0f, 1.0f);
  gfx->drawText("START: Left Mouse Button", 100, 24 * 10);
  gfx->drawText("EXIT: Right Mouse Button", 100, 24 * 11);

  // Draw game controls.
  gfx->setColor(0.8f, 0.8f, 0.8f);
  gfx->drawText("Game controls:", 100, 24 * 15);
  gfx->drawText("SHOOT: Left Mouse Button", 140, 24 * 16);
  gfx->drawText("PAUSE/MAIN MENU: Right Mouse Button", 140, 24 * 17);
}
