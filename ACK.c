
#include "Anel.h"

char *ACK(anel i)//TROCAR PARA MENSAGENS
{
	socklen_t addrlen_udp,addrlen_tcp;
	ssize_t nread;
	char *buffer;
	int newfd;       
	ssize_t j;
	int maxfdp1;
	fd_set rset;
	int nready;
	struct sockaddr addr_udp, addr_tcp;
	buffer= (char*) malloc(128);
	maxfdp1 = max(i.fdUDP, i.fdTCP)+1 ;
	for (;;) {FD_ZERO(&rset);// LIMPA

		// PROCURA DE SINAL TCP, UDP E DO USUARIO
		FD_SET(i.fdTCP, &rset);
		FD_SET(i.fdUDP, &rset);
	
		nready = select(maxfdp1, &rset, NULL, NULL, NULL);
		if(nready<=0)/*error*/exit(1);

		 //SE TIVER SINAL TCP, ACEITA
		if (FD_ISSET(i.fdTCP, &rset)) {
			addrlen_tcp=sizeof(addr_tcp);
			if((newfd=accept(i.fdTCP,&addr_tcp,&addrlen_tcp))==-1)/*error*/exit(0);
			j=read(newfd,buffer,128);
			if(j==-1)/*error*/exit(2);
			close(newfd);
			if (strncmp("ACK",buffer,3)==0)return buffer;
			
		}
		//  SE TIVER SINAL UDP, ACEITA
		if (FD_ISSET(i.fdUDP, &rset)) {
			addrlen_udp=sizeof(addr_udp);
			nread=recvfrom(i.fdUDP,buffer,128,0, &addr_udp,&addrlen_udp);
			if(nread==-1)/*error*/exit(4);
			printf("%s",buffer);
			close(nread);
			if (strncmp("ACK",buffer,3)==0)return buffer;
		}
		
	}
}   

