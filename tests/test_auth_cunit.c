#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "auth.h"

void test_login_admin() {
    CU_ASSERT(login("admin", "admin123") == 1);
}

void test_login_dispatcher() {
    CU_ASSERT(login("dispatcher1", "pass123") == 1);
}

void test_login_failure() {
    CU_ASSERT(login("wrong", "wrong") == 0);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Auth Tests", 0, 0);
    CU_add_test(suite, "test_login_admin", test_login_admin);
    CU_add_test(suite, "test_login_dispatcher", test_login_dispatcher);
    CU_add_test(suite, "test_login_failure", test_login_failure);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
