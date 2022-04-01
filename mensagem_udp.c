
#include "Anel.h"


void mensagem_udp(char *opt, no dest, no envio,int nbits,int k, int n_find)
{
	struct addrinfo hints,*res;
	int fd,errcode;
	ssize_t n;
	char ptr[nbits],*buffer;
	struct sockaddr addr;
	socklen_t addrlen;
	
	
	fd=socket(AF_INET,SOCK_DGRAM,0);//UDP socket
	if(fd==-1)/*error*/exit(31);
	memset(&hints,0,sizeof hints);
	hints.ai_family=AF_INET;//IPv4
	hints.ai_socktype=SOCK_DGRAM;//UDP socket
	errcode=getaddrinfo(dest.ip,dest.porto,&hints,&res);
	if(errcode!=0)/*error*/exit(1);
	
	if(n_find!=-1)snprintf(ptr,nbits,"%s %d %d %d %s %s\n",opt,k,n_find,envio.chave,envio.ip,envio.porto);
	else snprintf(ptr,nbits,"%s %d\n",opt,envio.chave);
	NOACK:
	if(nbits!=0)n=sendto(fd,ptr,nbits,0,res->ai_addr,res->ai_addrlen);
	if(n==-1)/*error*/exit(32);

       buffer=ACK(0,fd);
       if(strncmp(buffer,"ACK",4)!=0){free(buffer);goto NOACK;}
	printf("%s\n",buffer);
	//PROCESSO DE RECEBIMENTO DO PENTRY
	if(strncmp(opt,"EFND",4)==0){
		addrlen=sizeof(addr);
		n=recvfrom(fd,buffer,30,0,&addr,&addrlen);
		if(n==-1)/*error*/exit(1);
		printf("%s\n",buffer);
		sendto(fd,"ACK",4,0,&addr,addrlen);
	}
	freeaddrinfo(res);
	close(fd);
	return;
	
}
