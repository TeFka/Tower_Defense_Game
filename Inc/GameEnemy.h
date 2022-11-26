#ifndef GameEnemy_H_INCLUDED
#define GameEnemy_H_INCLUDED

#include<iostream>
#include<sstream>
#include<fstream>
#include<stdlib.h>
#include<vector>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>

#include <Render/RenderEngine.h>

#include <TowerDefenseGame.h>
#include <GameEntity.h>

class GameEnemy : public GameEntity
{
private:

    int enemyType;
    float reactionDistance;
    glm::vec2 mainTargetPos;
    int pathIndex;

    void reactToBullets();
    void AIaction();

public:

    GameEnemy(RenderEngine*, TowerDefenseGame*, int, int,
            std::vector<weaponInfo*>, float, glm::vec2, glm::vec2, glm::vec4, float,
            int, int, int, int,int);

    void assignTargetPos(glm::vec2);
    void enemyAIUpdate();

    void update();
};

#endif // GameEnemy_H_INCLUDED
