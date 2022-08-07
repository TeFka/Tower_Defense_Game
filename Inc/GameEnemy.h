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

    void reactToBullets();
    void AIaction();

public:

    GameEnemy(RenderEngine*, TowerDefenseGame*, std::vector<weaponInfo*>, int,glm::vec2, glm::vec2, int, int, int, int,
            float, float, int,
            int = 1,int = 1, glm::vec4 = glm::vec4(1.0),
            float = 20.0);

    void calcFaceDirection(glm::vec2);
    void calcWeaponDirection(int, glm::vec2);

    void update();

    void drawEnemy(glm::vec2);
};

#endif // GameEnemy_H_INCLUDED
