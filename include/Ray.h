#ifndef __RAY__
#define __RAY__

#include "Tuple.h"

typedef struct Ray Ray;

struct Ray{
	Tuple origin;
	Tuple direction;
};

Ray Ray_Create(Tuple origin, Tuple direction);
Tuple Ray_Position(Ray ray, float time);

#endif /* __RAY__ */
