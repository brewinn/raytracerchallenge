#include "Tuple.h"
#include "Utilities.h"
#include <math.h>
#include <stdio.h>

enum { VECTOR, POINT };

Tuple Tuple_Create(float x, float y, float z, float w) {
  Tuple tuple = {x, y, z, w};
  return tuple;
}

Tuple Tuple_CreatePoint(float x, float y, float z) {
  return Tuple_Create(x, y, z, POINT);
}

Tuple Tuple_CreateVector(float x, float y, float z) {
  return Tuple_Create(x, y, z, VECTOR);
}

bool Tuple_Equals(Tuple tuple1, Tuple tuple2) {
  if (!floatsEqual(tuple1.x, tuple2.x))
    return false;
  if (!floatsEqual(tuple1.y, tuple2.y))
    return false;
  if (!floatsEqual(tuple1.z, tuple2.z))
    return false;
  if (!floatsEqual(tuple1.w, tuple2.w))
    return false;
  return true;
}

Tuple Tuple_Add(Tuple tuple1, Tuple tuple2) {
  float x, y, z, w;
  x = tuple1.x + tuple2.x;
  y = tuple1.y + tuple2.y;
  z = tuple1.z + tuple2.z;
  w = tuple1.w + tuple2.w;
  return Tuple_Create(x, y, z, w);
}

Tuple Tuple_Subtract(Tuple tuple1, Tuple tuple2) {
  float x, y, z, w;
  x = tuple1.x - tuple2.x;
  y = tuple1.y - tuple2.y;
  z = tuple1.z - tuple2.z;
  w = tuple1.w - tuple2.w;
  return Tuple_Create(x, y, z, w);
}

Tuple Tuple_Negate(Tuple tuple) {
  return Tuple_Create(-tuple.x, -tuple.y, -tuple.z, -tuple.w);
}

Tuple Tuple_Multiply(Tuple tuple, float scalar) {
  float x, y, z, w;
  x = tuple.x * scalar;
  y = tuple.y * scalar;
  z = tuple.z * scalar;
  w = tuple.w * scalar;
  return Tuple_Create(x, y, z, w);
}

Tuple Tuple_Divide(Tuple tuple, float scalar) {
  float x, y, z, w;
  x = tuple.x / scalar;
  y = tuple.y / scalar;
  z = tuple.z / scalar;
  w = tuple.w / scalar;
  return Tuple_Create(x, y, z, w);
}

float Tuple_Magnitude(Tuple tuple) {
  float x2, y2, z2, w2;
  x2 = tuple.x * tuple.x;
  y2 = tuple.y * tuple.y;
  z2 = tuple.z * tuple.z;
  w2 = tuple.w * tuple.w;
  return sqrtf(x2 + y2 + z2 + w2);
}

Tuple Tuple_Normalize(Tuple tuple) {
  float magnitude = Tuple_Magnitude(tuple);
  return Tuple_Divide(tuple, magnitude);
}

float Tuple_Dot(Tuple tuple1, Tuple tuple2) {
  return tuple1.x * tuple2.x + tuple1.y * tuple2.y + tuple1.z * tuple2.z +
         tuple1.w * tuple2.w;
}

Tuple Tuple_Cross(Tuple tuple1, Tuple tuple2) {
  float x, y, z;
  x = tuple1.y * tuple2.z - tuple1.z * tuple2.y;
  y = tuple1.z * tuple2.x - tuple1.x * tuple2.z;
  z = tuple1.x * tuple2.y - tuple1.y * tuple2.x;
  return Tuple_CreateVector(x, y, z);
}

Tuple Tuple_Reflect(Tuple vector, Tuple normal) {
  float dotProduct = Tuple_Dot(vector, normal);
  Tuple changeVector = Tuple_Multiply(normal, 2 * dotProduct);
  Tuple reflection = Tuple_Subtract(vector, changeVector);
  return reflection;
}
