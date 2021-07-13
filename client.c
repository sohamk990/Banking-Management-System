#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdbool.h>

#include "client.h"

void client_show_menu(int sd)
{
	int select;
	if(account_type==1 || account_type==2)
	{
		write(1,"1) Check account balance. \n",sizeof("1) Check account balance. \n"));
		write(1,"2) View all Transactions. \n",sizeof("2) View all Transactions. \n"));
		write(1,"3) Deposit money into account. \n",sizeof("3) Deposit money into account. \n"));
		write(1,"4) Withdraw money into account. \n",sizeof("4) Withdraw money into account. \n"));
		write(1,"5) Change Password. \n",sizeof("5) Change Password. \n"));
		write(1,"6) Exit. \n",sizeof("6) Exit. \n"));
	
		write(1,"Choose the option : ",sizeof("Choose the option : "));
		scanf("%d",&select);

		if(select==1)
		{
			client_check_balance(sd);
		}
		else if(select==2)
		{
			client_view_details(sd);
		}
		else if(select==3)
		{
			client_deposit_money(sd);
		}
		else if(select==4)
		{
			client_withdraw_money(sd);			
		}
		else if(select==5)
		{
			client_change_password(sd);
		}
		else if(select==6)
		{
			write(sd,&select,sizeof(int));
			write(1,"Thank you !\n",sizeof("Thank you !\n"));
			write(1,"Created BY: Soham Kolhe. \n",sizeof("Created BY: Soham Kolhe. \n"));
			exit(0);
		}
		else
		{
			write(1,"Invalid option!!\n\n",sizeof("Invalid option!!\n\n"));
			client_show_menu(sd);
		}
	}
	else if(account_type==3)
	{
		write(1,"1) Search for an account. \n",sizeof("1) Search for an account. \n"));
		write(1,"2) Add an account. \n",sizeof("2) Add an account. \n"));
		write(1,"3) Delete an account. \n",sizeof("3) Delete an account. \n"));
		write(1,"4) Modify an account. \n",sizeof("4) Modify an account. \n"));
		write(1,"5) Exit. \n",sizeof("5) Exit. \n"));

		write(1,"Choose an option: ",sizeof("Choose an option: "));
		scanf("%d",&select);
		
		if(select == 1)
		{
			client_search_account(sd);
		}
		else if(select == 2)
		{
			client_add_account(sd);
		}
		else if(select == 3)
		{
			client_delete_account(sd);
		}
		else if(select == 4)
		{
			client_update_account(sd);
		}
		else if (select == 5)
		{
			write(sd,&select,sizeof(int));
			write(1,"Thank you !\n",sizeof("Thank you !\n"));
			write(1,"Created BY: Soham Kolhe. \n",sizeof("Created BY: Soham Kolhe. \n"));
			exit(0);
		}
		else
		{
			write(1,"Invalid option!!\n\n",sizeof("Invalid option!!\n\n"));
			client_show_menu(sd);
		}
	}
}

void client_choose_option(int sd)
{
	while(1)
	{
		write(1,"Choose Your Account Type \n",sizeof("Choose Your Account Type \n"));
		write(1,"1)Normal User\n",sizeof("1)Normal User\n"));
		write(1,"2)Joint Account User \n",sizeof("2)Joint Account User \n"));
		write(1,"3)Admin Login \n",sizeof("3)Admin Login \n"));
		
		write(1,"Choose the account type: ",sizeof("Choose the account type: "));
		scanf("%d",&account_type);

		if(account_type == 1)
		{
			client_normal_user_login(sd); 
			break;
		}
		else if(account_type == 2)
		{
			client_joint_user_login(sd);
			break;
		}
		else if(account_type == 3)
		{
			client_admin_user_login(sd);
			break;
		}
		else
		{
			write(1,"Invalid Choice!! \n\n",sizeof("Invalid Choice!! \n\n"));
		}
	}
	return;
}

void client_normal_user_login(int sd)
{
	bool result;
	normal_user currUser;

	write(1,"Enter your User ID: ",sizeof("Enter your User ID: "));
	scanf("%d",&currUser.userID);
	currUserID=currUser.userID;
	
	write(1,"Enter your password: ",sizeof("Enter your password: "));
	scanf("%s",currUser.password);

	write(sd,&account_type,sizeof(int));
	write(sd,&currUser,sizeof(normal_user));
	read(sd,&result,sizeof(result));

	if(!result)
	{
		write(1,"Invalid Credentials. !!\n\n",sizeof("Invalid Credentials. !!\n\n"));
		client_choose_option(sd);
	}
	else
	{
		write(1,"Logged in Sucessfully. !!\n\n",sizeof("Logged in Sucessfully. !!\n\n"));
	}
	return;
}

