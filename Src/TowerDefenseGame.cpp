
#include <TowerDefenseGame.h>

#include <GameEnemy.h>
#include <DefenseBuilding.h>

bool operator==(const indexPair &left, const indexPair &right) noexcept
{
    return (left.x == right.x) && (left.y == right.y);
}

TowerDefenseGame::TowerDefenseGame(RenderEngine* engine, ParticleEngine2D* partcEngine, AppEngine* app, InterfaceWidget* widget)
{
    this->renderEngine = engine;
    this->particleEngine = partcEngine;
    this->appEngine = app;
    this->activeWidget = widget;

    this->width = engine->getWindowWidth();
    this->height = engine->getWindowHeight();

    this->levelGenerator = new TowerDefenseGameLevelGenerator(engine);
    this->widthBlockNum = 10;
    this->heightBlockNum = 10;
    this->mapType = 1;

    this->baseTextureNum = 15;
    this->lairTextureNum = 15;

    this->gameDifficulty = 1;

    this->gameState = GAME_MENU;

    this->towerChosen = false;
    this->chosenTowerCode = 0;

    this->crystalNum = this->defaultCrystalAmount;
    this->baseHealth = this->baseMaxHealth;

    this->roundCounter = this->roundBreakTime;

    this->enemiesSpawned = 0;

    this->unitPopupContent = new InterfaceLayout(this->renderEngine, 0, VERTICAL);
    this->nameLabel = new InterfaceBox(this->renderEngine, 101, "Turret", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f, false, 1.0f, 0.5f);
    this->unitPopupContent->addWidget(this->nameLabel);
    this->upgradeButton = new InterfaceButton(this->renderEngine, this->appEngine->getInterfaceEngine(), 102, "Upgrade", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    this->unitPopupContent->addWidget(this->upgradeButton);
    this->sellButton = new InterfaceButton(this->renderEngine, this->appEngine->getInterfaceEngine(), 103, "Sell", glm::vec4(0.4,0.4,0.4,1.0),glm::vec4(1.0,1.0,1.0,1.0), 1.0f);
    this->unitPopupContent->addWidget(this->sellButton);
}

TowerDefenseGame::~TowerDefenseGame()
{

}

bool TowerDefenseGame::check_cell(std::vector<glm::ivec4>& usedQueue)
{

    if(this->levelGenerator->getDataPoint(usedQueue[0].x, usedQueue[0].y) == 1)
    {
        return false;
    }
    indexPair keyPair{usedQueue[0].x, usedQueue[0].y};

    if ((this->visitedCells.find(keyPair) != this->visitedCells.end()))
    {
        return false;
    }
    this->visitedCells.emplace(keyPair, glm::ivec2(usedQueue[0].z, usedQueue[0].w));

    if(usedQueue[0].x == this->baseIndexX && usedQueue[0].y == this->baseIndexY)
    {
        return true;
    }
    if(usedQueue[0].y+1<this->levelGenerator->getHeightBlockNum())
    {
        usedQueue.push_back(glm::ivec4(usedQueue[0].x, usedQueue[0].y+1, usedQueue[0].x, usedQueue[0].y));
    }
    if(usedQueue[0].x+1<this->levelGenerator->getWidthBlockNum())
    {
        usedQueue.push_back(glm::ivec4(usedQueue[0].x+1, usedQueue[0].y, usedQueue[0].x, usedQueue[0].y));
    }
    if(usedQueue[0].y>0)
    {
        usedQueue.push_back(glm::ivec4(usedQueue[0].x, usedQueue[0].y-1, usedQueue[0].x, usedQueue[0].y));
    }
    if(usedQueue[0].x>0)
    {
        usedQueue.push_back(glm::ivec4(usedQueue[0].x-1, usedQueue[0].y, usedQueue[0].x, usedQueue[0].y));
    }

    return false;
}

void TowerDefenseGame::findShortestPath()
{

    this->baseIndexX = this->getLevelGenerator()->getXPosIndex(this->baseLocation.x);
    this->baseIndexY = this->getLevelGenerator()->getYPosIndex(this->baseLocation.y);
    this->lairIndexX = this->getLevelGenerator()->getXPosIndex(this->lairLocation.x);
    this->lairIndexY = this->getLevelGenerator()->getYPosIndex(this->lairLocation.y);

    std::vector<glm::ivec4> checkQueue;
    this->visitedCells.clear();
    checkQueue.push_back(glm::ivec4(lairIndexX, lairIndexY, lairIndexX, lairIndexY));
    int iteration = 0;
    bool pathCantBeFound = false;
    while(checkQueue.size() > 0)
    {
        if(this->check_cell(checkQueue))
        {
            break;
        }
        iteration += 1;
        //std::cout<<"pathfinding iteration: "<<iteration<<std::endl;
        if(iteration >= 10000)
        {
            this->shortestPath.clear();
            break;
        }
        checkQueue.erase(checkQueue.begin());
    }
    this->shortestPath.clear();
    glm::ivec2 cur_pos = glm::ivec2(this->baseIndexX, this->baseIndexY);
    bool positionExists = true;

    while(positionExists)
    {
        indexPair keyPair{cur_pos.x, cur_pos.y};
        if(!((cur_pos.x==this->lairIndexX)&&(cur_pos.y==this->lairIndexY)))
            if((this->visitedCells.find(keyPair) != this->visitedCells.end()))
            {
                this->shortestPath.insert(this->shortestPath.begin(), this->levelGenerator->getPosition(cur_pos.x, cur_pos.y));

                cur_pos = visitedCells[keyPair];
            }
            else
            {
                positionExists = false;
            }
        else
        {
            positionExists = false;
        }

    }

}

void TowerDefenseGame::setLocations()
{

    int mapWidth = this->levelGenerator->getWidthBlockNum();
    int mapHeight = this->levelGenerator->getHeightBlockNum();

    bool baseLocationFound = false;
    bool lairLocationFound = false;

    for(int i = 0; i<mapHeight; i++)
    {

        if(!baseLocationFound)
        {
            if(this->levelGenerator->getDataPoint(mapWidth-1, i)==0)
            {
                baseLocationFound = true;
                this->baseLocation = this->levelGenerator->getPosition(mapWidth-1, i);

            }
        }

        if(!lairLocationFound)
        {
            if(this->levelGenerator->getDataPoint(0, mapHeight-1-i)==0)
            {
                lairLocationFound = true;
                this->lairLocation = this->levelGenerator->getPosition(0, mapHeight-1-i);
            }
        }
    }

    this->findShortestPath();
    for(int i = 0; i<this->shortestPath.size(); i++)
    {

        std::cout<<this->shortestPath[i].x<<" "<<this->shortestPath[i].y<<std::endl;
    }
}

void TowerDefenseGame::refreshGame()
{
    this->levelGenerator->setWidthBlockNum(this->widthBlockNum);
    this->levelGenerator->setHeightBlockNum(this->heightBlockNum);
    this->levelGenerator->generateNewMap();
    this->mapBlockWidth = this->levelGenerator->getBlockWidth();
    this->mapBlockHeight = this->levelGenerator->getBlockHeight();
    this->setLocations();

    this->theEnemies.clear();
    this->theAllies.clear();
    this->theBuildings.clear();

    this->allAllyProjectiles.clear();
    this->allEnemyProjectiles.clear();

    this->towerChosen = false;
    this->chosenTowerCode = 0;
    this->crystalNum = this->defaultCrystalAmount;

    this->baseHealth = this->baseMaxHealth;
}

void TowerDefenseGame::setupFramebuffer()
{
    //rbo
    glGenRenderbuffers(1,&this->theRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, this->theRBO);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,this->width,this->height);
    glBindRenderbuffer(GL_RENDERBUFFER,0);

    //FBOs
    glGenFramebuffers(1,&this->theFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, this->theFBO);
    //texture
    glGenTextures(1, &this->FBOTexture);
    glBindTexture(GL_TEXTURE_2D,this->FBOTexture);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA16F,this->width,this->height,0,GL_RGBA,GL_FLOAT,NULL);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,this->FBOTexture,0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,this->theRBO);
    unsigned int attachment = GL_COLOR_ATTACHMENT0;
    glDrawBuffers(1, &attachment);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout<<"ERROR:FRAMEBUFFER1:Framebuffer is not complete!"<<std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void TowerDefenseGame::setup()
{

    this->levelGenerator->setWidth(this->width);
    this->levelGenerator->setHeight(this->height);
    this->setupFramebuffer();
    this->refreshGame();
}

