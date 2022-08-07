
#include <TowerDefenseGame.h>

#include <GameEnemy.h>

TowerDefenseGame::TowerDefenseGame(RenderEngine* engine, ParticleEngine2D* partcEngine, AppEngine* app, InterfaceWidget* widget)
{
    this->renderEngine = engine;
    this->particleEngine = partcEngine;
    this->appEngine = app;
    this->activeWidget = widget;

    this->levelGenerator = new TowerDefenseGameLevelGenerator(engine);
    std::cout<<"refresing"<<std::endl;

    this->baseTextureNum = 15;
    this->lairTextureNum = 15;

}

TowerDefenseGame::~TowerDefenseGame()
{

}

void TowerDefenseGame::setLocations(){

    int mapWidth = this->levelGenerator->getWidthBlockNum();
    int mapHeight = this->levelGenerator->getHeightBlockNum();

    bool baseLocationFound = false;
    bool lairLocationFound = false;

    for(int i = 0;i<mapHeight;i++){

        if(!baseLocationFound){
            if(this->levelGenerator->getDataPoint(mapWidth-1, i)==1){
                baseLocationFound = true;
                this->baseLocation = this->levelGenerator->getPosition(mapWidth-1, i);

            }
        }

        if(!lairLocationFound){
            if(this->levelGenerator->getDataPoint(0, mapHeight-i)==1){
                lairLocationFound = true;
                this->lairLocation = this->levelGenerator->getPosition(0, mapHeight-i);
            }
        }
    }

}

void TowerDefenseGame::refreshGame()
{
    this->levelGenerator->generateNewMap();

    this->mapBlockWidth = this->levelGenerator->getBlockWidth();
    this->mapBlockHeight = this->levelGenerator->getBlockHeight();

    this->setLocations();

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

void TowerDefenseGame::setup(){

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
    }

}

void TowerDefenseGame::enemyUpdate()
{
    /*
    //enemies
    if(!this->bossBattle){
        this->enemyCounter -= this->renderEngine->getDeltaTime();
        if(this->enemyCounter<=0.0&&this->theEnemies.size()<this->enemyLimit)
        {
            float randVal = (float)rand()/RAND_MAX;
            enemyCounter=3.0;
            if(this->thePlayer->getExistence())
            {
                float enX = ((float)rand()/RAND_MAX)*width;
                float enY = ((float)rand()/RAND_MAX)*height/2;
                if(randVal<0.33)
                {
                    std::vector<weaponInfo*> info = {new weaponInfo{glm::vec2(1.0,0.4), glm::vec2(0.0),
                                                        glm::vec2(0.4,0.2), glm::vec2(1.0),false, 1.0, 0, 2}};
                    this->theEnemies.push_back(new GameEnemy(this->renderEngine, this, info, 1,(glm::vec2(enX-width/2,enY-height/2)+this->thePlayer->getPos()),
                                                           glm::vec2(100,100),100,1,50,2,20.0f,12.0f,3,1,1,glm::vec4(1.0,0.0,0.0,1.0), this->width*0.3f));
                }
                else if(randVal<0.66)
                {
                    std::vector<weaponInfo*> info = {new weaponInfo{glm::vec2(0.0), glm::vec2(0.0), glm::vec2(0.4,0.2), glm::vec2(1.0),false, 1.0, 0, 1}};
                    this->theEnemies.push_back(new GameEnemy(this->renderEngine, this, info, 2,(glm::vec2(enX-width/2,enY-height/2)+this->thePlayer->getPos()),
                                                           glm::vec2(100,100),100,1,50,2,5.0f,10.0f,5,0,0,glm::vec4(1.0,0.0,0.0,1.0), this->width*0.4f));
                }
                else if(randVal<1.0)
                {
                    std::vector<weaponInfo*> info = {new weaponInfo{glm::vec2(0.0), glm::vec2(0.0), glm::vec2(0.4,0.2), glm::vec2(1.0),false, 1.0, 0, 1}};
                    this->theEnemies.push_back(new GameEnemy(this->renderEngine, this, info, 3,(glm::vec2(enX-width/2,enY-height/2)+this->thePlayer->getPos()),
                                                           glm::vec2(100,100),100,1,50,2,30.0f,20.0f,6,1,1,glm::vec4(1.0,0.0,0.0,1.0), 20.0f));
                }
            }
        }
    }
    if(!this->bossBattle){

    }
    //enemies
    for(int e = this->theEnemies.size(); e--;)
    {
        if(thePlayer->getExistence())
        {
            this->theEnemies[e]->update();
            if(this->theEnemies[e]->getHp()<=0)
            {
                this->theEnemies[e]->deathEffect(this->theEnemies[e]->getPos(), 0.2,2);
                this->theEnemies.erase(this->theEnemies.begin()+e);
            }
        }
    }
*/
}

