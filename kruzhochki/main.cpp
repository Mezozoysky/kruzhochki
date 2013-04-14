#include <Windows.h>

#include "Kruzhochki.h"
#include "CWinapiRoot.h"
#include "CGameStateManager.h"
#include "CWinapiEventManager.h"
#include "COpenglGfxManager.h"
#include "IntroState.h"
#include "KruzhochkiState.h"
#include "MainMenuState.h"
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

  IRoot* root = CWinapiRoot::createOnce(
    hInstance
  );

  IGameState* introState = new IntroState(root, "intro");
  root->getStateManager()->registerState(introState);
  root->getStateManager()->setStartState(introState->getName());

  IGameState* kruzhochkiState = new KruzhochkiState(root, "kruzhochki");
  root->getStateManager()->registerState(kruzhochkiState);

  IGameState* mainMenuState = new MainMenuState(root, "main-menu");
  root->getStateManager()->registerState(mainMenuState);


  int errorCode = root->run();

  delete kruzhochkiState;
  delete introState;

  delete root;

#ifdef KRUZ_DEBUG
  cout.rdbuf(oldCoutBuf);
  coutFile.close();
#endif // KRUZ_DEBUG

	return 0;
}
