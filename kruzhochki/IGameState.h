#ifndef KRUZHOCHKI_IGAMESTATE_H
#define KRUZHOCHKI_IGAMESTATE_H

#include "IEventHandler.h"
#include <string>

namespace kruz
{

  //TODO: Make the states attacheble to the root and delete it when the root deleting.

  /// Game State interface.
  /// Common interface for the game states, such as intro, outro, actual game, main menu or something.
  class IGameState :
    public IEventHandler // Every game state wants to receive the events from from event manager.
  {
  public:
    virtual ~IGameState()
    {
    }
    /// Get the name.
    /// All the game state objects must have unique name.
    virtual std::string getName() const = 0;

    /// Activate the state.
    /// Called by state manager then the state became top via manager's changeState or pushState methods.
    virtual void activate() = 0;
    /// Deactivate the state
    /// Called by event manager then the state is poped.
    virtual void deactivate() = 0;

    /// Pause state.
    /// Called by event manager before pushing another game state after the given one.
    virtual void pause() = 0;
    /// Resume state.
    /// Called by event manager then the state became top after poping the previous top.
    virtual void resume() = 0;

    /// Handle the event.
    virtual void handleEvent(const Event& event) = 0;
    /// Update the state.
    virtual void update() = 0;
    /// Render the state.
    virtual void render() = 0;
  };

} // namespace kruz

#endif // KRUZHOCHKI_IGAMESTATE_H
