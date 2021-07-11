#ifndef __COLOR__
#define __COLOR__

typedef struct Color Color;

struct Color{
	float red;
	float green;
	float blue;
};

Color Color_Create(float red, float green, float blue);
Color Color_Add(Color color1, Color color2);

#endif /* __COLOR__ */
