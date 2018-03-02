#pragma once
#ifndef _VECTOR3_H_INCLUDED
#define _VECTOR3_H_INCLUDED

struct Vector3 {
	float x;
	float y;
	float z;
	float length;

	static Vector3 Origin;


	Vector3();
	Vector3(float, float, float);
	Vector3(float);


	float calculateLength();
	float squaredLength();
	float normalizar();

	Vector3& operator=(Vector3& rightSide);
	Vector3& operator+=(Vector3& rightSide);
	Vector3& operator-=(Vector3& rightSide);
	Vector3& operator/=(Vector3& rightSide);
	Vector3& operator+(Vector3& rightSide);
	Vector3& operator-(Vector3& rightSide);
	Vector3& operator*(Vector3& rightSide);
	Vector3& operator*=(Vector3& rightSide);
	Vector3& operator/(Vector3& rightSide);
	bool operator==(Vector3& rightSide);
	bool operator!=(Vector3& rightSide);
	friend Vector3 operator*(float, Vector3& rightSide);
	friend Vector3 operator*(Vector3& rightSide, float);
};












#endif // !_VECTOR3_H_INCLUDED

