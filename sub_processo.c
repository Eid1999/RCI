#include "Anel.h"

anel sub_processo(anel i, char buffer[])
{
       char *c;
       int j=0,k=0;
   	 char *opt;
   	 no p;
   	p.porto= (char*) malloc(50);
       p.ip= (char*) malloc(50);
   	 
    	
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
	if (strcmp(opt,"SELF")==0){


		if(i.prec.ip==NULL)
		{
			i.prec.porto= (char*) malloc(50);
			i.prec.ip= (char*) malloc(50);
			i.next.porto= (char*) malloc(50);
			i.next.ip= (char*) malloc(50);
			memcpy(i.prec.porto,p.porto,50);
			memcpy(i.prec.ip,p.ip,50);
			i.prec.chave=p.chave;
			opt="SELF";
			mensagem_tcp(opt,i.prec,i.eu,24,0,0);
			memcpy(i.next.porto,p.porto,50);
			memcpy(i.next.ip,i.prec.ip,50);
			 i.next.chave=i.prec.chave;

		}
		else if(i.next.ip==NULL )
		{
			i.next.porto= (char*) malloc(50);
			i.next.ip= (char*) malloc(50);
			memcpy(i.next.ip,p.ip,50);
			memcpy(i.next.porto,p.porto,50);
			i.next.chave=p.chave;

		}

		else{
			opt="PRED";
			if(d(i.eu.chave,i.next.chave)>d(i.eu.chave,p.chave))mensagem_tcp(opt,i.next,p,24,0,0);//MANDA MENSAGEM APENAS NA ENTRADA DO NÓ(PENTRY)
			memcpy(i.next.ip,p.ip,50);
			memcpy(i.next.porto,p.porto,50);
			i.next.chave=p.chave;
			return i;
		} 


	}
	if (strcmp(opt,"PRED")==0){
		opt="SELF";
		if( p.chave!=i.prec.chave)
		{
			memcpy(i.prec.porto,p.porto,50);
			memcpy(i.prec.ip,p.ip,50);
			i.prec.chave=p.chave;
			mensagem_tcp(opt,i.prec,i.eu,24,0,0);
		}
		else//SAIDA COM APENAS DOIS NÓS
		{
			free(i.prec.porto);i.prec.porto=NULL;
			free(i.prec.ip);i.prec.ip=NULL;
			free(i.next.porto);i.next.porto=NULL;
			free(i.next.ip);i.next.ip=NULL;
		}  
	}


	if (strcmp(opt,"FND")==0)
	{
		if(k==i.eu.chave)
		{
			opt="RSP";
			if(i.atalho.ip!=NULL && d(p.chave,i.atalho.chave)<d(p.chave,i.next.chave)){mensagem_udp(opt,i.atalho,i.eu,34,p.chave,i.n_find);}
			else {mensagem_tcp(opt,i.next,i.eu,34,p.chave,i.n_find);return i;}
			//CRIAR SELECT PARA O ACK
		}
		else if(i.eu.chave==p.chave)printf("Chave não se encontra no anel");
		else
		{
			opt="FND";
			if(i.atalho.ip!=NULL && d(i.atalho.chave,k)<d(i.next.chave,k)){mensagem_udp(opt,i.atalho,p,34,k,i.n_find);}
			else {mensagem_tcp(opt,i.next,p,34,k,i.n_find);}
			//CRIAR SELECT PARA O ACK
		}
	}
	if (strcmp(opt,"RSP")==0)
	{
		opt="RSP";
		if(k==i.eu.chave)
		{
			printf("Nó %d: (%s : %s)",p.chave, p.ip,p.porto);
			fflush(stdout);
			//CRIAR SELECT PARA O ACK
		}
		else
		{
			
			if(i.atalho.ip!=NULL && d(i.atalho.chave,k)<d(i.next.chave,k)){mensagem_udp(opt,i.atalho,p,34,k,i.n_find);}
			else {mensagem_tcp(opt,i.next,p,34,k,i.n_find);return i;}
			//CRIAR SELECT PARA O ACK
		}
		
	}

	else if(strcmp(opt,"PREB")==0) {
	printf("new");
	}
	return i;
	}
