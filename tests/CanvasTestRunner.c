#include "unity_fixture.h"

TEST_GROUP_RUNNER(Canvas)
{
	RUN_TEST_CASE(Canvas, EmptyCanvasIsBlack);
	RUN_TEST_CASE(Canvas, CanvasWriteChangesColorValue);
	RUN_TEST_CASE(Canvas, CanvasWritesToCorrectOffset);
	RUN_TEST_CASE(Canvas, PixelAtReturnsColorAtOffset);
}

TEST_GROUP_RUNNER(CanvasInit)
{
	RUN_TEST_CASE(CanvasInit, CanvasCreateTakesDifferentSizes);
}
