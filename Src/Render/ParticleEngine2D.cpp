
#include <Render/ParticleEngine2D.h>

ParticleEngine2D::ParticleEngine2D(RenderEngine* engine, AppEngine* app){

    this->renderEngine = engine;
    this->theApp = app;

    this->renderEngine->getShaderProgram(this->renderEngine->BASIC_2D_SHADER, true)->addPipeline();
    this->shaderPipelineNum = this->renderEngine->getShaderProgram(this->renderEngine->BASIC_2D_SHADER, true)->getVerticesListSize()-1;

}

ParticleEngine2D::~ParticleEngine2D(){



}

void ParticleEngine2D::particleSetup(int particleStorageSize)
{
    this->particlesNr = particleStorageSize;
}

int ParticleEngine2D::firstUnusedParticle(int type, int index)
{
    if(type==1)
    {
        for(int m = lastUsedParticle; m<particlesNr; m++)
        {
            if(this->temporaryParticleEffects[index]->particles[m].life<=0.0)
            {
                lastUsedParticle=m;
                return m;
            }
        }
        for(int m =0; m<lastUsedParticle; m++)
        {
            if(this->temporaryParticleEffects[index]->particles[m].life<=0.0)
            {
                lastUsedParticle=m;
                return m;
            }
        }
    }
    else if(type==2)
    {
        for(int m = lastUsedParticle; m<particlesNr; m++)
        {
            if(this->constantParticleEffects[index]->particles[m].life<=0.0)
            {
                lastUsedParticle=m;
                return m;
            }
        }
        for(int m =0; m<lastUsedParticle; m++)
        {
            if(this->constantParticleEffects[index]->particles[m].life<=0.0)
            {
                lastUsedParticle=m;
                return m;
            }
        }
    }
    lastUsedParticle=0;
    return 0;

}

void ParticleEngine2D::addParticle(glm::vec2 pos, glm::vec2 siz, glm::vec4 col, int textNum){

    this->renderEngine->getShaderProgram(this->renderEngine->BASIC_2D_SHADER, true)->addVertex(basic2DVertex{glm::vec2(pos.x-siz.x,pos.y-siz.y),glm::vec2(0.0,1.0),col,textNum}, this->shaderPipelineNum);
    this->renderEngine->getShaderProgram(this->renderEngine->BASIC_2D_SHADER, true)->addVertex(basic2DVertex{glm::vec2(pos.x-siz.x,pos.y+siz.y),glm::vec2(0.0,0.0),col,textNum}, this->shaderPipelineNum);
    this->renderEngine->getShaderProgram(this->renderEngine->BASIC_2D_SHADER, true)->addVertex(basic2DVertex{glm::vec2(pos.x+siz.x,pos.y+siz.y),glm::vec2(1.0,0.0),col,textNum}, this->shaderPipelineNum);
    this->renderEngine->getShaderProgram(this->renderEngine->BASIC_2D_SHADER, true)->addVertex(basic2DVertex{glm::vec2(pos.x-siz.x,pos.y-siz.y),glm::vec2(0.0,1.0),col,textNum}, this->shaderPipelineNum);
    this->renderEngine->getShaderProgram(this->renderEngine->BASIC_2D_SHADER, true)->addVertex(basic2DVertex{glm::vec2(pos.x+siz.x,pos.y+siz.y),glm::vec2(1.0,0.0),col,textNum}, this->shaderPipelineNum);
    this->renderEngine->getShaderProgram(this->renderEngine->BASIC_2D_SHADER, true)->addVertex(basic2DVertex{glm::vec2(pos.x+siz.x,pos.y-siz.y),glm::vec2(1.0,1.0),col,textNum}, this->shaderPipelineNum);
}

void ParticleEngine2D::respawnParticle(particle& partic,float partcLife, glm::vec2 pos, float velocity, glm::vec2 offSet, glm::vec4 col)
{
    float randomX = (1-(2*((float)(rand()%100)/100)));
    float randomY = (1-(2*((float)(rand()%100)/100)));
    partic.pos.x = pos.x+(randomX*offSet.x);
    partic.pos.y = pos.y+(randomY*offSet.y);
    partic.color = col;
    partic.life = partcLife;
    partic.velocity.x = randomX*velocity;
    partic.velocity.y = randomY*velocity;
}

void ParticleEngine2D::createParticleEffect(glm::vec2 pos, float lifeTime, float partcLife, int particleGenerationRate, glm::vec2 siz,
                                            float speed, glm::vec2 offset,glm::vec4 color, int textNum, int state,int id)
{
    std::vector<particle> partcs;
    for(int i=0; i<this->particlesNr; i++)
    {
        partcs.push_back(particle());
    }
    if(state==1)
    {
        this->temporaryParticleEffects.push_back(new particleEffect{id,lifeTime,partcLife,particleGenerationRate,pos,offset,siz,speed,color,textNum,partcs});
    }
    else if(state==2)
    {
        this->constantParticleEffects.push_back(new particleEffect{id,lifeTime,partcLife,particleGenerationRate,pos,offset,siz,speed,color,textNum,partcs});
    }
}