void TowerDefenseGame::systemInput()
{
    if(this->gameState==GAME_ACTIVE)
    {
        if(glfwGetKey(this->renderEngine->getWindow(),GLFW_KEY_A)==GLFW_PRESS)
        {

        }
        else if(glfwGetKey(this->renderEngine->getWindow(),GLFW_KEY_D)==GLFW_PRESS)
        {


        }
        if(glfwGetKey(this->renderEngine->getWindow(),GLFW_KEY_W)==GLFW_PRESS)
        {

        }

        if(this->towerChosen)
        {
            if(glfwGetMouseButton(this->renderEngine->getWindow(),GLFW_MOUSE_BUTTON_RIGHT)==GLFW_PRESS)
            {
                this->towerChosen = false;
            }
        }
    }

}

void TowerDefenseGame::enemyUpdate()
{
    //enemies
    if(!this->bossBattle)
    {
        if(this->enemiesSpawned<this->enemyLimit*this->currRound)
        {
            this->enemySpawnCounter -= this->appEngine->getDeltaTime();
            if(this->enemySpawnCounter<=0)
            {
                //std::cout<<"enemySpawnCounter: "<<this->enemySpawnCounter<<std::endl;
                float randVal = (float)rand()/RAND_MAX;
                this->enemySpawnCounter=this->enemySpawnDelay;
                if(randVal<0.33)
                {
                    std::vector<weaponInfo*> info = {new weaponInfo{glm::vec2(1.0,0.4), glm::vec2(0.0),
                                glm::vec2(0.4,0.2), glm::vec2(1.0),false, 1.0, 0, 2}
                    };

                    this->theEnemies.push_back(new GameEnemy(this->renderEngine, this, 1, 2, info,
                                               (this->levelGenerator->getBlockWidth()+this->levelGenerator->getBlockHeight())/2,
                                               this->lairLocation,
                                               glm::vec2(this->levelGenerator->getBlockWidth(),this->levelGenerator->getBlockHeight()),
                                               glm::vec4(1.0,0.0,0.0,1.0), 5.0f,
                                               100,1,50,2,1));
                }
                else if(randVal<0.66)
                {
                    std::vector<weaponInfo*> info = {new weaponInfo{glm::vec2(0.0), glm::vec2(0.0), glm::vec2(0.4,0.2), glm::vec2(1.0),false, 1.0, 0, 1}};
                    this->theEnemies.push_back(new GameEnemy(this->renderEngine, this, 2, 4, info,
                                               (this->levelGenerator->getBlockWidth()+this->levelGenerator->getBlockHeight())/2,
                                               this->lairLocation,
                                               glm::vec2(this->levelGenerator->getBlockWidth(),this->levelGenerator->getBlockHeight()),
                                               glm::vec4(1.0,0.0,0.0,1.0), 5.0f,
                                               100,1,50,2,1));
                }
                else if(randVal<1.0)
                {
                    std::vector<weaponInfo*> info = {new weaponInfo{glm::vec2(0.0), glm::vec2(0.0), glm::vec2(0.4,0.2), glm::vec2(1.0),false, 1.0, 0, 1}};
                    this->theEnemies.push_back(new GameEnemy(this->renderEngine, this, 3, 5, info,\
                                               (this->levelGenerator->getBlockWidth()+this->levelGenerator->getBlockHeight())/2,
                                               this->lairLocation,
                                               glm::vec2(this->levelGenerator->getBlockWidth(),this->levelGenerator->getBlockHeight()),
                                               glm::vec4(1.0,0.0,0.0,1.0), 5.0f,
                                               100,1,50,2,1));
                }
                this->theEnemies[this->theEnemies.size()-1]->assignTargetPos(this->baseLocation);
                this->enemiesSpawned++;
            }
        }
    }
    if(this->bossBattle)
    {

    }
    //std::cout<<"enemy update2"<<std::endl;
    //enemies
    for(int e = this->theEnemies.size(); e--;)
    {
        if(this->gameState == GAME_ACTIVE)
        {
            if(this->theEnemies[e]->getExistence()){
                this->theEnemies[e]->update();
                if(this->theEnemies[e]->getHp()<=0)
                {
                    this->theEnemies[e]->deathEffect(this->theEnemies[e]->getPos(), 0.2,2);
                    this->crystalNum += this->currRound;
                    this->appEngine->getInterfaceEngine()->getWidget(25)->setText(std::to_string(this->crystalNum));
                    this->theEnemies[e]->setExistence(false);
                }

                if(glm::length(this->baseLocation-this->theEnemies[e]->getPos())<0.25*this->mapBlockWidth)
                {
                    this->baseHealth -= this->currRound;
                    this->theEnemies[e]->deathEffect(this->theEnemies[e]->getPos(), 0.2,2);
                    this->theEnemies[e]->setExistence(false);
                }
            }
        }
    }

}

