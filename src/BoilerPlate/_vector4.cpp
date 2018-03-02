#include "_vector4.hpp"
#include <cmath>



Vector4 Vector4::Origin = Vector4();

Vector4::Vector4() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
	length = 0.0f;
}

Vector4::Vector4(float x_, float y_, float z_, float w_)
	: x(x_)
	, y(y_)
	, z(z_)
	, length(0.0f)
{
	calculateLength();
}

float Vector4::calculateLength() {
	return std::sqrt((x*x) + (y * y) + (z*z));

}
float Vector4::squaredLength() {
	return (x*x) + (y*y) + (z*z);
}

float Vector4::normalizar() {
	calculateLength();

	float inverse = 1.0f / length; //para reducir la cantidad de operaciones que tendremos que realizar
	x *= inverse;
	y *= inverse;
	z *= inverse;
	w *= inverse;
	return length;
}

Vector4& Vector4::operator=(Vector4& rightSide)
{
	
	if (this == &rightSide) return *this;

	x = rightSide.x;
	y = rightSide.y;
	z = rightSide.z;

	return *this;
}

Vector4& Vector4::operator+=(Vector4& rightSide)
{
	x = x + rightSide.x;
	y = y + rightSide.y;
	z = z + rightSide.z;
	w = w + rightSide.w;

	return *this;
}

Vector4& Vector4::operator-=(Vector4& rightSide)
{
	x = x - rightSide.x;
	y = y - rightSide.y;
	z = z - rightSide.z;
	w = w - rightSide.w;
	return *this;
}

Vector4& Vector4::operator*=(Vector4& rightSide)
{
	x = x * rightSide.x;
	y = y * rightSide.y;
	z = z * rightSide.z;
	w = w * rightSide.w;
	return *this;
}

Vector4& Vector4::operator/=(Vector4& rightSide)
{
	if (rightSide.x == 0) {
		throw "Can't divide by 0";
	}
	if (rightSide.y == 0) {
		throw "Can't divide by 0";
	}
	if (rightSide.z == 0) {
		throw "Can't divide by 0";
	}
	if (rightSide.w == 0) {
		throw "Can't divide by 0";
	}

	x = x / rightSide.x;
	y = y / rightSide.y;
	z = z / rightSide.z;
	w = w / rightSide.w;
	return *this;
}


Vector4& Vector4::operator+(Vector4& rightSide)
{
	return Vector4(
		x + rightSide.x,
		z + rightSide.z,
		y + rightSide.y,
		w + rightSide.w);
}

Vector4& Vector4::operator-(Vector4& rightSide)
{
	return Vector4(
		x - rightSide.x,
		z - rightSide.z,
		y - rightSide.y,
		w - rightSide.w);
}

Vector4& Vector4::operator*(Vector4& rightSide)
{
	return Vector4(
		x * rightSide.x,
		z * rightSide.z,
		y * rightSide.y,
		w * rightSide.w);
}

Vector4& Vector4::operator/(Vector4& rightSide)
{
	if (rightSide.x == 0) throw "Division by zero is not defined!";
	if (rightSide.y == 0) throw "Division by zero is not defined!";

	return Vector4(
		x / rightSide.x,
		z / rightSide.z,
		y / rightSide.y,
		w / rightSide.w);
}

bool Vector4::operator==(Vector4& rightSide)
{
	return
		x == rightSide.x &&
		y == rightSide.y;
}

bool Vector4::operator!=(Vector4& rightSide)
{
	return
		x != rightSide.x ||
		y != rightSide.y ||
		z != rightSide.z ||
		w != rightSide.w;
}

Vector4 operator*(float scaleUnit, Vector4& rightSide)
{
	return Vector4(
		scaleUnit * rightSide.x,
		scaleUnit * rightSide.z,
		scaleUnit * rightSide.y,
		scaleUnit * rightSide.w);
}

Vector4 operator*(Vector4& leftSide, float scaleUnit)
{
	return Vector4(
		scaleUnit * leftSide.x,
		scaleUnit * leftSide.x,
		scaleUnit * leftSide.y,
		scaleUnit * leftSide.w);
}
