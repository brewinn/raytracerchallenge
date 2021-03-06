#include "Sphere.h"
#include <math.h>
#include <stdlib.h>

static int idCounter = 0;

typedef struct SphereStruct {
  int id;
  Matrix transformation;
  Material material;
} SphereStruct;

Sphere Sphere_Create(void) {
  Sphere sphere = malloc(sizeof(SphereStruct));
  sphere->id = ++idCounter;
  sphere->transformation = Matrix_Identity(4);
  sphere->material = Material_Create();
  return sphere;
}

void Sphere_Destroy(Sphere *spherePtr) {
  Sphere sphere = *spherePtr;
  Matrix_Destroy(&(sphere->transformation));
  free(sphere);
  *spherePtr = NULL;
}

int Sphere_GetId(const Sphere sphere) { return sphere->id; }

Intersections Sphere_Intersect(const Sphere sphere, Ray ray) {
  Matrix transform = Matrix_Inverse(sphere->transformation);
  Ray transformedRay = Ray_Transform(ray, transform);
  Matrix_Destroy(&transform);

  Tuple sphereOrigin = Tuple_CreatePoint(0, 0, 0);
  Tuple sphereToRay = Tuple_Subtract(transformedRay.origin, sphereOrigin);

  float a = Tuple_Dot(transformedRay.direction, transformedRay.direction);
  float b = 2 * Tuple_Dot(transformedRay.direction, sphereToRay);
  float c = Tuple_Dot(sphereToRay, sphereToRay) - 1;

  float discriminant = b * b - 4 * a * c;

  if (discriminant < 0)
    return Intersection_Create(0);

  float timeOne = (-b - sqrtf(discriminant)) / (2 * a);
  float timeTwo = (-b + sqrtf(discriminant)) / (2 * a);

  Intersections xs = Intersection_Create(2);
  Intersection_SetTime(xs, 0, timeOne);
  Intersection_SetObject(xs, 0, sphere);
  Intersection_SetTime(xs, 1, timeTwo);
  Intersection_SetObject(xs, 1, sphere);
  return xs;
}

Matrix Sphere_GetTransformation(const Sphere sphere) {
  return sphere->transformation;
}

static void AssertMatrixCorrectDimensions(const Matrix matrix) {
  if (Matrix_GetColumns(matrix) != 4 || Matrix_GetRows(matrix) != 4)
    exit(-1);
}

void Sphere_SetTransformation(Sphere sphere, Matrix transformation) {
  AssertMatrixCorrectDimensions(transformation);
  Matrix_Destroy(&(sphere->transformation));
  sphere->transformation = transformation;
}

Tuple Sphere_NormalAt(Sphere sphere, Tuple point) {
  Tuple origin = Tuple_CreatePoint(0, 0, 0);
  Matrix inverseTransform = Matrix_Inverse(sphere->transformation);
  Tuple objectPoint = Matrix_MultiplyTuple(inverseTransform, point);
  Tuple objectNormal = Tuple_Subtract(objectPoint, origin);
  Matrix worldTransformation = Matrix_Transpose(inverseTransform);
  Tuple worldNormal = Matrix_MultiplyTuple(worldTransformation, objectNormal);
  Matrix_Destroy(&worldTransformation);
  Matrix_Destroy(&inverseTransform);
  worldNormal.w = 0;
  return Tuple_Normalize(worldNormal);
}

Material Sphere_GetMaterial(Sphere sphere) { return sphere->material; }

void Sphere_SetMaterial(Sphere sphere, Material material) {
  sphere->material = material;
}
