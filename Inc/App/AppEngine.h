#ifndef APPENGINE_H_INCLUDED
#define APPENGINE_H_INCLUDED

#include "Render/RenderEngine.h"
#include "Interface/InterfaceEngine.h"

class AppEngine{

private:

    RenderEngine* renderEngine;
    InterfaceEngine* interfaceEngine;

    GLboolean keysProc[1024];
    int latestKeyInputCode = 0;

    // time measuring
    float deltaTime;
    float lastTime;
    float currentTime;

    double mouseX = 0;
    double mouseY = 0;
    bool mousePress;

    void updateTime();

public:

    AppEngine(RenderEngine*, InterfaceEngine*);

    void systemInput(float deltaTime);

    void mouseInput();

    RenderEngine* getRenderEngine();
    InterfaceEngine* getInterfaceEngine();

    float getDeltaTime();

    double getMouseX();
    double getMouseY();

    void updateApp();

    void renderApp();

    void run();

    void runTest(int);

    void endApp();
};

#endif // APPENGINE_H_INCLUDED
