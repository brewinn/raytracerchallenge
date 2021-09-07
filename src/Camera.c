#include "Camera.h"

Camera Camera_Create(int hsize, int vsize, float fieldOfView)
{
	Camera c = {
		.hsize = hsize,
		.vsize = vsize,
		.fieldOfView = fieldOfView,
		.transform = Matrix_Identity(4)
	};
	return c;
}
