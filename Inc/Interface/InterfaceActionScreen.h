#ifndef INTERFACEACTIONSCREEN_H_INCLUDED
#define INTERFACEACTIONSCREEN_H_INCLUDED

#include "Interface/InterfaceScreen.h"
#include "Interface/InterfaceBox.h"

class InterfaceActionScreen : public InterfaceWidget{

private:

    float refreshPeriod;

    float refreshCounter;

    Texture* theTexture;
    int textureNum;

public:

    InterfaceActionScreen(RenderEngine*, int, float = 50);
    ~InterfaceActionScreen();

    void setTexture(unsigned int, int);

    void render();

    void renderText();

    void addWidget(InterfaceWidget*);

    InterfaceWidget* getWidget(int);
    InterfaceWidget* getWidgetByPosition(float, float);

    int getWidgetAmount();

    void activateFunction();

    void setMembersParameters();

    void setText(std::string);
    std::string getText();

    glm::vec4 getColor();
    void setColor(glm::vec4);

    glm::vec4 getTextColor();
    void setTextColor(glm::vec4);

    void toggleColor(glm::vec4, float = 1.0f);
    void toggleTextColor(glm::vec4, float = 1.0f);

    void toggleBackColor();
    void toggleBackTextColor();
};

#endif // INTERFACEACTIONSCREEN_H_INCLUDED
