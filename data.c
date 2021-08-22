/*Program to create three or more records in a file*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

#include"datatypes.h"

int get_normal_user_ID();
int get_joint_user_ID();
int get_admin_user_ID();

int get_normal_user_ID()
{
	int fd=open("normal_user.dat",O_RDONLY,0744);
	normal_user user;
	lseek(fd,-sizeof(normal_user),SEEK_END);
	read(fd,&user,sizeof(normal_user));
	close(fd);
	return user.userID+1;
}

int get_joint_user_ID()
{
	int fd=open("joint_user.dat",O_RDONLY,0744);
	joint_user user;
	lseek(fd,-sizeof(joint_user),SEEK_END);
	read(fd,&user,sizeof(joint_user));
	close(fd);
	return user.userID+1;
}

int get_admin_user_ID()
{
	int fd=open("admin_user.dat",O_RDONLY,0744);
	admin_user user;
	lseek(fd,-sizeof(admin_user),SEEK_END);
	read(fd,&user,sizeof(admin_user));
	close(fd);
	return user.userID+1;
}

int main()
{
	int fd=open("admin_user.dat",O_RDWR | O_CREAT | O_TRUNC,0744);
	int choice=0;
	admin_user new_admin_user;
	printf("Please enter the name of the admin_user: ");
	scanf(" %s",new_admin_user.username);
	printf("Please enter the password(max 10 characters): ");
	scanf(" %s",new_admin_user.password);
	new_admin_user.userID=1000;
	printf("Your userID is : %d\n",new_admin_user.userID);
	write(fd,&new_admin_user,sizeof(new_admin_user));
	printf("Do you want to continue(0/1)? ");
	scanf("%d",&choice);
	while(choice)
	{
		printf("Please enter the name of the admin_user: ");
		scanf(" %[^\n]",new_admin_user.username);
		printf("Please enter the password(max 10 characters): ");
		scanf(" %[^\n]",new_admin_user.password);
		new_admin_user.userID=get_admin_user_ID();
		printf("Your userID is : %d\n",new_admin_user.userID);
		write(fd,&new_admin_user,sizeof(admin_user));
		printf("Do you want to continue(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd);

	fd=open("normal_user.dat",O_RDWR | O_CREAT | O_TRUNC,0744);
	choice=1;
	normal_user new_normal_user;
	printf("Please enter the name of the normal user: ");
	scanf(" %[^\n]",new_normal_user.name);
	printf("Please enter the password(max 10 characters): ");
	scanf(" %[^\n]",new_normal_user.password);
	new_normal_user.userID=1000;
	new_normal_user.balance=1000;
	new_normal_user.account_number=(new_normal_user.userID-1000)+100000;
	printf("Your userID is : %d\n",new_normal_user.userID);
	strcpy(new_normal_user.status,"ACTIVE");
	write(fd,&new_normal_user,sizeof(normal_user));
	printf("Do you want to continue(0/1)? ");
	scanf("%d",&choice);
	while(choice)
	{
		printf("Please enter the name of the normal user: ");
		scanf(" %[^\n]",new_normal_user.name);
		printf("Please enter the password(max 10 characters): ");
		scanf(" %[^\n]",new_normal_user.password);
		new_normal_user.userID=get_normal_user_ID();
		new_normal_user.balance=1000;
		new_normal_user.account_number=(new_normal_user.userID-1000)+100000;
		printf("Your userID is : %d\n",new_normal_user.userID);
		strcpy(new_normal_user.status,"ACTIVE");
		write(fd,&new_normal_user,sizeof(normal_user));
		printf("Do you want to continue(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd);

	fd=open("joint_user.dat",O_RDWR | O_CREAT | O_TRUNC ,0744);
	choice=1;
	joint_user new_joint_user;
	printf("Please enter the main name of the joint user: ");
	scanf(" %[^\n]",new_joint_user.name1);
	printf("Please enter the second name of the joint user: ");
	scanf(" %[^\n]",new_joint_user.name2);
	printf("Please enter the password(max 10 characters): ");
	scanf(" %[^\n]",new_joint_user.password);
	new_joint_user.userID=1000;
	new_joint_user.balance=1000;
	new_joint_user.account_number=(new_joint_user.userID-1000)+100000;
	printf("Your userID is : %d\n",new_joint_user.userID);
	strcpy(new_joint_user.status,"ACTIVE");
	write(fd,&new_joint_user,sizeof(joint_user));
	printf("Do you want to continue(0/1)? ");
	scanf("%d",&choice);
	while(choice)
	{
		printf("Please enter the main name of the joint user: ");
		scanf(" %[^\n]",new_joint_user.name1);
		printf("Please enter the second name of the joint user: ");
		scanf(" %[^\n]",new_joint_user.name2);
		printf("Please enter the password(max 10 characters): ");
		scanf(" %[^\n]",new_joint_user.password);
		new_joint_user.userID=get_joint_user_ID();
		new_joint_user.balance=1000;
		new_joint_user.account_number=(new_joint_user.userID-1000)+100000;
		printf("Your userID is : %d\n",new_joint_user.userID);
		strcpy(new_joint_user.status,"ACTIVE");
		write(fd,&new_joint_user,sizeof(joint_user));
		printf("Do you want to continue(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd);

	fd=open("normal_transactions.dat",O_RDWR | O_CREAT | O_TRUNC, 0744);
	close(fd);

	fd=open("joint_transactions.dat",O_RDWR | O_CREAT | O_TRUNC, 0744);
	close(fd);
	
	return 0;
}