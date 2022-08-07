#ifndef TEXTMANAGER_H_INCLUDED
#define TEXTMANAGER_H_INCLUDED

#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include <vector>
#include <map>

#include<glm.hpp>
#include<vec3.hpp>

#include<ft2build.h>
#include<ft2build.h>
#include FT_FREETYPE_H

struct Character
{
    GLuint text;
    glm::ivec2 siz;
    glm::ivec2 bear;
    GLuint advance;
};

class RenderEngine;

class TextManager{

private:

     RenderEngine* renderEngine;
     std::map<GLchar, Character> characters;

     std::string emptySpace = " ";

public:

    TextManager(RenderEngine*);
    ~TextManager();

    float checkTextLength(std::string, float);
    float checkTextMaxHeight(std::string, float);

    void setTextType(std::string);

    void writeText(std::string, GLfloat, GLfloat, GLfloat, GLfloat,glm::vec3);

    void writeMessage(std::string, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, glm::vec3, bool = true);

};

#endif // TEXTMANAGER_H_INCLUDED
