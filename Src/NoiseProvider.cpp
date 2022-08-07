#include "../Inc/NoiseProvider.h"

NoiseProvider::NoiseProvider()
{
    this->createEmptyMap();
}
NoiseProvider::~NoiseProvider()
{


}

double NoiseProvider::easeIn(double interpolator){
    return interpolator * interpolator;
}

double NoiseProvider::easeOut(double interpolator){
    return 1 - easeIn(1 - interpolator);
}

double NoiseProvider::easeInOut(double interpolator){
    double easeInValue = this->easeIn(interpolator);
    double easeOutValue = this->easeOut(interpolator);
    return this->lerp(easeInValue, easeOutValue, interpolator);
}

double NoiseProvider::getNoise(double x, double y, double dirX, double dirY){
    /*double smallX = sin(x);
    double smGameAlly = sin(y);
    double random = smallX * dirX + smGameAlly * dirY;
    random = modf(sin(random) * 143758.5453, &intPart);
    return random;*/
    double intPart;
    double smallX = sin(x);
    double smGameAlly = sin(y);
    double random =  10*modf(smallX * ((double)(std::rand()%1000)/1000) * dirX + smGameAlly * ((double)(std::rand()%1000)/1000) * dirY, &intPart);
    return random;
}

//double NoiseProvider::getNoise(int x, int y)
//{
    //double randVal = ((double)(std::rand()%1000))/1000;
    //return x+randVal*(y);
//}

double NoiseProvider::lerp(double a, double b, double z)
{
    double mu2 = (1 - cos(z * 3.14)) / 2;
    return (a * (1 - mu2) + b * mu2);
}

double NoiseProvider::pointValueNoise(double x, double y)
{

    auto floorX = (double)((int)x); // This is kinda a cheap way to floor a double integer.
    auto floorY = (double)((int)y);

    auto s = 0.0, t = 0.0, u = 0.0, v = 0.0; // Integer declaration

    s = this->getNoise(floorX, floorY);
    t = this->getNoise(floorX + 1, floorY);
    u = this->getNoise(floorX, floorY + 1); // Get the surrounding values to calculate the transition.
    v = this->getNoise(floorX + 1, floorY + 1);

    auto rec1 = this->lerp(s, t,  this->easeInOut(x)); // Interpolate between the values.
    auto rec2 = this->lerp(u, v, this->easeInOut(x)); // Here we use x-floorX, to get 1st dimension. Don't mind

    auto rec3 =this->lerp(rec1, rec2, this->easeInOut(y)); // Here we use y-floorZ, to get the 2nd dimension.

    return rec3;
}

void NoiseProvider::createEmptyMap(){

    for(int x = 0; x<this->widthNum; x++)
    {
        std::vector<double> tempArray;
        for(int y = 0; y<this->heightNum; y++)
        {

            tempArray.push_back(0);

        }
        this->theHeightMap.push_back(tempArray);
    }

}

void NoiseProvider::setupNoise()
{

    this->theHeightMap[0][0] = this->pointPerlinNoise(0, 0);
    this->maxHeight = this->theHeightMap[0][0];
}

void NoiseProvider::generateValueNoise()
{
    this->setupNoise();
    for(int x = 0; x<this->widthNum; x++)
    {

        for(int y = 1; y<this->heightNum; y++)
        {

            this->theHeightMap[x][y] = this->pointValueNoise(x,y);

        }
    }
}

double NoiseProvider::pointPerlinNoise(double x, double y)
{
    auto newX = (x);
    auto newY = (y);

    auto totalValue = 0.0;

    for (auto a = 0; a < this->octaves - 1; a++) // This loops through the octaves.
    {
        auto frequency = pow(2.0, a); // This increases the frequency with every loop of the octave.
        auto amplitude = pow(this->roughness, a); // This decreases the amplitude with every loop of the octave.
        totalValue += this->pointValueNoise(((double)newX) * frequency / this->smoothness, ((double)newY) * frequency / this->smoothness) * amplitude;
    }

    return totalValue;//2.1)+1.2;
}

void NoiseProvider::generatePerlinNoise()
{
    this->setupNoise();
    for(int x = 0; x<this->widthNum; x++)
    {

        for(int y = 1; y<this->heightNum; y++)
        {

            this->theHeightMap[x][y] = this->pointPerlinNoise(x, y);
            if(this->maxHeight<this->theHeightMap[x][y]){

                this->maxHeight = this->theHeightMap[x][y];

            }
        }

    }

}

void NoiseProvider::generateNoise(int noiseChoice)
{
    std::srand(this->startPointX*this->widthNum+this->startPointY);
    if(noiseChoice==this->VALUE_NOISE)
    {
        this->usedNoiseName = "Value Noise";
        this->generateValueNoise();
    }
    else if(noiseChoice==this->PERLIN_NOISE)
    {
        this->usedNoiseName = "Perlin Noise";
        this->generatePerlinNoise();
    }
}
std::vector<std::vector<double>>& NoiseProvider::getData()
{
    return this->theHeightMap;
}

int NoiseProvider::getMaxNoiseNum()
{

    return this->maxNoiseNum;

}

std::string NoiseProvider::getNoiseName()
{
    std::cout<<"getting name 1: "<<this->usedNoiseName<<std::endl;
    return this->usedNoiseName;

}

void NoiseProvider::setWidthNum(int newVal)
{

    this->widthNum = newVal;

}
void NoiseProvider::setHeightNum(int newVal)
{

    this->heightNum = newVal;

}

int NoiseProvider::getWidthNum()
{

    return this->widthNum;

}
int NoiseProvider::getHeightNum()
{

    return this->widthNum;

}

double NoiseProvider::getMaxHeight(){

    return this->maxHeight;

}

double NoiseProvider::getRealVal(int xIndex, int yIndex){

    return (double)(this->theHeightMap[xIndex][yIndex]*this->amplitude) + this->heightOffset;

}

void NoiseProvider::setOctaves(int newVal)
{

    this->octaves = newVal;
}
void NoiseProvider::setAmplitude(int newVal)
{

    this->amplitude = newVal;
}
void NoiseProvider::setSmoothness(int newVal)
{

    this->smoothness = newVal;
}
void NoiseProvider::setHeightOffset(int newVal)
{

    this->heightOffset = newVal;
}
void NoiseProvider::setRoughness(double newVal)
{

    this->roughness = newVal;
}
int NoiseProvider::getOctaves()
{

    return this->octaves;
}
int NoiseProvider::getAmplitude()
{

    return this->amplitude;
}
int NoiseProvider::getSmoothness()
{

    return this->smoothness;
}
int NoiseProvider::getHeightOffset()
{

    return this->heightOffset;
}
double NoiseProvider::getRoughness()
{

    return this->roughness;
}
