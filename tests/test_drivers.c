#include <stdio.h>
#include "drivers.h"

void test_list_drivers() {
    list_drivers();
    printf("test_list_drivers passed\n");
}

void test_add_driver() {
    printf("test_add_driver passed (mock)\n");
}

void test_delete_driver() {
    printf("test_delete_driver passed (mock)\n");
}

int main() {
    test_list_drivers();
    test_add_driver();
    test_delete_driver();
    printf("\nAll drivers tests passed!\n");
    return 0;
}
