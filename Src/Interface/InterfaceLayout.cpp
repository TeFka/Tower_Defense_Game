
#include "Interface/InterfaceLayout.h"

InterfaceLayout::InterfaceLayout(RenderEngine* engine, int theId, orientation defaultOrientation,
                                 bool relative, float initialW, float initialH) :
    InterfaceWidget(engine, theId, relative, initialW, initialH)
{

    this->orient = defaultOrientation;
    this->layoutWidget = true;
}

InterfaceLayout::~InterfaceLayout()
{



}

void InterfaceLayout::addWidget(InterfaceWidget* newWidget)
{
    newWidget->setParent(this);
    this->widgets.push_back(newWidget);
    this->theActiveScreen->addWidget(newWidget);

}

InterfaceWidget* InterfaceLayout::getWidget(int neededId)
{
    for(int i = 0; i<this->widgets.size(); i++)
    {
        if(this->widgets[i]->getId()==neededId)
        {
            return this->widgets[i];
        }
    }

}

InterfaceWidget* InterfaceLayout::getWidgetByPosition(float x, float y)
{

    for(int i = 0; i<this->widgets.size(); i++)
    {
        if(this->widgets[i]->isEnabled())
        {
        if(x>this->widgets[i]->getRealX()-(this->widgets[i]->getRealWidth()/2)&&
                x<this->widgets[i]->getRealX()+(this->widgets[i]->getRealWidth()/2)&&
                y>this->widgets[i]->getRealY()-(this->widgets[i]->getRealHeight()/2)&&
                y<this->widgets[i]->getRealY()+(this->widgets[i]->getRealHeight()/2))
        {

            if(this->widgets[i]->isLayout())
            {
                return this->widgets[i]->getWidgetByPosition(x, y);
            }
            else
            {
                return this->widgets[i];
            }
        }
        }
    }

    return nullptr;

}

int InterfaceLayout::getWidgetAmount()
{

    return this->widgets.size();

}

void InterfaceLayout::setPadding(float newVal)
{

    this->padding = newVal;

}

float InterfaceLayout::getPadding()
{

    return this->padding;

}

void InterfaceLayout::setMembersParameters()
{

    float freeSpace = 1.0;
    float positioning = 0;
    int relativeNum = 0;
    if(this->orient == HORIZONTAL)
    {
        for(int i = 0; i<this->widgets.size(); i++)
        {
            if(this->widgets[i]->isEnabled())
            {
                this->widgets[i]->setHeightHint(1.0-this->widgets[i]->getMargin()*2);
                this->widgets[i]->setYHint(0.5);
                if(!this->widgets[i]->isRelative())
                {

                    freeSpace -= this->widgets[i]->getWidthHint();
                }
                else
                {
                    relativeNum++;
                }
            }
        }

        for(int i = 0; i<this->widgets.size(); i++)
        {
            if(this->widgets[i]->isEnabled())
            {
                if(this->widgets[i]->isRelative())
                {
                    this->widgets[i]->setWidthHint((freeSpace/relativeNum)-this->widgets[i]->getMargin()*2);
                    this->widgets[i]->setXHint(positioning + ((freeSpace/relativeNum)/2));
                    positioning += (freeSpace/relativeNum);
                }
                else
                {
                    this->widgets[i]->setXHint(positioning + (this->widgets[i]->getWidthHint()/2));
                    positioning += this->widgets[i]->getWidthHint();
                }

                if(this->widgets[i]->isLayout())
                {
                    this->widgets[i]->setMembersParameters();
                }
            }
        }

    }
    else if(this->orient == VERTICAL)
    {

        for(int i = (this->widgets.size()-1); i>=0; i--)
        {
            if(this->widgets[i]->isEnabled())
            {
                this->widgets[i]->setWidthHint(1.0-this->widgets[i]->getMargin()*2);
                this->widgets[i]->setXHint(0.5);
                if(!this->widgets[i]->isRelative())
                {
                    freeSpace -= this->widgets[i]->getHeightHint();
                }
                else
                {
                    relativeNum++;
                }
            }
        }

        for(int i = (this->widgets.size()-1); i>=0; i--)
        {
            if(this->widgets[i]->isEnabled())
            {
                if(this->widgets[i]->isRelative())
                {
                    this->widgets[i]->setHeightHint((freeSpace/relativeNum)-this->widgets[i]->getMargin()*2);
                    this->widgets[i]->setYHint(positioning + ((freeSpace/relativeNum)/2));
                    positioning += (freeSpace/relativeNum);
                }
                else
                {
                    this->widgets[i]->setYHint(positioning + (this->widgets[i]->getHeightHint()/2));
                    positioning += this->widgets[i]->getHeightHint();
                }

                if(this->widgets[i]->isLayout())
                {
                    this->widgets[i]->setMembersParameters();
                }
            }
        }

    }

}

void InterfaceLayout::render()
{
    if(this->enabled)
    {
        for(int i=0; i<this->widgets.size(); i++)
        {

            this->widgets[i]->render();

        }
    }

}

void InterfaceLayout::renderText()
{
    if(this->enabled)
    {
        for(int i=0; i<this->widgets.size(); i++)
        {

            this->widgets[i]->renderText();

        }
    }
}

void InterfaceLayout::activateFunction()
{


}

std::string InterfaceLayout::getText()
{

    return "";

}

void InterfaceLayout::setText(std::string addedText)
{


}

glm::vec4 InterfaceLayout::getColor()
{

    return glm::vec4(1.0);
}
void InterfaceLayout::setColor(glm::vec4)
{


}

glm::vec4 InterfaceLayout::getTextColor()
{

    return glm::vec4(1.0);
}
void InterfaceLayout::setTextColor(glm::vec4)
{


}

void InterfaceLayout::toggleColor(glm::vec4, float time)
{


}

void InterfaceLayout::toggleTextColor(glm::vec4, float time)
{


}

void InterfaceLayout::toggleBackColor()
{


}

void InterfaceLayout::toggleBackTextColor()
{


}

