#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<fcntl.h>
#include <pthread.h>

#include "server.h"

admin_user server_get_admin_user(int ID)
{
	int i=ID-1000;
	int fd=open("admin_user.dat",O_RDONLY,0744);
	int fl;
	struct flock file_lock;
	admin_user user;

	file_lock.l_type = F_RDLCK;
	file_lock.l_whence=SEEK_SET;
	file_lock.l_start=(i)*sizeof(admin_user);
	file_lock.l_len=sizeof(admin_user);
	file_lock.l_pid=getpid();
	
	fl=fcntl(fd,F_SETLKW,&file_lock);

	lseek(fd,(i)*sizeof(admin_user),SEEK_SET);
	read(fd,&user,sizeof(admin_user));

	file_lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&file_lock);

	close(fd);
	return user;
}

normal_user server_get_normal_user(int ID)
{
	int i=ID-1000;
	normal_user user;
	int fd=open("normal_user.dat",O_RDONLY,0744);	
	int fl;
	struct flock file_lock;

	file_lock.l_type = F_RDLCK;
	file_lock.l_whence=SEEK_SET;
	file_lock.l_start=(i)*sizeof(normal_user);
	file_lock.l_len=sizeof(normal_user);
	file_lock.l_pid=getpid();
	
	fl=fcntl(fd,F_SETLKW,&file_lock);

	lseek(fd,(i)*sizeof(normal_user),SEEK_SET);
	read(fd,&user,sizeof(normal_user));

	file_lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&file_lock);

	close(fd);
	return user;
}

joint_user server_get_joint_user(int ID)
{
	int i=ID-1000;
	joint_user user;
	int fd=open("joint_user.dat",O_RDONLY,0744);	
	int fl;
	struct flock file_lock;

	file_lock.l_type = F_RDLCK;
	file_lock.l_whence=SEEK_SET;
	file_lock.l_start=(i)*sizeof(joint_user);
	file_lock.l_len=sizeof(joint_user);
	file_lock.l_pid=getpid();
	
	fl=fcntl(fd,F_SETLKW,&file_lock);

	lseek(fd,(i)*sizeof(joint_user),SEEK_SET);
	read(fd,&user,sizeof(joint_user));

	file_lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&file_lock);

	close(fd);
	return user;
}

bool server_check_normal_user_password(normal_user current_user)
{
	int i=current_user.userID-1000;
	int fd=open("normal_user.dat",O_RDONLY,0744);
	bool result;
	normal_user temp;	
	int fl;
	struct flock file_lock;

	file_lock.l_type = F_RDLCK;
	file_lock.l_whence=SEEK_SET;
	file_lock.l_start=(i)*sizeof(normal_user);
	file_lock.l_len=sizeof(normal_user);
	file_lock.l_pid=getpid();	
	fl=fcntl(fd,F_SETLKW,&file_lock);
	lseek(fd,(i)*sizeof(normal_user),SEEK_SET);
	read(fd,&temp,sizeof(normal_user));
	if(!strcmp(temp.password,current_user.password) && !strcmp(temp.status,"ACTIVE"))
	{
		result=true;
	}
	else
	{
		result=false;
	}

	file_lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&file_lock);
	close(fd);
	return result;
}

bool server_check_joint_user_password(joint_user current_user)
{
	int i=current_user.userID-1000;
	int fd=open("joint_user.dat",O_RDONLY,0744);
	bool result;
	joint_user temp;	
	int fl;
	struct flock file_lock;

	file_lock.l_type = F_RDLCK;
	file_lock.l_whence=SEEK_SET;
	file_lock.l_start=(i)*sizeof(joint_user);
	file_lock.l_len=sizeof(joint_user);
	file_lock.l_pid=getpid();
	
	fl=fcntl(fd,F_SETLKW,&file_lock);

	lseek(fd,(i)*sizeof(joint_user),SEEK_SET);
	read(fd,&temp,sizeof(joint_user));
	if(!strcmp(temp.password,current_user.password) && !strcmp(temp.status,"ACTIVE"))
	{
		result=true;
	}
	else
	{
		result=false;
	}

	file_lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&file_lock);
	close(fd);
	return result;
}

