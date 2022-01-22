#include "unity_fixture.h"

TEST_GROUP_RUNNER(Lights) {
  RUN_TEST_CASE(Lights, PointLightHasPositionAndIntensity);
}
