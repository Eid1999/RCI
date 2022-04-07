



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
	int maxfdp1,maxfdp2;//
	char UDPaux[50];//AUXILIAR DE MENSAGEM UDP
	anel i;//ESTRUTUTA DO ANEL
	//AUXILIAR DE MENSAGEM TCP
	char *aux;
	
	
	aux=NULL;


	sscanf(argv[1], "%d", &i.eu.chave);
	i.eu.ip=argv[2];
	i.eu.porto=argv[3];

	printf("\nBem vindo ao ring\n");

	novo://PARTE DO COMANDO LEAVE
	
	//INICIALIÇÃO DE VARIAVEIS PARA CONTROLE(FLAGS)
	i.n_find=0;
	i.leave=0;
	i.next.ip=NULL; 
	i.prec.ip=NULL;
	i.atalho.ip=NULL;
	i.next.fd=-1;
	i.prec.fd=-1;
	i.fdTCP=-1;
	i.fdUDP=-1;
	i.k=-1;

	//INTERFACE
	do{
		printf("\nCrie ou conecte-se a um anel(-h para ajuda):\n");
		fflush(stdin);
		fgets(str, 50, stdin);
		i=interface(i,str);
	}while((i.prec.ip==NULL && i.fdTCP==-1));//SAI SE FORMAR UM NO(COMANDO N) OU ENTRAR EM UM ANEL(NEW, PENTRY OU BENTRY)
	
	
	
	//CRIA OS SOCKETS DEPOIS DE FAZER PARTE DE UM ANEL
	//TCP SOCKET
	if((i.fdTCP=socket(AF_INET,SOCK_STREAM,0))==-1)exit(11);//error

	memset(&hints,0,sizeof hints);

	hints.ai_family=AF_INET;//IPv4
	hints.ai_socktype=SOCK_STREAM;//TCP socket
	hints.ai_flags=AI_PASSIVE;


	if((errcode=getaddrinfo(NULL,i.eu.porto,&hints,&res))!=0)/*error*/exit(13);


	if(bind(i.fdTCP,res->ai_addr,res->ai_addrlen)==-1)/*error*/exit(14);
	if(listen(i.fdTCP,5)==-1)/*error*/exit(15);
	freeaddrinfo(res);


	//UDP SOCKETS
	if((i.fdUDP=socket(AF_INET,SOCK_DGRAM,0))==-1)exit(16);//error
	memset(&hints_udp,0,sizeof hints_udp);
	hints_udp.ai_family=AF_INET;//IPv4z
	hints_udp.ai_socktype=SOCK_DGRAM;//UDP socket
	hints_udp.ai_flags=AI_PASSIVE;
	if((errcode=getaddrinfo(NULL,i.eu.porto,&hints_udp,&res_udp))!=0)/*error*/exit(17);
	if(bind(i.fdUDP,res_udp->ai_addr,res_udp->ai_addrlen)==-1)/*error*/exit(18);//BUG NESSA LINHA PENTRY APOS LEAVE

	//CALCULA O MAIOR SOCKER
	freeaddrinfo(res_udp);
	maxfdp1 = max(i.fdUDP, i.fdTCP) ;
	maxfdp1 = max(i.prec.fd, maxfdp1) ;
	maxfdp1=max(STDIN,maxfdp1)+1;
	maxfdp2=maxfdp1;



	

	// PROCURA DE SINAL TCP, UDP E DO USUARIO
		
	printf("\nInterface do usuario, escreva um comando:(-h para ajuda):\n");
	for(;;)
	{
		if(i.leave==1){i.leave=0;goto novo;}//PARTE DO COMANDO LEAVE COMEÇA PROGRAMA DENOVO
		
		
		FD_ZERO(&rset);// LIMPA SELECT
		//INILICILIZA SELECT 
		
		FD_SET(i.fdTCP, &rset);
		if(i.prec.fd!=-1){FD_SET(i.prec.fd, &rset);maxfdp2 = max(i.prec.fd, maxfdp1)+1 ;}//SE TIVER PREDECESSOR PROCURA MENSAGEM DELE
		FD_SET(i.fdUDP, &rset);
		FD_SET(STDIN, &rset);
		
		nready = select(maxfdp2, &rset, NULL, NULL, NULL);//INICIA SELECT
		if(nready<=0)/*error*/exit(19);
		
		for (;;) {
			

			//INPUT DO USUARIO, ENTRA NO INTERFACE
			if (FD_ISSET(STDIN, &rset)){
				fgets(str, 50, stdin);
				i=interface(i,str);
				if(i.leave!=1) printf("\nInterface do usuario, escreva um comando:(-h para ajuda):\n");
				break;
			}
			 //SERVIDOR TCP
			if (FD_ISSET(i.fdTCP, &rset)) {
				addrlen_tcp=sizeof(addr_tcp);
				if((newfd=accept(i.fdTCP,&addr_tcp,&addrlen_tcp))==-1)/*error*/exit(20);//ACEITA E CRIA SOCKET(PENTRY/BENTRY)
				j=read(newfd,buffer,128);//LE MENSAGEM
				if(j==-1)/*error*/exit(21);
						
				if(strrchr(buffer,'\n')==NULL){//VE SE CHEGOU A MENSAGEM INTEIRA
					if(aux==NULL){
						aux= (char*) malloc(50);
						strncpy(aux,buffer,j);//COPIA A PRIMEIRA PARTE DA MENSAGEM
					}
					else strncat(aux,buffer,j);//COPIA AS OUTRA PARTE DA MENSAGEM
					break;
				}
				else if(aux!=NULL)
				{
					strncat(aux,buffer,j+1);
					strcpy(buffer,aux);//COPIA SEGUNDA PARTE DA MENSAGEM 				
					//LIBERTA OS AUXILIAR
					free(aux);
					aux=NULL;
				}
				//
				
				printf("%s\n",buffer);
				if(strncmp("SELF",buffer,4)==0){i.AUX=newfd;}//GRAVA FD DO CLIENTE
				i=sub_processo(i,buffer);//PROCESSOS INTERNOS DO ANEL(SELF, PRED..)
				break;
			}
			
			//SERVIDOR  UDP
			if (FD_ISSET(i.fdUDP, &rset)) {
				addrlen_udp=sizeof(addr_udp);
				nread=recvfrom(i.fdUDP,buffer,128,0, &addr_udp,&addrlen_udp);//RECEBE MENSAGEM
				if(nread==-1)/*error*/exit(30);
				sendto(i.fdUDP,"ACK",4,0,&addr_udp,addrlen_udp);//ENVIA ACK
				if(strncmp(UDPaux,buffer,nread)==0)break;//VE SE RECEBEU MENSAGEM REPETIDA(ACK NÃO CHEGOU)
				strncpy(UDPaux,buffer,nread+1);//SALVA MESAGEM PARA COMPARA PROXIMA VEZ
				if(strncmp("EFND",buffer,4)==0){i.addr=addr_udp;i.addrlen=addrlen_udp;}//SALVA INFORMACAO DO CLIENTE(BENTRY)
				printf("%s\n",buffer);
				i=sub_processo(i,buffer);//PROCESSOS INTERNOS DO ANEL(FND,RSP...)
				break;
				
			}
			//SERVIDOR TCP DO PREDECESSOR
			if (FD_ISSET(i.prec.fd, &rset)) {
				j=read(i.prec.fd,buffer,128);//LE MENSAGEM
				if(j==-1)/*error*/exit(21);
				printf("%s\n",buffer);
				i=sub_processo(i,buffer);//PROCESSOS INTERNOS DO ANEL(RSP,FND...)
				break;
			}
			
		}
	}
}   
















