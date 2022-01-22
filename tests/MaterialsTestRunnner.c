#include "unity_fixture.h"

TEST_GROUP_RUNNER(Materials) {
  RUN_TEST_CASE(Materials, DefaultMaterialValues);
}

TEST_GROUP_RUNNER(MaterialLighting) {
  RUN_TEST_CASE(MaterialLighting, LightingWithEyeBetweenTheLightAndTheSurface);
  RUN_TEST_CASE(MaterialLighting, LightingWithTheSurfaceInShadow);
  RUN_TEST_CASE(MaterialLighting,
                LightingWithEyeBetweenTheLightAndTheSurfaceOffset45Degrees);
  RUN_TEST_CASE(MaterialLighting,
                LightingWithEyeOppositeSurfaceAndLightOffset45Degrees);
  RUN_TEST_CASE(MaterialLighting, LightingWithEyeInPathOfReflectionVector);
  RUN_TEST_CASE(MaterialLighting, LightingWithTheLightBehindTheSurface);
}
