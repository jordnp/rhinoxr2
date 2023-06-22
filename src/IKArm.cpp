#include "IKArm.h"

#include <cmath>
using namespace std;


IKArm::IKArm(double length0, double length1)
{
	length[0] = length0;
	length[1] = length1;
}

double IKArm::CompAng2(double x, double y)
{
	double tempN = pow(x, 2.0) + pow(y, 2.0)
		- pow(length[0], 2.0) - pow(length[1], 2.0);
	double tempD = 2.0 * length[0] * length[1];
	return acos(tempN / tempD);
}

double IKArm::CompAng1(double x, double y, double Ang2)
{
	double tempN = length[0] * sin(Ang2);
	double tempD = pow((pow(x, 2.0) + pow(y, 2.0)), .5);
	return asin(tempN / tempD) + atan(y / x);
}
#include<stdio.h>
AnglePair IKArm::GetAnglePair(Point xy)
{
	double angle1, angle2;
	AnglePair Pair;
	angle2 = CompAng2(xy.x, xy.y);
	angle1 = CompAng1(xy.x, xy.y, angle2);

	angle1 = angle1;
	angle2 = angle2;

	Pair.ang1 = angle1;
	Pair.ang2 = angle2;

	return Pair;
}

