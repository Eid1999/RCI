



#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <arpa/inet.h>
#include "Anel.h"
#define STDIN 0
#define MAXLINE 1024

int max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}
int main(int argc,char* argv[])
{
       struct sigaction act;
       struct addrinfo hints,*res;
	struct addrinfo hints_udp,*res_udp;
       int fdUDP,errcode,nready;
       fd_set rset;
       struct sockaddr addr_udp, addr_tcp;
       socklen_t addrlen_udp,addrlen_tcp;
       ssize_t n,nread;
       char buffer[128];
       char *ptr, str[50];
        int fdTCP,newfd;       
       ssize_t j,nw;
       int maxfdp1;
       anel i;
       
       i.next.ip=NULL; 
       i.prec.ip=NULL;
   	
      
    	sscanf(argv[1], "%d", &i.eu.chave);
    	i.eu.ip=argv[2];
       i.eu.porto=argv[3];

       memset(&act,0,sizeof act);
       act.sa_handler=SIG_IGN;
       if(sigaction(SIGCHLD,&act,NULL)==-1)/*error*/exit(10);
    
 
    /* create listening TCP socket */
       if((fdTCP=socket(AF_INET,SOCK_STREAM,0))==-1)exit(11);//error
       
       memset(&hints,0,sizeof hints);
       
       hints.ai_family=AF_INET;//IPv4
       hints.ai_socktype=SOCK_STREAM;//TCP socket
       hints.ai_flags=AI_PASSIVE;
       
       
       if((errcode=getaddrinfo(NULL,i.eu.porto,&hints,&res))!=0)/*error*/exit(13);
       
       
       if(bind(fdTCP,res->ai_addr,res->ai_addrlen)==-1)/*error*/exit(14);
       if(listen(fdTCP,5)==-1)/*error*/exit(15);

 
    /* create UDP socket */
       if((fdUDP=socket(AF_INET,SOCK_DGRAM,0))==-1)exit(16);//error
       memset(&hints_udp,0,sizeof hints_udp);
       hints_udp.ai_family=AF_INET;//IPv4z
       hints_udp.ai_socktype=SOCK_DGRAM;//UDP socket
       hints_udp.ai_flags=AI_PASSIVE;
       if((errcode=getaddrinfo(NULL,i.eu.porto,&hints_udp,&res_udp))!=0)/*error*/exit(17);
       if(bind(fdUDP,res_udp->ai_addr,res_udp->ai_addrlen)==-1)/*error*/exit(18);
 
    
       freeaddrinfo(res);
           // get maxfd
       maxfdp1 = max(fdUDP, fdTCP) ;
       maxfdp1=max(STDIN,maxfdp1)+1;
       
        printf("Aperte enter para acessar a interface do utilizador:\n");
        
        
    
       for (;;) {FD_ZERO(&rset);// clear the descriptor set
 
               // set listenfd and udpfd in readset
               FD_SET(fdTCP, &rset);
               FD_SET(fdUDP, &rset);
               FD_SET(STDIN, &rset);
        
               // select the ready descriptor
               nready = select(maxfdp1, &rset, NULL, NULL, NULL);
              if(nready<=0)/*error*/exit(1);
        
               // if tcp socket is readable then handle
               // it by accepting the connection
                if (FD_ISSET(STDIN, &rset)){
                       fgets(str, 50, stdin);
                       i=interface(i);
                       printf("\nAperte enter para acessar a interface do utilizador:\n");
                }
               if (FD_ISSET(fdTCP, &rset)) {
                     addrlen_tcp=sizeof(addr_tcp);
                     if((newfd=accept(fdTCP,&addr_tcp,&addrlen_tcp))==-1)/*error*/exit(0);
                     j=read(newfd,buffer,128);
                     if(j==-1)/*error*/exit(2);
                     printf("%s",buffer);
                     close(newfd);
               }
               // if udp socket is readable receive the message.
               if (FD_ISSET(fdUDP, &rset)) {
                     addrlen_udp=sizeof(addr_udp);
                     nread=recvfrom(fdUDP,buffer,128,0, &addr_udp,&addrlen_udp);
                     if(nread==-1)/*error*/exit(4);
                     n=sendto(fdUDP,buffer,nread,0,&addr_udp,addrlen_udp);
                     if(n==-1)/*error*/exit(5);
               }
    }
}   
















