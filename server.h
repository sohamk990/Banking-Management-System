#ifndef SERVER_H
#define SERVER_H

#include "datatypes.h"

normal_user server_get_normal_user(int ID);
joint_user server_get_joint_user(int ID);
admin_user server_get_admin_user(int ID);

bool server_check_normal_user_password(normal_user currUser);
bool server_check_joint_user_password(joint_user currUser);
bool server_check_admin_user_password(admin_user currUser);
bool server_deposit_money(int accType,int ID,float amt);
bool server_withdraw_money(int accType,int ID,float amt);
bool server_change_user_password(int accType,int ID,char newPwd[10]);
bool server_add_normal_user(normal_user record);
bool server_add_joint_user(joint_user record);
bool server_delete_normal_user(int ID);
bool server_delete_joint_user(int ID);
bool server_modify_normal_user(normal_user modUser);
bool server_modify_joint_user(joint_user modUser);
float server_get_user_balance(int accType,int ID);
void server_get_transaction_details(int nsd,int account_type,int current_userID);
void server_task_handler(int nsd);
void *server_connection_handler(void *nsd);

#endif