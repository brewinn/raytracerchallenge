#include "World.h"
#include "stdlib.h"
#include "LinkedList.h"
#include "Transformations.h"

struct WorldStruct{
	LinkedList objectList;
	LinkedList lightList;
};

World World_Create()
{
	World world = malloc(sizeof(struct WorldStruct));
	world->objectList = LinkedList_Create();
	world->lightList = LinkedList_Create();
	return world;
}

void World_Destroy(World* worldPtr)
{
	World world = *worldPtr;
	while(LinkedList_GetLength(world->objectList) > 0)
	{
		Sphere object = (Sphere) LinkedList_RemoveEnd(world->objectList);
		Sphere_Destroy(&object);
	}
	LinkedList_Destroy(&world->objectList);
	while(LinkedList_GetLength(world->lightList) > 0)
	{
		Light* light = LinkedList_RemoveEnd(world->lightList);
		free(light);
	}
	LinkedList_Destroy(&world->lightList);
	free(world);
	world = NULL;
}

int World_GetObjectCount(const World world)
{
	return LinkedList_GetLength(world->objectList);
}

int World_GetLightCount(const World world)
{
	return LinkedList_GetLength(world->lightList);
}

World World_CreateDefault(void)
{
	World world = World_Create();
	Sphere sphere1 = Sphere_Create();
	Material material = {
		.color = Color_Create(0.8, 1, 0.6),
		.ambient = 0.1,
		.diffuse = 0.7,
		.specular = 0.2,
		.shininess = 200.0,
	};
	Sphere_SetMaterial(sphere1, material);
	Sphere sphere2 = Sphere_Create();
	Matrix transformation = Transformation_Scale(0.5, 0.5, 0.5);
	Sphere_SetTransformation(sphere2, transformation);
	Light pointLight = Light_CreatePointLight(
			Tuple_CreatePoint(-10, 10, -10),
			Color_Create(1, 1, 1)
			);
	Light* light1 = malloc(sizeof(Light));
	*light1 = pointLight;
	LinkedList_Append(world->objectList, sphere1);
	LinkedList_Append(world->objectList, sphere2);
	LinkedList_Append(world->lightList, light1);
	return world;
}

Light* World_GetLight(const World world, int index)
{
	return LinkedList_ValueAt(world->lightList, index);
}

Sphere World_GetObject(const World world, int index)
{
	return LinkedList_ValueAt(world->objectList, index);
}

Intersections World_Intersect(const World world, Ray ray)
{
	Intersections xs = Intersection_Create(0);
	for(int i = 0; i < World_GetObjectCount(world); i++)
	{
		Intersections objXs = Sphere_Intersect(
				World_GetObject(world, i),
				ray
				);
		xs = Intersection_Combine(xs, objXs);
	}
	Intersection_Sort(xs);
	return xs;
}
