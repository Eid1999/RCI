
#include "Anel.h"

anel interface (anel i){


       char *c;
       int j=0;
   	 char *opt, str[50];
   	 no p;
	//RECEBE OS COMANDO
	printf("\nInterface do usuario, escreva o comando:\n");
	
	fgets(str, 50, stdin);
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
	

	//COMANDO FIND
	if(strcmp(opt,"f")==0)
	{
		if(j!=2){printf("\nComando incompleto\n");return i;}//ERRO NO COMANDO
		if(i.next.ip==NULL)exit(0);//ANEL DE UM SÓ NÓ
		if(p.chave==i.eu.chave){printf("ES TU");return i;}//ES TU
		opt="FND";
		if(i.atalho.ip!=NULL && d(p.chave,i.atalho.chave)<d(p.chave,i.next.chave)){mensagem_udp(opt,i.atalho,i.eu,34,p.chave,i.n_find);}//PROCURA POR ATALHO
		else {mensagem_tcp(opt,i.next,i.eu,34,p.chave,i.n_find);}//PROCURA PELO SUCESSOR
	
	}
	//COMANDO BENTRY
	else if(strcmp(opt,"b")==0) {
			printf("new");
		}
	else if(strcmp(opt,"p")==0) {
		if(j!=4){printf("\nComando incompleto\n");return i;}//ERRO NO COMANDO
		i.prec.porto= (char*) malloc(50);
		i.prec.ip= (char*) malloc(50);
		//SALVA PRECESSOR
		i.prec.chave=p.chave;
		memcpy(i.prec.ip,p.ip,50);
		memcpy(i.prec.porto,p.porto,50);
		
		opt="SELF";
		mensagem_tcp(opt,i.prec,i.eu,24,0,0);//MENSAGEM COM AS SUAS INFORMAÇOES AO SEU NOVO PRECESSOR
		     
	}
	//COMANDO CHORD
	else if(strcmp(opt,"c")==0) {
		
		if(j!=4){printf("\nComando invalido\n");return i;}//ERRO NO COMANDO
		i.atalho.porto= (char*) malloc(50);
		i.atalho.ip= (char*) malloc(50);
		//SALVA ATALHO
		i.atalho.chave=p.chave;
		memcpy(i.atalho.ip,p.ip,50);
		memcpy(i.atalho.porto,p.porto,50);
		mensagem_udp("EMPTY",i.atalho,i.eu,0,0,0); // CONECTA AO ATALHO  
	}
	//COMANDO ECHORD
	else if(strcmp(opt,"e")==0) {
		if(i.atalho.ip!=NULL){free(i.atalho.ip);free(i.atalho.porto);i.atalho.ip=NULL;i.atalho.porto=NULL;}
	}
	//COMANDO SHOW
	else if(strcmp(opt,"s")==0) {
		
		printf("\nINFORMAÇÃO PROPRIA: %d %s %s \n", i.eu.chave,i.eu.ip,i.eu.porto );
		if(i.next.ip!=NULL)printf("\nINFORMAÇÃO SUCESSOR: %d %s %s \n",i.next.chave,i.next.ip,i.next.porto);
		if(i.prec.ip!=NULL)printf("\nINFORMAÇÃO PRECESSOR: %d %s %s\n",i.prec.chave,i.prec.ip,i.prec.porto);
		if(i.atalho.ip!=NULL)printf("\nINFORMAÇÃO ATALHO: %d %s %s \n",i.atalho.chave,i.atalho.ip,i.atalho.porto);
	}
	//COMANDO EXIT?????????????(MESMA INICIAL Q O ECHORD)
	else if(strcmp(opt,"q")==0){
		//LIMPA INFORMAÇOES
		if(i.prec.ip!=NULL){free(i.prec.ip);free(i.prec.porto);}
		if(i.next.ip!=NULL){free(i.next.ip);free(i.next.porto);}
		if(i.atalho.ip!=NULL){free(i.atalho.ip);free(i.atalho.porto);}
		//FECHA SOCKET
		close(i.fdTCP);
		close(i.fdUDP);
		exit(0);
	}
	//COMANDO LEAVE
	else if(strcmp(opt,"l")==0){
		opt="PRED";
		if(i.next.ip!=NULL)mensagem_tcp(opt,i.next,i.prec,24,0,0);//AVISA O SUCESSOR DAS INFORMAÇOES DO PRECESSOR
		//LIMPA INFORMAÇOES
		 if(i.prec.ip!=NULL){free(i.prec.ip);free(i.prec.porto);i.prec.ip=NULL;i.prec.porto=NULL;}
		if(i.next.ip!=NULL){free(i.next.ip);free(i.next.porto);i.next.ip=NULL;i.next.porto=NULL;}
		if(i.atalho.ip!=NULL){free(i.atalho.ip);free(i.atalho.porto);i.atalho.ip=NULL;i.atalho.porto=NULL;}
		i.leave=1;
	
		      
	}

	
	else{ printf("Comando invalido");}

	return i;
}