bool server_check_admin_user_password(admin_user current_user)
{
	int i=current_user.userID-1000;
	int fd=open("admin_user.dat",O_RDONLY,0744);
	bool result;
	admin_user temp;	
	int fl;
	struct flock file_lock;

	file_lock.l_type = F_RDLCK;
	file_lock.l_whence=SEEK_SET;
	file_lock.l_start=(i)*sizeof(admin_user);
	file_lock.l_len=sizeof(admin_user);
	file_lock.l_pid=getpid();
	
	fl=fcntl(fd,F_SETLKW,&file_lock);

	lseek(fd,(i)*sizeof(admin_user),SEEK_SET);
	read(fd,&temp,sizeof(admin_user));
	if(!strcmp(temp.password,current_user.password))
	{
		result=true;
	}
	else
	{
		result=false;
	}

	file_lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&file_lock);
	close(fd);
	return result;
}

bool server_deposit_money(int account_type,int ID,float deposit_amount)
{
	int i=ID-1000;
	if(account_type==1)
	{
		int fd=open("normal_user.dat",O_RDWR,0744);
		bool result;
		int fl;
		struct flock file_lock;

		file_lock.l_type = F_WRLCK;
		file_lock.l_whence=SEEK_SET;
		file_lock.l_start=(i)*sizeof(normal_user);
		file_lock.l_len=sizeof(normal_user);
		file_lock.l_pid=getpid();
	
		fl=fcntl(fd,F_SETLKW,&file_lock);

		normal_user current_user;
		lseek(fd,(i)*sizeof(normal_user),SEEK_SET);
		read(fd,&current_user,sizeof(normal_user));
		
		if(!strcmp(current_user.status,"ACTIVE"))
		{
			current_user.balance+=deposit_amount;
			lseek(fd,sizeof(normal_user)*(-1),SEEK_CUR);
			write(fd,&current_user,sizeof(normal_user));
			result=true;
		}
		else
		{
			result=false;
		}

		file_lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&file_lock);
		close(fd);

		fd=open("normal_transactions.dat",O_WRONLY,0744);
		lseek(fd,0,SEEK_END);
		transaction transaction_details;
		transaction_details.userID=ID;
		strcpy(transaction_details.transaction,"Deposit Money");
		transaction_details.value=deposit_amount;
		write(fd,&transaction_details,sizeof(transaction));
		close(fd);

		return result;	
	}
	else if(account_type==2)
	{
		int fd=open("joint_user.dat",O_RDWR,0744);
		bool result;
		int fl;
		struct flock file_lock;
		joint_user current_user;
		
		file_lock.l_type = F_WRLCK;
		file_lock.l_whence=SEEK_SET;
		file_lock.l_start=(i)*sizeof(joint_user);
		file_lock.l_len=sizeof(joint_user);
		file_lock.l_pid=getpid();
	
		fl=fcntl(fd,F_SETLKW,&file_lock);		
		lseek(fd,(i)*sizeof(joint_user),SEEK_SET);
		read(fd,&current_user,sizeof(joint_user));
		
		if(!strcmp(current_user.status,"ACTIVE"))
		{
			current_user.balance+=deposit_amount;
			lseek(fd,sizeof(joint_user)*(-1),SEEK_CUR);
			write(fd,&current_user,sizeof(joint_user));
			result=true;
		}
		else
		{
			result=false;
		}
		file_lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&file_lock);
		close(fd);

		fd=open("joint_transactions.dat",O_WRONLY,0744);
		lseek(fd,0,SEEK_END);
		transaction transaction_details;
		transaction_details.userID=ID;
		strcpy(transaction_details.transaction,"Deposit Money");
		transaction_details.value=deposit_amount;
		write(fd,&transaction_details,sizeof(transaction));
		close(fd);

		return result;
	}
	return false;
}

