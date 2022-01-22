#ifndef __TUPLE__
#define __TUPLE__

#include <stdbool.h>

typedef struct Tuple Tuple;

struct Tuple {
  float x;
  float y;
  float z;
  float w;
};

Tuple Tuple_Create(float x, float y, float z, float w);
Tuple Tuple_CreatePoint(float x, float y, float z);
Tuple Tuple_CreateVector(float x, float y, float z);
bool Tuple_Equals(Tuple tuple1, Tuple tuple2);
Tuple Tuple_Add(Tuple tuple1, Tuple tuple2);
Tuple Tuple_Subtract(Tuple tuple1, Tuple tuple2);
Tuple Tuple_Negate(Tuple tuple);
Tuple Tuple_Multiply(Tuple tuple, float scalar);
Tuple Tuple_Divide(Tuple tuple, float scalar);
float Tuple_Magnitude(Tuple tuple);
Tuple Tuple_Normalize(Tuple tuple);
float Tuple_Dot(Tuple tuple1, Tuple tuple2);
Tuple Tuple_Cross(Tuple tuple1, Tuple tuple2);
Tuple Tuple_Reflect(Tuple vector, Tuple normal);

#endif /* __TUPLE__ */
