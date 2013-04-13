#include <Windows.h>

#include "Kruzhochki.h"
#include "CWinapiRoot.h"
#include "CGameStateManager.h"
#include "CWinapiEventManager.h"
#include "COpenglGfxManager.h"
#include "IntroState.h"
#include "KruzhochkiState.h"
#include <iostream>
#include <fstream>


using namespace kruz;
using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
#ifdef KRUZ_DEBUG
  ofstream coutFile;
  coutFile.open("kruzhochki.cout");
  streambuf* oldCoutBuf = cout.rdbuf();
  cout.rdbuf(coutFile.rdbuf());
#endif // KRUZ_DEBUG

  IGameStateManager* stateManager = new CGameStateManager();
  IEventManager* eventManager = new CWinapiEventManager();
  IGfxManager* gfxManager = new COpenglGfxManager();

  IRoot* root = new CWinapiRoot(
    800, //Window width
    600, //Window height
    false, //Fullscreen option
    stateManager,
    eventManager,
    gfxManager
  );

  IGameState* introState = new IntroState("intro", root);
  root->getStateManager()->registerState(introState);
  root->getStateManager()->setStartState(introState->getName());
  IGameState* kruzhochkiState = new KruzhochkiState("kruzhochki", root);
  root->getStateManager()->registerState(kruzhochkiState);


  int errorCode = root->run();

  delete kruzhochkiState;
  delete introState;

  delete root;

  delete gfxManager;
  delete eventManager;
  delete stateManager;

#ifdef KRUZ_DEBUG
  cout.rdbuf(oldCoutBuf);
  coutFile.close();
#endif // KRUZ_DEBUG

	return 0;
}
