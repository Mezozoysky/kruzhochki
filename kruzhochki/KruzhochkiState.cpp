#include "KruzhochkiState.h"
#include <iostream>

using namespace kruz;
using namespace std;

KruzhochkiState::KruzhochkiState(const string& name, IRoot* root) :
  mName(name),
  mRoot(root)
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
  //TODO: Write/draw something
}

void KruzhochkiState::deactivate()
{
  mRoot->getEventManager()->removeEventHandler(this);
}

void KruzhochkiState::pause()
{
}

void KruzhochkiState::resume()
{
}

void KruzhochkiState::handleEvent(const Event& event)
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
      cout << mName << ": Left mouse button is pressed. Shooting the circle." << endl;
      //TODO: Shoot the circle!
    }
    if (event.mouseInput.input == MI_RIGHT_PRESSED)
    {
      cout << mName << ": Right mouse button pressed. Switching to the main menu." << endl;
      //mRoot->getStateManager()->pushState("main-menu");
      mRoot->terminate(0);
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