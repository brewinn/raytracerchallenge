#include "unity_fixture.h"

TEST_GROUP_RUNNER(LinkedList) {
  RUN_TEST_CASE(LinkedList, CreateMakesEmptyList);
  RUN_TEST_CASE(LinkedList, EmptyListReturnsNull);
  RUN_TEST_CASE(LinkedList, CanAppendToList);
  RUN_TEST_CASE(LinkedList, ValueAtReturnsNodeValue);
}

TEST_GROUP_RUNNER(MultipleNodeLinkedList) {
  RUN_TEST_CASE(MultipleNodeLinkedList, PrependNewValue);
  RUN_TEST_CASE(MultipleNodeLinkedList, InsertAddsNodeAtSpecifiedLocation);
  RUN_TEST_CASE(MultipleNodeLinkedList, RemoveBeginningTakesOffFirstNode);
  RUN_TEST_CASE(MultipleNodeLinkedList, RemoveEndTakesOffLastNode);
  RUN_TEST_CASE(MultipleNodeLinkedList, RemoveTakesOffSpecifiedNode);
}
