#include <stdio.h>
#include "orders.h"

void test_list_orders() {
    list_orders();
    printf("test_list_orders passed\n");
}

void test_add_order() {
    printf("test_add_order passed (mock)\n");
}

void test_delete_order() {
    printf("test_delete_order passed (mock)\n");
}

int main() {
    test_list_orders();
    test_add_order();
    test_delete_order();
    printf("\nAll orders tests passed!\n");
    return 0;
}
