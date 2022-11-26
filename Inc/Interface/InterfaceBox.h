#ifndef INTERFACEBOX_H_INCLUDED
#define INTERFACEBOX_H_INCLUDED

#include "Interface/InterfaceWidget.h"
#include "Interface/InterfaceScreen.h"
#include "Render/TextManager.h"

class InterfaceBox: public InterfaceWidget{

protected:

    bool textEnabled;
    std::string text;
    glm::vec4 textColor;
    float textSize;

    glm::vec4 color;

    int textureNum;

    int renderLayer;

public:

    InterfaceBox(RenderEngine*, int, std::string, glm::vec4, glm::vec4, float,
                 bool = true, float=1.0f, float=1.0f);

    ~InterfaceBox();

    void setText(std::string);
    std::string getText();

    void addWidget(InterfaceWidget*);

    InterfaceWidget* getWidget(int);
    InterfaceWidget* getWidgetByPosition(float, float);

    int getWidgetAmount();

    void setMembersParameters();

    void activateFunction();

    glm::vec4 getColor();
    void setColor(glm::vec4);

    glm::vec4 getTextColor();
    void setTextColor(glm::vec4);

    float getTextSize();
    void setTextSize(float);

    void showText(bool);

    void setTexture(int);

    void render();
    void renderText();

    void toggleColor(glm::vec4, float = 1.0f);
    void toggleTextColor(glm::vec4, float = 1.0f);

    void toggleBackColor();
    void toggleBackTextColor();
};

#endif // INTERFACEBOX_H_INCLUDED
