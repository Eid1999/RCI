
#include "Anel.h"

int mensagem_tcp(char *opt,no dest,no envio,int nbits,int k, int n_find, int fd)
{
        int n;
       ssize_t nwritten;
       char ptr[nbits],*aux;
       struct sigaction act;
       ssize_t nleft;
	
	
	memset(&act,0,sizeof act);
	act.sa_handler=SIG_IGN;
	if(sigaction(SIGPIPE,&act,NULL)==-1)/*error*/return -1;

       
       struct addrinfo hints,*res;
       if(fd==-1)//VE SE SOCKET JA EXISTE
       {
       	//CRIA SOCKET
       	fd=socket(AF_INET,SOCK_STREAM,0);//TCP socket
       	if(fd==-1)exit(21);/*error*/
        	memset(&hints,0,sizeof hints);
		hints.ai_family=AF_INET;//IPv4
		hints.ai_socktype=SOCK_STREAM;//TCP socket

		n=getaddrinfo(dest.ip,dest.porto,&hints,&res);
		if(n!=0)/*error*/return -1;
		n=connect(fd,res->ai_addr,res->ai_addrlen);
		if(n==-1)/*error*/return -1;
		freeaddrinfo(res);
       }

		//CRIA MENSAGEM
		if(k==-1)snprintf(ptr,nbits,"%s %d %s %s\n",opt,envio.chave,envio.ip,envio.porto);
		else snprintf(ptr,nbits,"%s %d %d %d %s %s\n",opt,k,n_find,envio.chave,envio.ip,envio.porto);

		//ENVIA MENSAGEM
		memset(&act,0,sizeof act);
		act.sa_handler=SIG_IGN;
		if(sigaction(SIGPIPE,&act,NULL)==-1)/*error*/return -1;
		
		aux=ptr;
		nleft=nbits;
		while(nleft>0){nwritten=write(fd,aux,nbits);
			if(nwritten<=0)/*error*/return -1;
			nleft-=nwritten;
			aux+=nwritten;
		}
		


       return fd;
}
   

