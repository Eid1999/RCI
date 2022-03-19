#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "newAnel.h"
int connect(int sockfd,const struct sockaddr *serv_addr,
socklen_t addrlen);
int main (int argc,char *argv[])
{
	char opt[20];
	char a[20];
	do{
	printf("new \nbentry \npentry \nchord \nshow \nfind \nleave \nexit \nChoose option:");
	scanf(" %19s", opt);
		if (strcmp(opt,"new")==0){
			strcpy(a,newAnel("va", "se", "fuder" ));
			printf("%s",a);
			}
		else if(strcmp(opt,"bentry")==0) {
			exit(3);
		}
	 }while(strcmp(opt,"new")==0);
	return 0;
}
