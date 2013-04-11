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

    virtual std::string getStartState() const = 0;
    virtual void setStartState(const std::string& stateName) = 0;

    virtual void update() = 0;
    virtual void render() = 0;

    virtual void registerState(IGameState* state) = 0;

    virtual void changeState(const std::string& stateName) = 0;
    virtual void pushState(const std::string& stateName) = 0;
    virtual void popState() = 0;
  };

} // namespace kruz

#endif // KRUZHOCHKI_IGAMESTATEMANAGER_H
