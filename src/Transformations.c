#include "Transformations.h"

Matrix Transformation_Translation(float x, float y, float z)
{
	Matrix translation =  Matrix_Identity(4);
	Matrix_SetValue(translation, 0, 3, x);
	Matrix_SetValue(translation, 1, 3, y);
	Matrix_SetValue(translation, 2, 3, z);
	return translation;
}

Matrix Transformation_Scale(float x, float y, float z)
{
	Matrix scale = Matrix_Create(4, 4);
	Matrix_SetValue(scale, 0, 0, x);
	Matrix_SetValue(scale, 1, 1, y);
	Matrix_SetValue(scale, 2, 2, z);
	Matrix_SetValue(scale, 3, 3, 1);
	return scale;
}
