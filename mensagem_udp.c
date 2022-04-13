
#include "Anel.h"


char *mensagem_udp(char *opt, no dest, no envio,int nbits,int k, int n_find)
{
	struct addrinfo hints,*res;
	int fd,errcode, j=0;
	ssize_t n;
	char ptr[nbits];
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
	if(n_find!=-1)snprintf(ptr,nbits,"%s %d %d %d %s %s\n",opt,k,n_find,envio.chave,envio.ip,envio.porto);
	else snprintf(ptr,nbits,"%s %d\n",opt,envio.chave);
	NOACK:
	//ENVIA STRING
	if(nbits!=0)n=sendto(fd,ptr,nbits,0,res->ai_addr,res->ai_addrlen);
	if(n==-1)/*error*/return "ERRO";
	
       strcpy(buffer,ACK(0,fd));//ESPERA ACK
       j++;
       if(j==5){return "ERRO";}
       if(strncmp(buffer,"ACK",3)!=0){goto NOACK;}//SE RECEBER ACK CONTINUA, SE NÃO ENVIA A MENSAGEM DENOVO
	printf("%s\n",buffer);//APAGAR DPS
	
	//PROCESSO DE RECEBIMENTO DO ENTRY
	if(strncmp(opt,"EFND",4)==0){
		addrlen=sizeof(addr);
		n=recvfrom(fd,buffer,30,0,&addr,&addrlen);
		if(n==-1)/*error*/exit(1);
		printf("%s\n",buffer);
		sendto(fd,"ACK\n",5,0,&addr,addrlen);
		
	}
	freeaddrinfo(res);
	close(fd);
	return buffer;
	
}
