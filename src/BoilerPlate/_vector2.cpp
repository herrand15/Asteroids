#include "_vector2.hpp"
#include <cmath>



Vector2 Vector2::Origin = Vector2();

Vector2::Vector2() {
	x = 0.0f;
	y = 0.0f;
	length = 0.0f;
}

Vector2::Vector2(float x_, float y_)
	: x(x_)
	, y(y_)
	, length(0.0f)
{
	calculateLength();
}

float Vector2::calculateLength() {
	return std::sqrt((x*x) + y * y);

}
float Vector2::squaredLength() {
	return (x*x) + (y*y);
}

float Vector2::normalizar() {
	calculateLength();
	
	float inverse = 1.0f / length; //para reducir la cantidad de operaciones que tendremos que realizar
	x *= inverse;
	y *= inverse;
	return length;
}

Vector2& Vector2::operator=(Vector2& rightSide)
{
	// Prevent self assignment
	if (this == &rightSide) return *this;

	x = rightSide.x;
	y = rightSide.y;

	return *this;
}

Vector2& Vector2::operator+=( Vector2& rightSide)
{
	x = x + rightSide.x;
	y = y + rightSide.y;

	return *this;
}

Vector2& Vector2::operator-=( Vector2& rightSide)
{
	x = x - rightSide.x;
	y = y - rightSide.y;

	return *this;
}

Vector2& Vector2::operator*=( Vector2& rightSide)
{
	x = x * rightSide.x;
	y = y * rightSide.y;

	return *this;
}

Vector2& Vector2::operator/=( Vector2& rightSide)
{
	if (rightSide.x == 0) {
		throw "Can't divide by 0";
	}
	if (rightSide.y == 0) {
		throw "Can't divide by 0";
	}
	x = x / rightSide.x;
	y = y / rightSide.y;

	return *this;
}


Vector2& Vector2::operator+( Vector2& rightSide) 
{
	return Vector2(
		x + rightSide.x,
		y + rightSide.y);
}

Vector2& Vector2::operator-(Vector2& rightSide) 
{
	return Vector2(
		x - rightSide.x,
		y - rightSide.y);
}

Vector2& Vector2::operator*( Vector2& rightSide) 
{
	return Vector2(
		x * rightSide.x,
		y * rightSide.y);
}

Vector2& Vector2::operator/( Vector2& rightSide) 
{
	if (rightSide.x == 0) throw "Division by zero is not defined!";
	if (rightSide.y == 0) throw "Division by zero is not defined!";

	return Vector2(
		x / rightSide.x,
		y / rightSide.y);
}

bool Vector2::operator==( Vector2& rightSide) 
{
	return
		x == rightSide.x &&
		y == rightSide.y;
}

bool Vector2::operator!=( Vector2& rightSide) 
{
	return
		x != rightSide.x ||
		y != rightSide.y;
}

Vector2 operator*(float scaleUnit,  Vector2& rightSide)
{
	return Vector2(
		scaleUnit * rightSide.x,
		scaleUnit * rightSide.y);
}

Vector2 operator*( Vector2& lhs, float scaleUnit)
{
	return Vector2(
		scaleUnit * lhs.x,
		scaleUnit * lhs.y);
}

