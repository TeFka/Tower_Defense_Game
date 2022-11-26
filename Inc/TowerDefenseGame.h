
#ifndef TowerDefenseGame_H_INCLUDED
#define TowerDefenseGame_H_INCLUDED

#include<iostream>
#include<sstream>
#include<fstream>
#include<stdlib.h>
#include<vector>
#include <unordered_map>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>

#include <Render/RenderEngine.h>
#include <Render/ParticleEngine2D.h>
#include <Interface/InterfaceWidget.h>
#include <Interface/InterfaceLayout.h>
#include <Interface/InterfaceEngine.h>
#include <App/AppEngine.h>

#include <TowerDefenseGameLevelGenerator.h>

#include <GameEntity.h>
#include <GameAlly.h>

enum gameSTATE
{
    GAME_ACTIVE,
    GAME_INACTIVE,
    GAME_PAUSE,
    GAME_MENU,
    GAME_LOST,
    GAME_WIN,
};

struct indexPair{

    int x;
    int y;

};

struct towerInfo{

    int cost;
    int upgradeCost;
    int textureNum;
    int type;

};

namespace std
{
template <> struct hash<indexPair>
{
    size_t operator()(const indexPair &inxPair) const noexcept
    {
        std::hash<decltype(inxPair.x)> hasher;

        auto hash1 = hasher(inxPair.x);
        auto hash2 = hasher(inxPair.y);

        return std::hash<decltype(inxPair.x)> {}((hash1 ^ hash2) >> 2);
    }
};
} // namespace std

namespace std
{
template <> struct hash<glm::ivec2>
{
    size_t operator()(const glm::ivec2 &vect) const noexcept
    {
        std::hash<decltype(vect.x)> hasher;

        auto hash1 = hasher(vect.x);
        auto hash2 = hasher(vect.y);

        return std::hash<decltype(vect.x)> {}((hash1 ^ hash2) >> 2);
    }
};
}

class GameEnemy;
class DefenseBuilding;

class TowerDefenseGame
{

private:

    RenderEngine* renderEngine;
    ParticleEngine2D* particleEngine;

    InterfaceWidget* activeWidget;
    AppEngine* appEngine;

    TowerDefenseGameLevelGenerator* levelGenerator;
    int widthBlockNum;
    int heightBlockNum;
    int mapType;

    GLboolean keysProc[1024];

    unsigned int theRBO;
    unsigned int theFBO;
    unsigned int FBOTexture;

    int width = 1200;
    int height = 900;
    gameSTATE gameState;
    int playMode = 0;
    float gameSpeed = 10;
    int gameRefresh = 0;

    double mouseX = 0;
    double mouseY = 0;

    //game variables
    int gameDifficulty;
    int currRound = 1;
    int roundBreakTime = 5;
    int roundCounter = 5;
    float roundSecCounter = 1.0;

    int crystalNum;
    int defaultCrystalAmount = 100;

    float enemySpawnDelay = 2.0;
    float enemySpawnCounter = 2.0;
    int enemyLimit = 5;
    int enemiesSpawned;
    bool bossBattle;
    bool bossAlive;

    //map saved info
    int mapBlockWidth = 0;
    int mapBlockHeight = 0;

    //tower addition handling
    bool towerChosen;
    int chosenTowerCode;
    glm::ivec2 chosenTowerIndexPos;

    int modificationIndex;
    bool buildingModificationOccuring;
    bool allyModificationOccuring;

    std::unordered_map<int, towerInfo> allTowerInfo;

    std::vector<GameWeapon*> weaponTypes;

    std::vector<GameAlly*> theAllies;

    std::vector<GameEnemy*> theEnemies;

    std::vector<DefenseBuilding*> theBuildings;

    std::vector<Bullet*> allAllyProjectiles;
    std::vector<Bullet*> allEnemyProjectiles;

    //main points info
    int baseTextureNum;
    glm::vec2 baseLocation;
    int baseMaxHealth = 100;
    int baseHealth;

    int lairTextureNum;
    glm::vec2 lairLocation;

    int baseIndexX;
    int baseIndexY;
    int lairIndexX;
    int lairIndexY;

    std::vector<glm::vec2> shortestPath;
    std::unordered_map<indexPair, glm::ivec2> visitedCells;

    //widget control
    InterfaceLayout* unitPopupContent;
    InterfaceBox* nameLabel;
    InterfaceButton* upgradeButton;
    InterfaceButton* sellButton;

public:

    TowerDefenseGame(RenderEngine*, ParticleEngine2D*, AppEngine*, InterfaceWidget*);

    ~TowerDefenseGame();

    void setup();

    void setupFramebuffer();

    void setLocations();
    bool check_cell(std::vector<glm::ivec4>&);
    void findShortestPath();

    void refreshGame();

    void systemInput();

    void handleMouseToggle(float, float);
    void mouseInput();

    void enemyUpdate();
    void buildingUpdate();
    void alliesUpdate();

    void projectileUpdate();

    void paceUpdate();

    void mainUpdate();

    void renderAllies();
    void renderEnemies();
    void renderBuildings();
    void renderProjectiles();
    void renderBase();
    void renderSpawn();
    void renderNewChoice();

    void spritePhase();

    void run();

    void addGameAlly(int, float, float);
    void addGameBuilding(int, float, float);
    void removeBuilding(float, float);

    void createTowerPopup();
    void sellChosenTower();
    void upgradeChosenTower();

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

    void chooseTower(int);
    bool isTowerChosen();
    void setTowerChoice(bool);

    void addWeaponType(float, float, float, float, int, int, int=1);
    GameWeapon* getWeaponType(int);

    void addTowerInfo(int, towerInfo);

    void addBullet(Bullet*, entityTYPE);

    float getEnemyCounter();
    int getEnemyLimit();

    std::vector<GameAlly*>& getAllies();
    std::vector<GameEnemy*>& getEnemies();
    std::vector<DefenseBuilding*>& getBuildings();

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

    int getGameDifficulty();
    int getMapType();
    int getMapWidthNum();
    int getMapHeightNum();

    void setGameDifficulty(int);
    void setMapType(int);
    void setMapWidthNum(int);
    void setMapHeightNum(int);

    AppEngine* getApp();

    float getMapBlockWidth();
    float getMapBlockHeight();
    TowerDefenseGameLevelGenerator* getLevelGenerator();

    glm::vec2 getShortestPathPoint(int);

};

#endif // TowerDefenseGame_H_INCLUDED