void TowerDefenseGame::mouseInput(){


}

void TowerDefenseGame::mainUpdate()
{
    if(this->gameRefresh)
    {
        this->refreshGame();
    }

    if(this->gameState!=GAME_MENU)
    {
        //variable and system update
        this->mouseInput();
        //background
        //update phase
        //particles
        //this->particleEngine->setRelativePos(this->getMiddlePos()-this->thePlayer->getRelativePos());

        //enemies
        this->enemyUpdate();
        //player
        if(this->gameState == GAME_ACTIVE){
            if(this->bossBattle && !this->bossAlive){


            }

        }
        //draw phase
    }
}

void TowerDefenseGame::renderAllies(){

    for(int i; i<this->theAllies.size();i++){

        this->theAllies[i]->render();

    }
}

void TowerDefenseGame::renderEnemies(){

    for(int i; i<this->theEnemies.size();i++){

        this->theEnemies[i]->render();

    }

}

void TowerDefenseGame::renderBuildings(){

    for(int i; i<this->theBuildings.size();i++){

        this->theBuildings[i]->render();

    }

}

void TowerDefenseGame::renderBase(){

    this->renderEngine->setBasic2DSprite(this->baseLocation, glm::vec2(this->mapBlockWidth, this->mapBlockHeight),
                                         glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), this->baseTextureNum, false);

}

void TowerDefenseGame::renderSpawn(){

    this->renderEngine->setBasic2DSprite(this->lairLocation, glm::vec2(this->mapBlockWidth, this->mapBlockHeight),
                                         glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), this->lairTextureNum, false);

}

void TowerDefenseGame::spritePhase()
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    //glClearColor(1.0,0.0,0.0,1.0);
    //glClear(GL_COLOR_BUFFER_BIT);
    //glViewport(0,0,this->width,this->height);
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

    this->renderEngine->getShaderProgram(this->renderEngine->BASIC_2D_SHADER, true)->use();
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void TowerDefenseGame::run()
{
    this->mainUpdate();
    this->spritePhase();
}

void addGameAlly();
void addBuilding();

unsigned int TowerDefenseGame::getFBO()
{

    return this->theFBO;
}

unsigned int TowerDefenseGame::getFBOTexture()
{

    return this->FBOTexture;
}

ParticleEngine2D* TowerDefenseGame::getParticleEngine(){

    return this->particleEngine;

}

void TowerDefenseGame::setWidth(int newVal){

    this->width = newVal;
}

    void TowerDefenseGame::setHeight(int newVal){

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

glm::vec2 TowerDefenseGame::getMiddlePos(){

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

void TowerDefenseGame::setBossState(bool newState){

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

void TowerDefenseGame::addWeaponType(float damage, float speed, float cost, float bSpeed, int textr, int bulletType, int drawW)
{

    this->weaponTypes.push_back(new GameWeapon(damage, speed, cost, bSpeed, textr, bulletType, drawW));
}

GameWeapon* TowerDefenseGame::getWeaponType(int index)
{
    return this->weaponTypes[index];
}

void TowerDefenseGame::addBullet(Bullet* theBullet, entityTYPE theType){

    if(theType == ALLY){
        this->allAllyProjectiles.push_back(theBullet);
    }
    else if(theType == ENEMY){
        this->allEnemyProjectiles.push_back(theBullet);
    }
    else if(theType == OTHER){
        this->allOtherProjectiles.push_back(theBullet);
    }
}

float TowerDefenseGame::getEnemyCounter()
{
    return this->enemyCounter;
}

int TowerDefenseGame::getEnemyLimit()
{
    return this->enemyLimit;
}

std::vector<GameEnemy*>& TowerDefenseGame::getEnemies()
{
    return this->theEnemies;
}

GameEnemy* TowerDefenseGame::getEnemy(int index){

    return this->theEnemies[index];
}
int TowerDefenseGame::getEnemyAmount(){

    return this->theEnemies.size();
}

void TowerDefenseGame::setGameSpeed(float newSpeed)
{
    this->gameSpeed = newSpeed;
}

void TowerDefenseGame::setLairTexture(int newVal){

    this->lairTextureNum = newVal;
}

void TowerDefenseGame::setBaseTexture(int newVal){

    this->baseTextureNum = newVal;
}

void TowerDefenseGame::setGameRefresh(int newRefresh)
{
    this->gameRefresh = newRefresh;
}

void TowerDefenseGame::setEnemyCounter(float newCounter)
{
    this->enemyCounter = newCounter;
}
void TowerDefenseGame::TowerDefenseGame::setEnemyLimit(int newLimit)
{
    this->enemyLimit = newLimit;
}

AppEngine* TowerDefenseGame::getApp(){

    this->appEngine;
}

TowerDefenseGameLevelGenerator* TowerDefenseGame::getLevelGenerator(){

    return this->levelGenerator;
}
