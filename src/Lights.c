#include "Lights.h"

Light Light_CreatePointLight(Tuple position, Color intensity)
{
	Light pointLight = {position, intensity};
	return pointLight;
}
