
#include "Anel.h"

anel pentry(anel i)
{
        int fd,n;
       ssize_t nwritten;
       char ptr[100];
       struct addrinfo hints,*res;
       fd=socket(AF_INET,SOCK_STREAM,0);//TCP socket
       if(fd==-1)exit(1);//error   

       memset(&hints,0,sizeof hints);
       hints.ai_family=AF_INET;//IPv4
       hints.ai_socktype=SOCK_STREAM;//TCP socket
       
       n=getaddrinfo(i.prec.ip,i.prec.porto,&hints,&res);
       if(n!=0)/*error*/exit(1);
       if(n!=0)/*error*/exit(1);
       n=connect(fd,res->ai_addr,res->ai_addrlen);
       if(n==-1)/*error*/exit(1);
       
       snprintf(ptr,100,"SELF %d %s %s\n",i.eu.chave,i.eu.ip,i.eu.porto);
       
       
       nwritten=write(fd,ptr,sizeof(ptr));
       if(nwritten<=0)/*error*/exit(1);
              
          
       
       close(fd);
       return i ;
}
   

