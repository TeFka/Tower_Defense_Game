#ifndef INTERFACEWIDGET_H_INCLUDED
#define INTERFACEWIDGET_H_INCLUDED

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<cmath>

#include<iostream>
#include<sstream>
#include<fstream>
#include<stdlib.h>
#include<vector>
#include<map>
#include<tuple>

#include "Render/RenderEngine.h"

enum orientation{

    HORIZONTAL,
    VERTICAL
};

class InterfaceScreen;

class InterfaceWidget{

protected:
    RenderEngine* renderEngine;

    int id;
    bool enabled;

    float widthHint;
    float heightHint;
    float xHint;
    float yHint;

    float realWidth;
    float realHeight;
    float realX;
    float realY;

    float horizontalMargin;
    float verticalMargin;

    bool relativeParameters;
    bool hasParent;
    bool layoutWidget = false;
    bool buttonWidget = false;
    bool actionWidget = false;

    glm::vec4 color;

    InterfaceScreen* theActiveScreen;
    bool assignedToScreen;

    InterfaceWidget* widgetParent;

    glm::vec2 toggledPos;
    bool widgetToggled;

public:

    InterfaceWidget(RenderEngine*, int = 0, bool = true, float=1.0f, float=1.0f);

    ~InterfaceWidget();

    void setActiveScreen(InterfaceScreen*);
    InterfaceScreen* getActiveScreen();

    int getId();
    bool isEnabled();
    void enable();
    void disable();
    float getWidthHint();
    float getHeightHint();
    float getXHint();
    float getYHint();

    float getRealWidth();
    float getRealHeight();
    float getRealX();
    float getRealY();

    float getMargin(orientation);
    void setMargin(float, orientation);

    float getOverallWidthHint();
    float getOverallHeightHint();
    float getOverallXHint();
    float getOverGameAllyHint();

    void setWidthHint(float);
    void setHeightHint(float);
    void setXHint(float);
    void setYHint(float);

    bool isRelative();
    bool isLayout();
    bool isButton();
    bool isAction();
    InterfaceWidget* getParent();

    void setRelative(bool);
    void setParent(InterfaceWidget*);

    void setActiveToggledPos(glm::vec2);
    glm::vec2 getActiveToggledPos();

    bool checkToggle();
    void setToggle(bool);

    void updateWidget();

    virtual void render() = 0;
    virtual void renderText() = 0;

    virtual void addWidget(InterfaceWidget*) = 0;

    virtual InterfaceWidget* getWidget(int) = 0;
    virtual InterfaceWidget* getWidgetByPosition(float, float) = 0;

    virtual int getWidgetAmount() = 0;

    virtual void activateFunction() = 0;

    virtual void setMembersParameters() = 0;

    virtual glm::vec4 getColor() = 0;
    virtual void setColor(glm::vec4) = 0;

    virtual glm::vec4 getTextColor() = 0;
    virtual void setTextColor(glm::vec4) = 0;

    virtual void toggleColor(glm::vec4, float = 1.0f) = 0;
    virtual void toggleTextColor(glm::vec4, float = 1.0f) = 0;

    virtual void toggleBackColor() = 0;
    virtual void toggleBackTextColor() = 0;

    virtual void setText(std::string) = 0;
    virtual std::string getText() = 0;

};

#endif // INTERFACEWIDGET_H_INCLUDED
