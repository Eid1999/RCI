#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "Anel.h"
int connect(int sockfd,const struct sockaddr *serv_addr,
socklen_t addrlen);





anel interface (anel i){


       char *c;
       int j=0;
   	 char *opt, str[50];
   	 no p;
   	 
    	       
		printf("\nInterface do usuario, escreva o comando:\n");
              p.porto= (char*) malloc(50);
              p.ip= (char*) malloc(50);
              fgets(str, 50, stdin);
              c = strtok(str, " ");
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
		


		if (strcmp(opt,"new")==0){
		              
				return i;
			}
		else if(strcmp(opt,"bentry")==0) {
			       printf("new");
		       }
	       else if(strcmp(opt,"pentry")==0) {
		       
                     i.prec.porto= (char*) malloc(50);
                     i.prec.ip= (char*) malloc(50);
                     //IMPOR PRECESSOR
	              i.prec.chave=p.chave;
	              memcpy(i.prec.ip,p.ip,50);
	              memcpy(i.prec.porto,p.porto,50);
	              
	              opt="SELF";
	              mensagem_tcp(opt,i.prec,i.eu,24);
		            
		}
		
		else if(strcmp(opt,"show")==0) {
		       printf("\nINFORMAÇÃO PROPRIA: %d %s %s \n", i.eu.chave,i.eu.ip,i.eu.porto );
		       if(i.next.ip!=NULL)printf("\nINFORMAÇÃO SUCESSOR: %d %s %s \n",i.next.chave,i.next.ip,i.next.porto);
		       if(i.prec.ip!=NULL)printf("\nINFORMAÇÃO PRECESSOR: %d %s %s\n",i.prec.chave,i.prec.ip,i.prec.porto);
		       if(i.atalho.ip!=NULL)printf("\nINFORMAÇÃO ATALHO: %d %s %s \n",i.atalho.chave,i.atalho.ip,i.atalho.porto);
		}
	       else if(strcmp(opt,"exit")==0){
		       if(i.prec.ip!=NULL){free(i.prec.ip);free(i.prec.porto);}
		       if(i.next.ip!=NULL){free(i.next.ip);free(i.next.porto);}
		       if(i.atalho.ip!=NULL){free(i.atalho.ip);free(i.atalho.porto);}
		       exit(0);
	       }
	       else if(strcmp(opt,"leave")==0){
	              
	              opt="PRED";
	              if(i.next.ip!=NULL)mensagem_tcp(opt,i.next,i.prec,24);
	              
	               if(i.prec.ip!=NULL){i.prec.ip=NULL;i.prec.porto=NULL;}
		       if(i.next.ip!=NULL){i.next.ip=NULL;i.next.porto=NULL;}
		       if(i.atalho.ip!=NULL){i.atalho.ip=NULL;i.atalho.porto=NULL;}
		       return i;
	              
	       }
	       else{ printf("Comando invalido");}
	       
	return i;
}