bool server_withdraw_money(int account_type,int ID,float withdraw_amount)
{
	int i=ID-1000;
	if(account_type==1)
	{
		int fd=open("normal_user.dat",O_RDWR,0744);
		bool result;
		int fl;
		struct flock file_lock;
		file_lock.l_type = F_WRLCK;
		file_lock.l_whence=SEEK_SET;
		file_lock.l_start=(i)*sizeof(normal_user);
		file_lock.l_len=sizeof(normal_user);
		file_lock.l_pid=getpid();
	
		fl=fcntl(fd,F_SETLKW,&file_lock);

		normal_user current_user;
		lseek(fd,(i)*sizeof(normal_user),SEEK_SET);
		read(fd,&current_user,sizeof(normal_user));
		
		if(!strcmp(current_user.status,"ACTIVE") && current_user.balance>=withdraw_amount)
		{
			current_user.balance-=withdraw_amount;
			lseek(fd,sizeof(normal_user)*(-1),SEEK_CUR);
			write(fd,&current_user,sizeof(normal_user));
			result=true;
		}
		else
		{
			result=false;
		}
		file_lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&file_lock);
		close(fd);
		
		fd=open("normal_transactions.dat",O_WRONLY,0744);
		lseek(fd,0,SEEK_END);
		transaction transaction_details;
		transaction_details.userID=ID;
		strcpy(transaction_details.transaction,"Withdraw Money");
		transaction_details.value=withdraw_amount;
		write(fd,&transaction_details,sizeof(transaction));
		close(fd);
		return result;	
	}
	else if(account_type==2)
	{
		int fd=open("joint_user.dat",O_RDWR,0744);
		bool result;
		int fl;
		struct flock file_lock;
		file_lock.l_type = F_WRLCK;
		file_lock.l_whence=SEEK_SET;
		file_lock.l_start=(i)*sizeof(joint_user);
		file_lock.l_len=sizeof(joint_user);
		file_lock.l_pid=getpid();
	
		fl=fcntl(fd,F_SETLKW,&file_lock);

		joint_user current_user;
		lseek(fd,(i)*sizeof(joint_user),SEEK_SET);
		read(fd,&current_user,sizeof(joint_user));
		
		if(!strcmp(current_user.status,"ACTIVE") && current_user.balance>=withdraw_amount)
		{
			current_user.balance-=withdraw_amount;
			lseek(fd,sizeof(joint_user)*(-1),SEEK_CUR);
			write(fd,&current_user,sizeof(joint_user));
			result=true;
		}
		else
		{
			result=false;
		}
		file_lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&file_lock);
		close(fd);
		fd=open("joint_transactions.dat",O_WRONLY,0744);
		lseek(fd,0,SEEK_END);
		transaction transaction_details;
		transaction_details.userID=ID;
		strcpy(transaction_details.transaction,"Withdraw Money");
		transaction_details.value=withdraw_amount;
		write(fd,&transaction_details,sizeof(transaction));
		close(fd);
		return result;
	}
	return false;
}

float server_get_user_balance(int account_type,int ID)
{
	int i=ID-1000;
	float result;
	if(account_type==1)
	{
		int i=ID-1000;
		int fd=open("normal_user.dat",O_RDONLY,0744);
		normal_user temp;
	
		int fl;
		struct flock file_lock;
		file_lock.l_type = F_RDLCK;
		file_lock.l_whence=SEEK_SET;
		file_lock.l_start=(i)*sizeof(normal_user);
		file_lock.l_len=sizeof(normal_user);
		file_lock.l_pid=getpid();
	
		fl=fcntl(fd,F_SETLKW,&file_lock);

		lseek(fd,(i)*sizeof(normal_user),SEEK_SET);
		read(fd,&temp,sizeof(normal_user));
		if(!strcmp(temp.status,"ACTIVE"))
		{
			result=temp.balance;
		}
		else
		{
			result=0;
		}
		file_lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&file_lock);

		close(fd);
		return result;
	}
	else if(account_type==2)
	{
		int i=ID-1000;
		int fd=open("joint_user.dat",O_RDONLY,0744);
		joint_user temp;
	
		int fl;
		struct flock file_lock;
		file_lock.l_type = F_RDLCK;
		file_lock.l_whence=SEEK_SET;
		file_lock.l_start=(i)*sizeof(joint_user);
		file_lock.l_len=sizeof(joint_user);
		file_lock.l_pid=getpid();
	
		fl=fcntl(fd,F_SETLKW,&file_lock);

		lseek(fd,(i)*sizeof(joint_user),SEEK_SET);
		read(fd,&temp,sizeof(joint_user));
		if(!strcmp(temp.status,"ACTIVE"))
		{
			result=temp.balance;
		}
		else
		{
			result=0;
		}
		file_lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&file_lock);

		close(fd);
		return result;
	}
	return 0;
}

