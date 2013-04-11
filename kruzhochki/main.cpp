#include <Windows.h>
#include "Kruzhochki.h"
#include "CWinapiRoot.h"
#include "CGameStateManager.h"
#include "CWinapiEventManager.h"

using namespace kruz;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
  IGameState* introState = new IntroState("intro");
  IGameState* kruzhochkiState = new KruzhochkiState("kruzhochki");

  IGameStateManager* stateManager = new CGameStateManager();
  IEventManager* eventManager = new CWinapiEventManager();
  IGfxManager* gfxManager = new COpenglGfxManager();

  IRoot* root = new CWinapiRoot(
    800, //Window width
    600, //Window height
    true, //Fullscreen option
    stateManager,
    eventManager,
    gfxManager
  );

  int errorCode = root->run();
  delete root;
	return 0;
}
