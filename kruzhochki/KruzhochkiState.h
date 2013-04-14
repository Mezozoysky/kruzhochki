#ifndef KRUZHOCHKI_KRUZHOCHKISTATE_H
#define KRUZHOCHKI_KRUZHOCHKISTATE_H

#include "Kruzhochki.h"
#include "Kruzhochek.h"
#include <string>
#include <list>

using namespace kruz;
using namespace std;

class KruzhochkiState :
  public IGameState
{
public:
  KruzhochkiState(IRoot* root, const string& name);
  ~KruzhochkiState();

  string getName() const;

  void activate();
  void deactivate();

  void pause();
  void resume();

  void handleEvent(const Event& event);
  void update();
  void render();

private:
  void shoot(unsigned short x, unsigned short y);

private:
  static const DWORD smKCreateDelayTime; ///< Time delay between the new kuzhocheks creations.

private:
  string mName;
  IRoot* mRoot;
  bool mIsPaused;
  std::list<Kruzhochek*> mScene; ///< Scene, the list of live kruzhocheks.
  unsigned long mPoints;
  
  DWORD mLastKCreatedTime; ///< The time of lats kruzhochek creation (msec).
  DWORD mLastUpdatedTime; ///< The time of last scene update.
};

#endif // KRUZHOCHKI_KRUZHOCHKISTATE_H
