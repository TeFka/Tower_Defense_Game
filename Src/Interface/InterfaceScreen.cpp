
#include "Interface/InterfaceScreen.h"
#include "Interface/InterfaceEngine.h"

InterfaceScreen::InterfaceScreen(std::string initialName, InterfaceEngine* interface, int theId)
{
    this->interfaceEngine = interface;
    this->name = initialName;
    this->id = theId;

    this->widgetIsActive = false;

    this->backgroundColor = glm::vec4(0.7,0.7,0.7,1.0);
}

InterfaceScreen::~InterfaceScreen()
{


}

int InterfaceScreen::getId(){

    return this->id;

}

void InterfaceScreen::addActiveCommandId(int activeId){

    this->activeIds.push_back(activeId);

}

int InterfaceScreen::getLatestActiveId(){
     if(this->activeIds.size()!=0){
        int theComm = this->activeIds[this->activeIds.size()-1];
        this->activeIds.pop_back();
        return theComm;
     }
     else{
        return 0;
     }

}

void InterfaceScreen::handleTogglePress(float xPos, float yPos){

    if(this->activePopups.size()==0){
        if(!this->widgetIsActive)
        {
            this->activeWidget = this->getWidgetByPosition(xPos, yPos);
            if(this->activeWidget != nullptr )
            {
                if(this->activeWidget->isButton())
                {
                    this->widgetIsActive = true;
                    this->activeWidget->toggleColor(1.0f-this->activeWidget->getColor());
                    this->activeWidget->toggleTextColor(1.0f-this->activeWidget ->getTextColor());
                }
                if(this->activeWidget->isAction())
                {
                    this->widgetIsActive = true;
                    this->activeWidget->setToggle(true);
                    this->activeWidget->setActiveToggledPos(glm::vec2((xPos - (this->activeWidget->getRealX()-(this->activeWidget->getRealWidth()/2)))/this->activeWidget->getRealWidth(),
                                                                      (yPos - (this->activeWidget->getRealY()-(this->activeWidget->getRealHeight()/2)))/this->activeWidget->getRealHeight()));

                }
            }
            else
            {
                std::cout<<"null button"<<std::endl;
            }
        }
    }
    else{

        this->activeWidget = this->getPopupByPosition(xPos, yPos);
        if(this->activeWidget == nullptr)
        {
            this->activePopups.clear();
        }
        else{
            if(this->activeWidget->isButton())
            {
                this->widgetIsActive = true;
                this->activeWidget->toggleColor(1.0f-this->activeWidget->getColor());
                this->activeWidget->toggleTextColor(1.0f-this->activeWidget ->getTextColor());
            }
            if(this->activeWidget->isAction())
            {
                this->widgetIsActive = true;
                this->activeWidget->setToggle(true);
                this->activeWidget->setActiveToggledPos(glm::vec2((xPos - (this->activeWidget->getRealX()-(this->activeWidget->getRealWidth()/2)))/this->activeWidget->getRealWidth(),
                                                                  (yPos - (this->activeWidget->getRealY()-(this->activeWidget->getRealHeight()/2)))/this->activeWidget->getRealHeight()));

            }
        }
    }

}

void InterfaceScreen::handleToggleRelease(){

    if(this->widgetIsActive)
    {
        if(this->activeWidget->isButton())
        {
            this->widgetIsActive = false;
            this->activeWidget->toggleBackColor();
            this->activeWidget->toggleBackTextColor();
            this->activeWidget->activateFunction();
        }
        if(this->activeWidget->isAction())
        {
            this->widgetIsActive = false;
            this->activeWidget->setToggle(false);

        }
    }

}

void InterfaceScreen::addWidget(InterfaceWidget* newWidget)
{
    newWidget->setActiveScreen(this);
    this->allWidgets.emplace(newWidget->getId(), std::move(newWidget));

}

void InterfaceScreen::addChildWidget(InterfaceWidget* newWidget){

    this->widgets.push_back(newWidget);
    this->addWidget(newWidget);

}

InterfaceWidget* InterfaceScreen::getActiveWidget()
{

    return this->activeWidget;
}

