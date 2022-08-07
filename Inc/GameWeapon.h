#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

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

struct Bullet
{
    float damage;
    glm::vec2 pos;
    glm::vec2 siz;
    float defaultSpeed;
    glm::vec2 speed;
    glm::vec4 col;
    int textureNum;
    int type;
};

struct weaponInfo{

    glm::vec2 relativePos;
    glm::vec2 realPos;
    glm::vec2 siz;
    glm::vec2 faceDirection;
    bool staticPos;
    float attackDelay;
    int weaponTurn;
    int num;
};

class GameWeapon
{
private:
    float attackDamage;
    float attackDelay;
    int textureNum;
    float bulletSpeed;
    float attackCost;

    int weaponShown;

    int bullelttType;

public:

    GameWeapon(float, float, float, float, int, int, int = 1);

    float getAttackDamage();
    float getAttackDelay();
    float getAttackCost();

    int getTextureNum();
    int getBulletSpeed();

    int weaponIsShown();

    void setAttackDamage(float);
    void setAttackDelay(float);
    void updateAttackDelay(float);
    void setAttackCost(float);

    void setTextureNum(int);
    void setBulletSpeed(int);

    void setWeaponShown(int);

    int getType();

};

#endif // WEAPON_H_INCLUDED