void client_joint_user_login(int sd)
{
	bool result;
	joint_user currUser;
	write(1,"Enter your User ID: ",sizeof("Enter your User ID: "));
	scanf("%d",&currUser.userID);
	currUserID=currUser.userID;

	write(1,"Enter your password: ",sizeof("Enter your password: "));
	scanf("%s",currUser.password);

	write(sd,&account_type,sizeof(int));
	write(sd,&currUser,sizeof(joint_user));
	read(sd,&result,sizeof(result));

	if(!result)
	{
		write(1,"Invalid Credentials. !!\n\n",sizeof("Invalid Credentials. !!\n\n"));
		client_choose_option(sd);
	}
	else{
		write(1,"Logged in Sucessfully. !!\n\n",sizeof("Logged in Sucessfully. !!\n\n"));
	}
	return;
}

void client_admin_user_login(int sd)
{
	bool result;
	admin_user currUser;

	write(1,"Enter your User ID: ",sizeof("Enter your User ID: "));
	scanf("%d",&currUser.userID);
	currUserID=currUser.userID;
	
	write(1,"Enter your password: ",sizeof("Enter your password: "));
	scanf("%s",currUser.password);

	write(sd,&account_type,sizeof(int));
	write(sd,&currUser,sizeof(admin_user));
	read(sd,&result,sizeof(result));
	
	if(!result)
	{
		write(1,"Invalid Credentials. !!\n\n",sizeof("Invalid Credentials. !!\n\n"));
		client_choose_option(sd);
	}
	else
	{
		write(1,"Logged in Sucessfully. !!\n\n",sizeof("Logged in Sucessfully. !!\n\n"));
	}
	return;
}

void client_deposit_money(int sd)
{
	float amount;
	int select=1;
	bool result;

	write(1,"Enter the amount you want to Deposit: Rs.",sizeof("Enter the amount you want to Deposit: Rs."));
	scanf("%f",&amount);

	while(amount<=0)
	{
		write(1,"Please enter a valid amount!!\n",sizeof("Please enter a valid amount!!\n"));
		write(1,"Enter the amount you want to Deposit: Rs.",sizeof("Enter the amount you want to Deposit: Rs."));
		scanf("%f",&amount);
	}

	write(sd,&select,sizeof(int));
	write(sd,&amount,sizeof(float));
	read(sd,&result,sizeof(result));

	if(!result)
	{
		write(1,"Error in depositing your money to your account. !!\n\n",sizeof("Error in depositing your money to your account. !!\n\n"));
	}
	else
	{
		write(1,"Your amount has been deposited succesfully !!\n\n",sizeof("Your amount has been deposited succesfully !!\n\n"));
	}

	client_show_menu(sd);
	return;
}

void client_withdraw_money(int sd)
{
	float amount;
	int select=2;
	bool result;

	write(1,"Enter the amount you want to Withdraw: Rs.",sizeof("Enter the amount you want to withdraw: Rs."));
	scanf("%f",&amount);

	while(amount<=0)
	{
		write(1,"Please enter a valid amount!!\n",sizeof("Please enter a valid amount!!\n"));
		write(1,"Enter the amount you want to Withdraw: Rs.",sizeof("Enter the amount you want to withdraw: Rs."));
		scanf("%f",&amount);
	}

	write(sd,&select,sizeof(int));
	write(sd,&amount,sizeof(float));
	read(sd,&result,sizeof(result));

	if(!result)
	{
		write(1,"Error in withdrawing your money from your account. !!\n\n",sizeof("Error in withdrawing your money from your account. !!\n\n"));
	}
	else
	{
		write(1,"Amount Succesfully withdrawn from your account !!\n\n",sizeof("Amount Succesfully withdrawn from your account !!\n\n"));
	}
	client_show_menu(sd);
	return;
}

void client_check_balance(int sd)
{
	float amount;
	int select=3;
	int len;

	write(sd,&select,sizeof(int));
	len=read(sd,&amount,sizeof(float));

	write(1,"Available balance in your account is: Rs.",sizeof("Available balance in your account is: Rs."));
	printf("%0.3f\n\n",amount);

	client_show_menu(sd);
	return;
}

