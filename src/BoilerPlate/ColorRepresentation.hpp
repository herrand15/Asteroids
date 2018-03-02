#ifndef COLORREPRESENTATION_H_INCLUDED
#define COLORREPRESENTATION_H_INCLUDED
#include "Color.h"

class ColorRepresentation {
	public:
		Color red;
		Color green;
		Color white;
		Color yellow;
		Color orange;
		Color midnightBlue;

	ColorRepresentation();
	Color turnRed();
	Color turnGreen();
	Color turnYellow();
	Color turnOrange();
	Color turnWhite();
};

#endif // COLORREPRESENTATION_H_INCLUDED
