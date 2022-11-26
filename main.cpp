
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
    theRenderEngine.getShaderProgram(theRenderEngine.BASIC_2D_SHADER, true)->setTexture((rootDir+textureDir+textureNames[11]).c_str(),11,1);
    theRenderEngine.getShaderProgram(theRenderEngine.BASIC_2D_SHADER, true)->setTexture((rootDir+textureDir+textureNames[12]).c_str(),12,1);
    //particle textures
    theRenderEngine.getShaderProgram(theRenderEngine.BASIC_2D_SHADER, true)->setTexture((rootDir+textureDir+textureNames[6]).c_str(),1,2);
    std::cout<<"setup2"<<std::endl;
    InterfaceEngine theInterfaceEngine(&theRenderEngine);
    std::cout<<"setup3"<<std::endl;
    //menu screen
    MainMenuScreen theMenuScreen("MainMenu", &theInterfaceEngine, &theRenderEngine, 1);

    InterfaceLayout menuMainLayout(&theRenderEngine, 1, VERTICAL);
    theMenuScreen.addChildWidget(&menuMainLayout);

    InterfaceButton playButton(&theRenderEngine, &theInterfaceEngine, 2, "Play", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    menuMainLayout.addWidget(&playButton);

    //difficulty
    InterfaceLayout difficultyLayout(&theRenderEngine, 32, HORIZONTAL);
    menuMainLayout.addWidget(&difficultyLayout);
    //button
    InterfaceButton difficultyButton(&theRenderEngine, &theInterfaceEngine, 3, "Difficulty", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    difficultyLayout.addWidget(&difficultyButton);

    //choices
    InterfaceLayout difficultyChoiceLayout(&theRenderEngine, 33, HORIZONTAL);
    difficultyLayout.addWidget(&difficultyChoiceLayout);
    difficultyChoiceLayout.disable();
    //buttons
    InterfaceButton difficultyEasyButton(&theRenderEngine, &theInterfaceEngine, 34, "Easy", glm::vec4(0.0,0.0,0.0,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    difficultyChoiceLayout.addWidget(&difficultyEasyButton);
    InterfaceButton difficultyNormalButton(&theRenderEngine, &theInterfaceEngine, 35, "Normal", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    difficultyChoiceLayout.addWidget(&difficultyNormalButton);
    InterfaceButton difficultyHardButton(&theRenderEngine, &theInterfaceEngine, 36, "Hard", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    difficultyChoiceLayout.addWidget(&difficultyHardButton);

    //settings
    InterfaceLayout settingsLayout(&theRenderEngine, 37, HORIZONTAL);
    menuMainLayout.addWidget(&settingsLayout);
    //button
    InterfaceButton settingsButton(&theRenderEngine, &theInterfaceEngine, 5, "Settings", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    settingsLayout.addWidget(&settingsButton);
    //choices
    InterfaceLayout settingsChoiceLayout(&theRenderEngine, 38, VERTICAL);
    settingsLayout.addWidget(&settingsChoiceLayout);
    settingsChoiceLayout.disable();
    //size
    InterfaceLayout settingsSizeLayout(&theRenderEngine, 39, HORIZONTAL);
    settingsChoiceLayout.addWidget(&settingsSizeLayout);

    InterfaceBox settingsSizeLabel(&theRenderEngine, 40, "Size", glm::vec4(0.7,0.7,0.7,1.0),glm::vec4(0.0,0.0,0.0,1.0), 1.0f);
    settingsSizeLayout.addWidget(&settingsSizeLabel);
    //buttons
    InterfaceButton settingsSizeSmallButton(&theRenderEngine, &theInterfaceEngine, 41, "Small", glm::vec4(0.0,0.0,0.0,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    settingsSizeLayout.addWidget(&settingsSizeSmallButton);
    InterfaceButton settingsSizeAverageButton(&theRenderEngine, &theInterfaceEngine, 42, "Average", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    settingsSizeLayout.addWidget(&settingsSizeAverageButton);
    InterfaceButton settingsSizeLargeButton(&theRenderEngine, &theInterfaceEngine, 43, "Large", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    settingsSizeLayout.addWidget(&settingsSizeLargeButton);

    InterfaceLayout settingsMapTypeLayout(&theRenderEngine, 44, HORIZONTAL);
    settingsChoiceLayout.addWidget(&settingsMapTypeLayout);

    InterfaceBox settingsMapTypeLabel(&theRenderEngine, 45, "Map Type", glm::vec4(0.7,0.7,0.7,1.0),glm::vec4(0.0,0.0,0.0,1.0), 1.0f);
    settingsMapTypeLayout.addWidget(&settingsMapTypeLabel);
    //buttons
    InterfaceButton settingsOpenMapButton(&theRenderEngine, &theInterfaceEngine, 46, "Open", glm::vec4(0.0,0.0,0.0,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    settingsMapTypeLayout.addWidget(&settingsOpenMapButton);
    InterfaceButton settingsLimitedMapButton(&theRenderEngine, &theInterfaceEngine, 47, "Limited", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    settingsMapTypeLayout.addWidget(&settingsLimitedMapButton);
    InterfaceButton settingsClosedMapButton(&theRenderEngine, &theInterfaceEngine, 48, "Closed", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    settingsMapTypeLayout.addWidget(&settingsClosedMapButton);

    //exit
    InterfaceButton exitButton(&theRenderEngine, &theInterfaceEngine, 6, "Exit", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    menuMainLayout.addWidget(&exitButton);

    //game screen
    TowerDefenseGameScreen theGameScreen("TowerDefense", &theInterfaceEngine, &theRenderEngine, 2);

    InterfaceLayout mainGameLayout(&theRenderEngine, 1, HORIZONTAL);
    theGameScreen.addChildWidget(&mainGameLayout);

    InterfaceActionScreen gameCanvas(&theRenderEngine, 2);
    mainGameLayout.addWidget(&gameCanvas);

    InterfaceLayout gameToolsLayout(&theRenderEngine, 3, VERTICAL, false, 0.2f, 1.0f);
    mainGameLayout.addWidget(&gameToolsLayout);

    //settings
    InterfaceLayout gameSettingsLayout(&theRenderEngine, 4, HORIZONTAL, false, 1.0f, 0.1f);
    gameToolsLayout.addWidget(&gameSettingsLayout);

    InterfaceButton menuButton(&theRenderEngine, &theInterfaceEngine, 5, "Quit", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    gameSettingsLayout.addWidget(&menuButton);

    //items
    InterfaceLayout itemsLayout(&theRenderEngine, 6, VERTICAL);
    gameToolsLayout.addWidget(&itemsLayout);

    //pacing info
    InterfaceLayout paceLayout(&theRenderEngine, 16, HORIZONTAL, false, 1.0f, 0.1f);
    itemsLayout.addWidget(&paceLayout);

    //round
    InterfaceLayout roundLayout(&theRenderEngine, 17, VERTICAL);
    paceLayout.addWidget(&roundLayout);

    InterfaceBox roundLabel(&theRenderEngine, 18, "Round", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    roundLayout.addWidget(&roundLabel);

    InterfaceBox roundNumberLabel(&theRenderEngine, 19, "1", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    roundLayout.addWidget(&roundNumberLabel);

    //time
    InterfaceLayout timeLayout(&theRenderEngine, 20, VERTICAL);
    paceLayout.addWidget(&timeLayout);

    InterfaceBox timeLabel(&theRenderEngine, 21, "Time", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    timeLayout.addWidget(&timeLabel);

    InterfaceBox timeNumberLabel(&theRenderEngine, 22, "00", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    timeLayout.addWidget(&timeNumberLabel);

    //crystals
    InterfaceLayout crystalLayout(&theRenderEngine, 23, HORIZONTAL, false, 1.0f, 0.1f);
    itemsLayout.addWidget(&crystalLayout);

    InterfaceBox crystalTexture(&theRenderEngine, 24, "crystalTexture", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    crystalLayout.addWidget(&crystalTexture);

    InterfaceBox crystalAmountLabel(&theRenderEngine, 25, "100", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    crystalLayout.addWidget(&crystalAmountLabel);

    //game tools
    InterfaceLayout choiceLayout(&theRenderEngine, 12, HORIZONTAL, false, 1.0f, 0.1f);
    itemsLayout.addWidget(&choiceLayout);

    InterfaceButton buildingButton(&theRenderEngine, &theInterfaceEngine, 13, "Buildings", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    choiceLayout.addWidget(&buildingButton);

    InterfaceButton allyButton(&theRenderEngine, &theInterfaceEngine, 14, "Allies", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    choiceLayout.addWidget(&allyButton);

    //buildings
    InterfaceLayout buildingLayout(&theRenderEngine, 8, VERTICAL, false, 1.0f, 0.4f);
    itemsLayout.addWidget(&buildingLayout);

    //building 1
    InterfaceLayout building1(&theRenderEngine, 26, HORIZONTAL);
    buildingLayout.addWidget(&building1);
    //picture
    InterfaceButton buildinglPicture(&theRenderEngine, &theInterfaceEngine, 9, "building1", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    buildinglPicture.setTexture(6);
    buildinglPicture.showText(false);
    building1.addWidget(&buildinglPicture);
    //cost
    InterfaceBox buildinglCost(&theRenderEngine, 27, "50", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f, false, 0.2f, 1.0f);
    building1.addWidget(&buildinglCost);

    //building 2
    InterfaceLayout building2(&theRenderEngine, 28, HORIZONTAL);
    buildingLayout.addWidget(&building2);
    //picture
    InterfaceButton building2Picture(&theRenderEngine, &theInterfaceEngine, 10, "building2", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    building2Picture.setTexture(7);
    building2Picture.showText(false);
    building2.addWidget(&building2Picture);
    //cost
    InterfaceBox building2Cost(&theRenderEngine, 29, "110", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f, false, 0.2f, 1.0f);
    building2.addWidget(&building2Cost);

    //building 3
    InterfaceLayout building3(&theRenderEngine, 30, HORIZONTAL);
    buildingLayout.addWidget(&building3);
    //picture
    InterfaceButton building3Picture(&theRenderEngine, &theInterfaceEngine, 15, "building3", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    building3Picture.setTexture(8);
    building3Picture.showText(false);
    building3.addWidget(&building3Picture);
    //cost
    InterfaceBox building3Cost(&theRenderEngine, 31, "200", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f, false, 0.2f, 1.0f);
    building3.addWidget(&building3Cost);

    //other stuff
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
    theGame.setBaseTexture(10);
    theGame.setLairTexture(11);
    std::cout<<"setup6"<<std::endl;

    theInterfaceEngine.addScreen(&theMenuScreen);
    theInterfaceEngine.addScreen(&theGameScreen);

    //additional setup
    //weapon types
    theGame.addWeaponType(25.0f,10.0f,10.0f,20.0f,6,1,0);
    theGame.addWeaponType(25.0f,10.0f,10.0f,20.0f,6,1);
    theGame.addWeaponType(30.0f,10.0f,20.0f,20.0f,7,2);
    theGame.addWeaponType(50.0f, 5.0f,20.0f,20.0f,8,3);

    //ally types
    theGame.addTowerInfo(11, towerInfo{10,1,2});

    //building types
    theGame.addTowerInfo(1, towerInfo{50, 40, 6, 1});
    theGame.addTowerInfo(2, towerInfo{110, 100, 7, 1});
    theGame.addTowerInfo(3, towerInfo{200, 210, 8, 1});

    theGame.setup();
    gameCanvas.setTexture(theGame.getFBOTexture(), 0);

    theGameScreen.setGame(&theGame);
    theMenuScreen.setGame(&theGame);

    std::cout<<"setup7"<<std::endl;
    while(!glfwWindowShouldClose(theRenderEngine.getWindow()))
    {
        theGame.run();
        theApp.run();

    }

    theApp.endApp();

    return 0;
}
