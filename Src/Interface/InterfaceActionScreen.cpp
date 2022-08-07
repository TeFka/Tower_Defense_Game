
#include "Interface/InterfaceActionScreen.h"

InterfaceActionScreen::InterfaceActionScreen(RenderEngine* engine, int theId, float periodInMs):
    InterfaceWidget(engine, theId)
{
    this->refreshPeriod = (periodInMs/1000);
    this->refreshCounter = (periodInMs/1000);

    this->actionWidget = true;
    if(this->renderEngine->getShaderProgram(this->renderEngine->BASIC_2D_SHADER, true)->getVerticesListSize()<2){
        this->renderEngine->getShaderProgram(this->renderEngine->BASIC_2D_SHADER, true)->addPipeline();
    }
}

InterfaceActionScreen::~InterfaceActionScreen()
{



}

void InterfaceActionScreen::setTexture(unsigned int textureId, int textureN)
{

    this->textureNum = textureN;

    this->theTexture = new Texture(textureId,GL_TEXTURE_2D, textureN);

    this->renderEngine->getShaderProgram(this->renderEngine->BASIC_2D_SHADER, true)->addTexture(this->theTexture, 1);

}

void InterfaceActionScreen::render()
{

    this->renderEngine->setBasic2DSprite(glm::vec2(this->realX,
                                         this->realY),
                                         (glm::vec2(this->realWidth,
                                                 this->realHeight)*0.98f),
                                         glm::vec4(1.0),this->textureNum, false, false, 1);

    this->renderEngine->getShaderProgram(this->renderEngine->BASIC_2D_SHADER, true)->getShader()->set1i(this->theTexture->getUnit(),"textr[0]");
    this->theTexture->bindT();
    this->renderEngine->drawBasic2D(false, 1);

}

void InterfaceActionScreen::renderText()
{


}

void InterfaceActionScreen::addWidget(InterfaceWidget* widget)
{


}

InterfaceWidget* InterfaceActionScreen::getWidget(int pos)
{

    return this;
}
InterfaceWidget* InterfaceActionScreen::getWidgetByPosition(float, float)
{

    return this;
}

int InterfaceActionScreen::getWidgetAmount()
{


}

void InterfaceActionScreen::activateFunction()
{


}

void InterfaceActionScreen::setMembersParameters()
{


}

std::string InterfaceActionScreen::getText()
{

    return "";

}

void InterfaceActionScreen::setText(std::string addedText)
{


}

glm::vec4 InterfaceActionScreen::getColor()
{

    return glm::vec4(1.0);
}
void InterfaceActionScreen::setColor(glm::vec4 color)
{


}

glm::vec4 InterfaceActionScreen::getTextColor()
{

    return glm::vec4(1.0);
}
void InterfaceActionScreen::setTextColor(glm::vec4 color)
{


}

void InterfaceActionScreen::toggleColor(glm::vec4 color, float time)
{


}
void InterfaceActionScreen::toggleTextColor(glm::vec4 color, float time)
{


}

void InterfaceActionScreen::toggleBackColor()
{


}
void InterfaceActionScreen::toggleBackTextColor()
{


}
