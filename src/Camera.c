#include "Camera.h"
#include <math.h>

Camera Camera_Create(int hsize, int vsize, float fieldOfView)
{
	float halfView, aspect, halfWidth, halfHeight, pixelSize;
	halfView = tanf(fieldOfView / 2);
	aspect = (float)hsize / (float)vsize;
	if(aspect >= 1)
	{
		halfWidth = halfView;
		halfHeight = halfView / aspect;
	}
	else{
		halfWidth = halfView * aspect;
		halfHeight = halfView;
	}
	pixelSize = halfWidth * 2 / hsize;

	Camera c = {
		.hsize = hsize,
		.vsize = vsize,
		.fieldOfView = fieldOfView,
		.transform = Matrix_Identity(4),
		.halfWidth = halfWidth,
		.halfHeight = halfHeight,
		.pixelSize = pixelSize
	};
	return c;
}

Ray Camera_RayForPixel(Camera c, int pixelX, int pixelY)
{
	float xOffset = (pixelX + 0.5) * c.pixelSize;
	float yOffset = (pixelY + 0.5) * c.pixelSize;

	float worldX = c.halfWidth - xOffset;
	float worldY = c.halfHeight - yOffset;

	Matrix inverse = Matrix_Inverse(c.transform);
	Tuple pixel = Matrix_MultiplyTuple(
			inverse,
			Tuple_CreatePoint(worldX, worldY, -1)
			);
	Tuple origin = Matrix_MultiplyTuple(
			inverse,
			Tuple_CreatePoint(0, 0, 0)
			);

	Tuple direction = Tuple_Normalize(
			Tuple_Subtract(pixel, origin)
			);
	Matrix_Destroy(&inverse);
	Ray ray = Ray_Create(origin, direction);
	return ray;
}

Canvas Camera_Render(Camera c, World world)
{
	Canvas canvas = Canvas_Create(c.hsize, c.vsize);
	Ray ray;
	Color color;

	for(int y = 0; y < c.vsize; y++)
	{
		for(int x = 0; x < c.hsize; x++)
		{
			ray = Camera_RayForPixel(c, x, y);
			color = World_ColorAt(world, ray);
			Canvas_WritePixel(canvas, x, y, color);
		}
	}
	return canvas;
}
