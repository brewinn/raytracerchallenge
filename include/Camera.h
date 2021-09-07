
#ifndef __CAMERA__
#define __CAMERA__

#include "Matrix.h"

typedef struct Camera{
	int hsize;
	int vsize;
	float fieldOfView;
	Matrix transform;
} Camera;

Camera Camera_Create(int hsize, int vsize, float fieldOfView);

#endif /* __CAMERA__ */

