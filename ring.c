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
	char *chave;;
    	char *ip;
   	char *porto;
   	 char opt[20];

    	chave= argv[1];
    	ip= argv[2];
    	porto= argv[3];
	do{
		printf("new \nbentry \npentry \nchord \nshow \nfind \nleave \nexit \nChoose option:");
		scanf(" %19s", opt);
			if (strcmp(opt,"new")==0){
				newAnel(chave,porto);
				}
			else if(strcmp(opt,"exi")==0) {
				exit(3);
		}
	 }while(strcmp(opt,"exit")!=0);
	return 0;
}
