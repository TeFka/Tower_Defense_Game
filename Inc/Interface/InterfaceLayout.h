#ifndef INTERFACELAYOUT_H_INCLUDED
#define INTERFACELAYOUT_H_INCLUDED

#include "Interface/InterfaceWidget.h"

class InterfaceLayout : public InterfaceWidget
{

private:

    std::vector<InterfaceWidget*> widgets;
    orientation orient;
    float padding;

public:

    InterfaceLayout(RenderEngine*, int, orientation = HORIZONTAL, bool = true, float=1.0f, float=1.0f);
    ~InterfaceLayout();

    void addWidget(InterfaceWidget*);

    InterfaceWidget* getWidget(int);
    InterfaceWidget* getWidgetByPosition(float, float);

    int getWidgetAmount();

    void setMembersParameters();

    void activateFunction();

    void setPadding(float);
    float getPadding();

    void render();
    void renderText();

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

#endif // INTERFACELAYOUT_H_INCLUDED
