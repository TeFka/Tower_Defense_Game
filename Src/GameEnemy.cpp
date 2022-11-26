
#include <GameEnemy.h>

GameEnemy::GameEnemy(RenderEngine* engine, TowerDefenseGame* activeGame, int code, int textureN,
                      std::vector<weaponInfo*> weaponInf, float reactionD , glm::vec2 pos, glm::vec2 siz, glm::vec4 col, float speed,
                       int health, int regen, int energy, int energyRegen, int terrainEffect)
    : GameEntity(engine, activeGame, code, textureN, weaponInf,
                       pos, siz, col, speed, health, regen, energy, energyRegen,
                       terrainEffect)
{
    this->enemyType = type;
    this->reactionDistance=reactionD;
    this->type = ENEMY;
    this->pathIndex = 0;
}


void GameEnemy::assignTargetPos(glm::vec2 newPos){

    this->mainTargetPos = newPos;

}

void GameEnemy::enemyAIUpdate(){

    if(!fightActive){
        if(glm::length(this->mainTargetPos-this->pos)>0.1){
            glm::vec2 tempTargetPos = this->theGame->getShortestPathPoint(this->pathIndex);
            if(glm::length(tempTargetPos-this->pos)>0.1){
                this->movementSpeed = this->defaultSpeed*glm::normalize(tempTargetPos-this->pos);
                /*if(this->blockedSides[0]){
                    if(this->movementSpeed.y>0){
                        this->movementSpeed.y = -this->movementSpeed.y;
                    }
                }
                if(this->blockedSides[1]){
                    if(this->movementSpeed.x>0){
                        this->movementSpeed.x = -this->movementSpeed.x;
                    }
                }
                if(this->blockedSides[2]){
                    if(this->movementSpeed.y<0){
                        this->movementSpeed.y = -this->movementSpeed.y;
                    }
                }
                if(this->blockedSides[3]){
                    if(this->movementSpeed.x<0){
                        this->movementSpeed.x = -this->movementSpeed.x;
                    }
                }*/
            }
            else{
                this->pathIndex += 1;
            }

        }
        else{

        }
    }
    else{

    }

}


void GameEnemy::update()
{
    if(this->existence){
        //std::cout<<"enemyUpdate1"<<std::endl;
        this->enemyAIUpdate();
        //std::cout<<"enemyUpdate2"<<std::endl;
        this->generalUpdate();
        //std::cout<<"enemyUpdate3"<<std::endl;
        if(this->health<=0){

            if(this->enemyType>100){

                this->theGame->setBossState(false);

            }

        }
        //std::cout<<"enemyUpdate4"<<std::endl;
    }
}
