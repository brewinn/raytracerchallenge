#include "Canvas.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_LINE_WIDTH 70

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

static int ColorFloatToInt(float colorComponent)
{
	if(colorComponent < 0)
		return 0;
	if(colorComponent > 1)
		return 255;
	return colorComponent * 255;
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
		return;
	}

	int pixelOffset = y * canvas.width + x;
	canvas.pixels[pixelOffset] = color;
}

Color Canvas_PixelAt(Canvas canvas, int x, int y)
{
	if(CanvasOutOfBounds(canvas, x, y))
	{
		fprintf(stderr, "Warning, attempted to read out-of-bounds pixel!\n");
		return Color_Create(0, 0, 0);
	}

	int pixelOffset = y * canvas.width + x;
	return canvas.pixels[pixelOffset];
}

static FILE* FileOpen(const char * filename)
{
	FILE * file;
	file  = fopen(filename, "w");
	if(!file)
	{
		fprintf(stderr, "Failed to open file, aborting...");
		exit(-1);
	}
	return file;
}

static int NumberWidth(int number)
{
	char numberString[20];
	sprintf(numberString, "%d", number);
	int length = 0;
	while(numberString[length] != '\0')
		++length;
	return length;
}

static void WritePPMHeader(FILE * ppm, Canvas canvas)
{
	fprintf(ppm, "P3\n");
	fprintf(ppm, "%d %d\n", canvas.width, canvas.height);
	fprintf(ppm, "255\n");
}

static void WriteFormatedInteger(FILE * ppm, int colorComponent, int * lineWidthPointer)
{
	if(*lineWidthPointer + NumberWidth(colorComponent) >= MAX_LINE_WIDTH)
	{
		fseek(ppm, -1, SEEK_CUR);
		fprintf(ppm, "\n");
		*lineWidthPointer = 0;
	}
	fprintf(ppm, "%d ", colorComponent);
	*lineWidthPointer += NumberWidth(colorComponent) + 1;
	return;
}

static void WriteColor(FILE * ppm, Color color, int * lineWidthPointer)
{
	int r, g, b;
	r = ColorFloatToInt(color.red);
	g = ColorFloatToInt(color.green);
	b = ColorFloatToInt(color.blue);

	WriteFormatedInteger(ppm, r, lineWidthPointer);
	WriteFormatedInteger(ppm, g, lineWidthPointer);
	WriteFormatedInteger(ppm, b, lineWidthPointer);

	return;
}

static void SetNewRow(FILE * ppm, int * lineWidthPointer)
{
	fseek(ppm, -1, SEEK_CUR);
	fprintf(ppm, "\n");
	*lineWidthPointer = 0;
	return;
}

static void WritePPMBody(FILE * ppm, Canvas canvas)
{
	int lineWidth = 0;
	for(int y = 0; y < canvas.height; y++)
	{
		for(int x = 0; x < canvas.width; x++)
		{
			Color color = Canvas_PixelAt(canvas, x, y);
			WriteColor(ppm, color, &lineWidth);
		}
		SetNewRow(ppm, &lineWidth);
	}
}

void Canvas_WriteToPPM(const char * filename, Canvas canvas)
{
	FILE * ppm;
	ppm = FileOpen(filename);
	WritePPMHeader(ppm, canvas);
	WritePPMBody(ppm, canvas);
	fclose(ppm);
}

void Canvas_FillColor(Canvas canvas, Color color)
{
	for(int x = 0; x < canvas.width; x++)
		for(int y = 0; y < canvas.height; y++)
			Canvas_WritePixel(canvas, x, y, color);
	return;
}
