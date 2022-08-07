#include <GameWeapon.h>

GameWeapon::GameWeapon(float damage, float delay, float cost, float bSpeed, int textureN, int bType, int weaponShow)
{

    this->attackDamage = damage;
    this->attackDelay = delay;
    this->attackCost = cost;

    this->textureNum = textureN;
    this->bulletSpeed = bSpeed;
    this->bullelttType = bType;
    this->weaponShown = weaponShow;
}

float GameWeapon::getAttackDamage()
{
    return this->attackDamage;
}

float GameWeapon::getAttackDelay()
{
    return this->attackDelay;
}

float GameWeapon::getAttackCost()
{
    return this->attackCost;
}

int GameWeapon::getTextureNum()
{
    return this->textureNum;
}

int GameWeapon::getBulletSpeed()
{
    return this->bulletSpeed;
}

int GameWeapon::weaponIsShown()
{
    return this->weaponShown;
}

void GameWeapon::setAttackDamage(float newAttack)
{

    this->attackDamage = newAttack;

}

void GameWeapon::setAttackDelay(float newDelay)
{

    this->attackDelay = newDelay;

}

void GameWeapon::updateAttackDelay(float value)
{

    this->attackDelay += value;

}

void GameWeapon::setAttackCost(float newCost)
{

    this->attackCost = newCost;

}

void GameWeapon::setTextureNum(int newTexture)
{

    this->textureNum = newTexture;

}
void GameWeapon::setBulletSpeed(int newBulletSpeed)
{

    this->bulletSpeed = newBulletSpeed;

}

void GameWeapon::setWeaponShown(int newShow)
{
    this->weaponShown = newShow;
}

int GameWeapon::getType(){

    return this->bullelttType;

}
