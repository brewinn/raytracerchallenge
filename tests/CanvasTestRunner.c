#include "unity_fixture.h"

TEST_GROUP_RUNNER(CanvasInit) {
  RUN_TEST_CASE(CanvasInit, CanvasCreateTakesDifferentSizes);
}

TEST_GROUP_RUNNER(Canvas) {
  RUN_TEST_CASE(Canvas, EmptyCanvasIsBlack);
  RUN_TEST_CASE(Canvas, CanvasWriteChangesColorValue);
  RUN_TEST_CASE(Canvas, CanvasWritesToCorrectOffset);
  RUN_TEST_CASE(Canvas, PixelAtReturnsColorAtOffset);
  RUN_TEST_CASE(Canvas, FillColorFillsCanvas);
}

TEST_GROUP_RUNNER(CanvasToPPM) {
  RUN_TEST_CASE(CanvasToPPM, WriteToPpmCreatesFile);
  RUN_TEST_CASE(CanvasToPPM, WriteToPpmCreatesPpmHeader);
  RUN_TEST_CASE(CanvasToPPM, WriteToPpmAddsColorArray);
  RUN_TEST_CASE(CanvasToPPM, PpmFileEndsWithNewline);
}

TEST_GROUP_RUNNER(CanvasWithColor) {
  RUN_TEST_CASE(CanvasWithColor, WriteToPpmConvertsToInt);
  RUN_TEST_CASE(CanvasWithColor, WriteToPpmSplitsLongLines);
}
