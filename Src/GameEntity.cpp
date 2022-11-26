
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
    //std::cout<<"phys update"<<std::endl;
    this->physicsUpdate();

}

void GameEntity::calcFaceDirection(glm::vec2 lookPos)
{
    this->faceDirection = glm::normalize(lookPos-this->pos);

}

void GameEntity::calcWeaponDirection(int index, glm::vec2 lookPos){

    this->activeWeapons[index]->faceDirection = glm::normalize(lookPos-this->activeWeapons[index]->realPos);
        if(this->theGame->getWeaponType(this->activeWeapons[index]->num-1)->weaponIsShown())
        {
            if(lookPos.x>this->activeWeapons[index]->realPos.x)
            {
                if(!this->activeWeapons[index]->staticPos){
                    this->activeWeapons[index]->relativePos.x = 1.0;
                }
                if(lookPos.y<this->activeWeapons[index]->realPos.y)
                {
                    this->activeWeapons[index]->weaponTurn = 270 + int(90-acos((lookPos.x-this->activeWeapons[index]->realPos.x)/glm::length(lookPos-this->activeWeapons[index]->realPos))*180/M_PI);
                }
                else
                {
                    this->activeWeapons[index]->weaponTurn = int(acos((lookPos.x-this->activeWeapons[index]->realPos.x)/glm::length(lookPos-this->activeWeapons[index]->realPos))*180/M_PI);
                }
            }
            else
            {
                if(!this->activeWeapons[index]->staticPos){
                    this->activeWeapons[index]->relativePos.x = -1.0;
                }

                if(lookPos.y>this->activeWeapons[index]->realPos.y)
                {
                    this->activeWeapons[index]->weaponTurn = 90 + (90 - int(acos((this->activeWeapons[index]->realPos.x-lookPos.x)/glm::length(lookPos-this->activeWeapons[index]->realPos))*180/M_PI));
                }
                else
                {
                    this->activeWeapons[index]->weaponTurn = 180 + int((acos((this->activeWeapons[index]->realPos.x-lookPos.x)/glm::length(lookPos-this->activeWeapons[index]->realPos))*180/M_PI));
                }

            }
        }

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
    //std::cout<<"collision update1"<<std::endl;
    int currentIndexX = this->theGame->getLevelGenerator()->getXPosIndex(this->pos.x);
    int currentIndexY = this->theGame->getLevelGenerator()->getYPosIndex(this->pos.y);

    int maxWidth = this->theGame->getLevelGenerator()->getWidthBlockNum();
    int maxHeight = this->theGame->getLevelGenerator()->getWidthBlockNum();
    //std::cout<<"collision update2"<<std::endl;
    if(currentIndexX<maxWidth-1){
        if(this->theGame->getLevelGenerator()->getDataPoint(currentIndexX+1, currentIndexY) == 1){
            this->blockedSides[1] = true;
        }
        else{
            this->blockedSides[1] = false;
        }
    }
    else{
        this->blockedSides[1] = true;
    }
    if(currentIndexX>0){
        if(this->theGame->getLevelGenerator()->getDataPoint(currentIndexX-1, currentIndexY) == 1){
            this->blockedSides[3] = true;
        }
        else{
            this->blockedSides[3] = false;
        }
    }
    else{
        this->blockedSides[3] = true;
    }
    if(currentIndexY<maxHeight-1){
        if(this->theGame->getLevelGenerator()->getDataPoint(currentIndexX, currentIndexY+1) == 1){
            this->blockedSides[0] = true;
        }
        else{
            this->blockedSides[0] = false;
        }
    }
    else{
        this->blockedSides[0] = true;
    }
    if(currentIndexY>0){
        if(this->theGame->getLevelGenerator()->getDataPoint(currentIndexX, currentIndexY-1) == 1){
            this->blockedSides[2] = true;
        }
        else{
            this->blockedSides[2] = false;
        }
    }
    else{
        this->blockedSides[2] = true;
    }
}

void GameEntity::environmentDetection(){



}

void GameEntity::useWeapon(glm::vec4 col, int weaponIndex)
{
    if(this->activeWeapons[weaponIndex]->num!=0){
        this->energy-=this->theGame->getWeaponType(this->activeWeapons[weaponIndex]->num-1)->getAttackCost();
        this->activeWeapons[weaponIndex]->attackDelay = this->theGame->getWeaponType(this->activeWeapons[weaponIndex]->num-1)->getAttackDelay();

        /*Bullet* bull = new Bullet{this->theGame->getWeaponType(this->activeWeapons[weaponIndex]->num-1)->getAttackDamage(),
                                  this->activeWeapons[weaponIndex]->realPos,
                                  this->hitbox/10.0f,
                                  this->theGame->getWeaponType(this->activeWeapons[weaponIndex]->num-1)->getBulletSpeed()*this->theGame->getGameSpeed(),
                                  (this->theGame->getWeaponType(this->activeWeapons[weaponIndex]->num-1)->getBulletSpeed()*this->theGame->getGameSpeed()*this->activeWeapons[weaponIndex]->faceDirection),
                                  col,16, this->theGame->getWeaponType(this->activeWeapons[weaponIndex]->num-1)->getType()};*/

    }
}

void GameEntity::physicsUpdate()
{
    //std::cout<<"phys update1"<<std::endl;
    this->updateMovement();
    //std::cout<<"phys update2"<<std::endl;
    if(this->affectionByTerrain)
    {
        this->collisionDetection();
    }
    //std::cout<<"phys update3"<<std::endl;
    this->previousPos = this->pos;
    this->pos+=(movementSpeed*this->theGame->getApp()->getDeltaTime()*this->theGame->getGameSpeed());

    for(int i = 0;i<this->activeWeapons.size();i++){
        this->activeWeapons[i]->realPos = this->pos+glm::vec2(this->hitbox.x*this->activeWeapons[i]->relativePos.x, this->hitbox.y*this->activeWeapons[i]->relativePos.y)/2.0f;

    }
    //std::cout<<"phys update4"<<std::endl;
}

GameEntity::GameEntity(RenderEngine* engine, TowerDefenseGame* activeGame, int code, int textureN, std::vector<weaponInfo*> weaponInf,
                       glm::vec2 pos, glm::vec2 siz, glm::vec4 col, float speed, int health, int regen, int energy, int energyRegen, int terrainEffect)
{
    this->renderEngine = engine;
    this->theGame = activeGame;

    this->entityCode = code;

    this->activeWeapons = weaponInf;

    this->pos=pos;
    this->previousPos = pos;
    this->blockedSides[0] = false;
    this->blockedSides[1] = false;
    this->blockedSides[2] = false;
    this->blockedSides[3] = false;
    this->entityTurn = 0;
    this->hitbox = siz;

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

    if(this->existence){
        this->renderEngine->setTurned2DSprite(this->pos,this->hitbox, this->color, this->entityTurn, this->textureNum, false);
    }
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

bool GameEntity::getExistence()
{
    return this->existence;
}

void GameEntity::setExistence(bool val)
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

void GameEntity::addForce(glm::vec2 addedForce){

    this->movementForce += addedForce;

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

