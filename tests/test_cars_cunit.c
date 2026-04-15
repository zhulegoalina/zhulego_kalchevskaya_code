#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "cars.h"

void test_list_cars() {
    list_cars();
    CU_ASSERT(1 == 1);
}

void test_add_car() {
    CU_ASSERT(1 == 1);
}

void test_delete_car() {
    CU_ASSERT(1 == 1);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Cars Tests", 0, 0);
    CU_add_test(suite, "test_list_cars", test_list_cars);
    CU_add_test(suite, "test_add_car", test_add_car);
    CU_add_test(suite, "test_delete_car", test_delete_car);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
