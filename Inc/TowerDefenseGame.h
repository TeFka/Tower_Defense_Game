
#ifndef TowerDefenseGame_H_INCLUDED
#define TowerDefenseGame_H_INCLUDED

#include<iostream>
#include<sstream>
#include<fstream>
#include<stdlib.h>
#include<vector>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>

#include <Render/RenderEngine.h>
#include <Render/ParticleEngine2D.h>
#include <Interface/InterfaceWidget.h>
#include <Interface/InterfaceEngine.h>
#include <App/AppEngine.h>

#include <TowerDefenseGameLevelGenerator.h>

#include <GameEntity.h>
#include <GameAlly.h>
#include <DefenseBuilding.h>

enum gameSTATE
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_LOST,
    GAME_WIN
};

class GameEnemy;

class TowerDefenseGame
{

private:

    RenderEngine* renderEngine;
    ParticleEngine2D* particleEngine;

    InterfaceWidget* activeWidget;
    AppEngine* appEngine;

    TowerDefenseGameLevelGenerator* levelGenerator;

    GLboolean keysProc[1024];

    unsigned int theRBO;
    unsigned int theFBO;
    unsigned int FBOTexture;

    int width = 1200;
    int height = 900;
    gameSTATE gameState = GAME_MENU;
    int playMode = 0;
    float gameSpeed = 10;
    int gameRefresh = 0;

    double mouseX = 0;
    double mouseY = 0;

    //game variables
    int currLevel = 1;
    float enemyCounter = 3.0;
    int enemyLimit = 5;
    bool bossBattle;
    bool bossAlive;

    //map saved info
    int mapBlockWidth = 0;
    int mapBlockHeight = 0;

    std::vector<GameWeapon*> weaponTypes;

    std::vector<GameAlly*> theAllies;

    std::vector<GameEnemy*> theEnemies;

    std::vector<DefenseBuilding*> theBuildings;

    std::vector<Bullet*> allAllyProjectiles;
    std::vector<Bullet*> allEnemyProjectiles;
    std::vector<Bullet*> allOtherProjectiles;

    //main points info
    int baseTextureNum;
    int lairTextureNum;

    glm::vec2 baseLocation;
    glm::vec2 lairLocation;

public:

    TowerDefenseGame(RenderEngine*, ParticleEngine2D*, AppEngine*, InterfaceWidget*);

    ~TowerDefenseGame();

    void setup();

    void setupFramebuffer();

    void setLocations();
    void refreshGame();

    void systemInput();

    void mouseInput();

    void enemyUpdate();

    void mainUpdate();

    void renderAllies();
    void renderEnemies();
    void renderBuildings();
    void renderBase();
    void renderSpawn();
    void spritePhase();

    void run();

    void addGameAlly();
    void addBuilding();

    ParticleEngine2D* getParticleEngine();

    void setWidth(int);

    void setHeight(int);

    int getWidth();

    int getHeight();

    glm::vec2 getMiddlePos();

    gameSTATE getGameState();

    int getPlayMode();

    float getGameSpeed();
    int getGameRefresh();

    double getMouseX();
    double getMouseY();

    void addWeaponType(float, float, float, float, int, int, int=1);
    GameWeapon* getWeaponType(int);

    void addBullet(Bullet*, entityTYPE);

    float getEnemyCounter();
    int getEnemyLimit();

    std::vector<GameEnemy*>& getEnemies();
    GameEnemy* getEnemy(int);
    int getEnemyAmount();

    unsigned int getFBO();

    unsigned int getFBOTexture();

    void setGameState(gameSTATE);

    void setPlayMode(int);
    void setBossState(bool);

    void setLairTexture(int);
    void setBaseTexture(int);

    void setGameSpeed(float);
    void setGameRefresh(int);

    void setEnemyCounter(float);
    void setEnemyLimit(int);

    AppEngine* getApp();

    TowerDefenseGameLevelGenerator* getLevelGenerator();

};

#endif // TowerDefenseGame_H_INCLUDED









