
#include "Anel.h"

char *ACK(int fdTCP, int fdUDP)//TROCAR PARA MENSAGENS
{
	socklen_t addrlen_udp;
	ssize_t nread;
	static char buffer[50];   
	ssize_t j;
	int maxfdp1;
	fd_set rset;
	int nready;
	struct timeval timer;
	struct sockaddr addr_udp;
	maxfdp1 = max(fdUDP, fdTCP)+1 ;

	strcpy(buffer,"ERRO");
 	FD_ZERO(&rset);// LIMPA
	// PROCURA DE SINAL TCP, UDP E DO USUARIO
	if(fdTCP!=0)FD_SET(fdTCP, &rset);
	if(fdUDP!=0)FD_SET(fdUDP, &rset);
 	 timer.tv_sec = 10;
	timer.tv_usec = 0;
 	nready = select(maxfdp1, &rset, NULL, NULL,&timer);
	if(nready<=0){return buffer;}

	 //SE TIVER SINAL TCP, ACEITA
	if (fdTCP!=0 && FD_ISSET(fdTCP, &rset)) 
	{
		j=read(fdTCP,buffer,4);
		if(j==-1)/*error*/exit(2);
		if (strncmp("ACK",buffer,3)==0)return buffer;
		
	}	
	//  SE TIVER SINAL UDP, ACEITA
	if (fdUDP!=0 && FD_ISSET(fdUDP, &rset)) 
	{
		addrlen_udp=sizeof(addr_udp);
		nread=recvfrom(fdUDP,buffer,5,0, &addr_udp,&addrlen_udp);
		if(nread==-1)/*error*/exit(4);
		if (strncmp("ACK",buffer,3)==0)return buffer;
	}
	return buffer;
}   

