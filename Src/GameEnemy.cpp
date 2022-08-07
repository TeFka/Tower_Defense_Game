
#include <GameEnemy.h>

GameEnemy::GameEnemy(RenderEngine* engine, TowerDefenseGame* activeGame, std::vector<weaponInfo*> weaponInf, int type, glm::vec2 pos, glm::vec2 dimensions, int health, int regen, int energy, int energyRegen,
                 float speed, float jumpForce, int textureN,
                 int terrainEffect,int gravityEffect, glm::vec4 col,
                 float reactionD)
    : GameEntity(engine, activeGame, weaponInf, pos, dimensions,
               health, regen, energy, energyRegen,speed,jumpForce, textureN,terrainEffect, gravityEffect, col)
{
    this->enemyType = type;
    this->reactionDistance=reactionD;
    this->type = ENEMY;
}

void GameEnemy::calcFaceDirection(glm::vec2 lookPos)
{
    this->faceDirection = glm::normalize(lookPos-this->pos);

}

void GameEnemy::calcWeaponDirection(int index, glm::vec2 lookPos){

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

void GameEnemy::AIaction()
{

}

void GameEnemy::reactToBullets()
{

}

void GameEnemy::update()
{
    if(this->iteration>10)
    {
        this->reactToBullets();

        this->AIaction();

        this->generalUpdate();

        if(this->health<=0){

            if(this->enemyType>100){

                this->theGame->setBossState(false);

            }

        }
    }
    else
    {
        this->iteration++;
    }
}

void GameEnemy::drawEnemy(glm::vec2 relativePos)
{
    /*
    for(int i = 0; i<this->shotBullets.size(); i++)
    {
        this->renderEngine->setSprite(this->shotBullets[i]->pos+this->theGame->getMiddlePos()-relativePos,
                                      this->shotBullets[i]->siz,this->shotBullets[i]->col,this->shotBullets[i]->textureNum);

    }

    this->renderEngine->setSprite(this->pos+this->theGame->getMiddlePos()-relativePos,
                                  this->hitbox, this->color, this->textureNum, this->entityTurn);

    for(int i = 0; i<this->activeWeapons.size(); i++)
    {
        if(this->theGame->getWeaponType(this->activeWeapons[i]->num-1)->weaponIsShown())
        {
            this->renderEngine->setSprite(this->activeWeapons[i]->realPos+this->theGame->getMiddlePos()-relativePos,
                                          glm::vec2(this->activeWeapons[i]->siz.x*this->hitbox.x, this->activeWeapons[i]->siz.y*this->hitbox.y), this->color,
                                          this->theGame->getWeaponType(this->activeWeapons[i]->num-1)->getTextureNum(),
                                          this->activeWeapons[i]->weaponTurn);
        }
    }
*/
}
