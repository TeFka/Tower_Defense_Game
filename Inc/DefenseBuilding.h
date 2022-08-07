#ifndef BUILDING_H_INCLUDED
#define BUILDING_H_INCLUDED

#include <Render/RenderEngine.h>

class TowerDefenseGame;

class DefenseBuilding{

private:
    RenderEngine* renderEngine;
    TowerDefenseGame* theGame;
    int type;
    float damage;
public:

    DefenseBuilding(RenderEngine*, TowerDefenseGame*, int, float);
    ~DefenseBuilding();
    int getType();

    float getDamage();
    void setDamage(float);

    void render();
};

#endif // BUILDING_H_INCLUDED
