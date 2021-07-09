#include "Tuple.h"
#include <stdio.h>

typedef struct Projectile Projectile;
typedef struct Environment Environment;

struct Projectile{
	Tuple position;
	Tuple velocity;
};

struct Environment{
	Tuple gravity;
	Tuple wind;
};

Projectile tick(Projectile projectile, Environment environment)
{
	Tuple position = Tuple_Add(projectile.position, projectile.velocity);
	Tuple velocity = Tuple_Add(projectile.velocity, Tuple_Add(environment.gravity, environment.wind));
	Projectile newProjectile = {position, velocity};
	return newProjectile;
}

void printPosition(Projectile projectile)
{
	printf("Projectile position: x = %f, y = %f, z = %f; ", projectile.position.x, projectile.position.y, projectile.position.z);
}

int main(int argc, char ** argv)
{
	Tuple position = Tuple_CreatePoint(0, 1, 0);
	Tuple velocity = Tuple_Normalize(Tuple_CreateVector(1, 1, 0));
	Projectile projectile = {position, velocity};

	Tuple gravity = Tuple_CreateVector(0, -0.1, 0);
	Tuple wind = Tuple_CreateVector(-0.01, 0, 0);
	Environment environment = {gravity, wind};

	unsigned int t = 0;
	while(projectile.position.y > 0){
		printPosition(projectile);
		printf("Tick number: %d. \n", t);
		projectile = tick(projectile, environment);
		++t;
	}
	printPosition(projectile);
	printf("Tick number: %d. \n", t);

	return 0;
}
