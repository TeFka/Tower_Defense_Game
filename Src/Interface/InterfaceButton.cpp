
#include "Interface/InterfaceButton.h"
#include "Interface/InterfaceEngine.h"
#include "App/AppEngine.h"

//template <typename... members>
InterfaceButton::InterfaceButton(RenderEngine* engine, InterfaceEngine* interface, int theId, std::string initialText,
                                 glm::vec4 initialColor, glm::vec4 initialTextColor, float txtSize,
                                 bool relative, float initialW, float initialH)
                                 :InterfaceBox(engine, theId, initialText, initialColor, initialTextColor, txtSize,
                                                relative, initialW, initialH){

    this->interfaceEngine = interface;

    this->numberOfArguments = 0;

    this->buttonWidget = true;

    this->defaultColor = initialColor;
    this->defaultTextColor = initialTextColor;
}

InterfaceButton::~InterfaceButton(){


}

float InterfaceButton::getColorCounter(){

    return this->colorToggleCounter;

}

float InterfaceButton::getTextColorCounter(){

    return this->textColorToggleCounter;

}

//template <typename... members>
void InterfaceButton::activateFunction(){

   this->interfaceEngine->addActiveCommandId(this->id);

}

void InterfaceButton::toggleColor(glm::vec4 toggleColor, float time){

    this->color = toggleColor;
    this->colorToggleCounter = time;

}

void InterfaceButton::toggleTextColor(glm::vec4 toggleColor, float time){
    this->textColor = toggleColor;
    this->textColorToggleCounter = time;

}

void InterfaceButton::toggleBackColor(){
    this->color = this->defaultColor;
}

void InterfaceButton::toggleBackTextColor(){
    this->textColor = this->defaultTextColor;

}

void InterfaceButton::update(){

    if(this->colorToggleCounter>0.0){
        this->colorToggleCounter-=this->interfaceEngine->getApp()->getDeltaTime();
    }

    if(this->textColorToggleCounter>0.0){
        this->textColorToggleCounter-=this->interfaceEngine->getApp()->getDeltaTime();
    }
}
