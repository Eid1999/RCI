
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
#include <arpa/inet.h>
void newAnel(char* chave,char* porto){	
	struct addrinfo hints,*res;

	int tcp,newtcp,errcode,udp;
	ssize_t n,nw, nread;
	struct sockaddr addr; 	socklen_t addrlen;
	char *ptr,buffer[128];
	
	//TCP socket
	tcp=socket(AF_INET,SOCK_STREAM,0);
	if(tcp==-1)exit(1);//error
	
	memset(&hints,0,sizeof hints);
	hints.ai_family=AF_INET;//IPv4
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_flags=AI_PASSIVE;
	if((errcode=getaddrinfo(NULL,porto,&hints,&res))!=0)/*error*/exit(1);
	
	if(bind(tcp,res->ai_addr,res->ai_addrlen)==-1)/*error*/exit(1);
	if(listen(tcp,5)==-1)/*error*/exit(1);
	
	freeaddrinfo(res);
	//UDP socket
	if((udp=socket(AF_INET,SOCK_DGRAM,0))==-1)exit(1);//error
	

       hints.ai_socktype=SOCK_DGRAM;//UDP socket
 
       if((errcode=getaddrinfo(NULL,porto,&hints,&res))!=0)/*error*/exit(1);
       
       if(bind(udp,res->ai_addr,res->ai_addrlen)==-1)/*error*/exit(1);
  
       freeaddrinfo(res);

	
	while(1)
	{
		addrlen=sizeof(addr);
		if((newtcp=accept(tcp,&addr,&addrlen))==-1)/*error*/exit(1);
		while((n=read(newtcp,buffer,128))!=0){
			if(n==-1)/*error*/exit(1);
			ptr=&buffer[0];
		while(n>0){if((nw=write(newtcp,ptr,n))<=0)/*error*/exit(1);
			n-=nw; ptr+=nw;}
		}
		nread=recvfrom(udp,buffer,128,0, &addr,&addrlen);
              if(nread==-1)/*error*/exit(1);
              n=sendto(udp,buffer,nread,0,&addr,addrlen);
              if(n==-1)/*error*/exit(1);

	       close(newtcp);
	}
	//freeaddrinfo(res);close(fd);exit(0);
	return;

}