void TowerDefenseGame::alliesUpdate()
{

    for(int i=0; i<this->theAllies.size(); i++)
    {

        this->theAllies[i]->update();

    }

}

void TowerDefenseGame::buildingUpdate()
{

    for(int i=0; i<this->theBuildings.size(); i++)
    {

        this->theBuildings[i]->update();

    }

}
/*
void TowerDefenseGame::removeBullet(int index, entityTYPE theType)
{

    if(this->shotBullets[index]->type==1){
        this->theGame->getParticleEngine()->createParticleEffect(this->shotBullets[index]->pos,
                0.2f, 0.2f,10,
                this->shotBullets[index]->siz,this->shotBullets[index]->defaultSpeed/2,
                2.0f*this->shotBullets[index]->siz,
                this->shotBullets[index]->col,
                16,1,0);
    }
    else if(this->shotBullets[index]->type==2){

        for(int c = 0; c<10;c++){

            Bullet* bull = new Bullet{this->shotBullets[index]->damage,
                      this->shotBullets[index]->pos,
                      this->hitbox/20.0f,
                      this->shotBullets[index]->defaultSpeed,
                      glm::vec2(cos(c*36*PI/180),sin(c*36*PI/180))*this->shotBullets[index]->defaultSpeed,
                      this->shotBullets[index]->col,16, 1};

            this->shotBullets.push_back(bull);

        }

    }
    else if(this->shotBullets[index]->type==3){

        for(int c = 0; c<30;c++){
            Bullet* bull = new Bullet{this->shotBullets[index]->damage,
                      this->shotBullets[index]->pos,
                      this->hitbox/20.0f,
                      this->shotBullets[index]->defaultSpeed,
                      glm::vec2(cos(c*12*PI/180),sin(c*12*PI/180))*this->shotBullets[index]->defaultSpeed,
                      this->shotBullets[index]->col,16, 1};

            this->shotBullets.push_back(bull);

        }

    }
    this->shotBullets.erase(this->shotBullets.begin()+index);
}
*/
void TowerDefenseGame::projectileUpdate()
{

    if(this->allAllyProjectiles.size()>0)
    {
        for(int i=this->allAllyProjectiles.size(); i--;)
        {
            if(this->allAllyProjectiles[i]->target->getExistence()){
                this->allAllyProjectiles[i]->direction = glm::normalize(this->allAllyProjectiles[i]->target->getPos()-this->allAllyProjectiles[i]->pos);
            }
            this->allAllyProjectiles[i]->pos+=(this->allAllyProjectiles[i]->direction*this->allAllyProjectiles[i]->defaultSpeed*this->appEngine->getDeltaTime()*this->gameSpeed);

            bool enemyHit = false;
            for(int n = this->theEnemies.size(); n--;)
            {

                if(glm::length(this->allAllyProjectiles[i]->pos-this->theEnemies[n]->getPos())<0.25*this->mapBlockWidth)
                {

                    this->theEnemies[n]->setHp(this->theEnemies[n]->getHp()-this->allAllyProjectiles[i]->damage);

                    this->allAllyProjectiles.erase(this->allAllyProjectiles.begin()+i);
                    enemyHit = true;
                    break;
                }

            }

            if(enemyHit)
            {
                break;
            }
            if(this->allAllyProjectiles[i]->pos.x<0||
                    this->allAllyProjectiles[i]->pos.x>this->width||
                    this->allAllyProjectiles[i]->pos.y<0||
                    this->allAllyProjectiles[i]->pos.y>this->height)
            {

                this->allAllyProjectiles.erase(this->allAllyProjectiles.begin()+i);
                break;

            }

        }
    }
    if(this->allEnemyProjectiles.size()>0)
    {
        for(int i = this->allEnemyProjectiles.size(); i--;)
        {
            if(this->allEnemyProjectiles[i]->target->getExistence()){
                this->allEnemyProjectiles[i]->direction = glm::normalize(this->allEnemyProjectiles[i]->target->getPos()-this->allEnemyProjectiles[i]->pos);
            }
            this->allEnemyProjectiles[i]->pos+=(this->allEnemyProjectiles[i]->direction*this->allEnemyProjectiles[i]->defaultSpeed*this->appEngine->getDeltaTime()*this->gameSpeed);

            bool allyHit = false;
            for(int n = this->theAllies.size(); n--;)
            {

                if(glm::length(this->allEnemyProjectiles[i]->pos-this->theAllies[n]->getPos())<0.25*this->mapBlockWidth)
                {

                    this->theAllies[n]->setHp(this->theAllies[n]->getHp()-this->allEnemyProjectiles[i]->damage);

                    this->allEnemyProjectiles.erase(this->allEnemyProjectiles.begin()+i);
                    allyHit = true;
                    break;
                }
            }

            if(allyHit)
            {
                break;
            }
            if(this->allEnemyProjectiles[i]->pos.x<0||
                    this->allEnemyProjectiles[i]->pos.x>this->width||
                    this->allEnemyProjectiles[i]->pos.y<0||
                    this->allEnemyProjectiles[i]->pos.y>this->height)
            {

                this->allEnemyProjectiles.erase(this->allEnemyProjectiles.begin()+i);
                break;

            }
        }
    }

}

