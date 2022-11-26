#ifndef BUILDING_H_INCLUDED
#define BUILDING_H_INCLUDED

#define _USE_MATH_DEFINES
#include<math.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>

#include <Render/RenderEngine.h>
#include <GameWeapon.h>
#include <GameEntity.h>
#include <GameEnemy.h>

class TowerDefenseGame;

class DefenseBuilding{

private:
    RenderEngine* renderEngine;
    TowerDefenseGame* theGame;
    int type;
    int version;

    glm::vec2 position;
    glm::ivec2 indexPosition;
    glm::vec2 theSize;
    glm::vec4 color;
    int textureNum;

    std::vector<weaponInfo*> activeWeapons;
    float damage;
    float attackCounter;
    float attackDelay;
    bool shotReady;

    glm::vec2 faceDiretion;
    int turn;
public:

    DefenseBuilding(RenderEngine*, TowerDefenseGame*, std::vector<weaponInfo*>,
                    glm::ivec2, glm::vec2, glm::vec2, glm::vec4, int, int, float);
    ~DefenseBuilding();

    int getType();

    int getVersion();
    void setVersion(int);

    glm::vec2 getPos();
    glm::vec2 getSize();
    glm::vec4 getColor();
    int getTextureNum();

    void setPos(glm::vec2);
    void setSize(glm::vec2);
    void setColor(glm::vec4);
    void setTextureNum(int);

    float getDamage();
    void setDamage(float);

    void update();
    void reactToEnemies();
    void shoot(int, GameEnemy*);

    void upgrade();

    void render();
};

#endif // BUILDING_H_INCLUDED
