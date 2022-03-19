
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
void newAnel(int chave,char* porto){	
	struct addrinfo hints_udp,*res_udp;
       int udp,errcode;
       struct sockaddr addr_udp, addr_tcp;
       socklen_t addrlen_udp,addrlen_tcp;
       ssize_t n,nread;
       char buffer[128];
       
       
       if((udp=socket(AF_INET,SOCK_DGRAM,0))==-1)exit(1);//error
       memset(&hints_udp,0,sizeof hints_udp);
       hints_udp.ai_family=AF_INET;//IPv4z
       hints_udp.ai_socktype=SOCK_DGRAM;//UDP socket
       hints_udp.ai_flags=AI_PASSIVE;
       if((errcode=getaddrinfo(NULL,porto,&hints_udp,&res_udp))!=0)/*error*/exit(1);
       if(bind(udp,res_udp->ai_addr,res_udp->ai_addrlen)==-1)/*error*/exit(1);
       
       struct addrinfo hints,*res;
       int fd,newfd;       
       ssize_t i,nw;
       char *ptr;
       
       if((fd=socket(AF_INET,SOCK_STREAM,0))==-1)exit(1);//error
       
       memset(&hints,0,sizeof hints);
       
       hints.ai_family=AF_INET;//IPv4
       hints.ai_socktype=SOCK_STREAM;//TCP socket
       hints.ai_flags=AI_PASSIVE;
       
       
       if((errcode=getaddrinfo(NULL,porto,&hints,&res))!=0)/*error*/exit(1);
       
       
       if(bind(fd,res->ai_addr,res->ai_addrlen)==-1)/*error*/exit(1);
       if(listen(fd,5)==-1)/*error*/exit(1);
       

       
       while(1)
       {      
              addrlen_udp=sizeof(addr_udp);
              nread=recvfrom(udp,buffer,128,0, &addr_udp,&addrlen_udp);
              if(nread==-1)/*error*/exit(1);
              n=sendto(udp,buffer,nread,0,&addr_udp,addrlen_udp);
              if(n==-1)/*error*/exit(1);
              
              
                     addrlen_tcp=sizeof(addr_tcp);
                     if((newfd=accept(fd,&addr_tcp,&addrlen_tcp))==-1)
                     /*error*/exit(1);
                      while((i=read(newfd,buffer,128))!=0){if(i==-1)/*error*/exit(1);
                            ptr=&buffer[0];
                            while(i>0){if((nw=write(newfd,ptr,i))<=0)/*error*/exit(1);
                                   i-=nw; ptr+=nw;}
                     }
                     close(newfd);
              
           
             
              
              
              
              }
              
              
              
              
              
              

}
