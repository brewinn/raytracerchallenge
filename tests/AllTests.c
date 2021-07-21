#include "unity_fixture.h"

static void RunAllTests(void)
{
	RUN_TEST_GROUP(Utilities);
	RUN_TEST_GROUP(Tuple);
	RUN_TEST_GROUP(Color);
	RUN_TEST_GROUP(CanvasInit);
	RUN_TEST_GROUP(Canvas);
	RUN_TEST_GROUP(CanvasToPPM);
	RUN_TEST_GROUP(CanvasWithColor);
	RUN_TEST_GROUP(MatrixInit);
	RUN_TEST_GROUP(Matrix);
	RUN_TEST_GROUP(MatrixOperations);
}

int main(int argc, const char * argv[])
{
	return UnityMain(argc, argv, RunAllTests);
}
