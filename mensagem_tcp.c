
#include "Anel.h"

int mensagem_tcp(char *opt,no dest,no envio,int nbits,int k, int n_find, int fd)
{
        int n;
       ssize_t nwritten;
       char ptr[nbits];
       
       
       struct addrinfo hints,*res;
       if(fd==-1)
       {
       	fd=socket(AF_INET,SOCK_STREAM,0);//TCP socket
       	if(fd==-1)exit(1);/*error*/
        	memset(&hints,0,sizeof hints);
		hints.ai_family=AF_INET;//IPv4
		hints.ai_socktype=SOCK_STREAM;//TCP socket

		n=getaddrinfo(dest.ip,dest.porto,&hints,&res);
		if(n!=0)/*error*/exit(1);
		n=connect(fd,res->ai_addr,res->ai_addrlen);
		if(n==-1)/*error*/exit(1);
       }
       if(nbits==24)snprintf(ptr,nbits,"%s %d %s %s\n",opt,envio.chave,envio.ip,envio.porto);
       if(nbits==34)snprintf(ptr,nbits,"%s %d %d %d %s %s\n",opt,k,n_find,envio.chave,envio.ip,envio.porto);
/*       NOACK:*/
       nwritten=write(fd,ptr,nbits);
       if(nwritten<=0)/*error*/exit(1);
              
/*          if(nbits==34)*/
/*          {*/
/*          buffer=ACK(fd,0);*/
/*          if(strncmp(buffer,"ACK",3)!=0){free(buffer);goto NOACK;}*/
/*          free(buffer);*/
/*          }*/

       return fd;
}
   

