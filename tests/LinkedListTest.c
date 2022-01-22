#include "LinkedList.h"
#include "unity_fixture.h"

static LinkedList list;

TEST_GROUP(LinkedList);

TEST_SETUP(LinkedList) { list = LinkedList_Create(); }

TEST_TEAR_DOWN(LinkedList) { LinkedList_Destroy(&list); }

TEST(LinkedList, CreateMakesEmptyList) {
  TEST_ASSERT_EQUAL_INT(0, LinkedList_GetLength(list));
}

TEST(LinkedList, EmptyListReturnsNull) {
  void *ptr = LinkedList_ValueAt(list, 0);
  TEST_ASSERT_NULL(ptr);
}

TEST(LinkedList, CanAppendToList) {
  int expected = 1;
  LinkedList_Append(list, &expected);
  int *actual = LinkedList_ValueAt(list, 0);
  TEST_ASSERT_EQUAL_INT(expected, *actual);
  int length = LinkedList_GetLength(list);
  TEST_ASSERT_EQUAL_INT(1, length);
}

TEST(LinkedList, ValueAtReturnsNodeValue) {
  float a = 1;
  float b = 0.5;
  float c = -1;
  LinkedList_Append(list, &a);
  LinkedList_Append(list, &b);
  LinkedList_Append(list, &c);
  float *actualA = (float *)LinkedList_ValueAt(list, 0);
  float *actualB = (float *)LinkedList_ValueAt(list, 1);
  float *actualC = (float *)LinkedList_ValueAt(list, 2);
  TEST_ASSERT_EQUAL_FLOAT(a, *actualA);
  TEST_ASSERT_EQUAL_FLOAT(b, *actualB);
  TEST_ASSERT_EQUAL_FLOAT(c, *actualC);
}

static int x, y, z;

TEST_GROUP(MultipleNodeLinkedList);

TEST_SETUP(MultipleNodeLinkedList) {
  x = 1;
  y = 2;
  z = 3;
  list = LinkedList_Create();
  LinkedList_Append(list, &x);
  LinkedList_Append(list, &y);
  LinkedList_Append(list, &z);
}

TEST_TEAR_DOWN(MultipleNodeLinkedList) { LinkedList_Destroy(&list); }

TEST(MultipleNodeLinkedList, PrependNewValue) {
  int w = 0;
  LinkedList_Prepend(list, &w);
  int *actualW = LinkedList_ValueAt(list, 0);
  int *actualX = LinkedList_ValueAt(list, 1);
  TEST_ASSERT_EQUAL_INT(w, *actualW);
  TEST_ASSERT_EQUAL_INT(x, *actualX);
}

TEST(MultipleNodeLinkedList, InsertAddsNodeAtSpecifiedLocation) {
  float w = 2.5;
  LinkedList_Insert(list, 2, &w);
  int *actualY = LinkedList_ValueAt(list, 1);
  TEST_ASSERT_EQUAL_INT(y, *actualY);
  float *actualW = LinkedList_ValueAt(list, 2);
  TEST_ASSERT_EQUAL_FLOAT(w, *actualW);
  int *actualZ = LinkedList_ValueAt(list, 3);
  TEST_ASSERT_EQUAL_INT(z, *actualZ);
}

TEST(MultipleNodeLinkedList, RemoveBeginningTakesOffFirstNode) {
  LinkedList_RemoveBeginning(list);
  int length = LinkedList_GetLength(list);
  TEST_ASSERT_EQUAL_INT(2, length);
  int *actualFirst = LinkedList_ValueAt(list, 0);
  TEST_ASSERT_EQUAL_INT(y, *actualFirst);
}

TEST(MultipleNodeLinkedList, RemoveEndTakesOffLastNode) {
  int w = 10;
  LinkedList_Insert(list, 2, &w);
  LinkedList_RemoveEnd(list);
  int length = LinkedList_GetLength(list);
  TEST_ASSERT_EQUAL_INT(3, length);
  int *actualLast = LinkedList_ValueAt(list, 2);
  TEST_ASSERT_EQUAL_INT(w, *actualLast);
}

TEST(MultipleNodeLinkedList, RemoveTakesOffSpecifiedNode) {
  LinkedList_Remove(list, 1);
  int *actualFirst = LinkedList_ValueAt(list, 0);
  int *actualLast = LinkedList_ValueAt(list, 1);
  TEST_ASSERT_EQUAL_INT(x, *actualFirst);
  TEST_ASSERT_EQUAL_INT(z, *actualLast);
  LinkedList_Remove(list, 1);
  int *lastValue = LinkedList_ValueAt(list, 0);
  TEST_ASSERT_EQUAL_INT(x, *lastValue);
}
