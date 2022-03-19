#include "newAnel.h"
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
#include <arpa/inet.h>
void newAnel(char *chave, char *porto, char *IP ){	
	int fd;
	
	fd=socket(AF_INET,SOCK_STREAM,0);//TCP socket
	if(fd==-1)exit(1);//error

}
