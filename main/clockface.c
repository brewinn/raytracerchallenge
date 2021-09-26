#include "Transformations.h"
#include "Canvas.h"
#include <math.h>

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

int main(void)
{
	int canvasWidth = 80, canvasHeight = 80;
	Canvas canvas = Canvas_Create(canvasWidth, canvasHeight);

	Tuple point = Tuple_CreatePoint(0, 0, 1);
	Matrix rotation = Transformation_RotationY(M_PI/6);
	Matrix scale = Transformation_Scale(canvasWidth * 3 / 8, 0, canvasHeight * 3 / 8);
	Matrix translation = Transformation_Translation(canvasWidth/2, 0, canvasHeight/2);

	Color white = Color_Create(1, 1, 1);
	Tuple pixel = Matrix_MultiplyTuple(scale, point);
	pixel = Matrix_MultiplyTuple(translation, pixel);
	Canvas_WritePixel(canvas, pixel.x, canvasHeight - pixel.z, white);
	for(int k = 0; k < 12; k++)
	{
		point = Matrix_MultiplyTuple(rotation, point);
		pixel = Matrix_MultiplyTuple(scale, point);
		pixel = Matrix_MultiplyTuple(translation, pixel);
		Canvas_WritePixel(canvas, pixel.x, canvasHeight - pixel.z, white);
	}

	Matrix_Destroy(&rotation);
	Matrix_Destroy(&scale);
	Matrix_Destroy(&translation);

	Canvas_WriteToPPM(canvas, "clockface.ppm");
	Canvas_Destroy(canvas);

	return 0;
}

