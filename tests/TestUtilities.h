#ifndef __TEST_UTILITIES__
#define __TEST_UTILITIES__

#include "Color.h"
#include "Lights.h"
#include "Materials.h"
#include "Matrix.h"
#include "Ray.h"
#include "Tuple.h"
#include "Utilities.h"

void AssertTuplesEqual(Tuple expected, Tuple actual);
void AssertColorsEqual(Color expected, Color actual);
void AssertRaysEqual(Ray expected, Ray actual);
void AssertMatricesEqual(Matrix expected, Matrix actual);
void AssertMaterialsEqual(Material expected, Material actual);
void AssertLightsEqual(Light expected, Light actual);

#endif /* __TEST_UTILITIES__ */
