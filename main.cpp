
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<SOIL2/SOIL2.h>
#include<ft2build.h>
#include FT_FREETYPE_H

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

#include<Render/Shader.h>
#include<Render/Camera.h>
#include<Render/Texture.h>

#include <Render/RenderEngine.h>

#include <TowerDefenseGame.h>
#include <TowerDefenseGameScreen.h>
#include <MainMenuScreen.h>

#include "Inc/helpers/RootDir.h"

using namespace std;
using namespace glm;

int main()
{

    string rootDir = ROOT_DIR;
    string shaderDir = "Resources/shaders/";
    string shaderNames = {};

    RenderEngine theRenderEngine("Tower Defender",
                              1200, 800,
                              4, 4,
                              (ROOT_DIR+shaderDir).c_str());
    std::cout<<"setup1"<<std::endl;
    std::string textFont = "arial";
    theRenderEngine.getTextManager()->setTextType(textFont);

    theRenderEngine.setDefaultShaderUniforms();

    string textureDir = "Resources/textures/";
    string textureNames[13] = {"background.png", "bricks.png", "yes_piskel.png", "aim.png",
     "spinner.png", "jumper.png", "particle.png", "basicWeapon.png",
     "launcherWeapon.png", "artilleryWeapon.png", "roboBoss.png", "base.png", "lair.png"};

    //Textures
    theRenderEngine.getShaderProgram(theRenderEngine.BASIC_2D_SHADER, true)->setTexture((rootDir+textureDir+textureNames[0]).c_str(),1,1);
    theRenderEngine.getShaderProgram(theRenderEngine.BASIC_2D_SHADER, true)->setTexture((rootDir+textureDir+textureNames[1]).c_str(),2,1);
    theRenderEngine.getShaderProgram(theRenderEngine.BASIC_2D_SHADER, true)->setTexture((rootDir+textureDir+textureNames[2]).c_str(),3,1);
    theRenderEngine.getShaderProgram(theRenderEngine.BASIC_2D_SHADER, true)->setTexture((rootDir+textureDir+textureNames[3]).c_str(),4,1);
    theRenderEngine.getShaderProgram(theRenderEngine.BASIC_2D_SHADER, true)->setTexture((rootDir+textureDir+textureNames[4]).c_str(),5,1);
    theRenderEngine.getShaderProgram(theRenderEngine.BASIC_2D_SHADER, true)->setTexture((rootDir+textureDir+textureNames[5]).c_str(),6,1);
    theRenderEngine.getShaderProgram(theRenderEngine.BASIC_2D_SHADER, true)->setTexture((rootDir+textureDir+textureNames[7]).c_str(),7,1);
    theRenderEngine.getShaderProgram(theRenderEngine.BASIC_2D_SHADER, true)->setTexture((rootDir+textureDir+textureNames[8]).c_str(),8,1);
    theRenderEngine.getShaderProgram(theRenderEngine.BASIC_2D_SHADER, true)->setTexture((rootDir+textureDir+textureNames[9]).c_str(),9,1);
    theRenderEngine.getShaderProgram(theRenderEngine.BASIC_2D_SHADER, true)->setTexture((rootDir+textureDir+textureNames[10]).c_str(),10,1);
    //theRenderEngine.getShaderProgram(theRenderEngine.BASIC_2D_SHADER, true)->setTexture((rootDir+textureDir+textureNames[11]).c_str(),11,1);
    //theRenderEngine.getShaderProgram(theRenderEngine.BASIC_2D_SHADER, true)->setTexture((rootDir+textureDir+textureNames[12]).c_str(),12,1);
    //particle textures
    theRenderEngine.getShaderProgram(theRenderEngine.BASIC_2D_SHADER, true)->setTexture((rootDir+textureDir+textureNames[6]).c_str(),1,2);
    std::cout<<"setup2"<<std::endl;
    InterfaceEngine theInterfaceEngine(&theRenderEngine);;
    std::cout<<"setup3"<<std::endl;
    //menu screen
    MainMenuScreen theMenuScreen("MainMenu", &theInterfaceEngine, &theRenderEngine, 1);

    InterfaceLayout menuMainLayout(&theRenderEngine, 1, VERTICAL);
    theMenuScreen.addChildWidget(&menuMainLayout);

    InterfaceButton playButton(&theRenderEngine, &theInterfaceEngine, 2, "Play", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    menuMainLayout.addWidget(&playButton);
    InterfaceButton difficultyButton(&theRenderEngine, &theInterfaceEngine, 3, "Difficulty", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    menuMainLayout.addWidget(&difficultyButton);
    InterfaceButton levelButton(&theRenderEngine, &theInterfaceEngine, 4, "Level Size", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    menuMainLayout.addWidget(&levelButton);
    InterfaceButton settingsButton(&theRenderEngine, &theInterfaceEngine, 5, "Settings", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    menuMainLayout.addWidget(&settingsButton);
    InterfaceButton exitButton(&theRenderEngine, &theInterfaceEngine, 6, "Exit", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    menuMainLayout.addWidget(&exitButton);
    std::cout<<"setup4"<<std::endl;

    //game screen
    TowerDefenseGameScreen theGameScreen("TowerDefense", &theInterfaceEngine, &theRenderEngine, 2);

    InterfaceLayout mainGameLayout(&theRenderEngine, 1, HORIZONTAL);
    theGameScreen.addChildWidget(&mainGameLayout);

    InterfaceActionScreen gameCanvas(&theRenderEngine, 2);
    mainGameLayout.addWidget(&gameCanvas);

    InterfaceLayout gameToolsLayout(&theRenderEngine, 3, VERTICAL, false, 0.2f, 1.0f);
    mainGameLayout.addWidget(&gameToolsLayout);

    InterfaceLayout settingsLayout(&theRenderEngine, 4, HORIZONTAL, false, 1.0f, 0.1f);
    gameToolsLayout.addWidget(&settingsLayout);

    InterfaceButton menuButton(&theRenderEngine, &theInterfaceEngine, 5, "Quit", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    settingsLayout.addWidget(&menuButton);

    InterfaceLayout itemsLayout(&theRenderEngine, 6, VERTICAL);
    gameToolsLayout.addWidget(&itemsLayout);

    InterfaceBox toolsLabel(&theRenderEngine, 7, "Tools", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f, false, 1.0f, 0.1f);
    itemsLayout.addWidget(&toolsLabel);

    InterfaceLayout buildingLayout(&theRenderEngine, 8, VERTICAL, false, 1.0f, 0.1f);
    itemsLayout.addWidget(&buildingLayout);

    InterfaceButton buildingl(&theRenderEngine, &theInterfaceEngine, 9, "building1", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    //buildingl.setTexture(3);
    buildingl.showText(false);
    buildingLayout.addWidget(&buildingl);

    InterfaceButton building2(&theRenderEngine, &theInterfaceEngine, 10, "building2", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    //building2.setTexture(5);
    building2.showText(false);
    buildingLayout.addWidget(&building2);

    InterfaceBox otherItemsLabel(&theRenderEngine, 11, "Other", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    itemsLayout.addWidget(&otherItemsLabel);
    //the app
    AppEngine theApp(&theRenderEngine, &theInterfaceEngine);

    ParticleEngine2D theParticleEngine(&theRenderEngine, &theApp);
    theParticleEngine.particleSetup(1000);

    //interface engine setup
    theInterfaceEngine.setApp(&theApp);
    std::cout<<"setup5"<<std::endl;
    TowerDefenseGame theGame(&theRenderEngine, &theParticleEngine, &theApp, &gameCanvas);
    //theGame.setBaseTexture(10);
    //theGame.setLairTexture(11);
    std::cout<<"setup6"<<std::endl;
    //additional setup
    theGame.setWidth(gameCanvas.getRealWidth());
    theGame.setHeight(gameCanvas.getRealHeight());

    theGame.setup();

    gameCanvas.setTexture(theGame.getFBOTexture(), 0);

    theGameScreen.setGame(&theGame);

    theInterfaceEngine.addScreen(&theMenuScreen);
    theInterfaceEngine.addScreen(&theGameScreen);

    std::cout<<"setup7"<<std::endl;
    while(!glfwWindowShouldClose(theRenderEngine.getWindow()))
    {

        theGame.run();
        theApp.run();

    }

    theApp.endApp();

    return 0;
}
