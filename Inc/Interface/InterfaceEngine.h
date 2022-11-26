#ifndef INTERFACEENGINE_H_INCLUDED
#define INTERFACEENGINE_H_INCLUDED

#include "Interface/InterfaceWidget.h"
#include "Interface/InterfaceBox.h"
#include "Interface/InterfaceButton.h"
#include "Interface/InterfaceScreen.h"
#include "Interface/InterfaceActionScreen.h"

class AppEngine;

class InterfaceEngine{

private:

    AppEngine* theApp;
    RenderEngine* renderEngine;
    //std::vector<InterfaceScreen*> screens;
    std::unordered_map<std::string, InterfaceScreen*> screens;
    std::string activeScreen;


public:

    InterfaceEngine(RenderEngine*);
    ~InterfaceEngine();

    void addScreen(InterfaceScreen*);
    InterfaceScreen* getActiveScreen();
    void setActiveScreen(std::string);
    void renderActiveScreen();
    void renderActiveScreenText();

    void addActiveCommandId(int);

    InterfaceWidget* getWidget(int);

    void setApp(AppEngine*);
    AppEngine* getApp();
    RenderEngine* getRenderEngine();
};
#endif // INTERFACEENGINE_H_INCLUDED
