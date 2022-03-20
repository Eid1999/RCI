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





int main (int argc,char *argv[]){

       char *c;
       int j=0;
   	 char *opt, str[20];
   	 anel i,p;
   	

    	c= argv[1];
    	sscanf(c, "%d", &i.chave);
    	i.ip= argv[2];
       i.porto= argv[3];
    	
    	
    	
	do{
		printf("\nInterface escreva comando:");

              fgets(str, 20, stdin);
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
				newAnel(i);
			}
			else if(strcmp(opt,"bentry")==0) {
				bentry(i);
		       }
		       else if(strcmp(opt,"pentry")==0) {
				pentry(i);
			}
	 }while(strcmp(opt,"exit")!=0);
	return 0;
}
