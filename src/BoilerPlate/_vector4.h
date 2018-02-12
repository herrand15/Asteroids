#pragma once
#pragma once
#ifndef _Vector4_H_INCLUDED
#define _Vector4_H_INCLUDED

struct Vector4 {
	float x;
	float y;
	float z;
	float w;
	float length;

	static Vector4 Origin;


	Vector4();
	Vector4(float, float, float, float);
	Vector4(float);


	float calculateLength();
	float squaredLength();
	float normalizar();

	Vector4& operator=(Vector4& rightSide);
	Vector4& operator+=(Vector4& rightSide);
	Vector4& operator-=(Vector4& rightSide);
	Vector4& operator/=(Vector4& rightSide);
	Vector4& operator+(Vector4& rightSide);
	Vector4& operator-(Vector4& rightSide);
	Vector4& operator*(Vector4& rightSide);
	Vector4& operator*=(Vector4& rightSide);
	Vector4& operator/(Vector4& rightSide);
	bool operator==(Vector4& rightSide);
	bool operator!=(Vector4& rightSide);
	friend Vector4 operator*(float, Vector4& rightSide);
	friend Vector4 operator*(Vector4& rightSide, float);
};





#endif // !_Vector4_H_INCLUDED
