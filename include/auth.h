#ifndef AUTH_H
#define AUTH_H

int register_user(const char *username, const char *password, const char *role);
int login(const char *username, const char *password);
int get_current_user_role();

#endif
