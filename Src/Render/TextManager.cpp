
#include "Render/TextManager.h"

#include "Render/RenderEngine.h"

TextManager::TextManager(RenderEngine* engine)
{

    this->renderEngine = engine;

}
TextManager::~TextManager()
{


}

float TextManager::checkTextLength(std::string theString, float scale)
{

    float theLength = 0;
    for(std::string::const_iterator c=theString.begin(); c!=theString.end(); c++)
    {
        Character ch = this->characters[*c];
        theLength += ((ch.bear.x+ch.siz.x)*scale);
    }
    return theLength;
}

float TextManager::checkTextMaxHeight(std::string theString, float scale)
{

    float theMax = 0;
    for( std::string::const_iterator c=theString.begin(); c!=theString.end(); c++)
    {
        Character ch = this->characters[*c];
        if(theMax<ch.siz.y*scale)
        {

            theMax = ch.siz.y*scale;

        }
    }
    return theMax;
}


void TextManager::setTextType(std::string fontChoice)
{
    std::string filePath = "C:/Windows/Fonts/" + fontChoice + ".ttf";

    FT_Library ft;
    if(FT_Init_FreeType(&ft))
    {
        std::cout<<"No freetype"<<std::endl;
    }
    FT_Face fc;
    if(FT_New_Face(ft, filePath.c_str(),0,&fc))
    {
        std::cout<<"No freetype face"<<std::endl;
    }
    FT_Set_Pixel_Sizes(fc,0,48);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    for(int m = 0; m<128; m++)
    {
        if(FT_Load_Char(fc,m,FT_LOAD_RENDER))
        {
            std::cout<<"Error: No glyph"<<std::endl;
        }
        GLuint textch;
        glGenTextures(1,&textch);
        glBindTexture(GL_TEXTURE_2D,textch);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RED,
                     fc->glyph->bitmap.width,fc->glyph->bitmap.rows,
                     0,GL_RED,GL_UNSIGNED_BYTE,fc->glyph->bitmap.buffer);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        Character ch =
        {
            textch,
            glm::vec2(fc->glyph->bitmap.width,fc->glyph->bitmap.rows),
            glm::vec2(fc->glyph->bitmap_left,fc->glyph->bitmap_top),
            fc->glyph->advance.x
        };
        if(m=='g' || m=='y'|| m=='p'){
            ch.bear.y = ch.bear.y - ch.siz.y*0.3;
        }
        this->characters.insert(std::pair<char,Character>(m,ch));
    }

    FT_Done_Face(fc);
    FT_Done_FreeType(ft);

}

void TextManager::writeText(std::string text, GLfloat wPart, GLfloat hPart, GLfloat maxHeight, GLfloat scale,glm::vec3 color)
{
    float x = wPart;
    std::string::const_iterator c;
    GLfloat sum = 0;
    for(c=text.begin(); c!=text.end(); c++)
    {
        Character ch = this->characters[*c];
        sum+=(ch.advance >> 6) * scale;
    }
    wPart=wPart-sum/2;
    for(c=text.begin(); c!=text.end(); c++)
    {
        this->renderEngine->getShaderProgram(this->renderEngine->CHAR_SHADER, true)->clearVerts();
        Character ch = this->characters[*c];
        GLfloat xPos = x+ch.bear.x*scale;
        GLfloat yPos = hPart-((ch.siz.y-ch.bear.y)*scale/2)-maxHeight/2;
        GLfloat chW = ch.siz.x*scale;
        GLfloat chH = ch.siz.y*scale;

        this->renderEngine->getShaderProgram(this->renderEngine->CHAR_SHADER, true)->addVertex(glm::vec4(xPos,yPos,0.0,1.0));
        this->renderEngine->getShaderProgram(this->renderEngine->CHAR_SHADER, true)->addVertex(glm::vec4(xPos+chW,yPos,1.0,1.0));
        this->renderEngine->getShaderProgram(this->renderEngine->CHAR_SHADER, true)->addVertex(glm::vec4(xPos,yPos+chH,0.0,0.0));

        this->renderEngine->getShaderProgram(this->renderEngine->CHAR_SHADER, true)->addVertex(glm::vec4(xPos,yPos+chH,0.0,0.0));
        this->renderEngine->getShaderProgram(this->renderEngine->CHAR_SHADER, true)->addVertex(glm::vec4(xPos+chW,yPos,1.0,1.0));
        this->renderEngine->getShaderProgram(this->renderEngine->CHAR_SHADER, true)->addVertex(glm::vec4(xPos+chW,yPos+chH,1.0,0.0));

        glBindTexture(GL_TEXTURE_2D,ch.text);

        this->renderEngine->getShaderProgram(this->renderEngine->CHAR_SHADER, true)->use();

        x += (ch.advance >> 6) * scale;
    }


}