void TowerDefenseGame::handleMouseToggle(float xRealPos, float yRealPos)
{

    if(this->towerChosen)
    {
        int xIndexVal = this->getLevelGenerator()->getXPosIndex(xRealPos);
        int yIndexVal = this->getLevelGenerator()->getYPosIndex(yRealPos);
        float xPos = this->mapBlockWidth*(0.5f+(float)xIndexVal);
        float yPos = this->mapBlockHeight*(0.5f+(float)yIndexVal);
        if(this->allTowerInfo[this->chosenTowerCode].type==1)
        {
            if(this->levelGenerator->getDataPoint(xIndexVal, yIndexVal) == 1)
            {
                this->addGameBuilding(this->chosenTowerCode, xPos, yPos);
                this->crystalNum -= this->allTowerInfo[this->chosenTowerCode].cost;
            }
        }
        else if(this->allTowerInfo[this->chosenTowerCode].type==2)
        {
            if(this->levelGenerator->getDataPoint(xIndexVal, yIndexVal) != 1)
            {
                this->addGameAlly(this->chosenTowerCode, xPos, yPos);
                this->crystalNum -= this->allTowerInfo[this->chosenTowerCode].cost;
            }

        }

        this->appEngine->getInterfaceEngine()->getWidget(25)->setText(std::to_string(this->crystalNum));
        this->towerChosen = false;
    }
    else{
            bool buildingChosen = true;

            glm::vec2 chosenBlockPos = this->getLevelGenerator()->getPosition(this->getLevelGenerator()->getXPosIndex(xRealPos),
                                                                              this->getLevelGenerator()->getYPosIndex(yRealPos));
            for(int i=0; i<this->theBuildings.size(); i++)
            {
                if(this->theBuildings[i]->getPos().x == chosenBlockPos.x &&
                   this->theBuildings[i]->getPos().y == chosenBlockPos.y){
                    buildingChosen = false;
                    this->modificationIndex = i;
                    this->buildingModificationOccuring = true;
                    this->allyModificationOccuring = false;
                    this->nameLabel->setText("Building "+std::to_string(this->theBuildings[i]->getType()));
                    this->appEngine->getInterfaceEngine()->getActiveScreen()->addPopup((chosenBlockPos.x+this->levelGenerator->getBlockWidth()*1.5f)/this->renderEngine->getWindowWidth(),
                                                                                        yRealPos/this->renderEngine->getWindowHeight(),
                                                                                        this->levelGenerator->getBlockWidth()*2.0f/this->renderEngine->getWindowWidth(),
                                                                                        this->levelGenerator->getBlockHeight()*3.0f/this->renderEngine->getWindowHeight(),
                                                                                        this->unitPopupContent);
                }
            }

            if(buildingChosen){
                for(int i=0; i<this->theAllies.size(); i++)
                {

                }
            }
    }

}

