
#include <MainMenuScreen.h>


MainMenuScreen::MainMenuScreen(std::string name, InterfaceEngine* interface, RenderEngine* engine, int theId)
    : InterfaceScreen(name, interface, theId)
{

    this->renderEngine = engine;

    this->difficultyOpen = false;
    this->settingsOpen = false;

    this->testPopup = new InterfaceLayout(this->renderEngine, 0, VERTICAL);
    this->testLabel = new InterfaceBox(this->renderEngine, 0, "hello", glm::vec4(1.0,0.0,0.0,1.0),glm::vec4(0.0,0.0,0.0,1.0), 1.0f);
    this->testPopup->addWidget(this->testLabel);
    this->testButton = new InterfaceButton(this->renderEngine, this->interfaceEngine, 100, "Do things", glm::vec4(0.0,0.0,0.0,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);;
    this->testPopup->addWidget(this->testButton);
}

MainMenuScreen::~ MainMenuScreen()
{



}

void MainMenuScreen::setGame(TowerDefenseGame* newGameVal){

    this->theGame = newGameVal;

}

void MainMenuScreen::customSetup(){


}

void MainMenuScreen::checkForFunctions()
{

    int id = this->getLatestActiveId();
    switch(id)
    {
    case 2:
        this->interfaceEngine->setActiveScreen("TowerDefense");
        this->interfaceEngine->getActiveScreen()->customSetup();
        break;
    case 3:
        if(this->difficultyOpen){
            this->getWidget(33)->disable();
            this->difficultyOpen = false;
        }
        else{
            this->getWidget(33)->enable();
            this->difficultyOpen = true;
        }
        this->getWidget(32)->setMembersParameters();

        //this->addPopup(0.5f, 0.5f, 0.5f, 0.5f, this->testPopup);

        break;
    case 5:
        if(this->settingsOpen){
            this->getWidget(38)->disable();
            this->settingsOpen = false;
        }
        else{
            this->getWidget(38)->enable();
            this->settingsOpen = true;
        }
        this->getWidget(37)->setMembersParameters();
        break;
    case 6:
        glfwSetWindowShouldClose(this->renderEngine->getWindow(), GLFW_TRUE);
        break;
    //diffiulty control
    case 34:
        this->theGame->setGameDifficulty(1);
        this->getWidget(34)->setColor(glm::vec4(0.0,0.0,0.0,1.0));
        this->getWidget(35)->setColor(glm::vec4(0.4,0.4,0.4,1.0));
        this->getWidget(36)->setColor(glm::vec4(0.4,0.4,0.4,1.0));
        break;

    case 35:
        this->theGame->setGameDifficulty(2);
        this->getWidget(34)->setColor(glm::vec4(0.4,0.4,0.4,1.0));
        this->getWidget(35)->setColor(glm::vec4(0.0,0.0,0.0,1.0));
        this->getWidget(36)->setColor(glm::vec4(0.4,0.4,0.4,1.0));
        break;

    case 36:
        this->theGame->setGameDifficulty(3);
        this->getWidget(34)->setColor(glm::vec4(0.4,0.4,0.4,1.0));
        this->getWidget(35)->setColor(glm::vec4(0.4,0.4,0.4,1.0));
        this->getWidget(36)->setColor(glm::vec4(0.0,0.0,0.0,1.0));
        break;

    //size ontrol
    case 41:
        this->theGame->setMapWidthNum(10);
        this->theGame->setMapHeightNum(10);
        this->getWidget(41)->setColor(glm::vec4(0.0,0.0,0.0,1.0));
        this->getWidget(42)->setColor(glm::vec4(0.4,0.4,0.4,1.0));
        this->getWidget(43)->setColor(glm::vec4(0.4,0.4,0.4,1.0));
        break;

    case 42:
        this->theGame->setMapWidthNum(20);
        this->theGame->setMapHeightNum(20);
        this->getWidget(41)->setColor(glm::vec4(0.4,0.4,0.4,1.0));
        this->getWidget(42)->setColor(glm::vec4(0.0,0.0,0.0,1.0));
        this->getWidget(43)->setColor(glm::vec4(0.4,0.4,0.4,1.0));
        break;

    case 43:
        this->theGame->setMapWidthNum(50);
        this->theGame->setMapHeightNum(50);
        this->getWidget(41)->setColor(glm::vec4(0.4,0.4,0.4,1.0));
        this->getWidget(42)->setColor(glm::vec4(0.4,0.4,0.4,1.0));
        this->getWidget(43)->setColor(glm::vec4(0.0,0.0,0.0,1.0));
        break;

    //map type control
    case 46:
        this->theGame->setMapType(1);
        this->getWidget(46)->setColor(glm::vec4(0.0,0.0,0.0,1.0));
        this->getWidget(47)->setColor(glm::vec4(0.4,0.4,0.4,1.0));
        this->getWidget(48)->setColor(glm::vec4(0.4,0.4,0.4,1.0));
        break;

    case 47:
        this->theGame->setMapType(2);
        this->getWidget(46)->setColor(glm::vec4(0.4,0.4,0.4,1.0));
        this->getWidget(47)->setColor(glm::vec4(0.0,0.0,0.0,1.0));
        this->getWidget(48)->setColor(glm::vec4(0.4,0.4,0.4,1.0));
        break;

    case 48:
        this->theGame->setMapType(3);
        this->getWidget(46)->setColor(glm::vec4(0.4,0.4,0.4,1.0));
        this->getWidget(47)->setColor(glm::vec4(0.4,0.4,0.4,1.0));
        this->getWidget(48)->setColor(glm::vec4(0.0,0.0,0.0,1.0));
        break;
    case 100:
        std::cout<<"popup doing things"<<std::endl;
        break;
    }

}
void MainMenuScreen::update()
{
    this->checkForFunctions();
}
