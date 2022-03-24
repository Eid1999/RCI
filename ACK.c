
#include "Anel.h"

char *ACK(int fdTCP, int fdUDP)//TROCAR PARA MENSAGENS
{
	socklen_t addrlen_udp,addrlen_tcp;
	ssize_t nread;
	char *buffer;
	int newfd;       
	ssize_t j;
	int maxfdp1;
	fd_set rset;
	int nready;
	struct timeval timer;
	struct sockaddr addr_udp, addr_tcp;
	buffer= (char*) malloc(128);
	maxfdp1 = max(fdUDP, fdTCP)+1 ;
	
	for (;;)
	 {
	 	
		FD_ZERO(&rset);// LIMPA
		// PROCURA DE SINAL TCP, UDP E DO USUARIO
		if(fdTCP!=0)FD_SET(fdTCP, &rset);
		if(fdUDP!=0)FD_SET(fdUDP, &rset);
		 timer.tv_sec = 5;
    		timer.tv_usec = 0;
    		
		nready = select(maxfdp1, &rset, NULL, NULL,&timer);
		if(nready<=0){buffer="ERRO";return buffer;};

		 //SE TIVER SINAL TCP, ACEITA
		if (fdTCP!=0 && FD_ISSET(fdTCP, &rset)) 
		{
			addrlen_tcp=sizeof(addr_tcp);
/*			if((newfd=accept(fdTCP,&addr_tcp,&addrlen_tcp))==-1)*/
/*			/*error**/
			j=read(fdTCP,buffer,128);
			if(j==-1)/*error*/exit(2);
			if (strncmp("ACK",buffer,3)==0)return buffer;
			
		}	
		//  SE TIVER SINAL UDP, ACEITA
		if (fdUDP!=0 && FD_ISSET(fdUDP, &rset)) 
		{
			addrlen_udp=sizeof(addr_udp);
			nread=recvfrom(fdUDP,buffer,128,0, &addr_udp,&addrlen_udp);
			if(nread==-1)/*error*/exit(4);
			printf("%s",buffer);
			close(nread);
			if (strncmp("ACK",buffer,3)==0)return buffer;
		}
		
	}
}   

