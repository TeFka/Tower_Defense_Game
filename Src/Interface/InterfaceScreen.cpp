
#include "Interface/InterfaceScreen.h"

InterfaceScreen::InterfaceScreen(std::string initialName, InterfaceEngine* interface, int theId)
{
    this->interfaceEngine = interface;
    this->name = initialName;
    this->id = theId;
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

void InterfaceScreen::addWidget(InterfaceWidget* newWidget)
{
    newWidget->setActiveScreen(this);
    this->allWidgets.emplace(newWidget->getId(), std::move(newWidget));

}

void InterfaceScreen::addChildWidget(InterfaceWidget* newWidget){

    this->widgets.push_back(newWidget);
    this->addWidget(newWidget);

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

}

DefaultInterfaceScreen::DefaultInterfaceScreen(std::string initialName, InterfaceEngine* interface) : InterfaceScreen(initialName, interface)
{

}

DefaultInterfaceScreen::~DefaultInterfaceScreen()
{


}

void DefaultInterfaceScreen::update(){


}

void DefaultInterfaceScreen::render()
{
    this->update();
    for(int i=0; i<this->widgets.size(); i++)
    {
        this->widgets[i]->render();

    }

}
