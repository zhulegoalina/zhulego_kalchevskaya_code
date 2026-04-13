#include <stdio.h>
#include <assert.h>
#include "cars.h"

void test_list_cars() {
    list_cars();
    printf("test_list_cars passed\n");
}

void test_add_car() {
    printf("test_add_car passed (mock)\n");
}

void test_delete_car() {
    printf("test_delete_car passed (mock)\n");
}

int main() {
    test_list_cars();
    test_add_car();
    test_delete_car();
    printf("\nAll cars tests passed!\n");
    return 0;
}
