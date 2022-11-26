
#include "App/AppEngine.h"

AppEngine::AppEngine(RenderEngine* engine, InterfaceEngine* intEngine)
{

    this->renderEngine = engine;
    this->interfaceEngine = intEngine;
    this->mousePress = false;

}

void AppEngine::systemInput(float deltaTime)
{
    if(glfwGetKey(this->renderEngine->getWindow(),GLFW_KEY_ESCAPE)==GLFW_PRESS)
    {
        glfwSetWindowShouldClose(this->renderEngine->getWindow(), GLFW_TRUE);
    }
    if(glfwGetMouseButton(this->renderEngine->getWindow(),GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS)
    {
        if(!this->mousePress){
            std::cout<<"mouse press"<<std::endl;
            this->interfaceEngine->getActiveScreen()->handleTogglePress(this->mouseX, this->mouseY);
            this->mousePress = true;
        }
    }

    if(glfwGetMouseButton(this->renderEngine->getWindow(),GLFW_MOUSE_BUTTON_LEFT)==GLFW_RELEASE)
    {
        if(this->mousePress){
            this->interfaceEngine->getActiveScreen()->handleToggleRelease();
            this->mousePress = false;
        }
    }
}

void AppEngine::mouseInput()
{

    glfwGetCursorPos(this->renderEngine->getWindow(), &this->mouseX, &this->mouseY);

    this->mouseY = this->renderEngine->getWindowHeight() - this->mouseY;
    if(this->mouseX>this->renderEngine->getWindowWidth())
    {
        this->mouseX=this->renderEngine->getWindowWidth();
    }
    if(this->mouseX<0)
    {
        this->mouseX=0;
    }
    if(this->mouseY>this->renderEngine->getWindowHeight())
    {
        this->mouseY=this->renderEngine->getWindowHeight();
    }
    if(this->mouseY<0)
    {
        this->mouseY=0;
    }
}

RenderEngine* AppEngine::getRenderEngine()
{

    return this->renderEngine;
}
InterfaceEngine* AppEngine::getInterfaceEngine()
{

    return this->interfaceEngine;
}

float AppEngine::getDeltaTime()
{
    return this->deltaTime;
}

double AppEngine::getMouseX()
{

    return this->mouseX;
}
double AppEngine::getMouseY()
{

    return this->mouseY;
}

void AppEngine::updateTime()
{
    this->currentTime = glfwGetTime();
    this->deltaTime = (currentTime - lastTime);
    this->lastTime = currentTime;

    if(this->deltaTime>1.0)
    {
        this->deltaTime=1.0;
    }

}

void AppEngine::updateApp()
{
    this->updateTime();
    this->mouseInput();
    this->systemInput(this->deltaTime);
    this->renderEngine->update();

}

void AppEngine::renderApp()
{
    this->renderEngine->renderBegin();
    //std::cout<<"app render"<<std::endl;
    this->interfaceEngine->renderActiveScreen();
    //std::cout<<"app render text"<<std::endl
    this->interfaceEngine->renderActiveScreenText();

    this->renderEngine->clearVerts(this->renderEngine->BASIC_2D_SHADER, true, 1);
    this->renderEngine->setBasic2DSprite(glm::vec2(this->mouseX, this->mouseY),glm::vec2(this->renderEngine->getWindowWidth()*0.005f), glm::vec4(1.0),15,false);
    this->renderEngine->drawBasic2D(false, 1);

    //std::cout<<"app draw done"<<std::endl;
    this->renderEngine->updateScreen();
    this->renderEngine->renderEnd();

}

void AppEngine::run()
{
    //std::cout<<"app run"<<std::endl;
    //draw phase
    this->updateApp();
    //std::cout<<"app update done"<<std::endl;
    this->renderApp();
    //std::cout<<"app render done"<<std::endl;

}

void AppEngine::runTest(int stage)
{
    this->updateApp();
    this->renderEngine->drawTest(stage);
}

void AppEngine::endApp()
{
    glfwDestroyWindow(this->renderEngine->getWindow());
    glfwTerminate();
}
