#ifndef GameAlly_H_INCLUDED
#define GameAlly_H_INCLUDED

#include <Render/RenderEngine.h>

#include <GameEntity.h>

class TowerDefenseGame;
class GameEnemy;

class GameAlly : public GameEntity{

private:

    int GameAllyType;
    float healthRegeneration;
    float reactionDistance;

    bool enemyTargeted;
    GameEnemy* targetEnemy;



public:
    GameAlly(RenderEngine*, TowerDefenseGame*, int, int,
            std::vector<weaponInfo*>, float, glm::vec2, glm::vec2, glm::vec4, float,
            int, int, int, int,int);

    void assignTargetPos(glm::vec2);

    void reactToEnemies();

    void allyAIUpdate();

    void update();

};

#endif // GameAlly_H_INCLUDED