void client_change_password(int sd)
{
	int select=4;
	char nPassword[10];
	bool result;

	write(1,"Enter the new password: ",sizeof("Enter the new password: "));
	scanf("%s",nPassword);

	write(sd,&select,sizeof(int));
	write(sd,nPassword,sizeof(nPassword));
	read(sd,&result,sizeof(result));

	if(!result)
	{
		write(1,"Error in changing your account password!!\n\n",sizeof("Error in changing your account password!!\n\n"));
	}
	else
	{
		write(1,"Succesfully changed your login password!!\n\n",sizeof("Succesfully changed your login password!!\n\n"));
	}

	client_show_menu(sd);
	return;
}

void client_view_details(int sd)
{
	int select=5;
	write(sd,&select,sizeof(int));
	if(account_type==1)
	{
		transaction transaction_details;
		while(read(sd,&transaction_details,sizeof(transaction))!=0)
		{
			if(transaction_details.value>0)
			{
				printf("%s %f\n",transaction_details.transaction,transaction_details.value);
			}
			else
			{
				break;
			}			
		}
	}
	else if(account_type==2)
	{
		transaction transaction_details;
		while(read(sd,&transaction_details,sizeof(transaction))!=0)
		{
			if(transaction_details.value>0)
			{
				printf("%s %f\n",transaction_details.transaction,transaction_details.value);
			}
			else
			{
				break;
			}			
		}
	}
	client_show_menu(sd);
	return;
}

void client_add_account(int sd)
{
	int select=1;
	int type;
	bool result;

	write(sd,&select,sizeof(int));

	write(1,"Enter the account type \n1) Normal use account \n2) Joint user account \nChoice: ",sizeof("Enter the account type \n1) Normal use account \n2) Joint user account \nChoice: "));
	scanf("%d",&type);

	write(sd,&type,sizeof(int));

	if(type==1)
	{
		normal_user addUser1;
		write(1,"Name of the account holder : ",sizeof("Name of the account holder : "));
		scanf(" %[^\n]",addUser1.name);

		write(1,"Account password: ",sizeof("Account password: "));
		scanf("%s",addUser1.password);
		
		write(1,"Account Initial Deposit: Rs.",sizeof("Account Initial Deposit: Rs."));
		scanf("%f",&addUser1.balance);
		write(sd,&addUser1,sizeof(normal_user));
	}
	else if(type==2)
	{
		joint_user addUser2;
		write(1,"Name of the primary account holder: ",sizeof("Name of the primary account holder: "));
		scanf(" %[^\n]",addUser2.name1);

		write(1,"Name of the secondary account holder: ",sizeof("Name of the secondary account holder: "));
		scanf(" %[^\n]",addUser2.name2);
		
		write(1,"Account password: ",sizeof("Account password: "));
		scanf("%s",addUser2.password);
		
		write(1,"Account Initial Deposit: Rs.",sizeof("Account Initial Deposit: Rs."));
		scanf("%f",&addUser2.balance);
		write(sd,&addUser2,sizeof(joint_user));
	}
	
	read(sd,&result,sizeof(result));

	if(!result)
	{
		write(1,"Error in adding the account !!\n\n",sizeof("Error in adding the account !!\n\n"));
	}
	else
	{
		write(1,"Succesfully added the account !!\n\n",sizeof("Succesfully added the account !!\n\n"));
	}

	client_show_menu(sd);
	return;
}

void client_delete_account(int sd)
{
	int select=2;
	int type,userID;
	bool result;

	write(sd,&select,sizeof(int));

	write(1,"Enter the account type \n1) Normal use account \n2) Joint user account \nChoice: ",sizeof("Enter the account type \n1) Normal use account \n2) Joint user account \nChoice: "));
	scanf("%d",&type);
	
	write(sd,&type,sizeof(int));

	write(1,"User ID : ",sizeof("User ID : "));
	scanf("%d",&userID);

	write(sd,&userID,sizeof(int));	
	read(sd,&result,sizeof(result));

	if(!result)
	{
		write(1,"Error int deleting the account.\nPlease check the User ID.\n\n",sizeof("Error int deleting the account.\nPlease check the User ID.\n\n"));
	}
	else
	{
		write(1,"Account Deleted Sucessfully !! \n\n",sizeof("Account Deleted Sucessfully !! \n\n"));
	}
	client_show_menu(sd);
	return;
}

