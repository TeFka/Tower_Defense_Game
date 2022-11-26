
#include <TowerDefenseGameScreen.h>


TowerDefenseGameScreen::TowerDefenseGameScreen(std::string name, InterfaceEngine* interface, RenderEngine* engine, int theId)
    : InterfaceScreen(name, interface, theId)
{
    this->renderEngine = engine;

}

TowerDefenseGameScreen::~TowerDefenseGameScreen()
{



}


void TowerDefenseGameScreen::customSetup(){

        this->theGame->refreshGame();
        this->theGame->setGameState(GAME_INACTIVE);
}

TowerDefenseGame* TowerDefenseGameScreen::getGame()
{

    return this->theGame;
}

void TowerDefenseGameScreen::setGame(TowerDefenseGame* game)
{

    this->theGame = game;

}

void TowerDefenseGameScreen::checkForFunctions()
{

    int id = this->getLatestActiveId();
    switch(id)
    {
    case 5:
        this->interfaceEngine->setActiveScreen("MainMenu");
        this->theGame->setGameState(GAME_MENU);
        break;
    case 9:
        this->theGame->chooseTower(1);
        break;
    case 10:
        this->theGame->chooseTower(2);
        break;
    case 15:
        this->theGame->chooseTower(3);
        break;
    case 102:
        this->theGame->upgradeChosenTower();
        break;
    case 103:
        this->theGame->sellChosenTower();
        break;
    }

}
void TowerDefenseGameScreen::update()
{
    this->checkForFunctions();
}
