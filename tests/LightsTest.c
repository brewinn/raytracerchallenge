#include "Lights.h"
#include "TestUtilities.h"
#include "unity_fixture.h"

TEST_GROUP(Lights);

TEST_SETUP(Lights) {}

TEST_TEAR_DOWN(Lights) {}

TEST(Lights, PointLightHasPositionAndIntensity) {
  Tuple position = Tuple_CreatePoint(0, 0, 0);
  Color intensity = Color_Create(1, 1, 1);
  Light pointLight = Light_CreatePointLight(position, intensity);
  AssertTuplesEqual(pointLight.position, position);
  AssertColorsEqual(pointLight.intensity, intensity);
}

// TODO Test for alloc
