#include "Transformations.h"

Matrix Transformation_Translation(float x, float y, float z)
{
	Matrix translation =  Matrix_Identity(4);
	Matrix_SetValue(translation, 0, 3, x);
	Matrix_SetValue(translation, 1, 3, y);
	Matrix_SetValue(translation, 2, 3, z);
	return translation;
}
