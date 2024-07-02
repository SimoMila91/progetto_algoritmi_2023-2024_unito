#include <stdio.h>
#include <stdlib.h>
#include "library.h"
#include "unity.h"




void test_edit_distance_same_strings(void) {
    const char *str1 = "house";
    const char *str2 = "house";
    TEST_ASSERT_EQUAL_INT(0, edit_distance(str1, str2));
    TEST_ASSERT_EQUAL_INT(0, edit_distance_dyn(str1, str2));
}


void test_edit_distance_empty_strings(void) {
    const char *str1 = "";
    const char *str2 = "";
    TEST_ASSERT_EQUAL_INT(0, edit_distance(str1, str2));
    TEST_ASSERT_EQUAL_INT(0, edit_distance_dyn(str1, str2));
}


void test_edit_distance_one_empty_string(void) {
    const char *str1 = "sleep";
    const char *str2 = "";
    TEST_ASSERT_EQUAL_INT(5, edit_distance(str1, str2));
    TEST_ASSERT_EQUAL_INT(5, edit_distance_dyn(str1, str2));
}


void test_edit_distance_general_case(void) {
    const char *str1 = "change";
    const char *str2 = "lunch";
    TEST_ASSERT_EQUAL_INT(4, edit_distance(str1, str2));
    TEST_ASSERT_EQUAL_INT(4, edit_distance_dyn(str1, str2));
}


void test_edit_distance_another_case(void) {
    const char *str1 = "goal";
    const char *str2 = "boatswain";
    TEST_ASSERT_EQUAL_INT(7, edit_distance(str1, str2));
    TEST_ASSERT_EQUAL_INT(7, edit_distance_dyn(str1, str2));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_edit_distance_same_strings);
    RUN_TEST(test_edit_distance_empty_strings);
    RUN_TEST(test_edit_distance_one_empty_string);
    RUN_TEST(test_edit_distance_general_case);
    RUN_TEST(test_edit_distance_another_case);
    return UNITY_END();
}
