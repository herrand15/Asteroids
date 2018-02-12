#include "_vector3.h"
#include <cmath>



Vector3 Vector3::Origin = Vector3();

Vector3::Vector3() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	length = 0.0f;
}

Vector3::Vector3(float x_, float y_, float z_)
	: x(x_)
	, y(y_)
	, z(z_)
	, length(0.0f)
{
	calculateLength();
}

float Vector3::calculateLength() {
	return std::sqrt((x*x) + (y * y) + (z*z) );

}
float Vector3::squaredLength() {
	return (x*x) + (y*y) + (z*z);
}

float Vector3::normalizar() {
	calculateLength();

	float inverse = 1.0f / length; //para reducir la cantidad de operaciones que tendremos que realizar
	x *= inverse;
	y *= inverse;
	z *= inverse;
	return length;
}

Vector3& Vector3::operator=(Vector3& rightSide)
{
	
	if (this == &rightSide) return *this;

	x = rightSide.x;
	y = rightSide.y;
	z = rightSide.z;

	return *this;
}

Vector3& Vector3::operator+=(Vector3& rightSide)
{
	x = x + rightSide.x;
	y = y + rightSide.y;
	z = z + rightSide.z;

	return *this;
}

Vector3& Vector3::operator-=(Vector3& rightSide)
{
	x = x - rightSide.x;
	y = y - rightSide.y;
	z = z - rightSide.z;

	return *this;
}

Vector3& Vector3::operator*=(Vector3& rightSide)
{
	x = x * rightSide.x;
	y = y * rightSide.y;
	z = z * rightSide.z;

	return *this;
}

Vector3& Vector3::operator/=(Vector3& rightSide)
{
	if (rightSide.x == 0) {
		throw "Can't divide by 0";
	}
	if (rightSide.y == 0) {
		throw "Can't divide by 0";
	}
	x = x / rightSide.x;
	y = y / rightSide.y;
	z = z / rightSide.z;

	return *this;
}


Vector3& Vector3::operator+(Vector3& rightSide)
{
	return Vector3(
		x + rightSide.x,
		z + rightSide.z,
		y + rightSide.y);
}

Vector3& Vector3::operator-(Vector3& rightSide)
{
	return Vector3(
		x - rightSide.x,
		z - rightSide.z,
		y - rightSide.y);
}

Vector3& Vector3::operator*(Vector3& rightSide)
{
	return Vector3(
		x * rightSide.x,
		z * rightSide.z,
		y * rightSide.y);
}

Vector3& Vector3::operator/(Vector3& rightSide)
{
	if (rightSide.x == 0) throw "Division by zero is not defined!";
	if (rightSide.y == 0) throw "Division by zero is not defined!";

	return Vector3(
		x / rightSide.x,
		z / rightSide.z,
		y / rightSide.y);
}

bool Vector3::operator==(Vector3& rightSide)
{
	return
		x == rightSide.x &&
		y == rightSide.y;
}

bool Vector3::operator!=(Vector3& rightSide)
{
	return
		x != rightSide.x ||
		y != rightSide.y;
}

Vector3 operator*(float scaleUnit, Vector3& rightSide)
{
	return Vector3(
		scaleUnit * rightSide.x,
		scaleUnit * rightSide.z,
		scaleUnit * rightSide.y);
}

Vector3 operator*(Vector3& leftSide, float scaleUnit)
{
	return Vector3(
		scaleUnit * leftSide.x,
		scaleUnit * leftSide.x,
		scaleUnit * leftSide.y);
}

