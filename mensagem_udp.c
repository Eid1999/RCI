
#include "Anel.h"


char *mensagem_udp(char *opt, no dest, no envio,int k, int n_find)
{
	struct addrinfo hints,*res;
	int fd,errcode, j=0;
	ssize_t n;
	char ptr[50];
	static char buffer [50];
	struct sockaddr addr;
	socklen_t addrlen;
	
	//CRIA SOCKET DO CLIENTE
	fd=socket(AF_INET,SOCK_DGRAM,0);//UDP socket
	if(fd==-1)/*error*/exit(31);
	memset(&hints,0,sizeof hints);
	hints.ai_family=AF_INET;//IPv4
	hints.ai_socktype=SOCK_DGRAM;//UDP socket
	errcode=getaddrinfo(dest.ip,dest.porto,&hints,&res);
	if(errcode!=0)/*error*/return "ERRO";
	
	
	//CRIA STRING DE ENVIO
	if(n_find!=-1)sprintf(ptr,"%s %d %d %d %s %s\n",opt,k,n_find,envio.chave,envio.ip,envio.porto);//FND OU RSP
	else sprintf(ptr,"%s %d\n",opt,envio.chave);//EFND
	NOACK:
	//ENVIA STRING
	n=sendto(fd,ptr,strlen(ptr)+1,0,res->ai_addr,res->ai_addrlen);
	if(n==-1)/*error*/return "ERRO";
	
       strcpy(buffer,ACK(0,fd));//ESPERA ACK
       j++;
       if(j==5){return "ERRO";}
       if(strncmp(buffer,"ACK",3)!=0){goto NOACK;}//SE RECEBER ACK CONTINUA, SE NÃO ENVIA A MENSAGEM DENOVO
	
	//PROCESSO DE RECEBIMENTO DO ENTRY
	if(strncmp(opt,"EFND",4)==0){
		addrlen=sizeof(addr);
		n=recvfrom(fd,buffer,30,0,&addr,&addrlen);
		if(n==-1)/*error*/exit(1);
		sendto(fd,"ACK",4,0,&addr,addrlen);
		
	}
	freeaddrinfo(res);
	close(fd);
	return buffer;
	
}
