#ifndef __LIGHTS__
#define __LIGHTS__

#include "Color.h"
#include "Tuple.h"

typedef struct Light {
  Tuple position;
  Color intensity;
} Light;

Light Light_CreatePointLight(Tuple position, Color intensity);
Light *Light_AllocatePointLight(Tuple position, Color intensity);

#endif /* __LIGHTS__ */
