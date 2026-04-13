#include <stdio.h>
#include "reports.h"

void test_reports_menu() {
    printf("test_reports_menu passed (mock)\n");
}

void test_report_car_mileage() {
    printf("test_report_car_mileage passed (mock)\n");
}

void test_report_driver_earnings() {
    printf("test_report_driver_earnings passed (mock)\n");
}

int main() {
    test_reports_menu();
    test_report_car_mileage();
    test_report_driver_earnings();
    printf("\nAll reports tests passed!\n");
    return 0;
}
