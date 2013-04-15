#include "KruzhochkiState.h"
#include "Kruzhochek.h"
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace kruz;
using namespace std;

KruzhochkiState::KruzhochkiState(IRoot* root, const string& name) :
  mRoot(root),
  mName(name),
  mIsPaused(false),
  mLastKCreatedTime(0),
  mPoints(0)
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
  kruzDebug(mName << ": Activated.");
  resume();
}

void KruzhochkiState::deactivate()
{
  // Unsubscribe from events.
  mRoot->getEventManager()->removeEventHandler(this);
  kruzDebug(mName << ": Deactivated.");
}

void KruzhochkiState::pause()
{
  // Set pause flag.
  mIsPaused = true;
  // Unsubscribe from events.
  mRoot->getEventManager()->removeEventHandler(this);
  kruzDebug(mName << ": Paused.");
}

void KruzhochkiState::resume()
{
  // Unset the pause flag.
  mIsPaused = false; 
  // Setting ourself as an event handler.
  mRoot->getEventManager()->addEventHandler(this);
  // Adjusting the timers after pause or after start.
  mLastKCreatedTime = mLastUpdatedTime = GetTickCount();
  kruzDebug(mName << ": Resumed.");
}

void KruzhochkiState::handleEvent(const Event& event)
{
  if (event.type == ET_SYSTEM_EVENT) // System event.
  {
    if (event.systemEvent.event == SE_WINDOW_CLOSE) // Window is closing.
    {
      kruzDebug(mName << ": 'Window close' system event received. terminating.");
      // Terminate the main loop.
      mRoot->terminate(0);
      return;
    }
  }
  else if (event.type == ET_MOUSE_INPUT) // Mouse input event.
  {
    if (event.mouseInput.input == MI_LEFT_PRESSED) // Left button
    {
      kruzDebug(mName << ": Left mouse button is pressed. Shooting the circle.");
      // Shoot!
      shoot(event.mouseInput.x, event.mouseInput.y);
    }
    if (event.mouseInput.input == MI_RIGHT_PRESSED) // Right button.
    {
      kruzDebug(mName << ": Right mouse button pressed. Switching to the main menu.");
      // Pause the game and go to the main menu.
      mRoot->getStateManager()->pushState("main-menu");
    }
  }
}

void KruzhochkiState::update()
{
  DWORD currentTime = GetTickCount();

  // Iterate throuch scene list in order to find and delete fallen circles or move those that are still alive.
  auto it = mScene.begin();
  while (it != mScene.end())
  {
    Kruzhochek* k = (*it);
    // Delete kruzhochek if it is falling out of the window.
    if (k->getY() - k->getR() > mRoot->getWindowHeight())
    {
      it = mScene.erase(it);
      delete k;
    }
    else // Update kruzhochek's position if it still in game.
    {
      k->fall(currentTime - mLastUpdatedTime); // Recalculate the Y-position of kruzhochek.
      ++it;
    }
  }

  // Create the new kruzhochek if where is a less than 30 kruzhocheks on the scene
  // and creation timeout is out.
  if ((mScene.size() < 30) && (GetTickCount() > mLastKCreatedTime + smKCreateDelayTime))
  {
    float r = rand() % (int)(Kruzhochek::MAX_RADIUS - 2 * Kruzhochek::MIN_RADIUS) + Kruzhochek::MIN_RADIUS;
    float x = rand() % (int)(mRoot->getWindowWidth() - 2 * Kruzhochek::MAX_RADIUS) + Kruzhochek::MAX_RADIUS;
    float y = -r; // Just on the top border of the window.    
    float red = (rand() % 5 + 6) / 10.0f; // 0.6f - 1.0f
    float green = (rand() % 5 + 6) / 10.0f; // 0.6f - 1.0f
    float blue = (rand() % 5 + 6) / 10.0f; // 0.6f - 1.0f

    /* Excrescen test
    if (x - r < 0)
    {
      x = r; // Fit it in the window.
    }
    else if (x + r > mRoot->getWindowWidth() -1)
    {
      x = mRoot->getWindowWidth() - r - 1; // Fit position in the window.
    }
    */

    // Create and put the new Kruzhochek onto the scene.
    Kruzhochek* k = new Kruzhochek(x, y, r, red, green, blue);
    mScene.push_back(k);
    // Update the time of last Kruzhochek creation.
    mLastKCreatedTime = GetTickCount();
  }

  mLastUpdatedTime = currentTime; // Update the time of last update.
}

void KruzhochkiState::render()
{
  IGfxManager* gfx = mRoot->getGfxManager();

  // Drawin the scene: kruzhochki!
  for (auto it = mScene.begin(); it != mScene.end(); ++it)
  {
    (*it)->draw(gfx);
  }

  // Drawing the player points counter.
  ostringstream ossTemp;
  ossTemp << mPoints;
  gfx->setColor(1.0f, 1.0f, 1.0f, 0.5f);
  gfx->drawText(ossTemp.str(), 10, 600 - 24 - 10);

}

void KruzhochkiState::shoot(unsigned short x, unsigned short y)
{
  // Find the circle which contains the point we've bang on.
  auto it = mScene.begin();
  while (it != mScene.end())
  {
    Kruzhochek* k = (*it);
    if (k->contains(x, y))
    {
      // We shot it!
      kruzDebug("Hit! " << k->getPoints() << "points achieved!");
      // Collecting the points.
      mPoints += k->getPoints();
      // Release and destroy the corpse.
      it = mScene.erase(it);
      delete k;
      break;
    }
    else
    {
      kruzDebug("Miss!");
      ++it;
    }
  }
}

const DWORD KruzhochkiState::smKCreateDelayTime = 500; // msec.
