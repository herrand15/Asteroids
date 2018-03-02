#include "ColorRepresentation.hpp"

ColorRepresentation::ColorRepresentation() {
	red = Color(1.0, 0.0, 0.0, 1.0);
	green = Color(0.0, 1.0, 0.0, 1.0);
	white = Color(1.0, 1.0, 1.0, 1.0);
	yellow = Color(1.0, 1.0, 0.0, 1.0);
	orange = Color(1.0, 0.5, 0.0, 1.0);
	midnightBlue = Color(0.184, 0.184, 0.309, 1.0);
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