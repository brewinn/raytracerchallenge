#ifndef __COLOR__
#define __COLOR__

typedef struct Color Color;

struct Color{
	float red;
	float green;
	float blue;
};

Color Color_Create(float red, float green, float blue);

#endif /* __COLOR__ */
