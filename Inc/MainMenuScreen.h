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

    bool difficultyOpen;
    bool settingsOpen;

    InterfaceLayout* testPopup;
    InterfaceBox* testLabel;
    InterfaceButton* testButton;

public:
    MainMenuScreen(std::string, InterfaceEngine*, RenderEngine*, int);
    ~MainMenuScreen();

    void setGame(TowerDefenseGame*);
    void customSetup();
    void checkForFunctions();
    void update();

    void printTest();
};

#endif // MAINMENUSCREEN_H_INCLUDED
