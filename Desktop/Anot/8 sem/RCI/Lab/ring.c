#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
int connect(int sockfd,const struct sockaddr *serv_addr,
socklen_t addrlen);
int main (int argc,char *argv[])
{
	char opt[20];
	do{
	printf("Choose option: new; 	bentry;  pentry;  chord; show; find; leave; exit ");
	scanf(" %s", opt);
	printf("%s",opt);
		if (strcmp(opt,"new")==0){
			exit(1);
			}
		else if(strcmp(opt,"bentry")==0) {
			exit(3);
		}
	 }while(strcmp(opt,"new")==0);
	return 0;
}
