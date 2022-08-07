
#include "App/AppEngine.h"

AppEngine::AppEngine(RenderEngine* engine, InterfaceEngine* intEngine)
{

    this->renderEngine = engine;
    this->interfaceEngine = intEngine;
    this->widgetIsActive = false;
    this->activeWidgetON = false;
    this->activeWidgetLocked = false;

    this->lockedMouseX = 0;
    this->lockedMouseY = 0;
}

void AppEngine::systemInput(float deltaTime)
{
    if(glfwGetKey(this->renderEngine->getWindow(),GLFW_KEY_ESCAPE)==GLFW_PRESS)
    {
        glfwSetWindowShouldClose(this->renderEngine->getWindow(), GLFW_TRUE);
    }
    if(!this->activeWidgetLocked)
    {
        if(glfwGetMouseButton(this->renderEngine->getWindow(),GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS)
        {
            if(!this->widgetIsActive)
            {
                this->activeWidget = this->interfaceEngine->getActiveScreen()->getWidgetByPosition(this->mouseX, this->mouseY);
                if(this->activeWidget != nullptr )
                {
                    if(this->activeWidget->isButton())
                    {
                        this->widgetIsActive = true;
                        this->activeWidget->activateFunction();
                        this->activeWidget->toggleColor(1.0f-this->activeWidget->getColor());
                        this->activeWidget->toggleTextColor(1.0f-this->activeWidget ->getTextColor());
                    }
                    if(this->activeWidget->isAction())
                    {

                        this->activeWidgetON = true;
                        this->activeMouseMinX = this->activeWidget->getRealX()-(this->activeWidget->getRealWidth()/2);
                        this->activeMouseMaxX = this->activeWidget->getRealX()+(this->activeWidget->getRealWidth()/2);
                        this->activeMouseMinY = this->activeWidget->getRealY()-(this->activeWidget->getRealHeight()/2);
                        this->activeMouseMaxY = this->activeWidget->getRealY()+(this->activeWidget->getRealHeight()/2);

                    }
                }
                else
                {
                    std::cout<<"null button"<<std::endl;
                }
            }

        }

        if(glfwGetMouseButton(this->renderEngine->getWindow(),GLFW_MOUSE_BUTTON_LEFT)==GLFW_RELEASE)
        {
            if(this->widgetIsActive)
            {
                if(this->activeWidget->isButton())
                {
                    this->widgetIsActive = false;
                    this->activeWidget->toggleBackColor();
                    this->activeWidget->toggleBackTextColor();
                }
            }

        }
    }
}

void AppEngine::mouseInput()
{

    glfwGetCursorPos(this->renderEngine->getWindow(), &this->mouseX, &this->mouseY);

    if(this->activeWidgetON)
    {
        if(!this->activeWidgetLocked)
        {
            if(this->mouseX>this->activeMouseMaxX ||
                    this->mouseX<this->activeMouseMinX ||
                    this->mouseY>this->activeMouseMaxY ||
                    this->mouseY<this->activeMouseMinY)
            {
                this->activeWidgetON = false;
                this->widgetIsActive = false;
            }
        }
    }
    else
    {
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

appSTATE AppEngine::getAppState()
{

    return this->appState;
}

bool AppEngine::activeWidgetIsON()
{

    return this->activeWidgetON;
}

InterfaceWidget* AppEngine::getActiveWidget()
{

    return this->activeWidget;
}

double AppEngine::getMouseX()
{

    return this->mouseX;
}
double AppEngine::getMouseY()
{

    return this->mouseY;
}

float AppEngine::getActiveMouseMinX()
{

    return this->activeMouseMinX;
}
float AppEngine::getActiveMouseMaxX()
{

    return this->activeMouseMaxX;
}
float AppEngine::getActiveMouseMinY()
{

    return this->activeMouseMinY;
}
float AppEngine::getActiveMouseMaxY()
{

    return this->activeMouseMaxY;
}


void AppEngine::setAppState(appSTATE newState)
{

    this->appState = newState;
}

void AppEngine::lockActiveWidget(bool newState)
{
    this->activeWidgetLocked = newState;
    if(newState)
    {
        this->lockedMouseX = this->mouseX;
        this->lockedMouseY = this->mouseY;
    }
    else
    {
        glfwSetCursorPos(this->renderEngine->getWindow(), this->lockedMouseX,this->lockedMouseY);
        this->mouseX = this->lockedMouseX;
        this->mouseY = this->lockedMouseY;
    }

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
    //std::cout<<"app render text"<<std::endl;
    this->interfaceEngine->renderActiveScreenText();
    //std::cout<<"app render done"<<std::endl;
    if(this->activeWidgetON)
    {

    }
    else
    {
        this->renderEngine->clearVerts(this->renderEngine->BASIC_2D_SHADER, true);
        this->renderEngine->setBasic2DSprite(glm::vec2(this->mouseX, this->mouseY),glm::vec2(this->renderEngine->getWindowWidth()*0.01f), glm::vec4(1.0),15,false);
        this->renderEngine->drawBasic2D();
    }
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
