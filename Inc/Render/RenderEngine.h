
#ifndef RenderEngine_H_INCLUDED
#define RenderEngine_H_INCLUDED

#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<ft2build.h>
#include<ft2build.h>
#include FT_FREETYPE_H

#include<iostream>
#include<sstream>
#include<fstream>
#include<stdlib.h>
#include<vector>
#include<tuple>

#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include<vec2.hpp>
#include<vec3.hpp>
#include<vec4.hpp>

#include <Render/Shader.h>
#include <Render/ShaderPipeline.h>
#include <../../Src/Render/ShaderPipeline.cpp>
#include <Render/Camera.h>
#include <Render/Texture.h>

#include <Render/TextManager.h>

#pragma once

struct basic2DVertex
{
    glm::vec2 pos;
    glm::vec2 textr;
    glm::vec4 col;
    int textNr;
};

struct basic3DVertex
{
    glm::vec3 pos;
    glm::vec2 textr;
    glm::vec4 col;
    int textNr;
};


struct simpleVertex
{
    glm::vec2 pos;
    glm::vec4 col;
};

struct screenVertex
{
    glm::vec3 pos;
    glm::vec2 textr;
};

class RenderEngine
{

private:

    //window data
    GLFWwindow* windax;
    int windowWidth;
    int windowHeight;
    int lastWindowWidth;
    int lastWindowHeight;
    int framebufferWidth = 0;
    int framebufferHeight = 0;
    int GLFWminorVersion;
    int GLFWmajorVersion;

    // Matrices
    glm::mat4 projectionMatrix = glm::mat4(1.0);
    glm::mat4 perspectiveProjectionMatrix = glm::mat4(1.0);

    // Ubos
    unsigned int defaultUbo;

    //screen texture
    unsigned int basicFBO;
    unsigned int RBO;
    unsigned int screenTexture;
    unsigned int mFBO;
    unsigned int mRBO;
    unsigned int mFBOtext;

    int backgroundFace = 0;
    bool backgroundExists = false;

    //default shaders
    ShaderPipeline<glm::vec2> testShadProgram;

    ShaderPipeline<glm::vec4> screenShadProgram;

    ShaderPipeline<glm::vec4> charShadProgram;

    ShaderPipeline<basic2DVertex> basic2DShadProgram;

    ShaderPipeline<basic2DVertex> basicTransparent2DShadProgram;

    ShaderPipeline<basic3DVertex> basic3DShadProgram;

    ShaderPipeline<basic3DVertex> basicTransparent3DShadProgram;

    std::vector<AbstractPipeline*> shaderPrograms;
    const int defaultShaderNum = 7;

    std::string defaultShaderNames[10] = {"test_vert.glsl", "test_frag.glsl",
                                          "screen_vert.glsl", "screen_frag.glsl",
                                          "char_vert.glsl", "char_frag.glsl",
                                          "basic_2D_vert.glsl", "basic_2D_frag.glsl",
                                          "basic_3D_vert.glsl", "basic_3D_frag.glsl"
                                         };


    TextManager* theTexter;
    static void frameBufferRez(GLFWwindow *, int, int);

    void setGLFW(const char*, const int, const int, const int, const int);

    void enableModes();

    void setDefaultShaders();

    void setScreen();

    void updateDefaultUniforms();

    void updateViewport();

public:

    //defaultShaders
    const int TEST_SHADER = 0;
    const int SCREEN_SHADER = 1;
    const int CHAR_SHADER = 2;
    const int BASIC_2D_SHADER = 3;
    const int BASIC_3D_SHADER = 4;
    const int BASIC_TRANSPARENT_2D_SHADER = 5;
    const int BASIC_TRANSPARENT_3D_SHADER = 6;

    RenderEngine(const char*,
                   const int, const int,
                   const int, const int,
                   std::string);

    ~RenderEngine();

    template<class vectorType>
    int setShaderProgram(const char* vertexFile, const char* fragmentFile, std::vector<verticeInfo*> vertInf,
                         int useGeometryShader = 0, const char* geometryFile = "")
    {
        this->shaderPrograms.push_back(new ShaderPipeline<vectorType>(vertexFile,fragmentFile, useGeometryShader, geometryFile, vertInf));
        this->shaderPrograms[this->shaderPrograms.size()-1]->setupVertex();
        return (this->shaderPrograms.size()-this->defaultShaderNum);
    }

    void setDefaultShaderUniforms();

    void setTextureToAll(const char*, int, int, int=0);
    void addTextureToAll(Texture*, int=0);

    void setUbo(const char*, int);

    void addDefaultUboToShader(int, bool=false);

    GLFWwindow* getWindow();

    AbstractPipeline* getShaderProgram(int, bool = false);

    TextManager* getTextManager();

    void setBasic2DSprite(glm::vec2, glm::vec2, glm::vec4, int = 15, bool = true, bool = false, int=0);

    void setBasic3DSprite(glm::vec3, glm::vec3, glm::vec4, int = 15, bool = false, int=0);

    template<class T>
    void setCustomSprite(std::vector<T>, int, int=0);

    void clearVerts(int, bool=false, int=0);

    void update();

    void renderBegin();

    void renderSkyboxBackground(glm::mat4);

    void drawTest(int);

    void drawBasic2D(bool = false, int=0);

    void drawBasic3D(bool = false, int=0);

    void drawCustom(int, bool = false, int=0);

    void updateScreen();

    void renderEnd();

    int getWindowWidth();

    int getWindowHeight();

    unsigned int getMainFBO();

};

#endif
