
#include <MainMenuScreen.h>


MainMenuScreen::MainMenuScreen(std::string name, InterfaceEngine* interface, RenderEngine* engine, int theId)
    : InterfaceScreen(name, interface, theId)
{

    this->renderEngine = engine;

}

MainMenuScreen::~ MainMenuScreen()
{



}

void MainMenuScreen::checkForFunctions()
{

    int id = this->getLatestActiveId();
    switch(id)
    {
    case 2:
        this->interfaceEngine->setActiveScreen("TowerDefense");
        break;
    case 6:
        glfwSetWindowShouldClose(this->renderEngine->getWindow(), GLFW_TRUE);
        break;

    }

}
void MainMenuScreen::update()
{
    this->checkForFunctions();
}

void MainMenuScreen::render()
{
    this->update();
    for(int i=0; i<this->widgets.size(); i++)
    {
        this->widgets[i]->render();

    }

}