void ParticleEngine2D::updateParticleEffect(int id, glm::vec2 newPos)
{
    this->constantParticleEffects[id]->pos = newPos;
}

void ParticleEngine2D::makeParticleEffect()
{
    float randomX;
    float randomY;
    //temporary particles
    for(int p = 0; p<this->temporaryParticleEffects.size(); p++)
    {
        this->temporaryParticleEffects[p]->life-=this->theApp->getDeltaTime();
        if(this->temporaryParticleEffects[p]->life>0)
        {
            for (GLuint i = 0; i < this->temporaryParticleEffects[p]->particleGenerationRate; ++i)
            {
                int unusedParticle = firstUnusedParticle(1,p);
                respawnParticle(this->temporaryParticleEffects[p]->particles[unusedParticle],this->temporaryParticleEffects[p]->partcLife,
                                this->temporaryParticleEffects[p]->pos,this->temporaryParticleEffects[p]->velocity,
                                this->temporaryParticleEffects[p]->offset, this->temporaryParticleEffects[p]->color);
            }
        }
        int zeroParticles = 1;
        for(int i = 0; i<this->temporaryParticleEffects[p]->particles.size(); i++)
        {
            randomX = (1-(2*((float)(rand()%100)/100)));
            randomY = (1-(2*((float)(rand()%100)/100)));
            particle &tempP = this->temporaryParticleEffects[p]->particles[i];
            tempP.life -= this->theApp->getDeltaTime();
            // reduce life
            if (tempP.life > 0.0f)
            {
                // particle is alive, thus update
                tempP.pos += tempP.velocity * this->theApp->getDeltaTime();
                tempP.color.a -= (this->theApp->getDeltaTime()/this->temporaryParticleEffects[p]->partcLife);
            }
            if(tempP.life>0.0)
            {
                zeroParticles = 0;

                this->addParticle(tempP.pos+this->relativePos,
                                                glm::vec2(this->temporaryParticleEffects[p]->siz.x*randomX/2, this->temporaryParticleEffects[p]->siz.y*randomY/2),
                                                tempP.color, this->temporaryParticleEffects[p]->textNum-1);
            }
        }
        if(zeroParticles)
        {
            this->particleEffectDestructor.push_back(p);
        }
    }
    for(int i = this->particleEffectDestructor.size(); i--;)
    {
        this->temporaryParticleEffects.erase(this->temporaryParticleEffects.begin()+this->particleEffectDestructor[i]);
    }

    this->particleEffectDestructor.clear();
    //constant particles
    for(int p = 0; p<this->constantParticleEffects.size(); p++)
    {
        for (GLuint i = 0; i < this->constantParticleEffects[p]->particleGenerationRate; ++i)
        {
            int unusedParticle = firstUnusedParticle(2,p);
            respawnParticle(this->constantParticleEffects[p]->particles[unusedParticle],this->constantParticleEffects[p]->partcLife,
                            this->constantParticleEffects[p]->pos,this->constantParticleEffects[p]->velocity,
                            this->constantParticleEffects[p]->offset, this->constantParticleEffects[p]->color);
        }
        for(int i = 0; i<this->constantParticleEffects[p]->particles.size(); i++)
        {
            randomX = (1-(2*((float)(rand()%100)/100)));
            randomY = (1-(2*((float)(rand()%100)/100)));
            particle &tempP = this->constantParticleEffects[p]->particles[i];
            tempP.life -= this->theApp->getDeltaTime();
            // reduce life
            if (tempP.life > 0.0f)
            {
                // particle is alive, thus update
                tempP.pos += tempP.velocity * this->theApp->getDeltaTime();
                tempP.color.a -= (this->theApp->getDeltaTime()/this->constantParticleEffects[p]->partcLife);
            }
            if(tempP.life>0.0)
            {

                this->addParticle(tempP.pos+this->relativePos,
                                  glm::vec2(this->temporaryParticleEffects[p]->siz.x*randomX/2, this->temporaryParticleEffects[p]->siz.y*randomY/2),
                                  tempP.color, this->temporaryParticleEffects[p]->textNum-1);
            }
        }
    }
}

void ParticleEngine2D::setRelativePos(glm::vec2 newPos){

    this->relativePos = newPos;

}

void ParticleEngine2D::render(){

    this->renderEngine->getShaderProgram(this->renderEngine->BASIC_2D_SHADER, true)->use(this->shaderPipelineNum);
}
