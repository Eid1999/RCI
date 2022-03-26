



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
#define mod 15

int max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

//CALCULO DA DISTANCIA
int d(int d1,int d2){
       int c;
       c=d2-d1;
       while(c<0)c=c+mod;
       return c;
}

int main(int argc,char* argv[])
{
	struct addrinfo hints,*res;
	struct addrinfo hints_udp,*res_udp;
	int errcode,nready;
	fd_set rset;
	struct sockaddr addr_udp, addr_tcp;
	socklen_t addrlen_udp,addrlen_tcp;
	ssize_t nread;
	char buffer[128];
	char  str[50];
	int newfd;       
	ssize_t j;
	int maxfdp1;
	anel i;


	sscanf(argv[1], "%d", &i.eu.chave);
	i.eu.ip=argv[2];
	i.eu.porto=argv[3];


	novo:
	//INICIALIÇÃO DE VARIAVEIS PARA CONTROLE
	i.n_find=0;
	i.leave=0;
	i.next.ip=NULL; 
	i.prec.ip=NULL;
	i.atalho.ip=NULL;
	i.next.fd=-1;
	i.prec.fd=-1;
	i.fdTCP=-1;

	//COMANDO NEW
/*	printf("Crie um anel ou aperte enter para acender a interface do utilizador:\n");*/
/*	fgets(str, 50, stdin);*/
/*	fflush(stdout);*/
	i=interface(i);

	/* create listening TCP socket */
	if((i.fdTCP=socket(AF_INET,SOCK_STREAM,0))==-1)exit(11);//error

	memset(&hints,0,sizeof hints);

	hints.ai_family=AF_INET;//IPv4
	hints.ai_socktype=SOCK_STREAM;//TCP socket
	hints.ai_flags=AI_PASSIVE;


	if((errcode=getaddrinfo(NULL,i.eu.porto,&hints,&res))!=0)/*error*/exit(13);


	if(bind(i.fdTCP,res->ai_addr,res->ai_addrlen)==-1)/*error*/exit(14);
	if(listen(i.fdTCP,5)==-1)/*error*/exit(15);


	/* create UDP socket */
	if((i.fdUDP=socket(AF_INET,SOCK_DGRAM,0))==-1)exit(16);//error
	memset(&hints_udp,0,sizeof hints_udp);
	hints_udp.ai_family=AF_INET;//IPv4z
	hints_udp.ai_socktype=SOCK_DGRAM;//UDP socket
	hints_udp.ai_flags=AI_PASSIVE;
	if((errcode=getaddrinfo(NULL,i.eu.porto,&hints_udp,&res_udp))!=0)/*error*/exit(17);
	if(bind(i.fdUDP,res_udp->ai_addr,res_udp->ai_addrlen)==-1)/*error*/exit(18);


	freeaddrinfo(res);
	
	maxfdp1 = max(i.fdUDP, i.fdTCP) ;
	maxfdp1=max(STDIN,maxfdp1)+1;



	
	printf("\nAperte enter para acender a interface do utilizador:\n");
	for (;;) {FD_ZERO(&rset);// LIMPA

		// PROCURA DE SINAL TCP, UDP E DO USUARIO
		FD_SET(i.fdTCP, &rset);
		FD_SET(i.fdUDP, &rset);
		FD_SET(STDIN, &rset);

		nready = select(maxfdp1, &rset, NULL, NULL, NULL);
		if(nready<=0)/*error*/exit(19);

		// SE TIVER SINAL INPUT DO USUARIO ENTRA NO INTERFACE
		if (FD_ISSET(STDIN, &rset)){
			fgets(str, 50, stdin);
			i=interface(i);
			printf("\nAperte enter para acender a interface do utilizador:\n");
		}
		 //SE TIVER SINAL TCP, ACEITA
		if (FD_ISSET(i.fdTCP, &rset)) {
			addrlen_tcp=sizeof(addr_tcp);
			if((newfd=accept(i.fdTCP,&addr_tcp,&addrlen_tcp))==-1)/*error*/exit(20);
			j=read(newfd,buffer,128);
			if(j==-1)/*error*/exit(21);
			printf("%s",buffer);
			if(strncmp("FND",buffer,3)==0|| strncmp("RSP",buffer,3)==0){
			newfd=write(newfd,"ACK\n",5);}
			i=sub_processo(i,buffer);

		}
		//  SE TIVER SINAL UDP, ACEITA
		if (FD_ISSET(i.fdUDP, &rset)) {
			addrlen_udp=sizeof(addr_udp);
			nread=recvfrom(i.fdUDP,buffer,128,0, &addr_udp,&addrlen_udp);
			if(nread==-1)/*error*/exit(30);
			if(strncmp("FND",buffer,3)|| strncmp("RSP",buffer,3))sendto(i.fdUDP,"ACK",nread,0,&addr_udp,addrlen_udp);
			printf("%s",buffer);
			i=sub_processo(i,buffer);
		}
		//PARTE DO COMANDO LEAVE
		if(i.leave==1){close(i.fdUDP);close(i.fdTCP);i.leave=0;goto novo;}
	}
}   
















