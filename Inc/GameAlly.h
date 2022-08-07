#ifndef GameAlly_H_INCLUDED
#define GameAlly_H_INCLUDED

#include <Render/RenderEngine.h>

#include <GameEntity.h>

class TowerDefenseGame;

class GameAlly : public GameEntity{

private:

    int GameAllyType;
    float healthRegeneration;
    float reactionDistance;

public:
    GameAlly(RenderEngine*, TowerDefenseGame*, std::vector<weaponInfo*>, int,glm::vec2, glm::vec2, int, int, int, int,
            float, float, int,
            int = 1,int = 1, glm::vec4 = glm::vec4(1.0),
            float = 20.0);

};

#endif // GameAlly_H_INCLUDED
