#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "sort_lib.h"

// Compare is done assuming the array items are int.
// It is not necessary to check other types because this is not relative
// to the sort algorithm.
int compare_int(const void* first, const void* second) {
  int first_field = *((int *)first);
  int second_field = *((int *)second);
 
  if (first_field < second_field)
    return -1;
  return first_field == second_field ? 0 : 1;
}

void test_merge_sort_null_array() {
  void *array = NULL;
  merge_sort(array, 0, 0, &compare_int);
  TEST_ASSERT(array == NULL);
}

void test_merge_sort_empty_array() {
  int array[0];
  merge_sort(&array, 0, 0, &compare_int);
  TEST_ASSERT_EQUAL_INT(0, sizeof(array));
}

void test_merge_sort_1_item_array() {
  int array[] = {1};
  int expected[] = {1};
  int items_num = sizeof(array)/sizeof(array[0]);
  merge_sort(
    &array,
    items_num,
    sizeof(array[0]),
    &compare_int
  );
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, array, items_num);
}

void test_merge_sort_2_items_array() {
  int array[] = {2, 1};
  int expected[] = {1, 2};
  int items_num = sizeof(array)/sizeof(array[0]);
  merge_sort(
    &array,
    items_num,
    sizeof(array[0]),
    &compare_int
  );
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, array, items_num);
}

void test_merge_sort_10_items_array() {
  int array[] = {-2, 1, -25, 23, 4, 6, 19, 8, 79, 0};
  int expected[] = {-25, -2, 0, 1, 4, 6, 8, 19, 23, 79};
  int items_num = sizeof(array)/sizeof(array[0]);
  merge_sort(
    &array,
    items_num,
    sizeof(array[0]),
    &compare_int
  );
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, array, items_num);
}

void test_quick_sort_null_array() {
  void *array = NULL;
  quick_sort(array, 0, 0, &compare_int);
  TEST_ASSERT(array == NULL);
}

void test_quick_sort_empty_array() {
  int array[0]; 
  quick_sort(&array, 0, 0, &compare_int);
  TEST_ASSERT_EQUAL_INT(0, sizeof(array));
}

void test_quick_sort_1_item_array() {
  int array[] = {1};
  int expected[] = {1};
  int items_num = sizeof(array)/sizeof(array[0]);
  quick_sort(
    &array,
    items_num,
    sizeof(array[0]),
    &compare_int
  );
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, array, items_num);
}

void test_quick_sort_2_items_array() {
  int array[] = {2, 1};
  int expected[] = {1, 2};
  int items_num = sizeof(array)/sizeof(array[0]);
  quick_sort(
    &array,
    items_num,
    sizeof(array[0]),
    &compare_int
  );
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, array, items_num);
}

void test_quick_sort_10_items_array() {
  int array[] = {-2, 1, -25, 23, 4, 6, 19, 8, 79, 0};
  int expected[] = {-25, -2, 0, 1, 4, 6, 8, 19, 23, 79};
  size_t items_num = sizeof(array)/sizeof(array[0]);
  quick_sort(
    &array,
    items_num,
    sizeof(array[0]),
    &compare_int
  );
  TEST_ASSERT_EQUAL_INT_ARRAY(expected, array, items_num);
}


int main(void) {

    UNITY_BEGIN();
    
    RUN_TEST(test_merge_sort_empty_array);
    RUN_TEST(test_merge_sort_null_array);
    RUN_TEST(test_merge_sort_empty_array);
    RUN_TEST(test_merge_sort_1_item_array);
    RUN_TEST(test_merge_sort_2_items_array);
    RUN_TEST(test_merge_sort_10_items_array);

    RUN_TEST(test_quick_sort_null_array);
    RUN_TEST(test_quick_sort_empty_array);
    RUN_TEST(test_quick_sort_1_item_array);
    RUN_TEST(test_quick_sort_2_items_array);
    RUN_TEST(test_quick_sort_10_items_array);

    return UNITY_END();
}