#include "Canvas.h"
#include <stdlib.h>
#include <stdbool.h>

static bool CanvasOutOfBounds(Canvas canvas, int x, int y)
{
	if(x > canvas.width | x < 0)
	{
		return true;
	}

	if(y > canvas.height | y < 0)
	{
		return true;
	}
	return false;
}

Canvas Canvas_Create(int width, int height)
{
	Canvas canvas = {(Color*)calloc(width * height, sizeof(Color)),
		width, height};
	return canvas;
}

void Canvas_Destroy(Canvas canvas)
{
	free(canvas.pixels);
}

void Canvas_WritePixel(Canvas canvas, int x, int y, Color color)
{
	if(CanvasOutOfBounds(canvas, x, y))
	{
		/* Error message? */
		return;
	}

	int pixelOffset = y * canvas.width + x;
	canvas.pixels[pixelOffset] = color;
}

Color Canvas_PixelAt(Canvas canvas, int x, int y)
{
	if(CanvasOutOfBounds(canvas, x, y))
	{
		/* Error message? */
		return Color_Create(0, 0, 0);
	}

	int pixelOffset = y * canvas.width + x;
	return canvas.pixels[pixelOffset];
}
