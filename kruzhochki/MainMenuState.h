#ifndef KRUZHOCHKI_MAINMENUSTATE_H
#define KRUZHOCHKI_MAINMENUSTATE_H

#include "Kruzhochki.h"
#include <string>

using namespace kruz;
using namespace std;

class MainMenuState :
  public IGameState
{
public:
  MainMenuState(IRoot* root, const string& name);
  ~MainMenuState();

  string getName() const;

  void activate();
  void deactivate();

  void pause();
  void resume();

  void handleEvent(const Event& event);
  void update();
  void render();

private:
  IRoot* mRoot;
  string mName;
};

#endif // KRUZHOCHKI_MAINMENUSTATE_H
