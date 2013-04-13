#include "KruzhochkiState.h"
#include <iostream>

using namespace kruz;
using namespace std;

KruzhochkiState::KruzhochkiState(IRoot* root, const string& name) :
  mRoot(root),
  mName(name),
  mIsPaused(false)
{
}


KruzhochkiState::~KruzhochkiState(void)
{
}

string KruzhochkiState::getName() const
{
  return mName;
}

void KruzhochkiState::activate()
{
  mRoot->getEventManager()->addEventHandler(this);
  kruzDebug(mName << ": Activated.");
}

void KruzhochkiState::deactivate()
{
  mRoot->getEventManager()->removeEventHandler(this);
  kruzDebug(mName << ": Deactivated.");
}

void KruzhochkiState::pause()
{
  mIsPaused = true;
  mRoot->getEventManager()->removeEventHandler(this);
  kruzDebug(mName << ": Paused.");
}

void KruzhochkiState::resume()
{
  mIsPaused = false;
  mRoot->getEventManager()->addEventHandler(this);
  kruzDebug(mName << ": Resumed.");
}

void KruzhochkiState::handleEvent(const Event& event)
{
  if (event.type == ET_SYSTEM_EVENT)
  {
    if (event.systemEvent.event == SE_WINDOW_CLOSE)
    {
      kruzDebug(mName << ": 'Window close' system event received. terminating.");
      mRoot->terminate(0);
      return;
    }
  }
  else if (event.type == ET_MOUSE_INPUT)
  {
    if (event.mouseInput.input == MI_LEFT_PRESSED)
    {
      kruzDebug(mName << ": Left mouse button is pressed. Shooting the circle.");
      //TODO: Shoot the circle!
    }
    if (event.mouseInput.input == MI_RIGHT_PRESSED)
    {
      kruzDebug(mName << ": Right mouse button pressed. Switching to the main menu.");
      mRoot->getStateManager()->pushState("main-menu");
    }
  }
}

void KruzhochkiState::update()
{
  //TODO: Create and/or move the circles
}

void KruzhochkiState::render()
{
  //TODO: Draw all we need with Gfx Manager
}