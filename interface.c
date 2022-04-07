//COMO ESTABELECER CONECÇÃO SEM WRITE(SEGUNDA ETAPA PENTRY, CONECÇÃO COM SUCESSOR)????????????????????????????????????????????????????????????????????????????????
#include "Anel.h"

anel interface (anel i, char str[]){


       char *c;
       int j=0;
   	 char *opt;
   	 no p;
   	 int fbits,pbits,lbits;
   	 int quit=0;
   	 static char buffer [50];
	
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
	 
	 
	 
	 //CALCULA TAMANHO DE MENSAGEM QUE SERA ENVIADA
	fbits=(strlen(opt)+strlen(i.eu.ip)+strlen(i.eu.porto)+16);
	pbits=(strlen(opt)+strlen(i.eu.ip)+strlen(i.eu.porto)+10);
	if(i.next.ip!=NULL){
	lbits=(strlen(opt)+strlen(i.prec.ip)+strlen(i.prec.porto)+10);}
	
	
	//COMANDO NEW
	if(strcmp(opt,"n")==0){
		if(i.next.ip==NULL&&i.fdTCP==-1)i.fdTCP=0;//FLAG PARA CRIAR SAIR DA INTERFACE
		else printf("ANEL JA EXISTE\n");//ANEL JA EXISTE
		return i;
		
	}
	
	
	
	
	//COMANDO FIND
	else if(strcmp(opt,"f")==0)
	{
		i.k=p.chave;//SALVA A CHAVE DE PROCURA
		
		if(j!=2){printf("\nComando incompleto\n");return i;}//ERRO NO COMANDO
		
		if(i.next.ip==NULL)exit(20);//ANEL DE UM SÓ NÓ
		
		if(p.chave==i.eu.chave){printf("\nES TU\n");return i;}//ES TU
		
		//ENVIA MENSAGEM
		opt="FND";
		if(i.atalho.ip!=NULL && d(p.chave,i.atalho.chave)<d(p.chave,i.next.chave)){mensagem_udp(opt,i.atalho,i.eu,fbits,p.chave,i.n_find);}//PROCURA POR ATALHO
		else {mensagem_tcp(opt,i.next,i.eu,fbits,p.chave,i.n_find,i.next.fd);}//PROCURA PELO SUCESSOR
	
	}
	
	
	
	
	
	//COMANDO BENTRY
	else if(strcmp(opt,"b")==0) {
		if(j<4){printf("\nComando incompleto\n");return i;}//ERRO NO COMANDO
		if(strcmp(p.ip,i.eu.ip)==0&&strcmp(p.porto,i.eu.porto)==0){printf("\nES TU\n");return i;}//ES TU
		//ENVIA MENSAGEM
		opt="EFND";
		strcpy(buffer,mensagem_udp(opt,p,i.eu,8,p.chave,-1));
		i=interface(i,buffer);//INICIA O PROCESSO PENTRY
	}
		
		
		
	//COMANDO PENTRY
	else if(strcmp(opt,"p")==0||strncmp("EPRED",opt,4)==0) {
		if(j<4){printf("\nComando incompleto\n");return i;}//ERRO NO COMANDO
		
		if(strcmp(p.ip,i.eu.ip)==0&&strcmp(p.porto,i.eu.porto)==0){printf("\nES TU\n");return i;}//ES TU
		if(p.chave==i.eu.chave){printf("\nCHAVE INVALIDA\n");return i;}//TENTATIVA DE ENTRAR COM CHAVE INVALIDA
		
		//ALOCA MEMORIA
		i.prec.porto= (char*) malloc(50);
		i.prec.ip= (char*) malloc(50);
		
		//SALVA PRECESSOR
		i.prec.chave=p.chave;
		memcpy(i.prec.ip,p.ip,50);
		memcpy(i.prec.porto,p.porto,50);
		
		//ENVIA MENSAGEM
		opt="SELF";
		i.prec.fd=mensagem_tcp(opt,i.prec,i.eu,pbits,-1,0,i.prec.fd);//MENSAGEM COM AS SUAS INFORMAÇOES AO SEU NOVO PRECESSOR
		return i;
		     
	}
	//COMANDO CHORD
	else if(strcmp(opt,"c")==0) {
		
		if(j<4){printf("\nComando invalido\n");return i;}//ERRO NO COMANDO
		if(strcmp(p.ip,i.eu.ip)==0&&strcmp(p.porto,i.eu.porto)==0){printf("\nES TU\n");return i;}//ES TU
		//ALOCA MEMORIA
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
		quit=1;//FLAG
		goto leave;//LEAVE PRIMEIRO
		
	}
	//COMANDO LEAVE
	else if(strcmp(opt,"l")==0){
		leave://PARTE DO EXIT
		opt="PRED";
		if(i.next.ip!=NULL)mensagem_tcp(opt,i.next,i.prec,lbits,-1,0,i.next.fd);//AVISA O SUCESSOR DAS INFORMAÇOES DO PRECESSOR
		
		
		//LIMPA INFORMAÇOES
		 if(i.prec.ip!=NULL){free(i.prec.ip);free(i.prec.porto);i.prec.ip=NULL;i.prec.porto=NULL;}
		if(i.next.ip!=NULL){free(i.next.ip);free(i.next.porto);i.next.ip=NULL;i.next.porto=NULL;}
		if(i.atalho.ip!=NULL){free(i.atalho.ip);free(i.atalho.porto);i.atalho.ip=NULL;i.atalho.porto=NULL;}
		
		i.leave=1;//FLAG DO COMANDO LEAVE
		
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
	}
	
	//FUTILIDADES
	else if(strcmp(opt,"-h")==0)printf("\nComandos disponiveis:\n\n n\t\t\t\t\t new: CRIA ANEL \n\n p [CHAVE] [IP] [PORTO]\t\t\t pentry: ENTRADA NO NÓ SABENDO POSIÇÃO\n\n b [CHAVE][IP] [PORTO] \t\t\t bentry: ENTRADA NO NÓ SEM SABER POSIÇÃO\n\n f [CHAVE]\t\t\t\t find: PROCURA DA CHAVE\n\n l\t\t\t\t\t leave: SAIDA DO ANEL\n\n e\t\t\t\t\t exit: SAIDA DO PROGRAMA\n\n c[CHAVE] [IP] [PORTO]\t\t\t chord: CRIAÇÃO DE CORDAS\n\n d\t\t\t\t\t delete chord: APAGA CORDA\n\n s\t\t\t\t\t show: MOSTRA QUEM TU ES\n\n");

	
	else{ printf("\nComando invalido\n");}

	if(quit==1)exit(1);//PARTE DO EXIT

	return i;
}

