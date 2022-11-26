#include <DefenseBuilding.h>
#include <TowerDefenseGame.h>

DefenseBuilding::DefenseBuilding(RenderEngine* engine, TowerDefenseGame* game, std::vector<weaponInfo*> theWeapons,
                                 glm::ivec2 indexPos, glm::vec2 pos, glm::vec2 siz, glm::vec4 col, int textrN, int theType, float theDamage)
{

    this->renderEngine = engine;
    this->theGame = game;

    this->activeWeapons = theWeapons;
    for(int i = 0;i<this->activeWeapons.size();i++){
        this->activeWeapons[i]->realPos = pos+glm::vec2(siz.x*this->activeWeapons[i]->relativePos.x, siz.y*this->activeWeapons[i]->relativePos.y)/2.0f;

    }

    this->indexPosition = indexPos;
    this->position = pos;
    this->theSize = siz;
    this->color = col;
    this->textureNum = textrN;
    this->type = theType;
    this->damage = theDamage;

    this->attackDelay = 1.0f;
    this->attackCounter = 1.0f;
    this->shotReady = false;

}

DefenseBuilding::~DefenseBuilding(){


}

int DefenseBuilding::getType()
{

    return this->type;

}

int DefenseBuilding::getVersion(){

    return this->version;

}

void DefenseBuilding::setVersion(int newVal){

    this->version = newVal;

}

float DefenseBuilding::getDamage()
{

    return this->damage;

}
void DefenseBuilding::setDamage(float newValue)
{

    this->damage = newValue;

}

glm::vec2 DefenseBuilding::getPos(){

    return this->position;

}
glm::vec2 DefenseBuilding::getSize(){

    return this->theSize;

}
glm::vec4 DefenseBuilding::getColor(){

    return this->color;

}
int DefenseBuilding::getTextureNum(){

    return this->textureNum;

}

void DefenseBuilding::setPos(glm::vec2 newVal){

    this->position = newVal;

}
void DefenseBuilding::setSize(glm::vec2 newVal){

    this->theSize = newVal;

}
void DefenseBuilding::setColor(glm::vec4 newVal){

    this->color = newVal;

}
void DefenseBuilding::setTextureNum(int newVal){

    this->textureNum = newVal;

}


void DefenseBuilding::reactToEnemies(){

    std::vector<GameEnemy*> enemies = this->theGame->getEnemies();

    for(int i = 0;i<enemies.size();i++){
        if(glm::length(this->position-enemies[i]->getPos())<2*this->theGame->getMapBlockWidth()){
            //std::cout<<"reacting to enemies"<<std::endl;
            for(int i = 0; i<this->activeWeapons.size();i++){
                this->shoot(i, enemies[i]);
                break;
            }

        }

    }

}

void DefenseBuilding::update(){

    if(this->attackCounter<=0){
        this->shotReady = true;
        this->attackCounter = attackDelay;
    }
    else{
        this->attackCounter -= this->theGame->getApp()->getDeltaTime();
    }
    if(this->shotReady){
        //std::cout<<"cheking for enemies"<<std::endl;
        this->reactToEnemies();
        this->shotReady = false;
    }
}

void DefenseBuilding::shoot(int index, GameEnemy* enemy){

    if(this->activeWeapons[index]->num!=0){

        glm::vec2 dirVec = enemy->getPos()-this->position;
        this->activeWeapons[index]->weaponTurn = (int(acos(glm::dot(glm::vec2(1.0,0.0), dirVec)/glm::length(dirVec))*180/M_PI));
        this->activeWeapons[index]->faceDirection = glm::normalize(dirVec);
        //this->energy-=this->theGame->getWeaponType(this->activeWeapons[index]->num-1)->getAttackCost();
        this->activeWeapons[index]->attackDelay = this->theGame->getWeaponType(this->activeWeapons[index]->num-1)->getAttackDelay();

        Bullet* bull = new Bullet{this->theGame->getWeaponType(this->activeWeapons[index]->num-1)->getAttackDamage(),
                                  dirVec,
                                  enemy,
                                  true,
                                  this->activeWeapons[index]->realPos,
                                  glm::vec2(this->theGame->getMapBlockWidth()/10.0f),
                                  this->theGame->getWeaponType(this->activeWeapons[index]->num-1)->getBulletSpeed(),
                                  color,15, this->theGame->getWeaponType(this->activeWeapons[index]->num-1)->getType()};

        this->theGame->addBullet(bull, ALLY);
    }
    //this->shotReady = false;
}

void DefenseBuilding::upgrade(){



}

void DefenseBuilding::render(){

    this->renderEngine->setTurned2DSprite(this->position,this->theSize, this->color, this->activeWeapons[0]->weaponTurn, this->textureNum, false);
    for(int i = 0; i<this->activeWeapons.size();i++){
        this->renderEngine->setTurned2DSprite(this->activeWeapons[i]->realPos,
                                      glm::vec2(this->activeWeapons[i]->siz.x*this->theSize.x,
                                      this->activeWeapons[i]->siz.y*this->theSize.y), this->color,
                                      this->activeWeapons[i]->weaponTurn,
                                      this->theGame->getWeaponType(this->activeWeapons[i]->num-1)->getTextureNum(), false);
    }

}