bool server_change_user_password(int account_type,int ID,char newPwd[10])
{
	int i=ID-1000;
	if(account_type==1)
	{
		int fd=open("normal_user.dat",O_RDWR,0744);
		bool result;
		int fl;
		struct flock file_lock;
		file_lock.l_type = F_WRLCK;
		file_lock.l_whence=SEEK_SET;
		file_lock.l_start=(i)*sizeof(normal_user);
		file_lock.l_len=sizeof(normal_user);
		file_lock.l_pid=getpid();
	
		fl=fcntl(fd,F_SETLKW,&file_lock);

		normal_user current_user;
		lseek(fd,(i)*sizeof(normal_user),SEEK_SET);
		read(fd,&current_user,sizeof(normal_user));
		
		if(!strcmp(current_user.status,"ACTIVE"))
		{
			strcpy(current_user.password,newPwd);
			lseek(fd,sizeof(normal_user)*(-1),SEEK_CUR);
			write(fd,&current_user,sizeof(normal_user));
			result=true;
		}
		else
		{
			result=false;
		}
		file_lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&file_lock);

		close(fd);
		return result;
	}
	else if(account_type==2)
	{
		int fd=open("joint_user.dat",O_RDWR,0744);
		bool result;
		int fl;
		struct flock file_lock;
		file_lock.l_type = F_WRLCK;
		file_lock.l_whence=SEEK_SET;
		file_lock.l_start=(i)*sizeof(joint_user);
		file_lock.l_len=sizeof(joint_user);
		file_lock.l_pid=getpid();
	
		fl=fcntl(fd,F_SETLKW,&file_lock);

		joint_user current_user;
		lseek(fd,(i)*sizeof(joint_user),SEEK_SET);
		read(fd,&current_user,sizeof(joint_user));
		
		if(!strcmp(current_user.status,"ACTIVE"))
		{
			strcpy(current_user.password,newPwd);
			lseek(fd,sizeof(joint_user)*(-1),SEEK_CUR);
			write(fd,&current_user,sizeof(joint_user));
			result=true;
		}
		else
		{
			result=false;
		}
		file_lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&file_lock);
		close(fd);
		return result;
	}
	return false;
}

bool server_add_normal_user(normal_user record)
{
	int fd=open("normal_user.dat",O_RDWR,0744);
	bool result;
	
	int fl;
	struct flock file_lock;
	file_lock.l_type = F_WRLCK;
	file_lock.l_whence=SEEK_END;
	file_lock.l_start=(-1)*sizeof(normal_user);
	file_lock.l_len=sizeof(normal_user);
	file_lock.l_pid=getpid();
	
	fl=fcntl(fd,F_SETLKW,&file_lock);

	normal_user endUser;
	lseek(fd,(-1)*sizeof(normal_user),SEEK_END);
	read(fd,&endUser,sizeof(normal_user));
		
	record.userID=endUser.userID+1;
	record.account_number=endUser.account_number+1;
	strcpy(record.status,"ACTIVE");
	
	int j=write(fd,&record,sizeof(normal_user));
	if(j!=0)
	{
		result=true;
	}
	else
	{
		result=false;
	}
	file_lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&file_lock);
	
	close(fd);
	return result;	
}

