#ifndef __CANVAS__
#define __CANVAS__

#include "Color.h"

typedef struct Canvas Canvas;

struct Canvas {
  Color *pixels;
  int width;
  int height;
};

Canvas Canvas_Create(int width, int height);
void Canvas_Destroy(Canvas canvas);
void Canvas_WritePixel(Canvas canvas, int x, int y, Color color);
Color Canvas_PixelAt(const Canvas canvas, int x, int y);
void Canvas_WriteToPPM(const Canvas canvas, const char *filename);
void Canvas_FillColor(Canvas canvas, Color color);

#endif /* __CANVAS__ */
