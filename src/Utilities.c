#include "Utilities.h"

static float absoluteValue(float f) {
  if (f < 0)
    return -1.0 * f;
  return f;
}

static float max(float f1, float f2) {
  if (f1 > f2)
    return f1;
  return f2;
}

bool floatsEqual(float f1, float f2) {
  float abs = absoluteValue(f1 - f2);
  if (abs < EPSILON)
    return true;
  return abs <= EPSILON * max(absoluteValue(f1), absoluteValue(f1));
}