void TowerDefenseGame::mouseInput()
{

    if(this->towerChosen)
    {
        this->chosenTowerIndexPos.x = this->getLevelGenerator()->getXPosIndex(this->width*(this->appEngine->getMouseX()-(this->activeWidget->getRealX()-this->activeWidget->getRealWidth()/2))/this->activeWidget->getRealWidth());
        this->chosenTowerIndexPos.y = this->getLevelGenerator()->getYPosIndex(this->height*(this->appEngine->getMouseY()-(this->activeWidget->getRealY()-this->activeWidget->getRealHeight()/2))/this->activeWidget->getRealHeight());
    }

    if(this->activeWidget->checkToggle())
    {
        glm::vec2 thePos = this->activeWidget->getActiveToggledPos();

        this->handleMouseToggle((float)this->width*thePos.x, (float)this->height*thePos.y);

        this->activeWidget->setToggle(false);

    }

}

void TowerDefenseGame::paceUpdate()
{
    if(this->gameState == GAME_INACTIVE)
    {

        this->roundSecCounter -= this->appEngine->getDeltaTime();
        if(this->roundSecCounter<=0)
        {
            this->roundSecCounter = 1.0;
            this->roundCounter--;
            if(this->roundCounter<0)
            {
                this->gameState = GAME_ACTIVE;
                this->appEngine->getInterfaceEngine()->getWidget(22)->setText("Go");
            }
            else
            {
                this->appEngine->getInterfaceEngine()->getWidget(22)->setText(std::to_string(this->roundCounter));
            }
        }

    }
    else if(this->gameState == GAME_ACTIVE)
    {
        //std::cout<<"checking enemies: "<<this->enemiesSpawned<<" "<<this->enemyLimit*this->currRound<<" "<<this->theEnemies.size()<<std::endl;
        if(this->enemiesSpawned>=this->enemyLimit*this->currRound&&this->theEnemies.size()==0)
        {
            this->currRound++;
            this->appEngine->getInterfaceEngine()->getWidget(19)->setText(std::to_string(this->currRound));
            this->enemiesSpawned = 0;
            this->roundCounter = this->roundBreakTime;
            this->roundSecCounter = 1.0f;
            this->appEngine->getInterfaceEngine()->getWidget(22)->setText("Break");
            this->gameState = GAME_INACTIVE;
        }
    }

}

void TowerDefenseGame::mainUpdate()
{

    if(this->gameState!=GAME_MENU)
    {
        //variable and system update
        this->systemInput();
        this->mouseInput();

        //game management
        this->paceUpdate();

        //particles
        //this->particleEngine->setRelativePos(this->getMiddlePos()-this->thePlayer->getRelativePos());
        this->projectileUpdate();
        //player
        if(this->gameState == GAME_ACTIVE)
        {
            //enemies
            this->enemyUpdate();
            //buildings
            this->buildingUpdate();
            if(this->bossBattle && !this->bossAlive)
            {


            }

            if(this->baseHealth<=0)
            {
                this->gameState = GAME_LOST;
                this->appEngine->getInterfaceEngine()->getWidget(22)->setText("LOST");
            }

        }
        //draw phase
    }
}

void TowerDefenseGame::renderAllies()
{

    for(int i=0; i<this->theAllies.size(); i++)
    {

        this->theAllies[i]->render();

    }
}

void TowerDefenseGame::renderEnemies()
{

    for(int i=0; i<this->theEnemies.size(); i++)
    {

        this->theEnemies[i]->render();

    }

}

void TowerDefenseGame::renderBuildings()
{

    for(int i=0; i<this->theBuildings.size(); i++)
    {

        this->theBuildings[i]->render();

    }

}

void TowerDefenseGame::renderProjectiles()
{

    for(int i=0; i<this->allAllyProjectiles.size(); i++)
    {

        this->renderEngine->setBasic2DSprite(this->allAllyProjectiles[i]->pos, this->allAllyProjectiles[i]->siz,
                                             this->allAllyProjectiles[i]->col,this->allAllyProjectiles[i]->textureNum,false);

    }

    for(int i=0; i<this->allEnemyProjectiles.size(); i++)
    {

        this->renderEngine->setBasic2DSprite(this->allEnemyProjectiles[i]->pos, this->allEnemyProjectiles[i]->siz,
                                             this->allEnemyProjectiles[i]->col,this->allEnemyProjectiles[i]->textureNum,false);

    }

}