void TextManager::writeMessage(std::string text, GLfloat wPart, GLfloat hPart,GLfloat scale,
                               GLfloat wLimit, GLfloat hLimit, glm::vec3 color, bool relative)
{

    GLfloat x = wPart;
    GLfloat y = hPart;
    GLfloat xLimit = wLimit;
    GLfloat yLimit = hLimit;
    float usedScale = scale;
    if(relative)
    {
        x = x * float(this->renderEngine->getWindowWidth());
        y = y * float(this->renderEngine->getWindowHeight());
        xLimit = xLimit * float(this->renderEngine->getWindowWidth());
        yLimit = yLimit * float(this->renderEngine->getWindowHeight());

    }

    std::vector<std::string> separateStrings;
    std::vector<float> separateLengths;
    std::string keptString = "";
    std::string tempString = "";

    float fullHeight = 0;
    std::vector<float> separateYPositions;
    std::vector<float> separateMaxHeights;

    for(int i = 0; i<text.size(); i++)
    {
        if(text[i] == this->emptySpace[0] || i==text.size()-1)
        {

            if(i==text.size()-1)
            {
                tempString.push_back(text[i]);
            }
            else{
                tempString.push_back(this->emptySpace[0]);
            }

            if(tempString.size()==0)
            {
                tempString = " ";
            }
            if(this->checkTextLength(keptString+tempString, usedScale)<=xLimit*0.9)
            {
                for(int n = 0; n<tempString.size(); n++)
                {
                    keptString.push_back(tempString[n]);
                }

                if(i==text.size()-1){

                    separateStrings.push_back(keptString);
                    separateLengths.push_back(this->checkTextLength(keptString, usedScale));
                    keptString.clear();

                }
                tempString.clear();
            }
            else
            {
                if(keptString.length()==0)
                {
                    while(this->checkTextLength(tempString, usedScale)>xLimit*0.9)
                    {
                        usedScale = usedScale-0.1f;
                    }
                    usedScale = usedScale-0.1f;
                    separateStrings.push_back(tempString);
                    separateLengths.push_back(this->checkTextLength(tempString, usedScale));
                    tempString.clear();
                }
                else
                {
                    tempString.pop_back();
                    i--;
                    separateStrings.push_back(keptString);
                    separateLengths.push_back(this->checkTextLength(keptString, usedScale));
                    keptString.clear();
                }

            }
        }
        else
        {
            tempString.push_back(text[i]);

        }
    }
    for(int i = 0; i<separateStrings.size(); i++)
    {

        float tempHeight = checkTextMaxHeight(separateStrings[i], usedScale);

        separateYPositions.push_back(fullHeight+tempHeight*0.5);
        separateMaxHeights.push_back(tempHeight);
        fullHeight += tempHeight;

    }

    glEnable(GL_BLEND);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    this->renderEngine->getShaderProgram(this->renderEngine->CHAR_SHADER, true)->getShader()->setVec3f(color,"textCol");
    glActiveTexture(GL_TEXTURE0);
    for(int i = 0; i<separateStrings.size(); i++)
    {
        this->writeText(separateStrings[i], x-separateLengths[i]/2, y+fullHeight/2-separateYPositions[i], separateMaxHeights[i], usedScale, color);
    }
    glEnable(GL_BLEND);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D,0);
    glDisable(GL_BLEND);
}
