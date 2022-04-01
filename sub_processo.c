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
	
	fbits=(strlen(opt)+strlen(i.eu.ip)+strlen(i.eu.porto)+16);
	fbits2=(strlen(opt)+strlen(p.ip)+strlen(p.porto)+16);
	pbits=(strlen(opt)+strlen(i.eu.ip)+strlen(i.eu.porto)+10);
	pbits2=(strlen(opt)+strlen(p.ip)+strlen(p.porto)+10);
	
	
	//PROCESSO SELF, USADO NO LEAVE E PENTRY
	if (strcmp(opt,"SELF")==0)
	{
		
		if(i.prec.ip==NULL)// PENTRY NO ANEL UNITARIO
		{
			i.prec.porto= (char*) malloc(50);
			i.prec.ip= (char*) malloc(50);
			i.next.porto= (char*) malloc(50);
			i.next.ip= (char*) malloc(50);
			memcpy(i.prec.porto,p.porto,50);
			memcpy(i.prec.ip,p.ip,50);
			i.prec.chave=p.chave;
			i.next.chave=p.chave;
			opt="SELF";
			i.prec.fd=mensagem_tcp(opt,i.prec,i.eu,pbits,-1,0,-1);
			i.next.fd=i.AUX;
			memcpy(i.next.porto,p.porto,50);
			memcpy(i.next.ip,i.prec.ip,50);
		}
		
		
		else if(i.next.ip==NULL )// ULTIMA ETAPA DO PENTRY, LIGAÇÃO AO SUCESSOR
		{
			i.next.porto= (char*) malloc(50);
			i.next.ip= (char*) malloc(50);
			memcpy(i.next.ip,p.ip,50);
			memcpy(i.next.porto,p.porto,50);
			i.next.chave=p.chave;

		}
		
		else//PRIMEIRA ETAPA DO PENTRY E ULTIMA DO LEAVE 
		{
			opt="PRED";
			if(d(i.eu.chave,i.next.chave)>d(i.eu.chave,p.chave))/*DIFERENCIA O PROCESSO DO PENTRY OU LEAVE*/mensagem_tcp(opt,i.next,p,pbits2,-1,0,i.next.fd);
			memcpy(i.next.ip,p.ip,50);
			memcpy(i.next.porto,p.porto,50);
			i.next.chave=p.chave;
			close(i.next.fd);
			i.next.fd=-1;
			i.next.fd=i.AUX;
			
			return i;
		} 


	}
	
	//PROCESSO PRED, USADO NO LEAVE E PENTRY
	if (strcmp(opt,"PRED")==0){
		opt="SELF";
		
		
		if( p.chave!=i.eu.chave)//PRIMEIRA ETAPA DO LEAVE, E SEGUNDA ETAPA DO PENTRY
		{
			memcpy(i.prec.porto,p.porto,50);
			memcpy(i.prec.ip,p.ip,50);
			i.prec.chave=p.chave;
			close(i.prec.fd);
			i.prec.fd=-1;
			i.prec.fd=mensagem_tcp(opt,i.prec,i.eu,pbits,-1,0,-1);
		}
		else// LEAVE COM UM ANEL COM DOIS NÓS
		{
			free(i.prec.porto);i.prec.porto=NULL;
			free(i.prec.ip);i.prec.ip=NULL;
			free(i.next.porto);i.next.porto=NULL;
			free(i.next.ip);i.next.ip=NULL;
			close(i.next.fd);
			i.next.fd=-1;
			close(i.prec.fd);
			i.prec.fd=-1;
			
		}  
	}

	//PROCESSO FND, USADO NO FIND E BENTRY
	if (strcmp(opt,"FND")==0)
	{
		find:
		
		if(k==i.eu.chave|| (d(i.eu.chave,k)<d(i.next.chave,k)&&(i.atalho.ip==NULL||d(i.eu.chave,k)<d(i.atalho.chave,k))))//VERIFICA SE É O NÓ PROCURADO 
		{
			if(p.chave==i.eu.chave){goto RSP;}//SE O NO DO PENTRY QUE INICIOU A PESQUISA FOR O MAIS PROXIMO 
			opt="RSP";//INICIA PROCESSO DE RESPOSTA DE SUCESSO
			if(i.atalho.ip!=NULL && d(p.chave,i.atalho.chave)<d(p.chave,i.next.chave)){mensagem_udp(opt,i.atalho,i.eu,fbits,p.chave,n_find);}//PROCURA O MENOR CAMINHO, ATALHO OU SUCESSOR
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
			opt="FND";
			if(i.atalho.ip!=NULL && d(i.atalho.chave,k)<d(i.next.chave,k)){mensagem_udp(opt,i.atalho,p,fbits2,k,n_find);}//PROCURA O MENOR CAMINHO, ENTRE ATALHO OU SUCESSOR
			else {mensagem_tcp(opt,i.next,p,fbits2,k,n_find,i.next.fd);}
		}
		return i;
	}
	
	
	
	
	
	
	
	//PROCESSO RSP, USADO NO FIND E BENTRY
	if (strcmp(opt,"RSP")==0)
	{
		opt="RSP";
		if(k==i.eu.chave&&n_find==i.n_find)//VERIFICA SE O NÓ É O PROCURADO
		{
			RSP:
			if(i.k==-1){
				do{
					snprintf(ptr,30,"EPRED %d %s %s\n",p.chave,p.ip,p.porto);
					n=sendto(i.fdUDP,ptr,32,0,&i.addr,i.addrlen);
					if(n==-1)/*error*/exit(32);
					 buffer=ACK(0,i.fdUDP);
				}while(strncmp("ACK",buffer,3)==0);
			}
			else printf("Chave %d: Nó %d: (%s : %s) da chamada %d\n",i.k,p.chave, p.ip,p.porto,i.n_find);//MENSAGEM DE SUCESSO
			fflush(stdout);
			i.n_find++;
			i.k=-1;
		}
		
		else//PROCURA O NO QUE INICIALIZOU O FIND
		{
			
			if(i.atalho.ip!=NULL && d(i.atalho.chave,k)<d(i.next.chave,k)){mensagem_udp(opt,i.atalho,p,fbits2,k,i.n_find);}//PROCURA O MENOR CAMINHO, ENTRE ATALHO OU SUCESSOR
			else {mensagem_tcp(opt,i.next,p,fbits2,k,n_find,i.next.fd);}
			
		}
	}
	
	
	
	

	else if(strcmp(opt,"EFND")==0) {
		k=p.chave;
		n_find=i.n_find;
		p=i.eu;
		goto find;
	}
	return i;
}
