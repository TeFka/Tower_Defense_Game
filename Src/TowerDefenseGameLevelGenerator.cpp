#include <TowerDefenseGameLevelGenerator.h>

TowerDefenseGameLevelGenerator::TowerDefenseGameLevelGenerator(RenderEngine* engine)
{

    this->renderEngine = engine;
    this->provider = new NoiseProvider();
}

void TowerDefenseGameLevelGenerator::createEmptyMap()
{

    this->mapData.clear();
    this->mapColors.clear();
    this->mapPositions.clear();

    this->blockWidth = this->mapWidth/this->widthBlockNum;
    this->blockHeight = this->mapHeight/this->heightBlockNum;

    for(int x = 0; x<this->widthBlockNum; x++)
    {
        std::vector<int> tempArray;
        std::vector<glm::vec4> tempCol;
        std::vector<glm::vec2> tempPos;
        for(int y = 0; y<this->heightBlockNum; y++)
        {

            tempArray.push_back(0);
            tempCol.push_back(glm::vec4(0.0f));
            tempPos.push_back(glm::vec2(((float)x+0.5)*this->blockWidth, ((float)y+0.5)*this->blockHeight));

        }
        this->mapData.push_back(tempArray);
        this->mapColors.push_back(tempCol);
        this->mapPositions.push_back(tempPos);
    }

}

void TowerDefenseGameLevelGenerator::generateNewMap()
{
    this->createEmptyMap();

    this->provider->setWidthNum(this->widthBlockNum);
    this->provider->setWidthNum(this->heightBlockNum);
    this->provider->generatePerlinNoise();

    std::vector<std::vector<double>>noiseData = this->provider->getData();


    for(int x = 0; x<this->widthBlockNum; x++)
    {
        for(int y = 0; y<this->heightBlockNum; y++)
        {
            std::cout<<"noise value at "<<x<<" "<<y<<" : "<<noiseData[x][y]<<std::endl;
            if(noiseData[x][y]>0.5)
            {
                std::cout<<"aigned value"<<std::endl;
                this->mapData[x][y] = 0;
                this->mapColors[x][y] = glm::vec4(0.6f,0.6f,0.0f,1.0f);
            }
            else if(noiseData[x][y]>0.3)
            {
                this->mapData[x][y] = 2;
                this->mapColors[x][y] = glm::vec4(0.0f,0.8f,0.8f,1.0f);
            }
            else
            {
                this->mapData[x][y] = 1;
                this->mapColors[x][y] = glm::vec4(0.0f,0.4f,0.0f,1.0f);
            }

        }

    }

}

float TowerDefenseGameLevelGenerator::getWidth()
{

    return this->mapWidth;

}
float TowerDefenseGameLevelGenerator::getHeight()
{

    return this->mapHeight;

}

void TowerDefenseGameLevelGenerator::setWidth(int newVal)
{

    this->mapWidth = newVal;

}
void TowerDefenseGameLevelGenerator::setHeight(int newVal)
{

    this->mapHeight = newVal;

}

int TowerDefenseGameLevelGenerator::getWidthBlockNum()
{

    return this->widthBlockNum;

}
int TowerDefenseGameLevelGenerator::getHeightBlockNum()
{

    return this->heightBlockNum;

}

void TowerDefenseGameLevelGenerator::setWidthBlockNum(int newVal)
{

    this->heightBlockNum = newVal;

}
    void TowerDefenseGameLevelGenerator::setHeightBlockNum(int newVal)
{

    this->heightBlockNum = newVal;

}

float TowerDefenseGameLevelGenerator::getBlockWidth()
{

return this->blockWidth;

}
float TowerDefenseGameLevelGenerator::getBlockHeight()
{

    return this->blockHeight;

}

int TowerDefenseGameLevelGenerator::getDataPoint(int x, int y )
{

    return this->mapData[x][y];

}
glm::vec2 TowerDefenseGameLevelGenerator::getPosition(int x, int y)
{

    return this->mapPositions[x][y];

}

std::vector<std::vector<int>>& TowerDefenseGameLevelGenerator::getMapData()
{

    return this->mapData;

}
std::vector<std::vector<glm::vec2>>& TowerDefenseGameLevelGenerator::getMapPositions()
{

    return this->mapPositions;

}

void TowerDefenseGameLevelGenerator::render()
{

    for(int x=0; x<this->widthBlockNum; x++)
    {
        for(int y=0; y<this->heightBlockNum; y++)
        {
            //std::cout<<"rendering at positoons: "<<this->mapPositions[x][y].x<<" "<<this->mapPositions[x][y].x<<" with size: "<<this->blockWidth<<" "<<this->blockHeight<<std::endl;
            this->renderEngine->setBasic2DSprite(this->mapPositions[x][y], glm::vec2(this->blockWidth,this->blockHeight),
                                                 this->mapColors[x][y], 15, false);
            if(this->mapData[x][y]==1)
            {
                if(x<this->widthBlockNum-1)
                {
                    if(this->mapData[x+1][y]==0)
                    {
                        this->renderEngine->setBasic2DSprite(this->mapPositions[x][y]+glm::vec2(this->blockWidth*0.2, 0.0f),
                                                             glm::vec2(this->blockWidth*0.1f,this->blockHeight),
                                                             this->mapColors[x][y]*0.2f, 15, false);
                    }
                }
                if(x>0)
                {
                    if(this->mapData[x-1][y]==0)
                    {
                        this->renderEngine->setBasic2DSprite(this->mapPositions[x][y]-glm::vec2(this->blockWidth*0.2, 0.0f),
                                                             glm::vec2(this->blockWidth*0.1f,this->blockHeight),
                                                             this->mapColors[x][y]*0.2f, 15, false);
                    }
                }
                if(y<this->heightBlockNum-1)
                {
                    if(this->mapData[x][y+1]==0)
                    {
                        this->renderEngine->setBasic2DSprite(this->mapPositions[x][y]+glm::vec2(0.0f, this->blockHeight*0.2),
                                                             glm::vec2(this->blockWidth,this->blockHeight*0.1f),
                                                             this->mapColors[x][y]*0.2f, 15, false);
                    }
                }
                if(y>0)
                {
                    if(this->mapData[x][y-1]==0)
                    {
                        this->renderEngine->setBasic2DSprite(this->mapPositions[x][y]-glm::vec2(0.0f, this->blockHeight*0.2),
                                                             glm::vec2(this->blockWidth,this->blockHeight*0.1f),
                                                             this->mapColors[x][y]*0.2f, 15, false);
                    }
                }
            }
            if(this->mapData[x][y]==2)
            {
                for(int i = 0; i<10; i++)
                {
                    this->renderEngine->setBasic2DSprite(this->mapPositions[x][y] + glm::vec2((float)(std::rand()%100)/100.0f,(float)(std::rand()%100)/100.0f),
                                                         glm::vec2(this->blockWidth*0.1f,this->blockHeight*0.1f),
                                                         this->mapColors[x][y]*0.8f, 15, false);
                }
            }
        }


    }

}


