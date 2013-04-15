#ifndef KRUZHOCHKI_IGAMESTATEMANAGER_H
#define KRUZHOCHKI_IGAMESTATEMANAGER_H

#include <string>
#include "IGameState.h"

namespace kruz
{
  /// Game state manager interface
  /// Manages registered game state using the stack manner.
  class IGameStateManager
  {
  public:
    virtual ~IGameStateManager()
    {
    }

    /// Return the name of the starting state.
    virtual std::string getStartState() const = 0;
    /// Set the starting state name. State with this name will be activated first.
    virtual void setStartState(const std::string& stateName) = 0;

    /// Updade the current state before render it.
    virtual void update() = 0;
    /// Render the current state.
    virtual void render() = 0;

    /// Register the new state with the manager.
    virtual void registerState(IGameState* state) = 0;

    /// Replace the top state with the another registered one specified by name.
    virtual void changeState(const std::string& stateName) = 0;
    /// Pause the top state, make another registered one the top and activate it.
    virtual void pushState(const std::string& stateName) = 0;
    /// Deactivate the top state, pop it, resume top state.
    virtual void popState() = 0;

    //Deactivate and unregister all the states.
    virtual void clearStates() = 0;
  };

} // namespace kruz

#endif // KRUZHOCHKI_IGAMESTATEMANAGER_H
