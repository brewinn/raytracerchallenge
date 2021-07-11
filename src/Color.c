#include "Color.h"

Color Color_Create(float red, float green, float blue)
{
	Color color = {red, green, blue};
	return color;
}

Color Color_Add(Color color1, Color color2)
{
	float red, green, blue;
	red = color1.red + color2.red;
	green = color1.green + color2.green;
	blue = color1.blue + color2.blue;
	return Color_Create(red, green, blue);
}
