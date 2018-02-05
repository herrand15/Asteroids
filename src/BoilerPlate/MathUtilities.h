#ifndef MATHUTILITIES_H_INCLUDED
#define MATHUTILITIES_H_INCLUDED

#include <iostream>
using namespace std;


class MathUtilities {
};

int nearestInt(float g);

int floatToEvenInt(float g);

template <class anyNumber>
anyNumber maximumNum(anyNumber a) {
	return a;
}

template <class anyNumber, class ... Args>
anyNumber maximumNum(anyNumber a, Args ... type) {
	return max(a, maximumNum(type));
} 

template <class anyNumber>
anyNumber minimumNum(anyNumber a) {
	return a;
}
template <class anyNumber, class ... Args>
anyNumber minimumNum(anyNumber a, Args ... type) {
	return min(a, minimumNum(type));

}



float range(float value, float low, float high);

float degreeToRadians(float angle);
float radiansToDegree(float angle);

float angularDistance(float a, float b);

bool isPowerOfTwo(int x);

float interpolate(float percentage, float low, float high);


 #endif // MATHUTILITIES_H_INCLUDED