
#include "Interface/InterfaceEngine.h"
#include "App/AppEngine.h"

InterfaceEngine::InterfaceEngine(RenderEngine* engine)
{

    this->renderEngine = engine;

}

InterfaceEngine::~InterfaceEngine(){


}

void InterfaceEngine::addScreen(InterfaceScreen* newScreen){

    //this->screens.push_back(newScreen);
    //this->screens[this->screens.size()-1]->setup();
    if(this->screens.size()<1){
        this->activeScreen = newScreen->getName();
    }
    this->screens.emplace(newScreen->getName(), std::move(newScreen));
    this->screens[newScreen->getName()]->setup();

}

InterfaceScreen* InterfaceEngine::getActiveScreen(){

    return this->screens[this->activeScreen];

}

void InterfaceEngine::setActiveScreen(std::string newActive){

    this->activeScreen = newActive;

}

void InterfaceEngine::renderActiveScreen(){
    this->renderEngine->clearVerts(this->renderEngine->BASIC_2D_SHADER, true, 1);
    this->renderEngine->setBasic2DSprite(glm::vec2(0.5), glm::vec2(1.0), this->screens[this->activeScreen]->getBackgroundColor());
    this->renderEngine->drawBasic2D(false, 1);

    this->renderEngine->clearVerts(this->renderEngine->BASIC_2D_SHADER, true, 1);
    this->screens[this->activeScreen]->render();
    this->renderEngine->drawBasic2D(false, 1);
}

void InterfaceEngine::renderActiveScreenText(){

    this->screens[this->activeScreen]->renderText();

}


void InterfaceEngine::addActiveCommandId(int activeId){

    this->screens[this->activeScreen]->addActiveCommandId(activeId);

}

InterfaceWidget* InterfaceEngine::getWidget(int neededId){

    return this->screens[this->activeScreen]->getWidget(neededId);
}

void InterfaceEngine::setApp(AppEngine* newApp){

    this->theApp = newApp;

}

AppEngine* InterfaceEngine::getApp(){

    return this->theApp;
}

RenderEngine* InterfaceEngine::getRenderEngine(){

    return this->renderEngine;

}
