#ifndef PARTICLEENGINE2D_H_INCLUDED
#define PARTICLEENGINE2D_H_INCLUDED

#include<iostream>
#include<sstream>
#include<fstream>
#include<stdlib.h>
#include<vector>
#include<map>
#include<tuple>
#include<math.h>

#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include<vec2.hpp>
#include<vec3.hpp>
#include<vec4.hpp>

#include <Render/RenderEngine.h>
#include <App/AppEngine.h>

struct particle
{
    glm::vec2 pos;
    glm::vec2 velocity;
    glm::vec4 color;
    float life;
    particle():pos(0.0),velocity(0.0),color(1.0),life(0.0) {}
};

struct particleEffect
{
    int id;
    float life;
    float partcLife;
    int particleGenerationRate;
    glm::vec2 pos;
    glm::vec2 offset;
    glm::vec2 siz;
    float velocity;
    glm::vec4 color;
    int textNum;
    std::vector<particle> particles;
};

class ParticleEngine2D{

private:

    RenderEngine* renderEngine;
    AppEngine* theApp;
    glm::vec2 relativePos;

    int shaderPipelineNum;

    std::vector<particleEffect*> temporaryParticleEffects;
    std::vector<particleEffect*> constantParticleEffects;
    int particlesNr = 0;
    int lastUsedParticle = 0;
    int createdParticles = 0;
    std::vector<int> particleEffectDestructor;
public:

    ParticleEngine2D(RenderEngine*, AppEngine*);
    ~ParticleEngine2D();

    //functions
    int firstUnusedParticle(int type, int index);

    void addParticle(glm::vec2, glm::vec2, glm::vec4, int);

    void respawnParticle(particle&,float, glm::vec2, float, glm::vec2, glm::vec4);

    void particleSetup(int=500);

    void createParticleEffect(glm::vec2, float, float, int, glm::vec2, float, glm::vec2,glm::vec4, int, int,int=0);

    void updateParticleEffect(int, glm::vec2);

    void makeParticleEffect();

    void setRelativePos(glm::vec2);

    void render();
};

#endif // PARTICLEENGINE2D_H_INCLUDED