void TowerDefenseGame::renderBase()
{

    this->renderEngine->setBasic2DSprite(this->baseLocation, glm::vec2(this->mapBlockWidth, this->mapBlockHeight),
                                         glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), this->baseTextureNum, false);

    this->renderEngine->setBasic2DSprite(glm::vec2(this->baseLocation.x+this->mapBlockWidth*0.5f*((float)this->baseHealth/this->baseMaxHealth-1),
                                         this->baseLocation.y+this->mapBlockHeight*0.6),
                                         glm::vec2(this->mapBlockWidth*this->baseHealth/this->baseMaxHealth, this->mapBlockHeight*0.2),
                                         glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), 15, false);

    this->renderEngine->setBasic2DSprite(glm::vec2(this->baseLocation.x+this->mapBlockWidth*0.5f*((float)this->baseHealth/this->baseMaxHealth),
                                         this->baseLocation.y+this->mapBlockHeight*0.6),
                                         glm::vec2(this->mapBlockWidth*(1-(float)this->baseHealth/this->baseMaxHealth), this->mapBlockHeight*0.2),
                                         glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), 15, false);


}

void TowerDefenseGame::renderSpawn()
{

    this->renderEngine->setBasic2DSprite(this->lairLocation, glm::vec2(this->mapBlockWidth, this->mapBlockHeight),
                                         glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), this->lairTextureNum, false);

}

void TowerDefenseGame::renderNewChoice()
{
    if(this->towerChosen)
    {
        if(this->chosenTowerIndexPos.x<this->levelGenerator->getWidthBlockNum() && this->chosenTowerIndexPos.y<this->levelGenerator->getHeightBlockNum())
        {
            this->renderEngine->setBasic2DSprite(glm::vec2(this->mapBlockWidth*(0.5f+this->chosenTowerIndexPos.x),
                                                 this->mapBlockHeight*(0.5f+this->chosenTowerIndexPos.y)),
                                                 glm::vec2(this->mapBlockWidth, this->mapBlockHeight),
                                                 glm::vec4(0.0f, 0.0f, 1.0f, 0.5f), this->allTowerInfo[this->chosenTowerCode].textureNum, false);
        }
    }

}

void TowerDefenseGame::spritePhase()
{
    if(this->gameState!=GAME_MENU)
    {
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        glBindFramebuffer(GL_FRAMEBUFFER,this->theFBO);

        glClearColor(1.0,0.0,0.0,1.0);
        glViewport(0,0,this->width,this->height);

        this->renderEngine->clearVerts(this->renderEngine->BASIC_2D_SHADER, true);

        //this->renderEngine->setBasic2DSprite(glm::vec2(0.5), glm::vec2(1.0), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

        this->levelGenerator->render();
        this->renderBase();
        this->renderSpawn();
        this->renderBuildings();
        this->renderEnemies();
        this->renderAllies();
        this->renderProjectiles();
        this->renderNewChoice();

        this->renderEngine->getShaderProgram(this->renderEngine->BASIC_2D_SHADER, true)->use();
        glBindFramebuffer(GL_FRAMEBUFFER,0);
    }
}

void TowerDefenseGame::run()
{
    //std::cout<<"run1"<<std::endl;
    this->mainUpdate();
    //std::cout<<"run2"<<std::endl;
    this->spritePhase();
    //std::cout<<"run3"<<std::endl;
}

void TowerDefenseGame::addGameAlly(int code, float realX, float realY)
{

    std::cout<<"adding ally"<<std::endl;
    int xIndex = this->getLevelGenerator()->getXPosIndex(realX);
    int yIndex = this->getLevelGenerator()->getYPosIndex(realY);
    if(code==6)
    {
        std::vector<weaponInfo*> info = {new weaponInfo{glm::vec2(0.5,0.5), glm::vec2(0.0),
                    glm::vec2(0.5f),
                    glm::vec2(1.0),false, 1.0, 0, 1}
        };
        this->theBuildings.push_back(new DefenseBuilding(this->renderEngine, this, info,
                                     glm::vec2(xIndex, yIndex), glm::vec2(realX, realY),
                                     glm::vec2(this->levelGenerator->getBlockWidth(),this->levelGenerator->getBlockHeight()),
                                     glm::vec4(0.0, 0.0, 1.0, 1.0), code, code, 10.0f));

    }
    else if(code==7)
    {
        std::vector<weaponInfo*> info = {new weaponInfo{glm::vec2(0.5,0.5), glm::vec2(0.0),
                    glm::vec2(0.5f),
                    glm::vec2(1.0),false, 1.0, 0, 1}
        };
        this->theBuildings.push_back(new DefenseBuilding(this->renderEngine, this, info,
                                     glm::vec2(xIndex, yIndex), glm::vec2(realX, realY),
                                     glm::vec2(this->levelGenerator->getBlockWidth(),this->levelGenerator->getBlockHeight()),
                                     glm::vec4(0.0, 0.0, 1.0, 1.0), code, code, 5.0f));

    }
    else if(code==8)
    {
        std::vector<weaponInfo*> info = {new weaponInfo{glm::vec2(0.5,0.5), glm::vec2(0.0),
                    glm::vec2(0.5f),
                    glm::vec2(1.0),false, 1.0, 0, 2}
        };
        this->theBuildings.push_back(new DefenseBuilding(this->renderEngine, this, info,
                                     glm::vec2(xIndex, yIndex), glm::vec2(realX, realY),
                                     glm::vec2(this->levelGenerator->getBlockWidth(),this->levelGenerator->getBlockHeight()),
                                     glm::vec4(0.0, 0.0, 1.0, 1.0), code, code, 15.0f));

    }

}

