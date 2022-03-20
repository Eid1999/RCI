#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "Anel.h"
int connect(int sockfd,const struct sockaddr *serv_addr,
socklen_t addrlen);





int main (int argc,char *argv[]){

	char *c;
    	char *ip;
   	char *porto;
   	 char opt[20];
   	 int chave;
   	 anel i;

    	c= argv[1];
    	sscanf(c, "%d", &chave);
    	ip= argv[2];
    	porto= argv[3];
    	
    	i.chave=chave;
    	i.ip=ip;
    	i.porto=porto;
    	
    	
	do{
		printf("new \nbentry \npentry \nchord \nshow \nfind \nleave \nexit \nChoose option:");
		scanf(" %19s", opt);
			if (strcmp(opt,"new")==0){
			        int chave=1;
				newAnel(i);
			}
			else if(strcmp(opt,"bentry")==0) {
				bentry(i);
		       }
		       else if(strcmp(opt,"pentry")==0) {
				pentry(i);
			}
	 }while(strcmp(opt,"exit")!=0);
	return 0;
}
