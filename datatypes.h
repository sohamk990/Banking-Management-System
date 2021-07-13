#ifndef DATABASE_H
#define DATABASE_H


typedef struct transaction
{
	int userID;
	char transaction[50];
	float value;
}transaction;

typedef struct normal_user
{
	int userID;
	char name[30];
	char password[10];
	int account_number;
	float balance;
	char status[20];
} normal_user;

typedef struct joint_user
{
	int userID;
	char name1[30];
	char name2[30];
	char password[10];
	int account_number;
	float balance;
	char status[20];
} joint_user;

typedef struct admin_user
{
	int userID;
	char username[30];
	char password[10];
} admin_user;


#endif