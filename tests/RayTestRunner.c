#include "unity_fixture.h"

TEST_GROUP_RUNNER(Ray) {
  RUN_TEST_CASE(Ray, RayContainsOriginPoint);
  RUN_TEST_CASE(Ray, RayContainsDirectionVector);
  RUN_TEST_CASE(Ray, RayOriginIsAPoint);
  RUN_TEST_CASE(Ray, RayDirectionIsAVector);
  RUN_TEST_CASE(Ray, PositionComputesPointAlongRay);
}

TEST_GROUP_RUNNER(RayTransforms) {
  RUN_TEST_CASE(RayTransforms, TransformReturnsRay);
  RUN_TEST_CASE(RayTransforms, TranslationMovesRayOrigin);
  RUN_TEST_CASE(RayTransforms, ScaleChangesBothRayOriginAndDirection);
}
