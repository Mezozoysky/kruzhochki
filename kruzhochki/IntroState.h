#ifndef KRUZHOCHKI_INTROSTATE_H
#define KRUZHOCHKI_INTROSTATE_H

#include "Kruzhochki.h"
#include <string>

using namespace std;
using namespace kruz;

class IntroState :
  public IGameState
{
public:
  IntroState(IRoot* root, const string& name);
  ~IntroState();

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

#endif // KRUZHOCHKI_INTROSTATE_H
