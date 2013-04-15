#ifndef KRUZHOCHKI_CGAMESTATEMANAGER_H
#define KRUZHOCHKI_CGAMESTATEMANAGER_H

#include "Kruzhochki.h"
#include <string>
#include <map>
#include <stack>

namespace kruz
{
  /// Cross-platform game state manager implementation.
  class CGameStateManager :
    public IGameStateManager
  {
  public:
    CGameStateManager();
    virtual ~CGameStateManager();

    inline std::string getStartState() const;
    inline void setStartState(const std::string& stateName);

    void update();
    void render();

    void registerState(IGameState* state);

    void changeState(const std::string& stateName);
    void pushState(const std::string& stateName);
    void popState();

    void clearStates();

  private:
    std::string mStartState; ///< The starting state name.
    std::map<std::string, IGameState*> mStates; ///< Map of all registered states.
    std::stack<IGameState*> mStack; ///< Actual stack.
  };

} // namespace kruz

#endif KRUZHOCHKI_CGAMESTATEMANAGER_H
