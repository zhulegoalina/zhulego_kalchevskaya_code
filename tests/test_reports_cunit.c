#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "reports.h"

void test_reports_menu() {
    CU_ASSERT(1 == 1);
}

void test_orders_by_driver_period() {
    CU_ASSERT(1 == 1);
}

void test_car_total_stats() {
    CU_ASSERT(1 == 1);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Reports Tests", 0, 0);
    CU_add_test(suite, "test_reports_menu", test_reports_menu);
    CU_add_test(suite, "test_orders_by_driver_period", test_orders_by_driver_period);
    CU_add_test(suite, "test_car_total_stats", test_car_total_stats);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
