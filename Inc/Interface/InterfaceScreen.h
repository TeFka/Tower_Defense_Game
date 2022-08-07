#ifndef INTERFACESCREEN_H_INCLUDED
#define INTERFACESCREEN_H_INCLUDED

#include <unordered_map>

#include "./InterfaceWidget.h"

class InterfaceEngine;

class InterfaceScreen
{

protected:

    InterfaceEngine* interfaceEngine;

    int id;

    std::string name;
    std::unordered_map<int, InterfaceWidget*> allWidgets;
    std::vector<InterfaceWidget*> widgets;

    std::vector<int> activeIds;

public:

    InterfaceScreen(std::string, InterfaceEngine*, int=0);
    ~InterfaceScreen();

    int getId();
    void addActiveCommandId(int);
    int getLatestActiveId();

    void addWidget(InterfaceWidget*);
    void addChildWidget(InterfaceWidget*);

    InterfaceWidget* getWidget(int);
    InterfaceWidget* getWidgetByPosition(float, float);

    std::string getName();

    void setMembersParameters();
    void setup();

    virtual void update() = 0;

    virtual void render() = 0;
    void renderText();
};

class DefaultInterfaceScreen : public InterfaceScreen
{

public:

    DefaultInterfaceScreen(std::string, InterfaceEngine*);
    ~DefaultInterfaceScreen();

    void update();

    void render();
};

#endif // INTERFACESCREEN_H_INCLUDED
