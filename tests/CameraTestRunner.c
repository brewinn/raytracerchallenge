#include "unity_fixture.h"

TEST_GROUP_RUNNER(Camera)
{
	RUN_TEST_CASE(Camera, ConstructingACamera);
	RUN_TEST_CASE(Camera, PixelSizeForHorizontalCanvas);
	RUN_TEST_CASE(Camera, PixelSizeForVerticalCanvas);
	RUN_TEST_CASE(Camera, ConstructingARayThroughTheCenterOfTheCanvas);
	RUN_TEST_CASE(Camera, ConstructingARayThroughTheCornerOfTheCanvas);
	RUN_TEST_CASE(Camera, ConstructingARayWhenTheCameraIsTransformed);
	RUN_TEST_CASE(Camera, RenderingAWorldWithACamera);
}

