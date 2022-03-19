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
void newAnel(char* chave,char* porto){	
	struct addrinfo hints,*res;

	int fd,newfd,errcode;
	ssize_t n,nw;
	struct sockaddr addr; 	socklen_t addrlen;
	char *ptr,buffer[128];
	
	fd=socket(AF_INET,SOCK_STREAM,0);//TCP socket
	if(fd==-1)exit(1);//error
	
	memset(&hints,0,sizeof hints);
	hints.ai_family=AF_INET;//IPv4
	hints.ai_socktype=SOCK_STREAM;//TCP socket
	hints.ai_flags=AI_PASSIVE;
	if((errcode=getaddrinfo(NULL,porto,&hints,&res))!=0)/*error*/exit(1);
	
	
	
	
	
	
	
	if(bind(fd,res->ai_addr,res->ai_addrlen)==-1)/*error*/exit(1);
	if(listen(fd,5)==-1)/*error*/exit(1);
	
	while(1)
	{
		addrlen=sizeof(addr);
		if((newfd=accept(fd,&addr,&addrlen))==-1)/*error*/exit(1);
		while((n=read(newfd,buffer,128))!=0){
			if(n==-1)/*error*/exit(1);
			ptr=&buffer[0];
		while(n>0){if((nw=write(newfd,ptr,n))<=0)/*error*/exit(1);
			n-=nw; ptr+=nw;}
		}
	close(newfd);
	}
	//freeaddrinfo(res);close(fd);exit(0);
	return;

}
