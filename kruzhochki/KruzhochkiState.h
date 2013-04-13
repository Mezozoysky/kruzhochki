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
  KruzhochkiState(const string& name, IRoot* root);
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
};

#endif // KRUZHOCHKI_KRUZHOCHKISTATE_H
