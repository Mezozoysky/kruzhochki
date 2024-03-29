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
  // Subscribe for events.
  mRoot->getEventManager()->addEventHandler(this);
  kruzDebug(mName << ": Activated.");
}

void MainMenuState::deactivate()
{
  // Unsubscribe from events.
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
  if (event.type == ET_SYSTEM_EVENT) // System event
  {
    if (event.systemEvent.event == SE_WINDOW_CLOSE) // Window is closing.
    {
      kruzDebug( mName << ": 'Window close' system event received. terminating.");
      // Terminate the main loop.
      mRoot->terminate(0);
      return;
    }
  }
  else if (event.type == ET_MOUSE_INPUT)
  {
    if (event.mouseInput.input == MI_LEFT_PRESSED) // Left button.
    {
      kruzDebug(mName << ": Left mouse button is pressed. Resume the game.");
      // Return to game.
      mRoot->getStateManager()->popState();
    }
    if (event.mouseInput.input == MI_RIGHT_PRESSED) // Right button.
    {
      kruzDebug(mName << ": Right button is pressed. Exit the game.");
      // Terminate the main loop.
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
  IGfxManager* gfx = mRoot->getGfxManager();

  gfx->setColor(1.0f, 1.0f, 1.0f);

  gfx->drawText("Main Menu.", 100, 24 * 5);

  gfx->drawText("RESUME GAME: Left Mouse Button", 140, 24 * 10);
  gfx->drawText("EXIT TO OS: Right Mouse Button", 140, 24 * 11);
}
