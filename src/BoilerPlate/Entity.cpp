#include "Entity.h"

Entity::Entity() {};

Entity::Entity(float width_ , float height_) {
	width = width_;
	height = height_;
	directionAngle = 0.0f;
}



float Warp(float position, float maxP, float minP) {
	if (position < minP) {
		return maxP - (minP - position);
	}
	if (position > maxP) {
		return minP + (position - maxP);
	}
	return position;
}