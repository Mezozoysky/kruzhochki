#include "MainMenuState.h"

using namespace kruz;
using namespace std;

MainMenuState::MainMenuState(IRoot* root, const string& name) :
  mRoot(root),
  mName(name)
{
}

MainMenuState::~MainMenuState(void)
{
}

string MainMenuState::getName() const
{
  return mName;
}

void MainMenuState::activate()
{
  mRoot->getEventManager()->addEventHandler(this);
  kruzDebug(mName << ": Activated.");
}

void MainMenuState::deactivate()
{
  mRoot->getEventManager()->removeEventHandler(this);
  kruzDebug(mName << ": Deactivated.");
}

void MainMenuState::pause()
{
  kruzDebug(mName << ": Paused.");
}

void MainMenuState::resume()
{
  kruzDebug(mName << ": Resumed.");
}

void MainMenuState::handleEvent(const Event& event)
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
      kruzDebug(mName << ": Left mouse button is pressed. Resume the game.");
      mRoot->getStateManager()->popState();
    }
    if (event.mouseInput.input == MI_RIGHT_PRESSED)
    {
      kruzDebug(mName << ": Right button is pressed. Exit the game.");
      mRoot->terminate(0);
    }
  }
}

void MainMenuState::update()
{
  //TODO: Create and/or move the circles
}

void MainMenuState::render()
{
  //TODO: Draw all we need with Gfx Manager
}
