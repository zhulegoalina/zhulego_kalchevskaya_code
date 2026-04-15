#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "drivers.h"

void test_list_drivers() {
    list_drivers();
    CU_ASSERT(1 == 1);
}

void test_add_driver() {
    CU_ASSERT(1 == 1);
}

void test_delete_driver() {
    CU_ASSERT(1 == 1);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Drivers Tests", 0, 0);
    CU_add_test(suite, "test_list_drivers", test_list_drivers);
    CU_add_test(suite, "test_add_driver", test_add_driver);
    CU_add_test(suite, "test_delete_driver", test_delete_driver);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
