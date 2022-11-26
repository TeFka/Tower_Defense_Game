
#include "Interface/InterfaceBox.h"

InterfaceBox::InterfaceBox(RenderEngine* engine, int theId,
                           std::string initialText, glm::vec4 initialColor, glm::vec4 initialTextColor,
                           float txtSize, bool relative, float initialW, float initialH) :
    InterfaceWidget(engine, theId, relative, initialW, initialH)
{

    this->text = initialText;
    this->textSize = txtSize;
    this->color = initialColor;
    this->textColor = initialTextColor;
    this->textureNum = 15;
    this->textEnabled = true;

}

InterfaceBox::~InterfaceBox()
{

}

std::string InterfaceBox::getText()
{

    return this->text;

}

void InterfaceBox::setText(std::string addedText)
{

    this->text = addedText;

}

glm::vec4 InterfaceBox::getColor()
{

    return this->color;

}

void InterfaceBox::setColor(glm::vec4 newColor)
{

    this->color.x = newColor.x;
    this->color.y = newColor.y;
    this->color.z = newColor.z;
    this->color.w = newColor.w;

}

glm::vec4 InterfaceBox::getTextColor()
{

    return this->textColor;

}

void InterfaceBox::setTextColor(glm::vec4 newColor)
{

    this->color.x = newColor.x;
    this->color.y = newColor.y;
    this->color.z = newColor.z;
    this->color.w = newColor.w;

}

float InterfaceBox::getTextSize()
{

    return this->textSize;
}

void InterfaceBox::setTextSize(float newSize)
{

    this->textSize = newSize;
}

void InterfaceBox::setTexture(int newTextr)
{

    this->textureNum = newTextr;
}

void InterfaceBox::showText(bool newVal)
{

    this->textEnabled = newVal;
}

void InterfaceBox::renderText()
{
    if(this->enabled)
    {
        if(this->textEnabled)
        {
            if(this->hasParent)
            {
                this->renderEngine->getTextManager()->writeMessage(this->text,
                        this->realX,
                        this->realY,
                        this->textSize,
                        this->realWidth,
                        this->realHeight,
                        this->textColor,
                        false);
            }
            else
            {
                this->renderEngine->getTextManager()->writeMessage(this->text,
                        this->xHint,
                        this->yHint,
                        this->textSize,
                        this->widthHint,
                        this->heightHint,
                        this->textColor);
            }
        }
    }
}

void InterfaceBox::render()
{
    if(this->enabled)
    {
        if(this->hasParent)
        {
            this->renderEngine->setBasic2DSprite(glm::vec2(this->realX,
                                                 this->realY),
                                                 (glm::vec2(this->realWidth,
                                                         this->realHeight)*0.99f),
                                                 this->color,this->textureNum, false);
        }
        else
        {

            this->renderEngine->setBasic2DSprite(glm::vec2(this->xHint, this->yHint),
                                                 glm::vec2(this->widthHint, this->heightHint),
                                                 this->color,this->textureNum, true);
        }
    }
}

void InterfaceBox::addWidget(InterfaceWidget* engine)
{


}

InterfaceWidget* InterfaceBox::getWidget(int index)
{

    return this;
}

InterfaceWidget* InterfaceBox::getWidgetByPosition(float, float)
{

    return this;
}

int InterfaceBox::getWidgetAmount()
{

    return 0;
}

void InterfaceBox::setMembersParameters()
{



}

void InterfaceBox::activateFunction()
{


}

void InterfaceBox::toggleColor(glm::vec4, float time)
{


}

void InterfaceBox::toggleTextColor(glm::vec4, float time)
{


}

void InterfaceBox::toggleBackColor()
{


}

void InterfaceBox::toggleBackTextColor()
{


}