void TowerDefenseGame::addGameBuilding(int code, float realX, float realY)
{
    std::cout<<"adding building"<<std::endl;
    int xIndex = this->getLevelGenerator()->getXPosIndex(realX);
    int yIndex = this->getLevelGenerator()->getYPosIndex(realY);
    if(code==1)
    {
        std::vector<weaponInfo*> info = {new weaponInfo{glm::vec2(0.5,0.5), glm::vec2(0.0),
                    glm::vec2(0.5f),
                    glm::vec2(1.0),false, 1.0, 0, 1}
        };
        this->theBuildings.push_back(new DefenseBuilding(this->renderEngine, this, info,
                                     glm::vec2(xIndex, yIndex), glm::vec2(realX, realY),
                                     glm::vec2(this->levelGenerator->getBlockWidth(),this->levelGenerator->getBlockHeight()),
                                     glm::vec4(0.0, 0.0, 1.0, 1.0), this->allTowerInfo[code].textureNum, code, 10.0f));

    }
    else if(code==2)
    {
        std::vector<weaponInfo*> info = {new weaponInfo{glm::vec2(0.5,0.5), glm::vec2(0.0),
                    glm::vec2(0.5f),
                    glm::vec2(1.0),false, 1.0, 0, 1}
        };
        this->theBuildings.push_back(new DefenseBuilding(this->renderEngine, this, info,
                                     glm::vec2(xIndex, yIndex), glm::vec2(realX, realY),
                                     glm::vec2(this->levelGenerator->getBlockWidth(),this->levelGenerator->getBlockHeight()),
                                     glm::vec4(0.0, 0.0, 1.0, 1.0), this->allTowerInfo[code].textureNum, code, 5.0f));

    }
    else if(code==3)
    {
        std::vector<weaponInfo*> info = {new weaponInfo{glm::vec2(0.5,0.5), glm::vec2(0.0),
                    glm::vec2(0.5f),
                    glm::vec2(1.0),false, 1.0, 0, 2}
        };
        this->theBuildings.push_back(new DefenseBuilding(this->renderEngine, this, info,
                                     glm::vec2(xIndex, yIndex), glm::vec2(realX, realY),
                                     glm::vec2(this->levelGenerator->getBlockWidth(),this->levelGenerator->getBlockHeight()),
                                     glm::vec4(0.0, 0.0, 1.0, 1.0), this->allTowerInfo[code].textureNum, code, 15.0f));

    }

}

void TowerDefenseGame::removeBuilding(float realX, float realY)
{
    int xIndex = this->getLevelGenerator()->getXPosIndex(realX);
    int yIndex = this->getLevelGenerator()->getYPosIndex(realY);
    for(int i=0; i<this->theBuildings.size(); i++)
    {

        glm::vec2 buildPos = this->theBuildings[i]->getPos();
        if(xIndex == this->getLevelGenerator()->getXPosIndex(buildPos.x) &&
                yIndex == this->getLevelGenerator()->getYPosIndex(buildPos.y))
        {

            this->theBuildings.erase(this->theBuildings.begin()+i);
        }

    }

}
void createTowerPopup()
{



}
void TowerDefenseGame::sellChosenTower()
{
    if(this->buildingModificationOccuring)
    {
        this->crystalNum += this->allTowerInfo[this->theBuildings[this->modificationIndex]->getType()].cost*0.8f;
        this->theBuildings.erase(this->theBuildings.begin()+this->modificationIndex);
        this->appEngine->getInterfaceEngine()->getActiveScreen()->removeLastPopup();

    }
    else if(this->allyModificationOccuring)
    {

    }
    this->appEngine->getInterfaceEngine()->getWidget(25)->setText(std::to_string(this->crystalNum));

}
void TowerDefenseGame::upgradeChosenTower()
{
    if(this->buildingModificationOccuring)
    {
        if(this->allTowerInfo[this->theBuildings[this->modificationIndex]->getType()].upgradeCost<this->crystalNum){
            this->theBuildings[this->modificationIndex]->upgrade();
            this->crystalNum -= this->allTowerInfo[this->theBuildings[this->modificationIndex]->getType()].upgradeCost;
        }
    }
    else if(this->allyModificationOccuring)
    {

    }

    this->appEngine->getInterfaceEngine()->getWidget(25)->setText(std::to_string(this->crystalNum));

}

unsigned int TowerDefenseGame::getFBO()
{

    return this->theFBO;
}

unsigned int TowerDefenseGame::getFBOTexture()
{

    return this->FBOTexture;
}

ParticleEngine2D* TowerDefenseGame::getParticleEngine()
{

    return this->particleEngine;

}

void TowerDefenseGame::setWidth(int newVal)
{

    this->width = newVal;
}

void TowerDefenseGame::setHeight(int newVal)
{

    this->height = newVal;
}

int TowerDefenseGame::getWidth()
{

    return this->width;

}

