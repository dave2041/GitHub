#define _USE_MATH_DEFINES
#include <stdexcept>
#include <math.h>
#include <iostream>
const int ki_InchesInAMile = 63360;
const double kd_MMToInches = 0.0393700787;

using namespace std;

double GearsToMoD(double dWheelInInches, double dFrontChainRing, double dRearChainRing)
{
	if (dFrontChainRing == 0 || dRearChainRing == 0)
		throw invalid_argument("Cannot be zero!");

	return dWheelInInches*(dFrontChainRing / dRearChainRing);
}

double MoDToSpeed(double dMoD, double dCadence)
{
	return (((dMoD*M_PI)*dCadence) * 60) / ki_InchesInAMile;
}

double SpeedToCadence(double dCadence, double dGearInches)
{
	return ((dCadence * ki_InchesInAMile) / 60) / (dGearInches*M_PI);
}

int main()
{
	double dGears, dFront, dRear;
	dGears = (622 + (2 * 25))*kd_MMToInches;
	dFront = 48;
	dRear = 20;
	double dMoD = GearsToMoD(dGears, dFront, dRear);
	double dSpeed = MoDToSpeed(dMoD, 75);
	double dCadence = SpeedToCadence(29.5, dMoD);

	cout << "Speed of " << dFront << "x" << dRear << " is: " << dSpeed << endl;
	system("pause");
	return 0;
}