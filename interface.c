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
    	
		printf("\nInterface escreva comando:");

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
		              i.prec.ip=p.ip;
		              i.prec.porto=p.porto;
		              i=pentry(i);
			}
			
	       else{ printf("Comando invalido");}
	return i;
}

