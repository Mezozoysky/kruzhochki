#ifndef KRUZHOCHKI_KRUZHOCHKISTATE_H
#define KRUZHOCHKI_KRUZHOCHKISTATE_H

#include "Kruzhochki.h"
#include <string>

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
  string mName;
  IRoot* mRoot;
  bool mIsPaused;
};

#endif // KRUZHOCHKI_KRUZHOCHKISTATE_H
