#include "Lights.h"
#include <stdlib.h>

Light Light_CreatePointLight(Tuple position, Color intensity) {
  Light pointLight = {position, intensity};
  return pointLight;
}

Light *Light_AllocatePointLight(Tuple position, Color intensity) {
  Light *pointlight = malloc(sizeof(Light));
  *pointlight = Light_CreatePointLight(position, intensity);
  return pointlight;
}
