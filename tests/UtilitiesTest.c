#include "Utilities.h"
#include "unity_fixture.h"

TEST_GROUP(Utilities);

TEST_SETUP(Utilities) {}

TEST_TEAR_DOWN(Utilities) {}

TEST(Utilities, FloatEqualsTrueForIdenticalFloats) {
  float f1 = 0.0;
  float f2 = 0;
  TEST_ASSERT(floatsEqual(f1, f2));
}

TEST(Utilities, FloatEqualsFalseForDifferentFloats) {
  float f1 = 0.0;
  float f2 = 0.0001;
  TEST_ASSERT_FALSE(floatsEqual(f1, f2));
}
