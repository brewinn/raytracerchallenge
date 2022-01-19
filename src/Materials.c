#include "Materials.h"
#include <stdbool.h>
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

static bool lightIsOppositeSurface(Light light, Tuple point, Tuple normalv)
{
	Tuple lightv = Tuple_Normalize(Tuple_Subtract(light.position, point));
	float lightDotNormal = Tuple_Dot(lightv, normalv);
	if(lightDotNormal < 0)
	{
		return true;
	}
	return false;
}

static Color CalculateAmbient(Material material, Light light)
{
	Color effectiveColor = Color_Multiply(material.color, light.intensity);
	Color ambient = Color_ScalarMultiply(effectiveColor, material.ambient);
	return ambient;
}

static Color CalculateDiffuse(Material material, Light light, Tuple point, Tuple normalv)
{
	Color effectiveColor = Color_Multiply(material.color, light.intensity);
	Tuple lightv = Tuple_Normalize(Tuple_Subtract(light.position, point));
	float lightDotNormal = Tuple_Dot(lightv, normalv);
	Color diffuse = Color_ScalarMultiply(
			Color_ScalarMultiply(
				effectiveColor, 
				material.diffuse
				), 
			lightDotNormal
			);
	return diffuse;
}

static Color CalculateSpecular(Material material, Light light, Tuple point, Tuple eyev, Tuple normalv)
{
	Tuple lightv = Tuple_Normalize(Tuple_Subtract(light.position, point));

	Tuple reflectv = Tuple_Reflect(
			 Tuple_Negate(lightv), 
			 normalv
			 );
	
	float reflectDotEye = Tuple_Dot(reflectv, eyev);
	if( reflectDotEye <= 0)
	{
		Color black = Color_Create(0, 0, 0);
		return black;
	}

	float factor = powf(reflectDotEye, material.shininess);
	Color specular = Color_ScalarMultiply(
			Color_ScalarMultiply(
				light.intensity,
				material.specular),
			factor
			);
	
	return specular;
}

Color Material_Lighting(Material material, Light light, Tuple point, Tuple eyev, Tuple normalv, bool inShadow)
{
	Color ambient = CalculateAmbient(material, light);
	if(lightIsOppositeSurface(light, point, normalv))
		return ambient;
	Color diffuse = CalculateDiffuse(material, light, point, normalv);
	Color specular = CalculateSpecular(material, light, point, eyev, normalv);
	Color result = Color_Add(
			Color_Add(
				ambient,
				diffuse),
			specular
			);
	return result;
}
