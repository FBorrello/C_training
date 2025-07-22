#include "unity.h"
#include "dynamic_array.h"

void setUp(void) {}
void tearDown(void) {}

void test_init_array_should_set_capacity_and_size(void) {
    DynamicArray arr;
    int result = init_array(&arr, 10);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL(10, arr.capacity);
    TEST_ASSERT_EQUAL(0, arr.size);
    TEST_ASSERT_NOT_NULL(arr.data);
    free_array(&arr);
}

void test_append_should_add_element(void) {
    DynamicArray arr;
    int result = init_array(&arr, 10);
    TEST_ASSERT_EQUAL_INT(0, result);
    result = append(&arr, 42);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL(1, arr.size);
    TEST_ASSERT_EQUAL(42, arr.data[0]);
    free_array(&arr);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_init_array_should_set_capacity_and_size);
    RUN_TEST(test_append_should_add_element);
    return UNITY_END();
}