#ifndef INTERFACESCREEN_H_INCLUDED
#define INTERFACESCREEN_H_INCLUDED

#include <unordered_map>

#include "Interface/InterfaceWidget.h"

#include "Interface/InterfaceLayout.h"

class InterfaceEngine;

class InterfaceScreen
{

protected:

    InterfaceEngine* interfaceEngine;

    int id;

    InterfaceWidget* activeWidget;

    bool widgetIsActive;

    std::string name;
    std::unordered_map<int, InterfaceWidget*> allWidgets;
    std::vector<InterfaceWidget*> widgets;

    std::vector<int> activeIds;

    std::vector<InterfaceWidget*> activePopups;

    glm::vec4 backgroundColor;
public:

    InterfaceScreen(std::string, InterfaceEngine*, int=0);
    ~InterfaceScreen();

    int getId();
    void addActiveCommandId(int);
    int getLatestActiveId();

    void handleTogglePress(float, float);
    void handleToggleRelease();

    void addWidget(InterfaceWidget*);
    void addChildWidget(InterfaceWidget*);

    InterfaceWidget* getActiveWidget();

    void addPopup(float, float, float, float, InterfaceWidget*);
    bool popupsAreActive();
    InterfaceWidget* getPopupByPosition(float, float);
    void removePopup(int);
    void removeLastPopup();
    void clearPopups();

    InterfaceWidget* getWidget(int);
    InterfaceWidget* getWidgetByPosition(float, float);

    std::string getName();

    glm::vec4 getBackgroundColor();
    void setBackgroundColor(glm::vec4);

    void setMembersParameters();
    void setup();

    void render();

    virtual void customSetup() = 0;

    virtual void update() = 0;

    void renderText();
};

class DefaultInterfaceScreen : public InterfaceScreen
{

public:

    DefaultInterfaceScreen(std::string, InterfaceEngine*);
    ~DefaultInterfaceScreen();

    void update();
};

#endif // INTERFACESCREEN_H_INCLUDED
