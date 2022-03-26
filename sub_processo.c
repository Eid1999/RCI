#include "Anel.h"

anel sub_processo(anel i, char buffer[])
{
	char *c;
	int j=0,k=0;
	char *opt;
	no p;
	p.porto= (char*) malloc(50);
	p.ip= (char*) malloc(50);
	int pbits2,pbits,fbits,fbits2;


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
		sscanf(p.ip, "%d", &i.n_find);
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
			opt="SELF";
/*			i.next.fd=mensagem_tcp(opt,p,i.eu,-1,0,0,-1);*/
			i.prec.fd=mensagem_tcp(opt,i.prec,i.eu,pbits,-1,0,-1);
			memcpy(i.next.porto,p.porto,50);
			memcpy(i.next.ip,i.prec.ip,50);
			i.next.chave=i.prec.chave;


		}
		
		
		else if(i.next.ip==NULL )// ULTIMA ETAPA DO PENTRY, LIGAÇÃO AO SUCESSOR
		{
			i.next.porto= (char*) malloc(50);
			i.next.ip= (char*) malloc(50);
			memcpy(i.next.ip,p.ip,50);
			memcpy(i.next.porto,p.porto,50);
			i.next.chave=p.chave;
/*			i.next.fd=mensagem_tcp(opt,i.next,i.eu,-1,0,0,-1);*/

		}
		
		else//PRIMEIRA ETAPA DO PENTRY E ULTIMA DO LEAVE 
		{
			opt="PRED";
/*			i.next.fd=mensagem_tcp(opt,p,i.eu,-1,0,0,-1);*/
			if(d(i.eu.chave,i.next.chave)>d(i.eu.chave,p.chave))/*DIFERENCIA O PROCESSO DO PENTRY OU LEAVE*/mensagem_tcp(opt,i.next,p,pbits2,-1,0,i.next.fd);
			memcpy(i.next.ip,p.ip,50);
			memcpy(i.next.porto,p.porto,50);
			i.next.chave=p.chave;
			i.next.fd=-1;
			
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
			i.prec.fd=-1;
			i.prec.fd=mensagem_tcp(opt,i.prec,i.eu,pbits,-1,0,-1);
		}
		else// LEAVE COM UM ANEL COM DOIS NÓS
		{
			free(i.prec.porto);i.prec.porto=NULL;
			free(i.prec.ip);i.prec.ip=NULL;
			free(i.next.porto);i.next.porto=NULL;
			free(i.next.ip);i.next.ip=NULL;
		}  
	}

	//PROCESSO FND, USADO NO FIND E BENTRY
	if (strcmp(opt,"FND")==0)
	{
		
		if(k==i.eu.chave)//VERIFICA SE É O NÓ PROCURADO 
		{
			opt="RSP";//INICIA PROCESSO DE RESPOSTA DE SUCESSO
			if(i.atalho.ip!=NULL && d(p.chave,i.atalho.chave)<d(p.chave,i.next.chave)){mensagem_udp(opt,i.atalho,i.eu,fbits,p.chave,i.n_find);}//PROCURA O MENOR CAMINHO, ATALHO OU SUCESSOR
			else {mensagem_tcp(opt,i.next,i.eu,fbits,p.chave,i.n_find,i.next.fd);}
			
		}
		else if(d(i.eu.chave,k)<d(i.next.chave,k))//VERIFICA SE O NÓ NÃO SE ENCONTRA NO ANEL
		{
			opt="RSP";//INICIA PROCESSO DE RESPOSTA COM MENSAGEM DA INEXISTENCIA
			if(i.atalho.ip!=NULL && d(p.chave,i.atalho.chave)<d(p.chave,i.next.chave)){mensagem_udp(opt,i.atalho,p,fbits2,p.chave,i.n_find);}//PROCURA O MENOR CAMINHO, ENTRE ATALHO OU SUCESSOR
			else {mensagem_tcp(opt,i.next,p,fbits2,p.chave,i.n_find,i.next.fd);}
		}
		else
		{
			opt="FND";
			if(i.atalho.ip!=NULL && d(i.atalho.chave,k)<d(i.next.chave,k)){mensagem_udp(opt,i.atalho,p,fbits2,k,i.n_find);}//PROCURA O MENOR CAMINHO, ENTRE ATALHO OU SUCESSOR
			else {mensagem_tcp(opt,i.next,p,fbits2,k,i.n_find,i.next.fd);}
		}
		return i;
	}
	
	//PROCESSO RSP, USADO NO FIND E BENTRY
	if (strcmp(opt,"RSP")==0)
	{
		opt="RSP";
		if(k==i.eu.chave)//VERIFICA SE O NÓ É O PROCURADO
		{
			if(p.chave==k)printf("Nó não existe no anel");//MENSAGEM DE INEXISTENCIA
			else printf("Nó %d: (%s : %s)",p.chave, p.ip,p.porto);//MENSAGEM DE SUCESSO
			fflush(stdout);
			
		}
		
		else//PROCURA O NO QUE INICIALIZOU O FIND
		{

			if(i.atalho.ip!=NULL && d(i.atalho.chave,k)<d(i.next.chave,k)){mensagem_udp(opt,i.atalho,p,fbits2,k,i.n_find);}//PROCURA O MENOR CAMINHO, ENTRE ATALHO OU SUCESSOR
			else {mensagem_tcp(opt,i.next,p,fbits2,k,i.n_find,i.next.fd);}
			
		}
	}

	else if(strcmp(opt,"PREB")==0) {
	printf("new");
	}
	return i;
}