bool server_add_joint_user(joint_user record)
{
	int fd=open("joint_user.dat",O_RDWR,0744);
	bool result;
	
	int fl;
	struct flock file_lock;
	file_lock.l_type = F_WRLCK;
	file_lock.l_whence=SEEK_END;
	file_lock.l_start=(-1)*sizeof(joint_user);
	file_lock.l_len=sizeof(joint_user);
	file_lock.l_pid=getpid();
	
	fl=fcntl(fd,F_SETLKW,&file_lock);

	joint_user endUser;
	lseek(fd,(-1)*sizeof(joint_user),SEEK_END);
	read(fd,&endUser,sizeof(joint_user));
		
	record.userID=endUser.userID+1;
	record.account_number=endUser.account_number+1;
	strcpy(record.status,"ACTIVE");
	
	int j=write(fd,&record,sizeof(joint_user));
	if(j!=0)
	{
		result=true;
	}
	else
	{
		result=false;
	}
	file_lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&file_lock);
	
	close(fd);
	return result;	
}

bool server_delete_normal_user(int ID)
{
	int i=ID-1000;
	int fd=open("normal_user.dat",O_RDWR,0744);
	bool result;
	
	int fl;
	struct flock file_lock;
	file_lock.l_type = F_WRLCK;
	file_lock.l_whence=SEEK_SET;
	file_lock.l_start=(i)*sizeof(normal_user);
	file_lock.l_len=sizeof(normal_user);
	file_lock.l_pid=getpid();
	
	fl=fcntl(fd,F_SETLKW,&file_lock);

	normal_user current_user;
	lseek(fd,(i)*sizeof(normal_user),SEEK_SET);
	read(fd,&current_user,sizeof(normal_user));
	
	if(!strcmp(current_user.status,"ACTIVE"))
	{	
		strcpy(current_user.status,"CLOSED");
		current_user.balance=0;
		
		lseek(fd,(-1)*sizeof(normal_user),SEEK_CUR); 
		int j=write(fd,&current_user,sizeof(normal_user));
		if(j!=0)
		{
			result=true;
		}
		else
		{
			result=false;
		}
	}
	
	file_lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&file_lock);	
	close(fd);
	return result;	
}

bool server_delete_joint_user(int ID)
{
	int i=ID-1000;
	int fd=open("joint_user.dat",O_RDWR,0744);
	bool result;
	
	int fl;
	struct flock file_lock;
	file_lock.l_type = F_WRLCK;
	file_lock.l_whence=SEEK_SET;
	file_lock.l_start=(i)*sizeof(joint_user);
	file_lock.l_len=sizeof(joint_user);
	file_lock.l_pid=getpid();
	
	fl=fcntl(fd,F_SETLKW,&file_lock);

	joint_user current_user;
	lseek(fd,(i)*sizeof(joint_user),SEEK_SET);
	read(fd,&current_user,sizeof(joint_user));
	
	if(!strcmp(current_user.status,"ACTIVE"))
	{
		strcpy(current_user.status,"CLOSED");
		current_user.balance=0;
		
		lseek(fd,(-1)*sizeof(joint_user),SEEK_CUR); 
		int j=write(fd,&current_user,sizeof(joint_user));
		if(j!=0)
		{
			result=true;
		}
		else
		{
			result=false;
		}
	}	
	file_lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&file_lock);	
	close(fd);
	return result;	
}

bool server_modify_normal_user(normal_user modUser)
{
	int i=modUser.userID-1000;
	int fd=open("normal_user.dat",O_RDWR,0744);
	bool result=false;
	
	int fl;
	struct flock file_lock;
	file_lock.l_type = F_WRLCK;
	file_lock.l_whence=SEEK_SET;
	file_lock.l_start=(i)*sizeof(normal_user); 
	file_lock.l_len=sizeof(normal_user);
	file_lock.l_pid=getpid();
	
	fl=fcntl(fd,F_SETLKW,&file_lock);

	normal_user current_user;
	lseek(fd,(i)*sizeof(normal_user),SEEK_SET);
	read(fd,&current_user,sizeof(normal_user));
	
	if(!strcmp(current_user.status,"ACTIVE") && (modUser.account_number==current_user.account_number))
	{	
		strcpy(modUser.status,"ACTIVE");
		lseek(fd,(-1)*sizeof(normal_user),SEEK_CUR); 
		int j=write(fd,&modUser,sizeof(normal_user));
		if(j!=0)
		{
			result=true;
		}
		else
		{
			result=false;
		}
	}

	file_lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&file_lock);	
	close(fd);
	return result;
}

