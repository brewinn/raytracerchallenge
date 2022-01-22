#ifndef __RAY__
#define __RAY__

#include "Matrix.h"
#include "Tuple.h"

typedef struct Ray Ray;

struct Ray {
  Tuple origin;
  Tuple direction;
};

Ray Ray_Create(Tuple origin, Tuple direction);
Tuple Ray_Position(Ray ray, float time);
Ray Ray_Transform(Ray ray, const Matrix transformation);

#endif /* __RAY__ */
