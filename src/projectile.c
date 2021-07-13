#include "Tuple.h"
#include "Canvas.h"
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

void printTick(int tick)
{
	printf("Tick number: %d. \n", tick);
}

void printTrajectory(Projectile projectile, Environment environment)
{
	unsigned int t = 0;
	while(projectile.position.y > 0){
		printPosition(projectile);
		printTick(t);
		projectile = tick(projectile, environment);
		++t;
	}
	printPosition(projectile);
	printTick(t);
}

void plotPosition(Canvas canvas, Projectile projectile)
{
	int x, y;
	x = projectile.position.x;
	y = canvas.height - projectile.position.y;
	Color white = Color_Create(1, 1, 1);
	Canvas_WritePixel(canvas, x, y, white);
}

void plotTrajectory(Canvas canvas, Projectile projectile, Environment environment)
{
	while(projectile.position.y > 0)
	{
		plotPosition(canvas, projectile);
		projectile = tick(projectile, environment);
	}
	Canvas_WriteToPPM("trajectory.ppm", canvas);
}

int main(int argc, char ** argv)
{
	Tuple position = Tuple_CreatePoint(0, 1, 0);
	Tuple velocity = Tuple_Multiply(Tuple_Normalize(Tuple_CreateVector(1, 1.8, 0)), 11.25);
	Projectile projectile = {position, velocity};

	Tuple gravity = Tuple_CreateVector(0, -0.1, 0);
	Tuple wind = Tuple_CreateVector(-0.01, 0, 0);
	Environment environment = {gravity, wind};

	Canvas canvas = Canvas_Create(900, 550);

	printTrajectory(projectile, environment);
	plotTrajectory(canvas, projectile, environment);

	Canvas_Destroy(canvas);

	return 0;
}
