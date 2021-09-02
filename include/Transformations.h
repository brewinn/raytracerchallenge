#ifndef __TRANSFORMATIONS__
#define __TRANSFORMATIONS__

#include "Matrix.h"

Matrix Transformation_Translation(float x, float y, float z);
Matrix Transformation_Scale(float x, float y, float z);
Matrix Transformation_RotationX(float radians);
Matrix Transformation_RotationY(float radians);
Matrix Transformation_RotationZ(float radians);
Matrix Transformation_Shear(float Xy, float Xz, float Yx, float Yz, float Zx, float Zy);
Matrix Transformation_ViewTransform(Tuple from, Tuple to, Tuple up);

#endif /* __TRANSFORMATIONS__ */
