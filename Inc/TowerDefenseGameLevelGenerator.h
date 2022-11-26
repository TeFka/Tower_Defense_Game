#ifndef TOWERDEFENSEGAMELEVEL_H_INCLUDED
#define TOWERDEFENSEGAMELEVEL_H_INCLUDED

#include <iostream>
#include <Render/RenderEngine.h>
#include <NoiseProvider.h>

class TowerDefenseGameLevelGenerator{

private:
    RenderEngine* renderEngine;
    NoiseProvider* provider;

    float mapWidth = 10;
    float mapHeight = 10;

    int widthBlockNum = 10;
    int heightBlockNum = 10;

    float blockWidth = 1;
    float blockHeight = 1;

    std::vector<std::vector<int>> mapData;
    std::vector<std::vector<glm::vec4>> mapColors;
    std::vector<std::vector<glm::vec2>> mapPositions;


public:
    TowerDefenseGameLevelGenerator(RenderEngine*);

    void createEmptyMap();
    void generateNewMap();

    float getWidth();
    float getHeight();

    int getWidthBlockNum();
    int getHeightBlockNum();

    void setWidthBlockNum(int);
    void setHeightBlockNum(int);

    float getBlockWidth();
    float getBlockHeight();

    void setWidth(int);
    void setHeight(int);

    int getBlockType(glm::vec2);

    int getDataPoint(int, int);
    glm::vec2 getPosition(int, int);

    std::vector<std::vector<int>>& getMapData();
    std::vector<std::vector<glm::vec2>>& getMapPositions();

    int getXPosIndex(float);

    int getYPosIndex(float);

    void render();

};

#endif // TOWERDEFENSEGAMELEVEL_H_INCLUDED
