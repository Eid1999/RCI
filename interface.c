//COMO ESTABELECER CONECÇÃO SEM WRITE(SEGUNDA ETAPA PENTRY, CONECÇÃO COM SUCESSOR)????????????????????????????????????????????????????????????????????????????????
#include "Anel.h"

anel interface (anel i, char str[]){


       char *c;//PONTEIRO AUXILIAR
       int j=0;
   	 char *opt;//OPÇÃO
   	 no p;//NO AUXILIAR
   	 
   	 static char buffer [50];
   	 int auxTCP;
   	 char *auxUDP;
   	 
   	 //INICIALIZA AUXILIARES
	auxTCP=0;
	auxUDP="EMPTY";
	
	
	
	c = strtok(str, " ");
	
	
	//SEPARA AS DIFERENTES PARTES DO INPUT
	while (c != NULL)
	{
		if(strrchr(c,'\n')!=NULL){c[strcspn(c, "\n")] = 0;}//RETIRA /N DA STRING
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
	 
	
	//COMANDO NEW
	if(strcmp(opt,"n")==0){
		if(j!=1){printf("\nComando invalido\n");return i;}
		if(i.next.ip==NULL&&i.fdTCP==-1)i.fdTCP=0;//FLAG PARA SAIR DA INTERFACE
		else printf("ANEL JA EXISTE\n");//ANEL JA EXISTE
		return i;
		
	}
	
	
	
	
	//COMANDO FIND
	else if(strcmp(opt,"f")==0)
	{
		
		
		if(j!=2){printf("\nComando invalido\n");return i;}//ERRO NO COMANDO
		
		if(i.next.ip==NULL)return i;//ANEL DE UM SÓ NÓ
		
		if(p.chave==i.eu.chave){printf("\nES TU\n");return i;}//ES TU
		
		i.k[i.n_find]=p.chave;//SALVA A CHAVE DE PROCURA
		
		//ENVIA MENSAGEM
		opt="FND";
		if(i.atalho.ip!=NULL && d(i.atalho.chave,p.chave)<d(i.next.chave,p.chave)){auxUDP=mensagem_udp(opt,i.atalho,i.eu,p.chave,i.n_find);}//PROCURA POR ATALHO
		else {auxTCP=mensagem_tcp(opt,i.next,i.eu,p.chave,i.n_find,i.next.fd);}//PROCURA PELO SUCESSOR
		
		if(auxUDP==NULL)//ERRO NA COMUNICAÇÃO DE UDP
		{
			printf("\nCorda Quebrada, continuando pesquisa pelo sucessor\n");
			i=interface(i,"d\n");	//APAGA CORDA
			auxTCP=mensagem_tcp(opt,i.next,i.eu,p.chave,i.n_find,i.next.fd);//CONTINUA PESQUISA PELO SUCESSOR
		}
		if(auxTCP==-1)//ERRO NA COMUNICAÇÃO DE TCP
		{
			printf("\nAnel quebrado, reinicializando programa\n");
			i=ERRO(i);//ANEL FOI QUEBRADO, COMEÇA PROCESSO DE QUEBRA
		}
	
	}
	
	
	
	
	
	//COMANDO BENTRY
	else if(strcmp(opt,"b")==0) {
		if(i.next.ip!=NULL||i.fdTCP!=-1){printf("\nJa pertence a um anel\n");return i;}//JA ESTA DENTRO DE UM ANEL
		if(j!=4){printf("\nComando incompleto\n");return i;}//ERRO NO COMANDO
		if(strcmp(p.ip,i.eu.ip)==0&&strcmp(p.porto,i.eu.porto)==0){printf("\nES TU\n");return i;}//ES TU
		
		//ENVIA MENSAGEM
		opt="EFND";
		strcpy(buffer,mensagem_udp(opt,p,i.eu,p.chave,-1));
		
		if(strcmp(buffer,"ERRO")==0){printf("\nNó invalido, tente novamente\n");return i;}//COMUNICAÇÃO COM NO NÃO FOI POSSIVEL
		i=interface(i,buffer);//INICIA O PROCESSO PENTRY
	}
		
		
		
	//COMANDO PENTRY
	else if(strcmp(opt,"p")==0||strncmp("EPRED",opt,4)==0) {
	
		if(j!=4){printf("\nComando incompleto\n");return i;}//ERRO NO COMANDO
		if(i.next.ip!=NULL||i.fdTCP!=-1){printf("\nJa pertence a um anel\n");return i;}//JA ESTA DENTRO DE UM ANEL
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
		i.prec.fd=mensagem_tcp(opt,i.prec,i.eu,-1,0,i.prec.fd);//MENSAGEM COM AS SUAS INFORMAÇOES AO SEU NOVO PRECESSOR
		
		if(i.prec.fd==-1){printf("\nNó invalido, tente novamente\n");i=ERRO(i);}//COMUNICAÇÃO COM NO NÃO FOI POSSIVEL
		return i;
		     
	}
	//COMANDO CHORD
	else if(strcmp(opt,"c")==0) {
		
		if(j!=4){printf("\nComando invalido\n");return i;}//ERRO NO COMANDO
		if(strcmp(p.ip,i.eu.ip)==0&&strcmp(p.porto,i.eu.porto)==0){printf("\nES TU\n");return i;}//ES TU
		//ALOCA MEMORIA
		i.atalho.porto= (char*) malloc(50);
		i.atalho.ip= (char*) malloc(50);
		
		//SALVA ATALHO
		i.atalho.chave=p.chave;
		memcpy(i.atalho.ip,p.ip,50);
		memcpy(i.atalho.porto,p.porto,50);

		return i;
	}
	
	
	//COMANDO DCHORD
	else if(strcmp(opt,"d")==0) {
		if(i.atalho.ip!=NULL){free(i.atalho.ip);free(i.atalho.porto);i.atalho.ip=NULL;i.atalho.porto=NULL;}//DELETA INFORMAÇÃO SOBRE O ATALHO
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
		i=interface (i, "l");//LEAVE PRIMEIRO
		exit(0);
		
	}
	//COMANDO LEAVE
	else if(strcmp(opt,"l")==0){
		opt="PRED";
		if(i.next.ip!=NULL)mensagem_tcp(opt,i.next,i.prec,-1,0,i.next.fd);//AVISA O SUCESSOR DAS INFORMAÇOES DO PRECESSOR
		
		
		//LIMPA INFORMAÇOES
		 if(i.prec.ip!=NULL){free(i.prec.ip);free(i.prec.porto);i.prec.ip=NULL;i.prec.porto=NULL;}
		if(i.next.ip!=NULL){free(i.next.ip);free(i.next.porto);i.next.ip=NULL;i.next.porto=NULL;}
		if(i.atalho.ip!=NULL){free(i.atalho.ip);free(i.atalho.porto);i.atalho.ip=NULL;i.atalho.porto=NULL;}
		
		i.leave=1;//FLAG DO COMANDO LEAVE
		
		if(i.next.fd!=-1)//FECHA LIGAÇAO CRIADO COM MENSAGENS 
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

	return i;
}

