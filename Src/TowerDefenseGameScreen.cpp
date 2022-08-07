
#include <TowerDefenseGameScreen.h>


TowerDefenseGameScreen::TowerDefenseGameScreen(std::string name, InterfaceEngine* interface, RenderEngine* engine, int theId)
    : InterfaceScreen(name, interface, theId)
{
    this->renderEngine = engine;

}

TowerDefenseGameScreen::~TowerDefenseGameScreen()
{



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
        break;
    }

}
void TowerDefenseGameScreen::update()
{
    this->checkForFunctions();
}

void TowerDefenseGameScreen::render()
{
    this->update();
    for(int i=0; i<this->widgets.size(); i++)
    {
        this->widgets[i]->render();

    }

}
