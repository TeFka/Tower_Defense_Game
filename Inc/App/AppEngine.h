#ifndef APPENGINE_H_INCLUDED
#define APPENGINE_H_INCLUDED

#include "Render/RenderEngine.h"
#include "Interface/InterfaceEngine.h"

enum appSTATE
{
    APP_MENU,
};

class AppEngine{

private:

    RenderEngine* renderEngine;
    InterfaceEngine* interfaceEngine;

    GLboolean keysProc[1024];
    appSTATE appState = APP_MENU;

    // time measuring
    float deltaTime;
    float lastTime;
    float currentTime;

    double mouseX = 0;
    double mouseY = 0;

    void writeAppText();

    InterfaceWidget* activeWidget;

    bool widgetIsActive;

    bool activeWidgetON;

    bool activeWidgetLocked;
    float lockedMouseX;
    float lockedMouseY;

    float activeMouseMinX;
    float activeMouseMaxX;
    float activeMouseMinY;
    float activeMouseMaxY;

    void updateTime();

public:

    AppEngine(RenderEngine*, InterfaceEngine*);

    void systemInput(float deltaTime);

    void mouseInput();

    RenderEngine* getRenderEngine();
    InterfaceEngine* getInterfaceEngine();
    appSTATE getAppState();

    bool activeWidgetIsON();
    InterfaceWidget* getActiveWidget();

    float getDeltaTime();

    double getMouseX();
    double getMouseY();

    float getActiveMouseMinX();
    float getActiveMouseMaxX();
    float getActiveMouseMinY();
    float getActiveMouseMaxY();

    void setAppState(appSTATE);

    void setMode(int);

    void lockActiveWidget(bool);

    void updateApp();

    void renderApp();

    void run();

    void runTest(int);

    void endApp();
};

#endif // APPENGINE_H_INCLUDED
