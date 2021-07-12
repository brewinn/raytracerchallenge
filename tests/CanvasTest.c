#include "unity_fixture.h"
#include "Canvas.h"

static Canvas canvas;

static void AssertColorsEqual(Color color1, Color color2)
{
	TEST_ASSERT_EQUAL_FLOAT(color1.red, color2.red);
	TEST_ASSERT_EQUAL_FLOAT(color1.green, color2.green);
	TEST_ASSERT_EQUAL_FLOAT(color1.blue, color2.blue);
}

TEST_GROUP(Canvas);

TEST_SETUP(Canvas)
{
	canvas = Canvas_Create(10, 10);
}

TEST_TEAR_DOWN(Canvas)
{
	Canvas_Destroy(canvas);
}

TEST(Canvas, EmptyCanvasIsBlack)
{
	Color color = *canvas.pixels;
	Color black = Color_Create(0, 0, 0);
	AssertColorsEqual(black, color);
}

TEST(Canvas, CanvasWriteChangesColorValue)
{
	Color red = Color_Create(1, 0, 0);
	Canvas_WritePixel(canvas, 0, 0, red);
	Color color = *canvas.pixels;
	AssertColorsEqual(red, color);
}

TEST(Canvas, CanvasWritesToCorrectOffset)
{
	Color purple = Color_Create(0.5, 0, 0.5);
	Canvas_WritePixel(canvas, 1, 1, purple);
	Color color = canvas.pixels[11];
	AssertColorsEqual(purple, color);
}

TEST(Canvas, PixelAtReturnsColorAtOffset)
{
	Color purple = Color_Create(0.5, 0, 0.5);
	Canvas_WritePixel(canvas, 1, 2, purple);
	Color color = Canvas_PixelAt(canvas, 1, 2);
	AssertColorsEqual(purple, color);
}

TEST_GROUP(CanvasInit);

TEST_SETUP(CanvasInit)
{
}

TEST_TEAR_DOWN(CanvasInit)
{
}

TEST(CanvasInit, CanvasCreateTakesDifferentSizes)
{
	canvas = Canvas_Create(10, 20);
	TEST_ASSERT_EQUAL_INT(10, canvas.width);
	TEST_ASSERT_EQUAL_INT(20, canvas.height);
	Canvas_Destroy(canvas);
	canvas = Canvas_Create(25, 15);
	TEST_ASSERT_EQUAL_INT(25, canvas.width);
	TEST_ASSERT_EQUAL_INT(15, canvas.height);
	Canvas_Destroy(canvas);
}