void InterfaceScreen::addPopup(float xPos, float yPos, float width, float height, InterfaceWidget* popupContent){

    InterfaceLayout* tempLayout = new InterfaceLayout(this->interfaceEngine->getRenderEngine(), 0, VERTICAL, false, width, height);
    this->addWidget(tempLayout);
    tempLayout->setXHint(xPos);
    tempLayout->setYHint(yPos);
    tempLayout->addWidget(popupContent);
    tempLayout->setMembersParameters();
    std::cout<<"adding popup to overall: "<<this->activePopups.size()<<std::endl;
    this->activePopups.push_back(tempLayout);

}

bool InterfaceScreen::popupsAreActive(){

    return (this->activePopups.size()>0);

}

InterfaceWidget* InterfaceScreen::getPopupByPosition(float x, float y)
{

    for(int i = 0; i<this->activePopups.size(); i++)
        {
            if(x>this->activePopups[i]->getRealX()-(this->activePopups[i]->getRealWidth()/2)&&
                    x<this->activePopups[i]->getRealX()+(this->activePopups[i]->getRealWidth()/2)&&
                    y>this->activePopups[i]->getRealY()-(this->activePopups[i]->getRealHeight()/2)&&
                    y<this->activePopups[i]->getRealY()+(this->activePopups[i]->getRealHeight()/2))
            {
                if(this->activePopups[i]->isLayout())
                {
                    return this->activePopups[i]->getWidgetByPosition(x, y);
                }
                else
                {
                    return this->activePopups[i];
                }
            }
        }

    return nullptr;

}

void InterfaceScreen::removePopup(int index){

    this->activePopups.erase(this->activePopups.begin()+index);

}
void InterfaceScreen::removeLastPopup(){
    std::cout<<"removing last popup of "<<this->activePopups.size()<<std::endl;
    this->activePopups.erase(this->activePopups.begin()+this->activePopups.size()-1);

}
void InterfaceScreen::clearPopups(){

    this->activePopups.clear();

}

InterfaceWidget* InterfaceScreen::getWidget(int neededId)
{
    return this->allWidgets[neededId];

}

InterfaceWidget* InterfaceScreen::getWidgetByPosition(float x, float y)
{

    for(int i = 0; i<this->widgets.size(); i++)
    {
        if(this->widgets[i]->isEnabled()){
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

std::string InterfaceScreen::getName()
{

    return this->name;

}

glm::vec4 InterfaceScreen::getBackgroundColor(){

    return this->backgroundColor;

}
void InterfaceScreen::setBackgroundColor(glm::vec4 newVal){

    this->backgroundColor = newVal;
}

void InterfaceScreen::setMembersParameters()
{
    float gaps = 1.0f/this->widgets.size();
    float positioning = 0;
    int relativeNum = 0;

    for(int i = 0; i<this->widgets.size(); i++)
    {
        if(this->widgets[i]->isEnabled()){
        this->widgets[i]->setHeightHint(1.0f);
        this->widgets[i]->setWidthHint(1.0f);
        this->widgets[i]->setXHint(positioning + (gaps/2));
        positioning += gaps;

        if(this->widgets[i]->isLayout())
        {
            this->widgets[i]->setMembersParameters();
        }
        }
    }
}


void InterfaceScreen::setup()
{

    this->setMembersParameters();

}

void InterfaceScreen::renderText()
{
    for(int i=0; i<this->widgets.size(); i++)
    {

        this->widgets[i]->renderText();

    }

    for(int i=0; i<this->activePopups.size(); i++)
    {
        this->activePopups[i]->renderText();
    }

}

void InterfaceScreen::render()
{
    this->update();
    for(int i=0; i<this->widgets.size(); i++)
    {
        this->widgets[i]->render();

    }

    for(int i=0; i<this->activePopups.size(); i++)
    {
        this->activePopups[i]->render();
    }

}

DefaultInterfaceScreen::DefaultInterfaceScreen(std::string initialName, InterfaceEngine* interface) : InterfaceScreen(initialName, interface)
{

}

DefaultInterfaceScreen::~DefaultInterfaceScreen()
{


}

void DefaultInterfaceScreen::update(){


}

