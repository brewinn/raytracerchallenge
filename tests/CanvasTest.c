#include "unity_fixture.h"
#include "Canvas.h"
#include "TestUtilities.h"
#include <stdio.h>

#define HEADER_OFFSET 13

static Canvas canvas;
static FILE * file;
static char line[140];

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

TEST(Canvas, FillColorFillsCanvas)
{
    Color white = Color_Create(1, 1, 1);
    Canvas_FillColor(canvas, white);
    Color color = Canvas_PixelAt(canvas, 7, 2);
    AssertColorsEqual(white, color);
}

TEST_GROUP(CanvasToPPM);

static void ReadLine(FILE * file, char * line)
{
    fscanf(file, "%[^\n] ", line);
}

TEST_SETUP(CanvasToPPM)
{
    canvas = Canvas_Create(10, 10);
    Canvas_WriteToPPM(canvas, "test.ppm");
    file = fopen("test.ppm", "r");
}

TEST_TEAR_DOWN(CanvasToPPM)
{
    fclose(file);
    Canvas_Destroy(canvas);
}

TEST(CanvasToPPM, WriteToPpmCreatesFile)
{
    TEST_ASSERT_NOT_NULL(file);
}

TEST(CanvasToPPM, WriteToPpmCreatesPpmHeader)
{
    ReadLine(file, line);
    TEST_ASSERT_EQUAL_STRING("P3", line);
    ReadLine(file, line);
    TEST_ASSERT_EQUAL_STRING("10 10", line);
    ReadLine(file, line);
    TEST_ASSERT_EQUAL_STRING("255", line);
}

TEST(CanvasToPPM, WriteToPpmAddsColorArray)
{
    char * blackLine = "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0";
    fseek(file, HEADER_OFFSET, SEEK_SET);
    ReadLine(file, line);
    TEST_ASSERT_EQUAL_STRING(blackLine, line);
}

TEST(CanvasToPPM, PpmFileEndsWithNewline)
{
    fseek(file, -1, SEEK_END);
    TEST_ASSERT_EQUAL_CHAR('\n', getc(file));
}

TEST_GROUP(CanvasWithColor);

TEST_SETUP(CanvasWithColor)
{
    canvas = Canvas_Create(10, 10);
    Canvas_FillColor(canvas, Color_Create(0.75, 0.76, 0.77));
    Canvas_WriteToPPM(canvas, "test.ppm");
    file = fopen("test.ppm", "r");
}

TEST_TEAR_DOWN(CanvasWithColor)
{
    fclose(file);
    Canvas_Destroy(canvas);
}

TEST(CanvasWithColor, WriteToPpmConvertsToInt)
{
    int redValue = 255 * 0.75;
    int actualValue;
    fseek(file, HEADER_OFFSET, SEEK_SET);
    fscanf(file, "%d", &actualValue);
    TEST_ASSERT_EQUAL_INT(redValue, actualValue);
}

TEST(CanvasWithColor, WriteToPpmSplitsLongLines)
{
    char * line1 = "191 193 196 191 193 196 191 193 196 191 193 196 191 193 196 191 193";
    char * line2 = "196 191 193 196 191 193 196 191 193 196 191 193 196";
    fseek(file, HEADER_OFFSET, SEEK_SET);
    ReadLine(file, line);
    TEST_ASSERT_EQUAL_STRING(line1, line);
    ReadLine(file, line);
    TEST_ASSERT_EQUAL_STRING(line2, line);
}

