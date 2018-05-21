#include "BeiDou.h"


BeiDou::BeiDou()
{
    Init();
}

BeiDou::~BeiDou()
{
}

int BeiDou::Init()
{
    heading = 359;
    longitude = 108.938729;
    latitude = 34.224500;

    return 0;
}

int BeiDou::getPosition(int *headVal, float *longitudeVal, float *latitudeVal)
{
    *headVal = heading;
    *longitudeVal = longitude;
    *latitudeVal = latitude;
    return 0;
}


// BeiDou message handler
void BeiDou::OnPositionChange()
{

}

void BeiDou::update()
{

}
