#include "common.h"

double Abs(double x)
{
    if (x < 0)
        return -x;
    else
        return x;
}

double TicksToDeg(int ticks)
{
    return ticks * DEG_PER_TICK;
}

int DegToTicks(double deg)
{
    return int(deg / DEG_PER_TICK);
}

double TicksToRad(int ticks)
{
    return DegToRad(TicksToDeg(ticks));
}

int RadToTicks(double rad)
{
    return DegToTicks(RadToDeg(rad));
}

double DegToRad(double deg)
{
    return deg * (PI / 180);
}

double RadToDeg(double rad)
{
    return rad * (180 / PI);
}

