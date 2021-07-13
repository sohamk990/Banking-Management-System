#ifndef CLIENT_H
#define CLIENT_H

#include"datatypes.h"

void client_normal_user_login(int sd);
void client_joint_user_login(int sd);
void client_admin_user_login(int sd);
void client_show_menu(int sd);
void client_deposit_money(int sd);
void client_withdraw_money(int sd);
void client_check_balance(int sd);
void client_change_password(int sd);
void client_view_details(int sd);
void client_add_account(int sd);
void client_delete_account(int sd);
void client_update_account(int sd);
void client_search_account(int sd);

int account_type,currUserID;

#endif