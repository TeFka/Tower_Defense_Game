#ifndef MAINMENUSCREEN_H_INCLUDED
#define MAINMENUSCREEN_H_INCLUDED

#include <Interface/InterfaceLayout.h>
#include <Interface/InterfaceBox.h>
#include <Interface/InterfaceButton.h>
#include <Interface/InterfaceActionScreen.h>
#include <Interface/InterfaceScreen.h>
#include <App/AppEngine.h>
#include <TowerDefenseGame.h>

class MainMenuScreen : public InterfaceScreen{

private:

    RenderEngine* renderEngine;
    TowerDefenseGame* theGame;

public:
    MainMenuScreen(std::string, InterfaceEngine*, RenderEngine*, int);
    ~MainMenuScreen();

    void checkForFunctions();
    void update();

    void render();

    void printTest();
};

#endif // MAINMENUSCREEN_H_INCLUDED
