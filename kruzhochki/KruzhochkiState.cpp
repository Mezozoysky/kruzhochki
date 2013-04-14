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
  mLastKCreatedTime(0)
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
  mRoot->getEventManager()->addEventHandler(this); // Setting ourself as an event handler.
  mLastKCreatedTime = mLastUpdatedTime = GetTickCount(); // Adjusting the timers after pause or after start.
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
  DWORD currentTime = GetTickCount();

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

  if ((mScene.size() < 30) && (GetTickCount() > mLastKCreatedTime + smKCreateDelayTime))
  {
    float x = rand() % (int)(mRoot->getWindowWidth() - 2 * Kruzhochek::MAX_RADIUS) + Kruzhochek::MAX_RADIUS;
    float y;
    float r = rand() % (int)(Kruzhochek::MAX_RADIUS - 2 * Kruzhochek::MIN_RADIUS) + Kruzhochek::MIN_RADIUS;
    float red = (rand() % 5 + 6) / 10.0f;
    float green = (rand() % 5 + 6) / 10.0f;
    float blue = (rand() % 5 + 6) / 10.0f;
    //TODO: Use randomizer to create values.
    //TODO: Normilize values.
    y = -r; // Just on the top border of the window.
    if (x - r < 0)
    {
      x = r; // Fit it in the window.
    }
    else if (x + r > mRoot->getWindowWidth() -1)
    {
      x = mRoot->getWindowWidth() - r - 1; // Fit position in the window.
    }

    Kruzhochek* k = new Kruzhochek(x, y, r, red, green, blue);
    mScene.push_back(k);
    mLastKCreatedTime = GetTickCount();
  }

  mLastUpdatedTime = currentTime;
  mWholeUpdateTime = GetTickCount() - currentTime; // Debug value;
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
  gfx->setColor(1.0f, 1.0f, 1.0f, 0.5f);
  gfx->drawText("COUNTER", 10, 600 - 24 - 10);

  // Debug: Showing the time we spending to update the scene.
  ostringstream ossTemp;
  ossTemp << mWholeUpdateTime;
  gfx->drawText(ossTemp.str(), 350, 600 - 24 - 10);
}

const DWORD KruzhochkiState::smKCreateDelayTime = 800; // msec.