void client_update_account(int sd)
{
	int select=3;
	int type;
	bool result;

	write(sd,&select,sizeof(int));

	write(1,"Enter the account type \n1) Normal use account \n2) Joint user account \nChoice: ",sizeof("Enter the account type \n1) Normal use account \n2) Joint user account \nChoice: "));
	scanf("%d",&type);

	write(sd,&type,sizeof(int));

	if(type==1)
	{
		normal_user modUser1;
		write(1,"Enter account ID: ",sizeof("Enter account ID: "));
		scanf("%d",&modUser1.userID);

		write(1,"Enter Account Number: ",sizeof("Enter Account Number: "));
		scanf("%d",&modUser1.account_number);

		write(1,"Enter New Account Holder Name: ",sizeof("Enter New Account Holder Name: "));
		scanf(" %[^\n]",modUser1.name);

		write(1,"Enter New Account Password: ",sizeof("Enter New Account Password: "));
		scanf("%s",modUser1.password);

		write(1,"Enter New Account Balance : ",sizeof("Enter New Account Balance : "));
		scanf("%f",&modUser1.balance);
		write(sd,&modUser1,sizeof(normal_user));
	}
	else if(type==2)
	{
		joint_user modUser2;
		write(1,"Enter account ID: ",sizeof("Enter account ID: "));
		scanf("%d",&modUser2.userID);

		write(1,"Enter Account Number: ",sizeof("Enter Account Number: "));
		scanf("%d",&modUser2.account_number);
		
		write(1,"Enter New Primary Account Holder Name: ",sizeof("Enter New Primary Account Holder Name: "));
		scanf(" %[^\n]",modUser2.name1);
		
		write(1,"Enter New Secondary Account Holder Name: ",sizeof("Enter New Secondary Account Holder Name: "));
		scanf(" %[^\n]",modUser2.name2);
		
		write(1,"Enter New Account Password: ",sizeof("Enter New Account Password: "));
		scanf("%s",modUser2.password);

		write(1,"Enter New Account Balance : ",sizeof("Enter New Account Balance : "));
		scanf("%f",&modUser2.balance);
		write(sd,&modUser2,sizeof(joint_user));
	}
	
	read(sd,&result,sizeof(result));

	if(!result)
	{
		write(1,"Error in modifying the entered account.\nPlease check the User ID and Account No.\n\n",sizeof("Error in modifying the entered account.\nPlease check the User ID and Account No.\n\n"));
	}
	else
	{
		write(1,"Account modified Sucessfully !!\n\n",sizeof("Account modified Sucessfully !!\n\n"));
	}

	client_show_menu(sd);
	return;
}

void client_search_account(int sd)
{
	int select=4;
	int type,len;
	bool result;

	write(sd,&select,sizeof(int));

	write(1,"Enter the account type \n1) Normal use account \n2) Joint user account \nChoice: ",sizeof("Enter the account type \n1) Normal use account \n2) Joint user account \nChoice: "));
	scanf("%d",&type);

	write(sd,&type,sizeof(int));

	if(type==1)
	{
		normal_user searchUser1;
		int userID;
		write(1,"Enter account ID: ",sizeof("Enter account ID: "));
		scanf("%d",&userID);

		write(sd,&userID,sizeof(int));
		
		len=read(sd,&searchUser1,sizeof(normal_user));
		if(len==0)
		{
			write(1,"Please check the Account ID!!\n\n",sizeof("Please check the Account ID!!\n\n"));
		}
		else
		{
			printf("Account ID : %d\n",searchUser1.userID);
			printf("Account Number : %d\n",searchUser1.account_number);
			printf("Account holder name : %s\n",searchUser1.name);			
			printf("Available Balance: Rs.%0.3f\n",searchUser1.balance);
			printf("Account status : %s\n\n",searchUser1.status);
		}
	}
	else if(type==2)
	{
		joint_user searchUser2;
		int userID1;
		write(1,"Enter account ID: ",sizeof("Enter account ID: "));
		scanf("%d",&userID1);
		write(sd,&userID1,sizeof(int));
		
		len=read(sd,&searchUser2,sizeof(joint_user));
		if(len==0)
		{
			write(1,"Please check the Account ID!!\n\n",sizeof("Please check the Account ID!!\n\n"));
		}
		else
		{
			printf("Account ID: %d\n",searchUser2.userID);
			printf("Account Number: %d\n",searchUser2.account_number);
			printf("Primary Account Holder's Name: %s\n",searchUser2.name1);
			printf("Secondary Account Holder's Name: %s\n",searchUser2.name2);			
			printf("Available Balance: Rs.%0.3f\n",searchUser2.balance);
			printf("Account Status: %s\n\n",searchUser2.status);
		}
	}
	client_show_menu(sd);
	return;
}

int main()
{
	struct sockaddr_in server;
	int sd,msgLength;
	char buff[50];
	char result;

	sd=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(5555);
	connect(sd,(struct sockaddr *)&server,sizeof(server));
	client_choose_option(sd);
	client_show_menu(sd);
	close(sd);
	return 0;
}