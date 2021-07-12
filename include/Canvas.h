#ifndef __CANVAS__
#define __CANVAS__

#include "Color.h"

typedef struct Canvas Canvas;

struct Canvas{
	Color * pixels;
	int width;
	int height;
};

Canvas Canvas_Create(int width, int height);
void Canvas_Destroy(Canvas canvas);
void Canvas_WritePixel(Canvas canvas, int x, int y, Color color);
Color Canvas_PixelAt(Canvas canvas, int x, int y);

#endif /* __CANVAS__ */
