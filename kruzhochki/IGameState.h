#ifndef KRUZHOCHKI_IGAMESTATE_H
#define KRUZHOCHKI_IGAMESTATE_H

#include "IEventHandler.h"
#include <string>

namespace kruz
{

  //TODO: Make the states attacheble to the root and delete it when the root deleting.

  /// IGameState "interface".
  ///
  /// Common interface for the game states, such as intro, outro, actual game, main menu or something.
  class IGameState : public IEventHandler
  {
  public:
    virtual ~IGameState()
    {
    }

    virtual std::string getName() const = 0;

    virtual void activate() = 0;
    virtual void deactivate() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handleEvent(const Event& event) = 0;
    virtual void update() = 0;
    virtual void render() = 0;
  };

} // namespace kruz

#endif // KRUZHOCHKI_IGAMESTATE_H
