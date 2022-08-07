
#include "Interface/InterfaceWidget.h"
#include "Interface/InterfaceScreen.h"

InterfaceWidget::InterfaceWidget(RenderEngine* engine, int theId, bool relative, float initialW, float initialH)
{

    this->id = theId;
    this->renderEngine = engine;
    this->hasParent = false;
    this->enabled = true;
    this->relativeParameters = relative;
    this->xHint = 0.5f;
    this->yHint = 0.5f;
    this->widthHint = initialW;
    this->heightHint = initialH;

    this->realX = 0.5f*this->renderEngine->getWindowWidth();
    this->realY = 0.5f*this->renderEngine->getWindowHeight();
    this->realWidth = initialW*this->renderEngine->getWindowWidth();
    this->realHeight = initialH*this->renderEngine->getWindowHeight();

    this->margin = 0.1;
}

InterfaceWidget::~InterfaceWidget()
{


}


void InterfaceWidget::setActiveScreen(InterfaceScreen* newScreen)
{

    this->theActiveScreen = newScreen;
}

InterfaceScreen* InterfaceWidget::getActiveScreen()
{

    return this->theActiveScreen;
}

int InterfaceWidget::getId()
{

    return this->id;
}

bool InterfaceWidget::isEnabled()
{

    return this->enabled;
}

void InterfaceWidget::enable()
{

    this->enabled = true;
}

void InterfaceWidget::disable()
{

    this->enabled = false;
}

float InterfaceWidget::getWidthHint()
{

    return this->widthHint;
}
float InterfaceWidget::getHeightHint()
{

    return this->heightHint;
}
float InterfaceWidget::getXHint()
{

    return this->xHint;
}
float InterfaceWidget::getYHint()
{

    return this->yHint;
}

float InterfaceWidget::getRealWidth()
{

    return this->realWidth;

}

float InterfaceWidget::getRealHeight()
{

    return this->realHeight;

}

float InterfaceWidget::getRealX()
{

    return this->realX;

}

float InterfaceWidget::getRealY()
{

    return this->realY;

}

float InterfaceWidget::getMargin()
{

    return this->margin;

}

void InterfaceWidget::setMargin(float newVal)
{

    this->margin = newVal;

}
float InterfaceWidget::getOverallWidthHint()
{
    if(this->hasParent)
    {
        return this->widthHint*this->widgetParent->getOverallWidthHint();
    }
    else
    {
        return this->widthHint;
    }

}
float InterfaceWidget::getOverallHeightHint()
{
    if(this->hasParent)
    {
        return this->heightHint*this->widgetParent->getOverallHeightHint();
    }
    else
    {
        return this->heightHint;
    }
}
float InterfaceWidget::getOverallXHint()
{
    if(this->hasParent)
    {
        return this->xHint*this->widgetParent->getOverallXHint();
    }
    else
    {
        return this->xHint;
    }
}
float InterfaceWidget::getOverGameAllyHint()
{

    if(this->hasParent)
    {
        return this->yHint*this->widgetParent->getOverGameAllyHint();
    }
    else
    {
        return this->yHint;
    }
}

bool InterfaceWidget::isRelative()
{
    return this->relativeParameters;
}

bool InterfaceWidget::isLayout()
{
    return this->layoutWidget;
}

bool InterfaceWidget::isButton()
{
    return this->buttonWidget;
}

bool InterfaceWidget::isAction()
{
    return this->actionWidget;
}


InterfaceWidget* InterfaceWidget::getParent()
{

    return this->widgetParent;
}

void InterfaceWidget::setWidthHint(float newHint)
{

    this->widthHint = newHint;
    if(hasParent)
    {
        this->realWidth = this->widgetParent->getRealWidth()*newHint;
    }
    else
    {
        this->realWidth = this->renderEngine->getWindowWidth()*newHint;
    }
}
void InterfaceWidget::setHeightHint(float newHint)
{

    this->heightHint = newHint;
    if(hasParent)
    {
        this->realHeight = this->widgetParent->getRealHeight()*newHint;
    }
    else
    {
        this->realHeight = this->renderEngine->getWindowHeight()*newHint;
    }
}
void InterfaceWidget::setXHint(float newHint)
{

    this->xHint = newHint;
    if(hasParent)
    {
        this->realX = (this->widgetParent->getRealX()+(this->widgetParent->getRealWidth()*(newHint-0.5f)));
    }
    else
    {
        this->realX = this->renderEngine->getWindowWidth()*newHint;
    }
}
void InterfaceWidget::setYHint(float newHint)
{

    this->yHint = newHint;
    if(hasParent)
    {
        this->realY = (this->widgetParent->getRealY()+(this->widgetParent->getRealHeight()*(newHint-0.5f)));
    }
    else
    {
        this->realY = this->renderEngine->getWindowHeight()*newHint;
    }
}
void InterfaceWidget::setRelative(bool newVal)
{

    this->relativeParameters = newVal;
}

void InterfaceWidget::setParent(InterfaceWidget* newParent)
{
    this->hasParent = true;
    this->widgetParent = newParent;

}
