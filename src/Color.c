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

Color Color_Subtract(Color color1, Color color2)
{
	float red, green, blue;
	red = color1.red - color2.red;
	green = color1.green - color2.green;
	blue = color1.blue - color2.blue;
	return Color_Create(red, green, blue);
}

Color Color_ScalarMultiply(Color color, float scalar)
{
	float red, green, blue;
	red = color.red * scalar;
	green = color.green * scalar;
	blue = color.blue * scalar;
	return Color_Create(red, green, blue);
}

Color Color_Multiply(Color color1, Color color2)
{
	float red, green, blue;
	red = color1.red * color2.red;
	green = color1.green * color2.green;
	blue = color1.blue * color2.blue;
	return Color_Create(red, green, blue);
}
