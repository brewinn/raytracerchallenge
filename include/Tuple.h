#ifndef __TUPLE__
#define __TUPLE__

typedef struct Tuple Tuple;

struct Tuple{
	float x;
	float y;
	float z;
	float w;
};

Tuple Tuple_Create(float x, float y, float z, float w);

#endif /* __TUPLE__ */