bool server_modify_joint_user(joint_user modUser)
{
	int i=modUser.userID-1000;
	int fd=open("joint_user.dat",O_RDWR,0744);
	bool result=false;
	
	int fl;
	struct flock file_lock;
	file_lock.l_type = F_WRLCK;
	file_lock.l_whence=SEEK_SET;
	file_lock.l_start=(i)*sizeof(joint_user);
	file_lock.l_len=sizeof(joint_user);
	file_lock.l_pid=getpid();
	
	fl=fcntl(fd,F_SETLKW,&file_lock);

	joint_user current_user;
	lseek(fd,(i)*sizeof(joint_user),SEEK_SET);
	read(fd,&current_user,sizeof(joint_user));
	
	if(!strcmp(current_user.status,"ACTIVE")  && (modUser.account_number==current_user.account_number))
	{
		strcpy(modUser.status,"ACTIVE");
		lseek(fd,(-1)*sizeof(joint_user),SEEK_CUR); 
		int j=write(fd,&modUser,sizeof(joint_user));
		if(j!=0)
		{
			result=true;
		}
		else
		{
			result=false;
		}
	}
	
	file_lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&file_lock);
	
	close(fd);
	return result;	
}

void server_get_transaction_details(int nsd,int account_type,int current_userID)
{
	if(account_type==1)
	{
		int fd=open("normal_transactions.dat",O_RDONLY,0744);
		printf("%d",fd);
		lseek(fd,0,SEEK_SET);
		transaction transaction_details;
		while(read(fd,&transaction_details,sizeof(transaction))!=0)
		{
			if(transaction_details.userID==current_userID)
			{
				write(nsd,&transaction_details,sizeof(transaction));
			}		
		}
		transaction_details.value=-1;
		write(nsd,&transaction_details,sizeof(transaction));
		close(fd);
	}
	else if(account_type==2)
	{
		int fd=open("joint_transactions.dat",O_RDONLY,0744);
		lseek(fd,0,SEEK_SET);
		transaction transaction_details;
		while(read(fd,&transaction_details,sizeof(transaction))!=0)
		{
			if(transaction_details.userID==current_userID)
			{
				write(nsd,&transaction_details,sizeof(transaction));
			}		
		}
		transaction_details.value=-1;
		write(nsd,&transaction_details,sizeof(transaction));
		close(fd);
	}
}

