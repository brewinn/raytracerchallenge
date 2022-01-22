#ifndef __MATERIALS__
#define __MATERIALS__

#include "Color.h"
#include "Lights.h"

typedef struct Material {
  Color color;
  float ambient;
  float diffuse;
  float specular;
  float shininess;
} Material;

Material Material_Create();
Color Material_Lighting(Material material, Light light, Tuple point, Tuple eyev,
                        Tuple normalv, bool inShadow);

#endif /* __MATERIALS__ */
