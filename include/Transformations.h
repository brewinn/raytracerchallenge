#ifndef __TRANSFORMATIONS__
#define __TRANSFORMATIONS__

#include "Matrix.h"

Matrix Transformation_Translation(float x, float y, float z);
Matrix Transformation_Scale(float x, float y, float z);
Matrix Transformation_RotationX(float radians);
Matrix Transformation_RotationY(float radians);
Matrix Transformation_RotationZ(float radians);

#endif /* __TRANSFORMATIONS__ */
