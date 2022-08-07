#ifndef GAMESCREEN_H_INCLUDED
#define GAMESCREEN_H_INCLUDED

#include <Interface/InterfaceLayout.h>
#include <Interface/InterfaceBox.h>
#include <Interface/InterfaceButton.h>
#include <Interface/InterfaceActionScreen.h>
#include <Interface/InterfaceScreen.h>
#include <App/AppEngine.h>
#include <TowerDefenseGame.h>

class TowerDefenseGameScreen : public InterfaceScreen{

private:

    RenderEngine* renderEngine;
    TowerDefenseGame* theGame;

public:
    TowerDefenseGameScreen(std::string, InterfaceEngine*, RenderEngine*, int);
    ~TowerDefenseGameScreen();

    TowerDefenseGame* getGame();
    void setGame(TowerDefenseGame*);

    void checkForFunctions();
    void update();

    void render();

    void printTest();
};

#endif // GAMESCREEN_H_INCLUDED
