#pragma once
#ifndef _VECTOR2_H_INCLUDED
#define _VECTOR2_H_INCLUDED
#include <iostream>
struct Vector2 {
	float x;
	float y;
	float length;

	static Vector2 Origin;


	Vector2();
	Vector2(float, float);
	Vector2(float);


	float calculateLength();
	float squaredLength();
	float normalizar();

	Vector2& operator=(Vector2& rightSide);
	Vector2& operator+=(Vector2& rightSide);
	Vector2& operator-=(Vector2& rightSide);
	Vector2& operator/=(Vector2& rightSide);
	Vector2& operator+(Vector2& rightSide);
	Vector2& operator-(Vector2& rightSide);
	Vector2& operator*(Vector2& rightSide);
	Vector2& operator*=(Vector2& rightSide);
	Vector2& operator/(Vector2& rightSide);
	bool operator==(Vector2& rightSide);
	bool operator!=(Vector2& rightSide);
	friend Vector2 operator*(float, Vector2& rightSide);
	friend Vector2 operator*(Vector2& rightSide, float);
	};









#endif // _VECTOR2_H_INCLUDED
