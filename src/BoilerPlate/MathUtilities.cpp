#include "MathUtilities.h"
#include <iostream>
#include <math.h>
using namespace std;

 int nearestInt(float g) {
	float intPart=0;
	float decimalPart = modf(g, &intPart);
	int returnValue;
	
	if (decimalPart >= 0.5) {
		returnValue = int( intPart + 1);
	}
	else{
		returnValue = int(intPart);
	}
	return returnValue;
}

int floatToEvenInt(float g) {
	float intPart=0;
	float decimalPart = modf(g, &intPart);

	float faltante = 1 - decimalPart;

	int returnValue;

	if ((int)intPart % 2 == 0) {
		returnValue = (int)intPart;
	}
	if ((int)intPart % 2 != 0 ) {
		returnValue = (int)intPart+1;
	}

	return returnValue;

}

float range(float value, float low, float high) {
	if (value < low) {
		value = value + (low - value);
	}
	else if (value > high) {
		value = value - (value - high);
	}
	return value;
}

float degreeToRadians(float angle) {
	return (angle *3.14159) / 180;
}

float radiansToDegree(float angle) {
	return (angle * 180) / 3.14159;
}

float angularDistance(float a, float b) {
	return a - b;
}

bool isPowerOfTwo(int x) {
	if (x == 0) return false;

	bool is_pow = !(x & (x - 1));
	return is_pow;
}

float interpolate(float percentage, float low, float high) {
	float diff = (high - low);
	float percent = diff * percentage;

		return (high - diff) + percent;
}






