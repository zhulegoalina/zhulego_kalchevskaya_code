#include <stdio.h>
#include <string.h>
#include "auth.h"
#include "cars.h"
#include "drivers.h"
#include "orders.h"
#include "reports.h"
#include "database.h"

void show_menu(int role) {
    printf("\n=== Autopark Management ===\n");
    printf("1. View cars\n");
    printf("2. View drivers\n");
    printf("3. View orders\n");
    if (role >= 2) {
        printf("4. Add car\n");
        printf("5. Add driver\n");
        printf("6. Add order\n");
    }
    if (role >= 3) {
        printf("7. Delete car\n");
        printf("8. Delete driver\n");
        printf("9. Delete order\n");
        printf("10. Reports\n");
    }
    printf("0. Exit\n");
}

int main() {
    char username[50], password[50];
    
    printf("=== Autopark Login ===\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    
    if (!login(username, password)) {
        printf("Login failed!\n");
        return 1;
    }
    
    int role = get_current_user_role();
    printf("Login successful!\n");
    
    // Проверка подключения к БД и вывод данных
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) == SQLITE_OK) {
        printf("\n=== Drivers in database ===\n");
        execute_query(db, "SELECT id, full_name, experience FROM drivers;");
        db_close(db);
    } else {
        printf("Warning: Could not open database\n");
    }
    
    int choice;
    do {
        show_menu(role);
        printf("Choose: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: list_cars(); break;
            case 2: list_drivers(); break;
            case 3: list_orders(); break;
            case 4: if (role >= 2) add_car(); break;
            case 5: if (role >= 2) add_driver(); break;
            case 6: if (role >= 2) add_order(); break;
            case 7: if (role >= 3) delete_car(); break;
            case 8: if (role >= 3) delete_driver(); break;
            case 9: if (role >= 3) delete_order(); break;
            case 10: if (role >= 3) reports_menu(); break;
        }
    } while (choice != 0);
    
    return 0;
}
