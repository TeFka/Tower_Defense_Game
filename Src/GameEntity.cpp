
#include <GameEntity.h>

#include <TowerDefenseGame.h>

void GameEntity::generalUpdate()
{
    for(int i = 0;i<this->activeWeapons.size();i++){
        if(this->activeWeapons[i]->attackDelay>0.0)
        {
            this->activeWeapons[i]->attackDelay -= this->theGame->getApp()->getDeltaTime();
        }
    }
    if(this->health<this->fullHealth)
    {
        this->health+=this->healthRegeneration*this->theGame->getApp()->getDeltaTime();
    }
    if(this->energy<this->fullEnergy)
    {
        this->energy+=this->energyRegeneration*this->theGame->getApp()->getDeltaTime();
    }

    this->physicsUpdate();

}

void GameEntity::updateMovement()
{
    //wind resistance
    //this->movementSpeed.x *= 0.95;
    //this->movementSpeed.y *= 0.95;

    this->movementSpeed += this->movementForce;

    if(abs(this->movementForce.x)>0.1){
        this->movementForce.x *= 0.7;
    }
    if(abs(this->movementForce.y)>0.1){
        this->movementForce.y *= 0.7;
    }

}

void GameEntity::collisionDetection()
{

    std::vector<std::vector<int>> allBlocks = this->theGame->getLevelGenerator()->getMapData();

}

void GameEntity::useWeapon(glm::vec4 col, int weaponIndex)
{
    if(this->activeWeapons[weaponIndex]->num!=0){
        this->energy-=this->theGame->getWeaponType(this->activeWeapons[weaponIndex]->num-1)->getAttackCost();
        this->activeWeapons[weaponIndex]->attackDelay = this->theGame->getWeaponType(this->activeWeapons[weaponIndex]->num-1)->getAttackDelay();

        Bullet* bull = new Bullet{this->theGame->getWeaponType(this->activeWeapons[weaponIndex]->num-1)->getAttackDamage(),
                                  this->activeWeapons[weaponIndex]->realPos,
                                  this->hitbox/10.0f,
                                  this->theGame->getWeaponType(this->activeWeapons[weaponIndex]->num-1)->getBulletSpeed()*this->theGame->getGameSpeed(),
                                  (this->theGame->getWeaponType(this->activeWeapons[weaponIndex]->num-1)->getBulletSpeed()*this->theGame->getGameSpeed()*this->activeWeapons[weaponIndex]->faceDirection),
                                  col,16, this->theGame->getWeaponType(this->activeWeapons[weaponIndex]->num-1)->getType()};

        this->theGame->addBullet(bull, this->type);
    }
}

void GameEntity::physicsUpdate()
{

    this->updateMovement();

    if(this->affectionByTerrain)
    {
        this->collisionDetection();
    }

    this->previousPos = this->pos;
    this->pos+=(movementSpeed*this->theGame->getApp()->getDeltaTime()*this->theGame->getGameSpeed());

    for(int i = 0;i<this->activeWeapons.size();i++){
        this->activeWeapons[i]->realPos = this->pos+glm::vec2(this->hitbox.x*this->activeWeapons[i]->relativePos.x, this->hitbox.y*this->activeWeapons[i]->relativePos.y)/2.0f;

    }
}

GameEntity::GameEntity(RenderEngine* engine, TowerDefenseGame* activeGame, std::vector<weaponInfo*> weaponInf,
                       glm::vec2 pos, glm::vec2 siz, int health, int regen, int energy, int energyRegen, float speed,
                       float jumpForceVal, int textureN,
                       int terrainEffect, int gravityEffect, glm::vec4 col)
{
    this->renderEngine = engine;
    this->theGame = activeGame;

    this->activeWeapons = weaponInf;

    float randm = (((float)rand())/RAND_MAX);
    this->pos=pos;
    this->previousPos = pos;
    this->entityTurn = 0;
    this->hitbox = siz;
    if(randm<0.5)
    {
        this->faceDirection=glm::vec2(1.0,0.0);
    }
    else
    {
        this->faceDirection=glm::vec2(-1.0,0.0);
    }

    this->healthRegeneration = regen;
    this->health=health;
    this->fullHealth = health;

    this->fullEnergy = energy;
    this->energy = energy;
    this->energyRegeneration = energyRegen;

    this->defaultSpeed = speed;

    this->textureNum = textureN;
    this->color = col;

    this->affectionByTerrain = terrainEffect;
    this->existence=1;
}

void GameEntity::deathEffect(glm::vec2 effectPos, float duration,int amount)
{
    this->theGame->getParticleEngine()->createParticleEffect(effectPos,
            0.2f, duration,amount,
            this->hitbox/5.0f,this->theGame->getGameSpeed()*this->defaultSpeed/2, glm::vec2(0.0f),this->color,
            16,1,0);
}

void GameEntity::refreshEntity()
{



}

void GameEntity::render(){

    this->renderEngine->setBasic2DSprite(this->pos,this->hitbox, color, this->textureNum, false);
}

glm::vec2 GameEntity::getPos()
{
    return this->pos;
}

int GameEntity::getHp()
{
    return this->health;
}

int GameEntity::getFullHp()
{
    return this->fullHealth;
}

int GameEntity::getAttackDelayValue(int index)
{

    return this->activeWeapons[index]->attackDelay;

}

void GameEntity::addWeapon(weaponInfo* newWeap){

    this->activeWeapons.push_back(newWeap);
}

int GameEntity::getActiveWeaponNum(int weaponIndex)
{

    return this->activeWeapons[weaponIndex]->num;

}

void GameEntity::setActiveWeaponNum(int newNum, int weaponIndex)
{

    this->activeWeapons[weaponIndex]->num = newNum;

}

int GameEntity::getEnergy()
{
    return this->energy;
}

int GameEntity::getFullEnergy()
{
    return this->fullEnergy;
}

void GameEntity::setHp(int newHp)
{
    this->health = newHp;
}

glm::vec2 GameEntity::getHitBox()
{
    return this->hitbox;
}

int GameEntity::getExistence()
{
    return this->existence;
}

int GameEntity::setExistence(int val)
{
    this->existence = val;
}

glm::vec2 GameEntity::getFaceDirection()
{

    return this->faceDirection;
}

glm::vec2 GameEntity::getMovementSpeed()
{

    return this->movementSpeed;
}

int GameEntity::getHealthRegeneration()
{

    return this->healthRegeneration;
}

int GameEntity::getEnergyRegeneration()
{

    return this->energyRegeneration;
}

glm::vec4 GameEntity::getColor()
{

    return this->color;
}
int GameEntity::getTextureNum()
{

    return this->textureNum;
}

int GameEntity::getAffectionByTerrain()
{

    return this->affectionByTerrain;
}

void GameEntity::setFaceDirection(glm::vec2 newDirection)
{

    this->faceDirection = newDirection;
}

void GameEntity::setMovementSpeed(glm::vec2 newSpeed)
{

    this->movementSpeed = newSpeed;
}

void GameEntity::setHealthRegeneration(int newRegeneration)
{

    this->healthRegeneration = newRegeneration;
}

void GameEntity::setEnergyRegeneration(int newRegeneration)
{

    this->energyRegeneration = newRegeneration;
}

void GameEntity::setColor(glm::vec4 newColor)
{

    this->color = newColor;
}
void GameEntity::setTextureNum(int newNum)
{

    this->textureNum = newNum;
}

void GameEntity::setAffectionByTerrain(int newAffection)
{

    this->affectionByTerrain = newAffection;
}

