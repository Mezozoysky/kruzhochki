#ifndef KRUZHOCHKI_IGAMESTATEMANAGER_H
#define KRUZHOCHKI_IGAMESTATEMANAGER_H

#include <string>
#include "IGameState.h"

namespace kruz
{

  class IGameStateManager
  {
  public:
    virtual ~IGameStateManager()
    {
    }

    /// Return the name of the starting state.
    virtual std::string getStartState() const = 0;
    /// Set the starting state name.
    virtual void setStartState(const std::string& stateName) = 0;

    /// Updade the current state before render it.
    virtual void update() = 0;
    /// Render the current state.
    virtual void render() = 0;

    /// Register the new state with the manager.
    virtual void registerState(IGameState* state) = 0;

    /// Replace the current state with the another registered one specified by name.
    virtual void changeState(const std::string& stateName) = 0;
    /// Pause the current state, make another registered one the current and activate it.
    virtual void pushState(const std::string& stateName) = 0;
    /// Deactivate the current state, make previous the current and resume it.
    virtual void popState() = 0;

    //Deactivate and remove all the states.
    virtual void clearStates() = 0;
  };

} // namespace kruz

#endif // KRUZHOCHKI_IGAMESTATEMANAGER_H
