#include <stdio.h>
#include <assert.h>
#include "auth.h"

void test_login_success() {
    int result = login("admin", "admin123");
    assert(result == 1);
    printf(" test_login_success passed\n");
}

void test_login_failure() {
    int result = login("wrong", "wrong");
    assert(result == 0);
    printf(" test_login_failure passed\n");
}

int main() {
    test_login_success();
    test_login_failure();
    printf("\nAll auth tests passed!\n");
    return 0;
}
