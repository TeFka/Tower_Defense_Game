
#ifndef GameEntity_H_INCLUDED
#define GameEntity_H_INCLUDED

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>
#include<sstream>
#include<fstream>
#include<stdlib.h>
#include<vector>

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

enum entityTYPE
{
    ALLY,
    ENEMY,
    OTHER
};
class TowerDefenseGame;

class GameEntity
{

protected:

    RenderEngine* renderEngine;
    TowerDefenseGame* theGame;

    entityTYPE type;

    glm::vec2 pos;
    glm::vec2 previousPos;
    int entityTurn;

    glm::vec2 hitbox;
    glm::vec2 faceDirection;

    float defaultSpeed;
    glm::vec2 movementSpeed=glm::vec2(0.0);
    glm::vec2 movementForce=glm::vec2(0.0);

    glm::vec4 color=glm::vec4(0.0);

    float fullHealth;
    float health;
    float healthRegeneration;

    float energy;
    float fullEnergy;
    float energyRegeneration;

    int textureNum;

    int affectionByTerrain;
    int existence;

    std::vector<weaponInfo*> activeWeapons;
    int weaponTurn = 0;

    int iteration = 0;

    void generalUpdate();

    void updateMovement();

    void collisionDetection();

    void useWeapon(glm::vec4, int=0);

    void generalBulletUpdate();

    void physicsUpdate();

public:
    GameEntity(RenderEngine*, TowerDefenseGame*, std::vector<weaponInfo*>, glm::vec2, glm::vec2, int, int, int, int, float,
             float, int,
             int = 1, int = 1, glm::vec4 = glm::vec4(1.0));

    void deathEffect(glm::vec2, float,  int);

    void refreshEntity();

    void render();

    glm::vec2 getPos();

    int getHp();

    int getFullHp();

    int getAttackDelayValue(int = 0);

    int getActiveWeaponNum(int=0);
    void setActiveWeaponNum(int, int=0);

    int getEnergy();

    int getFullEnergy();

    void setHp(int);

    void addWeapon(weaponInfo*);

    void setWeaponPos();

    glm::vec2 getHitBox();

    int getExistence();

    int setExistence(int);

    glm::vec2 getFaceDirection();

    glm::vec2 getMovementSpeed();

    float getJumpForce();

    int getHealthRegeneration();

    int getEnergyRegeneration();

    glm::vec4 getColor();

    int getTextureNum();

    int getAffectionByTerrain();

    int getAffectionByGravity();

    void removeBullet(int);

    void setMovementSpeed(glm::vec2);

    void setFaceDirection(glm::vec2);

    void setJumpForce(float);

    void setHealthRegeneration(int);

    void setEnergyRegeneration(int);
    void setColor(glm::vec4);
    void setTextureNum(int);
    void setAffectionByTerrain(int);
    void setAffectionByGravity(int);
};

#endif // GameEntity_H_INCLUDED
