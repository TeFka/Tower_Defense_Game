
#include <GameAlly.h>
#include <GameEnemy.h>
#include <TowerDefenseGame.h>

GameAlly::GameAlly(RenderEngine* engine, TowerDefenseGame* activeGame, int code, int textureN,
                      std::vector<weaponInfo*> weaponInf, float reactionD , glm::vec2 pos, glm::vec2 siz, glm::vec4 col, float speed,
                       int health, int regen, int energy, int energyRegen,int terrainEffect)
    : GameEntity(engine, activeGame, code, textureN, weaponInf,
                       pos, siz, col, speed, health, regen, energy, energyRegen,
                       terrainEffect)
{
    this->GameAllyType = type;
    this->reactionDistance=reactionD;
    this->type = ALLY;
    this->enemyTargeted = false;
}

void GameAlly::assignTargetPos(glm::vec2){



}

void GameAlly::reactToEnemies(){

    std::vector<GameEnemy*> enemies = this->theGame->getEnemies();

    for(int i = 0;i<enemies.size();i++){
        glm::vec2 enemPos = enemies[i]->getPos();
        if(glm::length(this->pos-enemPos)<2*this->theGame->getMapBlockWidth()){
            std::cout<<"ally reacting to enemies"<<std::endl;
            this->targetEnemy = enemies[i];
            this->enemyTargeted = true;
        }

    }

}

void GameAlly::allyAIUpdate(){

    if(this->enemyTargeted){

        if(glm::length(this->pos-this->targetEnemy->getPos())<this->reactionDistance){
            this->movementSpeed = this->defaultSpeed*glm::normalize(this->targetEnemy->getPos()-this->pos);
        }
        else{
            this->movementSpeed.x = 0.0f;
            this->movementSpeed.y = 0.0f;
        }

        if(this->entityCode==11){

            this->targetEnemy->setHp(this->targetEnemy->getHp()-this->theGame->getWeaponType(this->activeWeapons[0]->num-1)->getAttackDamage());
            this->targetEnemy->addForce(glm::normalize(this->targetEnemy->getPos()-this->pos)*10.0f);
        }

    }

}


void GameAlly::update(){

    this->reactToEnemies();
    this->allyAIUpdate();
}
