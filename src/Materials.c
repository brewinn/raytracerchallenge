#include "Materials.h"
#include <math.h>

Material Material_Create()
{
	Material material = {
		.color = Color_Create(1, 1, 1),
		.ambient = 0.1,
		.diffuse = 0.9,
		.specular = 0.9,
		.shininess = 200.0,
	};
	return material;
}

Color Material_Lighting(Material material, Light light, Tuple point, Tuple eyev, Tuple normalv)
{
	Color effectiveColor = Color_Multiply(material.color, light.intensity);
	Tuple lightv = Tuple_Normalize(Tuple_Subtract(light.position, point));
	Color ambient = Color_ScalarMultiply(effectiveColor, material.ambient);

	Color diffuse, specular;
	Color black = Color_Create(0, 0, 0);
	float lightDotNormal = Tuple_Dot(lightv, normalv);
	if(lightDotNormal < 0)
	{
		diffuse = black;
		specular = black;
	}
	else {
		diffuse = Color_ScalarMultiply(
				Color_ScalarMultiply(
					effectiveColor, 
					material.diffuse
					), 
				lightDotNormal
				);

		Tuple reflectv = Tuple_Reflect(
				 Tuple_Negate(lightv), 
				 normalv
				 );

		float reflectDotEye = Tuple_Dot(reflectv, eyev);
		if( reflectDotEye <= 0)
		{
			specular = black;
		}
		else{
			float factor = powf(reflectDotEye, material.shininess);
			specular = Color_ScalarMultiply(
					Color_ScalarMultiply(
						light.intensity,
						material.specular),
					factor
					);
		}

	}
	Color result = Color_Add(
			Color_Add(
				ambient,
				diffuse),
			specular
			);
	return result;
}
