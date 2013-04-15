#ifndef KRUZHOCHKI_INTROSTATE_H
#define KRUZHOCHKI_INTROSTATE_H

#include "Kruzhochki.h"
#include <string>

using namespace std;
using namespace kruz;

/// Game state with starting menu. Player will see it first then starting the game.
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
  string mName; ///< State's name.
  IRoot* mRoot; ///< Pointer to the root object.
};

#endif // KRUZHOCHKI_INTROSTATE_H