int TowerDefenseGame::getHeight()
{

    return this->height;

}

glm::vec2 TowerDefenseGame::getMiddlePos()
{

    return glm::vec2(this->width/2, this->height/2);

}

gameSTATE TowerDefenseGame::getGameState()
{
    return this->gameState;
}

int TowerDefenseGame::getPlayMode()
{
    return this->playMode;
}

void TowerDefenseGame::setGameState(gameSTATE newState)
{
    this->gameState = newState;
}

void TowerDefenseGame::setPlayMode(int newMode)
{
    this->playMode = newMode;
}

void TowerDefenseGame::setBossState(bool newState)
{

    this->bossAlive = newState;

}

float TowerDefenseGame::getGameSpeed()
{
    return this->gameSpeed;
}

int TowerDefenseGame::getGameRefresh()
{
    return this->gameRefresh;
}

double TowerDefenseGame::getMouseX()
{
    return this->mouseX;
}
double TowerDefenseGame::getMouseY()
{
    return this->mouseY;
}

void TowerDefenseGame::chooseTower(int newVal)
{
    if(this->crystalNum >= this->allTowerInfo[newVal].cost)
    {
        this->towerChosen = true;
        this->chosenTowerCode = newVal;
    }

}

bool TowerDefenseGame::isTowerChosen()
{

    return this->towerChosen;

}

void TowerDefenseGame::setTowerChoice(bool newVal)
{

    this->towerChosen = newVal;

}

void TowerDefenseGame::addWeaponType(float damage, float speed, float cost, float bSpeed, int textr, int bulletType, int drawW)
{

    this->weaponTypes.push_back(new GameWeapon(damage, speed, cost, bSpeed, textr, bulletType, drawW));
}

GameWeapon* TowerDefenseGame::getWeaponType(int index)
{
    return this->weaponTypes[index];
}

void TowerDefenseGame::addTowerInfo(int code, towerInfo newInfo)
{

    this->allTowerInfo.emplace(code, newInfo);

}

void TowerDefenseGame::addBullet(Bullet* theBullet, entityTYPE theType)
{

    if(theType == ALLY)
    {
        this->allAllyProjectiles.push_back(theBullet);
    }
    else if(theType == ENEMY)
    {
        this->allEnemyProjectiles.push_back(theBullet);
    }
}

float TowerDefenseGame::getEnemyCounter()
{
    return this->enemySpawnCounter;
}

int TowerDefenseGame::getEnemyLimit()
{
    return this->enemyLimit;
}

std::vector<GameAlly*>& TowerDefenseGame::getAllies()
{

    return this->theAllies;

}

std::vector<GameEnemy*>& TowerDefenseGame::getEnemies()
{
    return this->theEnemies;
}

std::vector<DefenseBuilding*>& TowerDefenseGame::getBuildings()
{

    return this->theBuildings;

}

GameEnemy* TowerDefenseGame::getEnemy(int index)
{

    return this->theEnemies[index];
}
int TowerDefenseGame::getEnemyAmount()
{

    return this->theEnemies.size();
}

void TowerDefenseGame::setGameSpeed(float newSpeed)
{
    this->gameSpeed = newSpeed;
}

void TowerDefenseGame::setLairTexture(int newVal)
{

    this->lairTextureNum = newVal;
}

void TowerDefenseGame::setBaseTexture(int newVal)
{

    this->baseTextureNum = newVal;
}

void TowerDefenseGame::setGameRefresh(int newRefresh)
{
    this->gameRefresh = newRefresh;
}

void TowerDefenseGame::setEnemyCounter(float newCounter)
{
    this->enemySpawnCounter = newCounter;
}
void TowerDefenseGame::TowerDefenseGame::setEnemyLimit(int newLimit)
{
    this->enemyLimit = newLimit;
}

int TowerDefenseGame::getGameDifficulty()
{

    return this->gameDifficulty;

}

int TowerDefenseGame::getMapType()
{

    return this->mapType;

}
int TowerDefenseGame::getMapWidthNum()
{

    return this->widthBlockNum;

}
int TowerDefenseGame::getMapHeightNum()
{

    return this->heightBlockNum;

}

void TowerDefenseGame::setGameDifficulty(int newVal)
{

    this->gameDifficulty = newVal;

}
void TowerDefenseGame::setMapType(int newVal)
{

    this->mapType = newVal;

}
void TowerDefenseGame::setMapWidthNum(int newVal)
{

    this->widthBlockNum = newVal;

}
void TowerDefenseGame::setMapHeightNum(int newVal)
{

    this->heightBlockNum = newVal;

}

AppEngine* TowerDefenseGame::getApp()
{

    return this->appEngine;
}

TowerDefenseGameLevelGenerator* TowerDefenseGame::getLevelGenerator()
{

    return this->levelGenerator;
}

float TowerDefenseGame::getMapBlockWidth()
{

    return this->mapBlockWidth;
}
float TowerDefenseGame::getMapBlockHeight()
{

    return this->mapBlockHeight;
}

glm::vec2 TowerDefenseGame::getShortestPathPoint(int index)
{

    if(index<this->shortestPath.size())
    {
        return this->shortestPath[index];
    }
    else{
        return glm::vec2(0.0f);
    }
}
