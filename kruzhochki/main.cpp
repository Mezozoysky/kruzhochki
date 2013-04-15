#include <Windows.h>

#include "Kruzhochki.h"
#include "CWinapiRoot.h"
#include "IntroState.h"
#include "KruzhochkiState.h"
#include "MainMenuState.h"
#include <iostream>
#include <fstream>


using namespace kruz;
using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
//Store all the standard output to the file if KRUZ_DEBUG is defined.
#ifdef KRUZ_DEBUG
  ofstream coutFile;
  coutFile.open("kruzhochki.cout");
  streambuf* oldCoutBuf = cout.rdbuf();
  cout.rdbuf(coutFile.rdbuf());
#endif // KRUZ_DEBUG

  // Create the root object using Winapi realisation.
  IRoot* root = CWinapiRoot::createOnce(
    hInstance
  );

  // Create and register the game states.
  IGameState* introState = new IntroState(root, "intro");
  root->getStateManager()->registerState(introState);
  root->getStateManager()->setStartState(introState->getName()); // introState will be starting state.

  IGameState* kruzhochkiState = new KruzhochkiState(root, "kruzhochki");
  root->getStateManager()->registerState(kruzhochkiState);

  IGameState* mainMenuState = new MainMenuState(root, "main-menu");
  root->getStateManager()->registerState(mainMenuState);

  // Start the Main Loop.
  int errorCode = root->run();

  // Main Loop is terminated, so...
  // ... delete the game states ...
  delete mainMenuState;
  delete kruzhochkiState;
  delete introState;
  // ... and delete the root object.
  delete root;

// Turn back the stdout to normal state and close the file if KRUZ_DEBUG is defined.
#ifdef KRUZ_DEBUG
  cout.rdbuf(oldCoutBuf);
  coutFile.close();
#endif // KRUZ_DEBUG

	return 0;
}
