#include "unity_fixture.h"

static void RunAllTests(void)
{
	RUN_TEST_GROUP(Tuple);
	RUN_TEST_GROUP(Color);
	RUN_TEST_GROUP(Canvas);
	RUN_TEST_GROUP(CanvasInit);
}

int main(int argc, const char * argv[])
{
	return UnityMain(argc, argv, RunAllTests);
}
