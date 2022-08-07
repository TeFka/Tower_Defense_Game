#ifndef NOISEPROVIDER_H_INCLUDED
#define NOISEPROVIDER_H_INCLUDED

#include<iostream>
#include<vector>
#include<stdio.h>
#include<math.h>

class NoiseProvider{

private:

    const int maxNoiseNum = 2;
    std::string usedNoiseName;

    std::vector<std::vector<double>> theHeightMap;
    int widthNum = 100;
    int heightNum = 100;
    int startPointX = 0;
    int startPointY = 0;
    double maxHeight = 0.0;

    int octaves = 7;
    int amplitude = 20;
    int smoothness = 235;
    int heightOffset = 0;
    double roughness = 0.53;

public:
    const int VALUE_NOISE = 0;
    const int PERLIN_NOISE = 1;

    NoiseProvider();
    ~NoiseProvider();

    void createEmptyMap();
    void setupNoise();

    double easeIn(double);
    double easeOut(double);
    double easeInOut(double);
    double getNoise(double, double, double = 12.9898, double = 78.233);
    double lerp(double, double, double);

    double pointValueNoise(double, double);
    void generateValueNoise();

    double pointPerlinNoise(double, double);
    void generatePerlinNoise();

    void generateNoise(int);

    std::vector<std::vector<double>>& getData();

    int getMaxNoiseNum();

    std::string getNoiseName();

    void setWidthNum(int);
    void setHeightNum(int);
    int getWidthNum();
    int getHeightNum();
    double getMaxHeight();

    double getRealVal(int, int);

    void setOctaves(int);
    void setAmplitude(int);
    void setSmoothness(int);
    void setHeightOffset(int);
    void setRoughness(double);

    int getOctaves();
    int getAmplitude();
    int getSmoothness();
    int getHeightOffset();
    double getRoughness();


};

#endif // NOISEPRESENTER_H_INCLUDED
