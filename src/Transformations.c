#include "Transformations.h"
#include <math.h>

Matrix Transformation_Translation(float x, float y, float z) {
  Matrix translation = Matrix_Identity(4);
  Matrix_SetValue(translation, 0, 3, x);
  Matrix_SetValue(translation, 1, 3, y);
  Matrix_SetValue(translation, 2, 3, z);
  return translation;
}

Matrix Transformation_Scale(float x, float y, float z) {
  Matrix scale = Matrix_Create(4, 4);
  Matrix_SetValue(scale, 0, 0, x);
  Matrix_SetValue(scale, 1, 1, y);
  Matrix_SetValue(scale, 2, 2, z);
  Matrix_SetValue(scale, 3, 3, 1);
  return scale;
}

Matrix Transformation_RotationX(float radians) {
  Matrix rotation = Matrix_Create(4, 4);
  Matrix_SetValue(rotation, 0, 0, 1);
  Matrix_SetValue(rotation, 1, 1, cosf(radians));
  Matrix_SetValue(rotation, 1, 2, -sinf(radians));
  Matrix_SetValue(rotation, 2, 1, sinf(radians));
  Matrix_SetValue(rotation, 2, 2, cosf(radians));
  Matrix_SetValue(rotation, 3, 3, 1);
  return rotation;
}

Matrix Transformation_RotationY(float radians) {
  Matrix rotation = Matrix_Create(4, 4);
  Matrix_SetValue(rotation, 0, 0, cosf(radians));
  Matrix_SetValue(rotation, 0, 2, sinf(radians));
  Matrix_SetValue(rotation, 1, 1, 1);
  Matrix_SetValue(rotation, 2, 0, -sinf(radians));
  Matrix_SetValue(rotation, 2, 2, cosf(radians));
  Matrix_SetValue(rotation, 3, 3, 1);
  return rotation;
}

Matrix Transformation_RotationZ(float radians) {
  Matrix rotation = Matrix_Create(4, 4);
  Matrix_SetValue(rotation, 0, 0, cosf(radians));
  Matrix_SetValue(rotation, 0, 1, -sinf(radians));
  Matrix_SetValue(rotation, 1, 0, sinf(radians));
  Matrix_SetValue(rotation, 1, 1, cosf(radians));
  Matrix_SetValue(rotation, 2, 2, 1);
  Matrix_SetValue(rotation, 3, 3, 1);
  return rotation;
}

Matrix Transformation_Shear(float Xy, float Xz, float Yx, float Yz, float Zx,
                            float Zy) {
  Matrix shear = Matrix_Identity(4);
  Matrix_SetValue(shear, 0, 1, Xy);
  Matrix_SetValue(shear, 0, 2, Xz);
  Matrix_SetValue(shear, 1, 0, Yx);
  Matrix_SetValue(shear, 1, 2, Yz);
  Matrix_SetValue(shear, 2, 0, Zx);
  Matrix_SetValue(shear, 2, 1, Zy);
  return shear;
}

Matrix Transformation_ViewTransform(Tuple from, Tuple to, Tuple up) {
  Tuple forward = Tuple_Normalize(Tuple_Subtract(to, from));
  Tuple left = Tuple_Cross(forward, Tuple_Normalize(up));
  Tuple trueUp = Tuple_Cross(left, forward);
  Matrix orientation = Matrix_Create(4, 4);

  Matrix_SetValue(orientation, 0, 0, left.x);
  Matrix_SetValue(orientation, 0, 1, left.y);
  Matrix_SetValue(orientation, 0, 2, left.z);

  Matrix_SetValue(orientation, 1, 0, trueUp.x);
  Matrix_SetValue(orientation, 1, 1, trueUp.y);
  Matrix_SetValue(orientation, 1, 2, trueUp.z);

  Matrix_SetValue(orientation, 2, 0, -forward.x);
  Matrix_SetValue(orientation, 2, 1, -forward.y);
  Matrix_SetValue(orientation, 2, 2, -forward.z);

  Matrix_SetValue(orientation, 3, 3, 1);

  Matrix translation = Transformation_Translation(-from.x, -from.y, -from.z);
  Matrix transformation = Matrix_Multiply(orientation, translation);
  Matrix_Destroy(&orientation);
  Matrix_Destroy(&translation);

  return transformation;
}
