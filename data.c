/*Program to create three or more records in a file*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

#include"datatypes.h"

int main()
{
	int fd=open("admin_user.dat",O_RDWR | O_CREAT | O_TRUNC,0744);

	admin_user new_admin_user;
	strcpy(new_admin_user.username,"admin");
	strcpy(new_admin_user.password,"123");
	new_admin_user.userID=1000;
	write(fd,&new_admin_user,sizeof(admin_user));
	close(fd);

	fd=open("normal_user.dat",O_RDWR | O_CREAT | O_TRUNC,0744);
	close(fd);

	fd=open("joint_user.dat",O_RDWR | O_CREAT | O_TRUNC ,0744);
	close(fd);

	fd=open("normal_transactions.dat",O_RDWR | O_CREAT | O_TRUNC, 0744);
	close(fd);

	fd=open("joint_transactions.dat",O_RDWR | O_CREAT | O_TRUNC, 0744);
	close(fd);
	
	return 0;
}