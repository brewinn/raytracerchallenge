#include "Canvas.h"
#include "Sphere.h"
#include "Ray.h"
#include "Intersection.h"
#include "Transformations.h"
#include "Camera.h"
#include <math.h>
#include <stdlib.h>

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

int main(void)
{
    Matrix t1, t2, t3, t4, m1, m2;

    Sphere floor = Sphere_Create();
    Matrix floorTransform = Transformation_Scale(10, 0.01, 10);
    Sphere_SetTransformation(floor, floorTransform);
    Material floorMaterial = Material_Create();
    floorMaterial.color = Color_Create(1, 0.9, 0.9);
    floorMaterial.specular = 0;
    Sphere_SetMaterial(floor, floorMaterial);

    Sphere leftWall = Sphere_Create();
    t1 = Transformation_Translation(0, 0, 5);
    t2 = Transformation_RotationY(-M_PI/4);
    m1 = Matrix_Multiply(t1, t2);
    t3 = Transformation_RotationX(M_PI/2);
    t4 = Transformation_Scale(10, 0.01, 10);
    m2 = Matrix_Multiply(t3, t4);
    Matrix leftWallTransform = Matrix_Multiply(m1, m2);
    Sphere_SetTransformation(leftWall, leftWallTransform);
    Sphere_SetMaterial(leftWall, floorMaterial);

    Sphere rightWall = Sphere_Create();
    Matrix_Transfer(t1, Transformation_Translation(0, 0, 5));
    Matrix_Transfer(t2, Transformation_RotationY(M_PI/4));
    Matrix_Transfer(m1, Matrix_Multiply(t1, t2));
    Matrix_Transfer(t3, Transformation_RotationX(M_PI/2));
    Matrix_Transfer(t4, Transformation_Scale(10, 0.01, 10));
    Matrix_Transfer(m2, Matrix_Multiply(t3, t4));
    Matrix_Destroy(&t3);
    Matrix_Destroy(&t4);
    Matrix rightWallTransform = Matrix_Multiply(m1, m2);
    Matrix_Destroy(&m1);
    Matrix_Destroy(&m2);
    Sphere_SetTransformation(rightWall, rightWallTransform);
    Sphere_SetMaterial(rightWall, floorMaterial);

    Sphere middle = Sphere_Create();
    Matrix middleTransform = Transformation_Translation(-0.5, 1, 0.5);
    Sphere_SetTransformation(middle, middleTransform);
    Material middleMaterial = Material_Create();
    middleMaterial.color = Color_Create(0.1, 1, 0.5);
    middleMaterial.diffuse = 0.7;
    middleMaterial.specular = 0.3;
    Sphere_SetMaterial(middle, middleMaterial);

    Sphere right = Sphere_Create();
    Matrix_Transfer(t1, Transformation_Translation(1.5, 0.5, -0.5));
    Matrix_Transfer(t2, Transformation_Scale(0.5, 0.5, 0.5));
    Matrix rightTransform = Matrix_Multiply(t1, t2);
    Sphere_SetTransformation(right, rightTransform);
    Material rightMaterial = Material_Create();
    rightMaterial.color = Color_Create(0.5, 1, 0.1);
    rightMaterial.diffuse = 0.7;
    rightMaterial.specular = 0.3;
    Sphere_SetMaterial(right, rightMaterial);

    Sphere left = Sphere_Create();
    Matrix_Transfer(t1, Transformation_Translation(-1.5, 0.33, -0.75));
    Matrix_Transfer(t2, Transformation_Scale(0.33, 0.33, 0.33));
    Matrix leftTransform = Matrix_Multiply(t1, t2);
    Sphere_SetTransformation(left, leftTransform);
    Matrix_Destroy(&t1);
    Matrix_Destroy(&t2);
    Material leftMaterial = Material_Create();
    leftMaterial.color = Color_Create(1, 0.8, 0.1);
    leftMaterial.diffuse = 0.7;
    leftMaterial.specular = 0.3;
    Sphere_SetMaterial(left, leftMaterial);

    World world = World_Create();
    Light* pointlight = malloc(sizeof(Light));
    Light tempLight = Light_CreatePointLight(
            Tuple_CreatePoint(-10, 10, -10),
            Color_Create(1, 1, 1)
            );
    *pointlight = tempLight;
    World_AddLight(world, pointlight);
    World_AddObject(world, floor);
    World_AddObject(world, leftWall);
    World_AddObject(world, rightWall);
    World_AddObject(world, middle);
    World_AddObject(world, right);
    World_AddObject(world, left);

    Camera camera = Camera_Create(100, 50, M_PI/3);
    Matrix_Destroy(&camera.transform);
    camera.transform = Transformation_ViewTransform(
            Tuple_CreatePoint(0, 1.5, -5),
            Tuple_CreatePoint(0, 1, 0),
            Tuple_CreateVector(0, 1, 0));


    Canvas canvas = Camera_Render(camera, world);
    Canvas_WriteToPPM(canvas, "sphereCastWithCamera.ppm");

    Matrix_Destroy(&camera.transform);
    Canvas_Destroy(canvas);
    World_Destroy(&world);

    return 0;
}


