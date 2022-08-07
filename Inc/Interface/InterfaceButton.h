#ifndef INTERFACEBUTTON_H_INCLUDED
#define INTERFACEBUTTON_H_INCLUDED

#include <functional>
#include <type_traits>
#include <tuple>
#include <any>
#include "Interface/InterfaceScreen.h"
#include "Interface/InterfaceBox.h"

class InterfaceEngine;
class InterfaceButton: public InterfaceBox{

protected:

   InterfaceEngine* interfaceEngine;
   glm::vec4 defaultColor;
   glm::vec4 defaultTextColor;

   float colorToggleCounter;
   float textColorToggleCounter;
   int numberOfArguments;


public:

    InterfaceButton(RenderEngine*, InterfaceEngine*, int, std::string, glm::vec4, glm::vec4, float,
                    bool = true, float=1.0f, float=1.0f);

    ~InterfaceButton();

    float getColorCounter();
    float getTextColorCounter();

    void activateFunction();

    void toggleColor(glm::vec4, float = 1.0f);
    void toggleTextColor(glm::vec4, float = 1.0f);

    void toggleBackColor();
    void toggleBackTextColor();

    void update();

};

#endif // INTERFACEBUTTON_H_INCLUDED
