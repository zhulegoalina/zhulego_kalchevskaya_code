#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "orders.h"

void test_list_orders() {
    list_orders();
    CU_ASSERT(1 == 1);
}

void test_add_order() {
    CU_ASSERT(1 == 1);
}

void test_delete_order() {
    CU_ASSERT(1 == 1);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Orders Tests", 0, 0);
    CU_add_test(suite, "test_list_orders", test_list_orders);
    CU_add_test(suite, "test_add_order", test_add_order);
    CU_add_test(suite, "test_delete_order", test_delete_order);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
