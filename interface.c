//COMO ESTABELECER CONECÇÃO SEM WRITE(SEGUNDA ETAPA PENTRY, CONECÇÃO COM SUCESSOR)????????????????????????????????????????????????????????????????????????????????
#include "Anel.h"

anel interface (anel i, char str[]){


       char *c;
       int j=0;
   	 char *opt;
   	 no p;
   	 int fbits,pbits,lbits;
	//RECEBE OS COMANDO
/*	INTERFACE:*/
/*	printf("\nInterface do usuario, escreva um comando:(-h para ajuda)\n");*/
/*	fflush(stdin);*/
/*	while(fgets(str, 50, stdin)==NULL);*/
	
	c = strtok(str, " ");
	
	
	//SEPARA AS DIFERENTES PARTES DO INPUT
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

		   }
		c = strtok (NULL, " ");
		j++;
	 }
	 
	fbits=(strlen(opt)+strlen(i.eu.ip)+strlen(i.eu.porto)+16);
	pbits=(strlen(opt)+strlen(i.eu.ip)+strlen(i.eu.porto)+10);
	if(i.next.ip!=NULL){
	lbits=(strlen(opt)+strlen(i.prec.ip)+strlen(i.prec.porto)+10);}
	//COMANDO FIND
	if(strcmp(opt,"n")==0){i.fdTCP=0; return i;}
	else if(strcmp(opt,"f")==0)
	{
		if(j!=2){printf("\nComando incompleto\n");return i;}//ERRO NO COMANDO
		if(i.next.ip==NULL)exit(20);//ANEL DE UM SÓ NÓ
		if(p.chave==i.eu.chave){printf("ES TU");return i;}//ES TU
		opt="FND";
		if(i.atalho.ip!=NULL && d(p.chave,i.atalho.chave)<d(p.chave,i.next.chave)){mensagem_udp(opt,i.atalho,i.eu,fbits,p.chave,i.n_find);}//PROCURA POR ATALHO
		else {mensagem_tcp(opt,i.next,i.eu,fbits,p.chave,i.n_find,i.next.fd);}//PROCURA PELO SUCESSOR
	
	}
	//COMANDO BENTRY
	else if(strcmp(opt,"b")==0) {
			opt="EFND";
			mensagem_udp(opt,p,i.eu,8,p.chave,-1);
		}
	else if(strcmp(opt,"p")==0) {
		if(j<4){printf("\nComando incompleto\n");return i;}//ERRO NO COMANDO
		if(strcmp(p.ip,i.eu.ip)==0&&strcmp(p.porto,i.eu.porto)==0){printf("ES TU");return i;}//ES TU
		i.prec.porto= (char*) malloc(50);
		i.prec.ip= (char*) malloc(50);
		//SALVA PRECESSOR
		i.prec.chave=p.chave;
		memcpy(i.prec.ip,p.ip,50);
		memcpy(i.prec.porto,p.porto,50);
		
		opt="SELF";
		i.prec.fd=mensagem_tcp(opt,i.prec,i.eu,pbits,-1,0,i.prec.fd);//MENSAGEM COM AS SUAS INFORMAÇOES AO SEU NOVO PRECESSOR
		return i;
		     
	}
	//COMANDO CHORD
	else if(strcmp(opt,"c")==0) {
		
		if(j<4){printf("\nComando invalido\n");return i;}//ERRO NO COMANDO
		i.atalho.porto= (char*) malloc(50);
		i.atalho.ip= (char*) malloc(50);
		//SALVA ATALHO
		i.atalho.chave=p.chave;
		memcpy(i.atalho.ip,p.ip,50);
		memcpy(i.atalho.porto,p.porto,50);
/*		mensagem_udp("EMPTY",i.atalho,i.eu,-1,0,0); // CONECTA AO ATALHO*/
		return i;
	}
	//COMANDO DCHORD
	else if(strcmp(opt,"d")==0) {
		if(i.atalho.ip!=NULL){free(i.atalho.ip);free(i.atalho.porto);i.atalho.ip=NULL;i.atalho.porto=NULL;}
	}
	//COMANDO SHOW
	else if(strcmp(opt,"s")==0) {
		
		printf("\nINFORMAÇÃO PROPRIA: %d %s %s \n", i.eu.chave,i.eu.ip,i.eu.porto );
		if(i.next.ip!=NULL)printf("\nINFORMAÇÃO SUCESSOR: %d %s %s \n",i.next.chave,i.next.ip,i.next.porto);
		if(i.prec.ip!=NULL)printf("\nINFORMAÇÃO PRECESSOR: %d %s %s\n",i.prec.chave,i.prec.ip,i.prec.porto);
		if(i.atalho.ip!=NULL)printf("\nINFORMAÇÃO ATALHO: %d %s %s \n",i.atalho.chave,i.atalho.ip,i.atalho.porto);
	}
	//COMANDO EXIT	
	else if(strcmp(opt,"e")==0){
		//LIMPA INFORMAÇOES
		if(i.prec.ip!=NULL){free(i.prec.ip);free(i.prec.porto);}
		if(i.next.ip!=NULL){free(i.next.ip);free(i.next.porto);}
		if(i.atalho.ip!=NULL){free(i.atalho.ip);free(i.atalho.porto);}
		//FECHA SOCKET
		if(i.next.fd!=-1)//FECHA LIGAÇAO CLIENTE-SOCKETS
		{
			close(i.next.fd);
			close(i.prec.fd);
		}
		close(i.fdTCP);
		close(i.fdUDP);
		exit(10);
	}
	//COMANDO LEAVE
	else if(strcmp(opt,"l")==0){
		opt="PRED";
		if(i.next.ip!=NULL)mensagem_tcp(opt,i.next,i.prec,lbits,-1,0,i.next.fd);//AVISA O SUCESSOR DAS INFORMAÇOES DO PRECESSOR
		//LIMPA INFORMAÇOES
		 if(i.prec.ip!=NULL){free(i.prec.ip);free(i.prec.porto);i.prec.ip=NULL;i.prec.porto=NULL;}
		if(i.next.ip!=NULL){free(i.next.ip);free(i.next.porto);i.next.ip=NULL;i.next.porto=NULL;}
		if(i.atalho.ip!=NULL){free(i.atalho.ip);free(i.atalho.porto);i.atalho.ip=NULL;i.atalho.porto=NULL;}
		i.leave=1;
		if(i.next.fd!=-1)//FECHA LIGAÇAO CLIENTE-SOCKETS
		{
			close(i.next.fd);
		}
		if(i.prec.fd!=-1)
		{
			close(i.prec.fd);
		}
		//FECHA SOCKETS
		if(i.fdTCP!=-1){
			close(i.fdTCP);
			close(i.fdUDP);
		}
		return i;
		      
	}
	
	
	else if(strcmp(opt,"-h")==0)printf("\nComandos disponiveis:\n\n n->new \n\n p [CHAVE] [IP] [PORTO]->pentry\n\n b[CHAVE](EM CONSTRUÇAO)->bentry \n\n f [CHAVE]->find\n \n l->leave\n\n e->exit \n\n c->chord\n\n d->delete chord \n\n s->show\n\n");

	
	else{ printf("\nComando invalido\n");}
/*	if(i.next.ip==NULL&&i.fdTCP==-1) goto INTERFACE;*/

	return i;
}