void server_task_handler(int nsd)
{
	int msgLength,select,type,account_type,accType,current_userID;
	bool result;
	while(1)
	{
		read(nsd,&account_type,sizeof(account_type));
		printf("Option : %d\n",account_type);

		if(account_type==1)
		{
			normal_user current_user1;
			accType=1;
			msgLength=read(nsd,&current_user1,sizeof(normal_user));
			printf("Username : %d\n",current_user1.userID);
			printf("Password : %s\n",current_user1.password);
			current_userID=current_user1.userID;
			result=server_check_normal_user_password(current_user1);
			write(nsd,&result,sizeof(result));
		}
		else if(account_type==2)
		{
			joint_user current_user2;
			accType=2;
			msgLength=read(nsd,&current_user2,sizeof(joint_user));
			current_userID=current_user2.userID;
			printf("Username : %d\n",current_user2.userID);
			printf("Password : %s\n",current_user2.password);
			result=server_check_joint_user_password(current_user2);
			write(nsd,&result,sizeof(result));
		}
		else if(account_type==3)
		{
			admin_user current_user3;
			accType=3;
			msgLength=read(nsd,&current_user3,sizeof(admin_user));
			current_userID=current_user3.userID;
			printf("Username : %d\n",current_user3.userID);
			printf("Password : %s\n",current_user3.password);
			result=server_check_admin_user_password(current_user3);
			write(nsd,&result,sizeof(result));
		}
		else
		{
			result=false;
			write(nsd,&result,sizeof(result));
		}
		if(result)	break;		
	}

	while(1)
	{
		read(nsd,&select,sizeof(int));
		if(account_type==1 || account_type==2)
		{
			if(select==1)
			{
				float amt;
				read(nsd,&amt,sizeof(float));
				result=server_deposit_money(accType,current_userID,amt);
				write(nsd,&result,sizeof(result));
			}
			else if(select==2)
			{
				float amt;
				read(nsd,&amt,sizeof(float));
				result=server_withdraw_money(accType,current_userID,amt);
				write(nsd,&result,sizeof(result));
			}
			else if(select==3)
			{
				float amt;
				amt=server_get_user_balance(accType,current_userID);
				write(nsd,&amt,sizeof(float));
			}
			else if(select==4)
			{
				char pwd[10];
				read(nsd,pwd,sizeof(pwd));
				result=server_change_user_password(accType,current_userID,pwd);
				write(nsd,&result,sizeof(result));
			}
			else if(select==5)
			{
				if(account_type==1)
				{
					server_get_transaction_details(nsd,account_type,current_userID);
				}
				else if(account_type==2)
				{
					server_get_transaction_details(nsd,account_type,current_userID);
				}
			}
			else if(select==6)
			{
				break;
			}
		}
		else if(account_type==3)
		{
			read(nsd,&type,sizeof(int));
			if(select==1)
			{
				if(type==1)
				{
					normal_user newUser1;
					read(nsd,&newUser1,sizeof(normal_user));
					result=server_add_normal_user(newUser1);
					write(nsd,&result,sizeof(result));
				}
				else if(type==2)
				{
					joint_user newUser2;
					read(nsd,&newUser2,sizeof(joint_user));
					result=server_add_joint_user(newUser2);
					write(nsd,&result,sizeof(result));
				}
			}
			else if(select==2)
			{
				if(type==1)
				{
					int delUserID1;
					read(nsd,&delUserID1,sizeof(int));
					result=server_delete_normal_user(delUserID1);
					write(nsd,&result,sizeof(result));
				}
				else if(type==2)
				{
					int delUserID2;
					read(nsd,&delUserID2,sizeof(int));
					result=server_delete_joint_user(delUserID2);
					write(nsd,&result,sizeof(result));
				}
			}
			else if(select==3)
			{
				if(type==1)
				{
					normal_user modUser1;
					read(nsd,&modUser1,sizeof(normal_user));
					result=server_modify_normal_user(modUser1);
					write(nsd,&result,sizeof(result));
				}
				else if(type==2)
				{
					joint_user modUser2;
					read(nsd,&modUser2,sizeof(joint_user));
					result=server_modify_joint_user(modUser2);
					write(nsd,&result,sizeof(result));
				}
			}
			else if(select==4)
			{
				if(type==1)
				{
					normal_user searchUser1;
					int userID1;
					read(nsd,&userID1,sizeof(int));
					searchUser1=server_get_normal_user(userID1);
					write(nsd,&searchUser1,sizeof(normal_user));
				}
				else if(type==2)
				{
					joint_user searchUser2;
					int userID2;
					read(nsd,&userID2,sizeof(int));
					searchUser2=server_get_joint_user(userID2);
					write(nsd,&searchUser2,sizeof(joint_user));
				}
			}
			else if(select==5)
			{
				break;
			}
		}
	}
	close(nsd);
	write(1,"Client session is Endend \n\n",sizeof("Client session is Endend \n\n"));
	return;
}

void *server_connection_handler(void *nsd)
{
	int nsfd = *(int*)nsd;
	server_task_handler(nsfd);
}


int main()
{
	struct sockaddr_in server,client;
	int sd,nsd,clientLen;
	pthread_t threads;
	bool result;
	sd=socket(AF_INET,SOCK_STREAM,0);

	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(5555);

	bind(sd,(struct sockaddr *)&server,sizeof(server));
	listen(sd,5);
	
	write(1,"Serve is Waiting for the Client \n",sizeof("Serve is Waiting for the Client \n"));
	while(1)
	{
		clientLen=sizeof(client);
		nsd=accept(sd,(struct sockaddr *)&client,&clientLen);

		write(1,"Client is connected to the Server. \n",sizeof("Client is connected to the Server. \n"));
		if(pthread_create(&threads,NULL,server_connection_handler,(void*) &nsd)<0)
		{
			perror("could not create thread");
			return 1;
		}
	}
	pthread_exit(NULL);
	close(sd);
	return 0;
}