#include "ColorRepresentation.hpp"

ColorRepresentation::ColorRepresentation() {
	red = Color(1.0f, 0.0f, 0.0f, 1.0f);
	green = Color(0.0f, 1.0f, 0.0f, 1.0f);
	white = Color(1.0f, 1.0f, 1.0f, 1.0f);
	yellow = Color(1.0f, 1.0f, 0.0f, 1.0f);
	orange = Color(1.0f, 0.5f, 0.0f, 1.0f);
	midnightBlue = Color(0.184f, 0.184f, 0.309f, 1.0f);
}

Color ColorRepresentation::turnRed() {
	return red;
}
Color ColorRepresentation::turnGreen() {
	return green;
}
Color ColorRepresentation::turnYellow() {
	return yellow;
}
Color ColorRepresentation::turnOrange() {
	return orange;
}
Color ColorRepresentation::turnWhite() {
	return white;
}