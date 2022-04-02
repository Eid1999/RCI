#include "Anel.h"

anel sub_processo(anel i, char buffer[])
{
	char *c;
	int j=0,k=0,n_find;
	char *opt;
	char ptr[50];
	no p;
	p.porto= (char*) malloc(50);
	p.ip= (char*) malloc(50);
	int pbits2,pbits,fbits,fbits2,n;

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
	
	//CALCULA TAMANHO DA STRING QUE SERA ENVIADA	
	fbits=(strlen(opt)+strlen(i.eu.ip)+strlen(i.eu.porto)+16);
	fbits2=(strlen(opt)+strlen(p.ip)+strlen(p.porto)+16);
	pbits=(strlen(opt)+strlen(i.eu.ip)+strlen(i.eu.porto)+10);
	pbits2=(strlen(opt)+strlen(p.ip)+strlen(p.porto)+10);
	
	
	//PROCESSO SELF, USADO NO LEAVE E PENTRY
	if (strcmp(opt,"SELF")==0)
	{
		
		if(i.prec.ip==NULL)// PENTRY NO ANEL UNITARIO
		{
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
			
			//ENVIA MENSAGEM E SALVA SOCKET DO PREDECESSOR
			opt="SELF";
			i.prec.fd=mensagem_tcp(opt,i.prec,i.eu,pbits,-1,0,-1);
			
			
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

		}
		
		else//SEGUNDA ETAPA DO PENTRY E ULTIMA DO LEAVE 
		{	
			//ENVIA MENSAGEM
			opt="PRED";
			if(d(i.eu.chave,i.next.chave)>d(i.eu.chave,p.chave))mensagem_tcp(opt,i.next,p,pbits2,-1,0,i.next.fd);//DIFERENCIA O PROCESSO DO PENTRY OU LEAVE
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
	if (strcmp(opt,"PRED")==0){
	
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
			i.prec.fd=mensagem_tcp(opt,i.prec,i.eu,pbits,-1,0,-1);
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
	if (strcmp(opt,"FND")==0)
	{
		find://PARTE DO COMANDO BENTRY
		
		if(k==i.eu.chave|| (d(i.eu.chave,k)<d(i.next.chave,k)&&(i.atalho.ip==NULL||d(i.eu.chave,k)<d(i.atalho.chave,k))))//VERIFICA SE É O NÓ PROCURADO OU PERTENCE
		{
			opt="RSP";//INICIA PROCESSO DE RESPOSTA
			if(p.chave==i.eu.chave){goto RSP;}//BENTRY, SE O NO QUE FOI CHAMADO FOR O MAIS PROXIMO
			
			if(i.atalho.ip!=NULL && d(p.chave,i.atalho.chave)<d(p.chave,i.next.chave)){mensagem_udp(opt,i.atalho,i.eu,fbits,p.chave,n_find);}//PROCURA O MENOR CAMINHO PARA A PROCURA, ATALHO OU SUCESSOR
			else {mensagem_tcp(opt,i.next,i.eu,fbits,p.chave,n_find,i.next.fd);}
			
		}
/*		else if(d(i.eu.chave,k)<d(i.next.chave,k))//VERIFICA SE O NÓ NÃO SE ENCONTRA NO ANEL*/
/*		{*/
/*			opt="RSP";//INICIA PROCESSO DE RESPOSTA COM MENSAGEM DA INEXISTENCIA*/
/*			if(i.atalho.ip!=NULL && d(p.chave,i.atalho.chave)<d(p.chave,i.next.chave)){mensagem_udp(opt,i.atalho,p,fbits2,p.chave,n_find);}//PROCURA O MENOR CAMINHO, ENTRE ATALHO OU SUCESSOR*/
/*			else {mensagem_tcp(opt,i.next,p,fbits2,p.chave,n_find,i.next.fd);}*/
/*		}*/

		else
		{
			opt="FND";//CONTINUA O PROCESSO DE PROCURA
			if(i.atalho.ip!=NULL && d(i.atalho.chave,k)<d(i.next.chave,k)){mensagem_udp(opt,i.atalho,p,fbits2,k,n_find);}//PROCURA O MENOR CAMINHO, ENTRE ATALHO OU SUCESSOR
			else {mensagem_tcp(opt,i.next,p,fbits2,k,n_find,i.next.fd);}
		}
		return i;
	}
	
	
	
	
	
	
	
	//PROCESSO RSP, USADO NO FIND E BENTRY, 
	if (strcmp(opt,"RSP")==0)
	{
		opt="RSP";
		if(k==i.eu.chave&&n_find==i.n_find)//VERIFICA SE O NÓ É O PROCURADO
		{
			RSP://PARTE DO COMANDO FND(INICIALIZADO PELO BENTRY)
			
			if(i.k==-1){//VERIFICA SE ESTA NO COMANDO FIND OU BENTRY
			
				do{//PROCESSO DO ACK
				
					//MENSAGEM DE RESPOSTA 
					snprintf(ptr,30,"EPRED %d %s %s\n",p.chave,p.ip,p.porto);
					n=sendto(i.fdUDP,ptr,32,0,&i.addr,i.addrlen);
					if(n==-1)/*error*/exit(32);
					
					//ESPERA O ACK
					 buffer=ACK(0,i.fdUDP);
					 
				}while(strncmp("ACK",buffer,3)!=0);
			}
			else printf("Chave %d: Nó %d: (%s : %s) da chamada %d\n",i.k,p.chave, p.ip,p.porto,i.n_find);//PRINTF DO FIND
			fflush(stdout);
			i.n_find++;//MUDA O NUMERO DE CHAMADA
			i.k=-1;//REINICIALIZA FLAG
		}
		
		else//PROCURA O NO QUE INICIALIZOU O FIND
		{
			
			if(i.atalho.ip!=NULL && d(i.atalho.chave,k)<d(i.next.chave,k)){mensagem_udp(opt,i.atalho,p,fbits2,k,i.n_find);}//PROCURA O MENOR CAMINHO, ENTRE ATALHO OU SUCESSOR
			else {mensagem_tcp(opt,i.next,p,fbits2,k,n_find,i.next.fd);}
			
		}
	}
	
	
	
	
	//PROCESSO EFND, USADO NO BENTRY 
	else if(strcmp(opt,"EFND")==0) {
		//SALVA INFORMAÇAO RECEBIDAS
		k=p.chave;
		//PROCESSO DE PROCURA
		n_find=i.n_find;
		p=i.eu;
		goto find;
	}
	return i;
}
