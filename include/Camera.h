
#ifndef __CAMERA__
#define __CAMERA__

#include "Matrix.h"
#include "Ray.h"
#include "Canvas.h"
#include "World.h"

typedef struct Camera{
	int hsize;
	int vsize;
	float fieldOfView;
	Matrix transform;
	float halfWidth;
	float halfHeight;
	float pixelSize;
} Camera;

Camera Camera_Create(int hsize, int vsize, float fieldOfView);
Ray Camera_RayForPixel(Camera c, int pixelX, int pixelY);
Canvas Camera_Render(Camera c, World world);

#endif /* __CAMERA__ */

