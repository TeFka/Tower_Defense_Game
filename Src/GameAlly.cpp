
#include <GameAlly.h>
#include <TowerDefenseGame.h>

GameAlly::GameAlly(RenderEngine* engine, TowerDefenseGame* activeGame, std::vector<weaponInfo*> weaponInf,
                  int type, glm::vec2 pos, glm::vec2 dimensions, int health, int regen, int energy, int energyRegen,
                 float speed, float jumpForce, int textureN,
                 int terrainEffect,int gravityEffect, glm::vec4 col,
                 float reactionD)
    : GameEntity(engine, activeGame, weaponInf, pos, dimensions,
               health, regen, energy, energyRegen,speed,jumpForce, textureN,terrainEffect, gravityEffect, col)
{
    this->GameAllyType = type;
    this->reactionDistance=reactionD;
    this->type = ALLY;
}
