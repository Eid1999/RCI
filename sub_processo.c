#include "Anel.h"

anel sub_processo(anel i, char buffer[])
{
	char *c;
	int j=0,k=0,n_find;
	char *opt;
	char ptr[50];
	no p;
	char *auxUDP;
	int auxTCP;
	auxUDP="EMPTY";
	auxTCP=0;
	
	p.porto= (char*) malloc(50);
	p.ip= (char*) malloc(50);
	int n;

	//SEPARA A STRING RECEBIDAS
	c = strtok(buffer, " ");
	while (c != NULL)
	{
		c[strcspn(c, "\n")] = 0;
		switch(j) {

		case 0 :
		opt=c;
		break; 
		case 1  :
		sscanf(c, "%d", &p.chave);
		break; 
		case 2  :
		p.ip=c;
		break; 
		case 3  :
		p.porto=c;
		break;
		//VARIAVEIS DO FIND
		case 4:
		k=p.chave;
		sscanf(p.ip, "%d", &n_find);
		sscanf(p.porto,"%d",&p.chave);
		p.ip=c;
		break;
		case 5:
		p.porto=c;
		break;                        		
		}

		c = strtok (NULL, " ");
		j++;
	}
	
	
	//PROCESSO SELF, USADO NO LEAVE E PENTRY
	if (strcmp(opt,"SELF")==0)
	{
		if(j!=4){return i;}//ERRO NO COMANDO
		if(i.prec.ip==NULL)// PENTRY NO ANEL UNITARIO
		{
			//ENVIA MENSAGEM E SALVA SOCKET DO PREDECESSOR
			opt="SELF";
			i.prec.fd=mensagem_tcp(opt,p,i.eu,-1,0,-1);
			if(i.prec.fd==-1){close(i.AUX);return i;}//ERRO NA COMUNICAÇÃO
			//ALOCA MEMORIA DOS COMPONENTES DO ANEL
			i.prec.porto= (char*) malloc(50);
			i.prec.ip= (char*) malloc(50);
			i.next.porto= (char*) malloc(50);
			i.next.ip= (char*) malloc(50);
			
			//SALVA INFORMAÇÃO RECEBIDA
			memcpy(i.prec.porto,p.porto,50);
			memcpy(i.prec.ip,p.ip,50);
			i.prec.chave=p.chave;
			i.next.chave=p.chave;
			i.next.fd=i.AUX;
			memcpy(i.next.porto,p.porto,50);
			memcpy(i.next.ip,i.prec.ip,50);
			
			
			
			
			
		}
		
		
		else if(i.next.ip==NULL )// ULTIMA ETAPA DO PENTRY, LIGAÇÃO AO SUCESSOR
		{
			//ALOCA MEMORIA DOS COMPONENTES DO ANEL
			i.next.porto= (char*) malloc(50);
			i.next.ip= (char*) malloc(50);
			
			//SALVA INFORMAÇÃO RECEBIDA
			memcpy(i.next.ip,p.ip,50);
			memcpy(i.next.porto,p.porto,50);
			i.next.chave=p.chave;
			//SALVA SOCKET DO NOVO SUCESSOR
			i.next.fd=i.AUX;
			
		}
		
		else//SEGUNDA ETAPA DO PENTRY E ULTIMA DO LEAVE 
		{	
			//ENVIA MENSAGEM
			
			opt="PRED";
			if(d(i.eu.chave,i.next.chave)>d(i.eu.chave,p.chave))auxTCP=mensagem_tcp(opt,i.next,p,-1,0,i.next.fd);//DIFERENCIA ENTRE O PROCESSO DO PENTRY E LEAVE
			if(auxTCP==-1){close(i.AUX);return i;}//ERRO NA COMUNICAÇÃO
			//SALVA INFORMAÇÃO RECEBIDA
			memcpy(i.next.ip,p.ip,50);
			memcpy(i.next.porto,p.porto,50);
			i.next.chave=p.chave;
			//FECHA SOCKET DO ANTIGO SUCESSOR
			close(i.next.fd);
			i.next.fd=-1;
			//SALVA SOCKET DO NOVO SUCESSOR
			i.next.fd=i.AUX;
			
			return i;
		} 


	}
	
	//PROCESSO PRED, USADO NO LEAVE E PENTRY
	else if (strcmp(opt,"PRED")==0){
		if(j!=4){return i;}//ERRO NO COMANDO
		opt="SELF";		
		if( p.chave!=i.eu.chave)//SEGUNDA ETAPA DO LEAVE E PENULTIMA ETAPA DO PENTRY
		{
			//SALVA INFORMAÇAO RECEBIDA
			memcpy(i.prec.porto,p.porto,50);
			memcpy(i.prec.ip,p.ip,50);
			i.prec.chave=p.chave;
			
			//FECHA SOCKET DO ANTIGO PREDECESSOR
			close(i.prec.fd);
			i.prec.fd=-1;
			//ENVIA MENSAGEM AO NOVO PREDECESSOR E SALVA O SOCKET CRIADO
			i.prec.fd=mensagem_tcp(opt,i.prec,i.eu,-1,0,-1);
			if(i.prec.fd==-1){printf("\nAnel quebrado, reinicializando programa\n");i=ERRO(i);}//ERRO DE COMUNICAÇÃO DE TCP
		}
		else// LEAVE COM UM ANEL COM DOIS NÓS
		{
			//APAGA INFORMAÇOES
			free(i.prec.porto);i.prec.porto=NULL;
			free(i.prec.ip);i.prec.ip=NULL;
			free(i.next.porto);i.next.porto=NULL;
			free(i.next.ip);i.next.ip=NULL;
			//FECHA SOCKETS
			close(i.next.fd);
			i.next.fd=-1;
			close(i.prec.fd);
			i.prec.fd=-1;
			
		}  
	}

	//PROCESSO FND, USADO NO FIND E BENTRY
	else if (strcmp(opt,"FND")==0)
	{
		find://PARTE DO COMANDO BENTRY
		if(j!=6){return i;}//ERRO NO COMANDO
		
		if(k==i.eu.chave|| (i.next.ip==NULL||(d(i.eu.chave,k)<d(i.next.chave,k)&&(i.atalho.ip==NULL||d(i.eu.chave,k)<d(i.atalho.chave,k)))))//VERIFICA SE É O NÓ PROCURADO OU PERTENCE
		{
			opt="RSP";//INICIA PROCESSO DE RESPOSTA
			if(p.chave==i.eu.chave){goto RSP;}//BENTRY, SE O NO QUE FOI CHAMADO FOR O MAIS PROXIMO
			
			if(i.atalho.ip!=NULL && d(i.atalho.chave,p.chave)<d(i.next.chave,p.chave)){auxUDP=mensagem_udp(opt,i.atalho,i.eu,p.chave,n_find,i.fdUDP);}//PROCURA O MENOR CAMINHO PARA A PROCURA, ATALHO OU SUCESSOR
			else {auxTCP=mensagem_tcp(opt,i.next,i.eu,p.chave,n_find,i.next.fd);}
			
		}

		else
		{
			opt="FND";//CONTINUA O PROCESSO DE PROCURA
			if(i.atalho.ip!=NULL && d(i.atalho.chave,k)<d(i.next.chave,k)){auxUDP=mensagem_udp(opt,i.atalho,p,k,n_find,i.fdUDP);}//PROCURA O MENOR CAMINHO, ENTRE ATALHO OU SUCESSOR
			else {auxTCP=mensagem_tcp(opt,i.next,p,k,n_find,i.next.fd);}
		}
		
		if(strcmp(auxUDP,"ERRO")==0)//ERRO DE COMUNICAÇÃO POR UDP
		{
			printf("\nCorda quebrada, continuando pesquisa pelo sucessor\n");
			i=interface(i,"d");	
			if (strcmp(opt,"FND")==0)auxTCP=mensagem_tcp(opt,i.next,p,k,n_find,i.next.fd);
			else auxTCP=mensagem_tcp(opt,i.next,i.eu,p.chave,n_find,i.next.fd);
		}
		if(auxTCP==-1)//ERRO DE COMUNICAÇÃO POR TCP
		{
			printf("\nAnel quebrado, reinicializando programa\n");
			i=ERRO(i);
		}	
	}
	
	
	
	
	
	
	
	//PROCESSO RSP, USADO NO FIND E BENTRY, 
	else if (strcmp(opt,"RSP")==0)
	{
		opt="RSP";
		if(j!=6){return i;}//ERRO NO COMANDO
		if(k==i.eu.chave)//VERIFICA SE O NÓ É O PROCURADO
		{
			RSP://PARTE DO COMANDO FND(INICIALIZADO PELO BENTRY)
			
			if(i.k[i.n_find]==-1){//VERIFICA SE ESTA NO COMANDO FIND OU BENTRY
			
				do{//PROCESSO DO ACK
				
					//MENSAGEM DE RESPOSTA 
					snprintf(ptr,30,"EPRED %d %s %s\n",p.chave,p.ip,p.porto);
					n=sendto(i.fdUDP,ptr,32,0,&i.addr,i.addrlen);
					if(n==-1)/*error*/return i;
					
					//ESPERA O ACK
					 strcpy(buffer,ACK(0,i.fdUDP));
					 
				}while(strncmp("ACK",buffer,3)!=0);
			}
			else printf("\nChave %d: Nó %d(%s : %s) \n \nInterface do usuario, escreva um comando:(-h para ajuda):\n",i.k[n_find],p.chave, p.ip,p.porto);//PRINTF DO FIND
			fflush(stdout);
			if(i.n_find<99)i.n_find++;//MUDA O NUMERO DE CHAMADA
			else {i.n_find=0;memset(i.k, -1, sizeof(i.k));}//REINICIALIZA FLAG
			
			
			
		}
		
		else//PROCURA O NO QUE INICIALIZOU O FIND
		{
			
			if(i.atalho.ip!=NULL && d(i.atalho.chave,k)<d(i.next.chave,k)){auxUDP=mensagem_udp(opt,i.atalho,p,k,i.n_find,i.fdUDP);}//PROCURA O MENOR CAMINHO, ENTRE ATALHO OU SUCESSOR
			else {auxTCP=mensagem_tcp(opt,i.next,p,k,n_find,i.next.fd);}
			
		}
		
		if(strcmp(auxUDP,"ERRO")==0)//ERRO DE COMUNICAÇÃO DE UDP
		{
			printf("\nCorda quebrada, continuando pesquisa pelo sucessor\n");
			i=interface(i,"d");	//APAGA CORDA
			auxTCP=mensagem_tcp(opt,i.next,p,k,n_find,i.next.fd);//CONTINUA PESQUISA PELO SUCESSOR
		}
		if(auxTCP==-1)//ERRO DE COMUNICAÇÃO DE TCP
		{
			printf("\nAnel quebrado, reinicializando programa\n");
			i=ERRO(i);//PROCESSO DE QUEBRA
		}		
	}
	
	
	
	
	//PROCESSO EFND, USADO NO BENTRY 
	else if(strcmp(opt,"EFND")==0) {
		//SALVA INFORMAÇAO RECEBIDAS
		if(j!=2){return i;}//ERRO NO COMANDO
		k=p.chave;
		
		//PROCESSO DE PROCURA
		j=6;
		n_find=i.n_find;
		i.k[n_find]=-1;
		p=i.eu;
		goto find;
	}
	else if (strcmp(opt,"ERRO")==0){printf("\nAnel quebrado, reinicializando programa\n");i=ERRO(i);}//PROCESSO DE QUEBRA
	return i;
}
