#include <DefenseBuilding.h>
#include <TowerDefenseGame.h>

DefenseBuilding::DefenseBuilding(RenderEngine* engine, TowerDefenseGame* game, int theType, float theDamage)
{

    this->renderEngine = engine;
    this->theGame = game;
    this->type = theType;
    this->damage = theDamage;

}

DefenseBuilding::~DefenseBuilding(){


}

int DefenseBuilding::getType()
{

    return this->type;

}

float DefenseBuilding::getDamage()
{

    return this->damage;

}
void DefenseBuilding::setDamage(float newValue)
{

    this->damage = newValue;

}

void DefenseBuilding::render(){



}
