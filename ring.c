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
       int chave,j=0;
   	 char *opt, porto[20],ip[20];
   	 anel i,p;
   	

    	c= argv[1];
    	sscanf(c, "%d", &i.chave);
    	i.ip= argv[2];
       i.porto= argv[3];
    	
    	
    	
	do{
		printf("\nInterface escreva comando:");
/*		scanf(" %19s ",opt );*/
/*		if(scanf(“%[^\n]”, st)!=1);{*/
/*		scanf(" %d  " ,&chave );*/
/*		scanf(" %19s " ,ip  );*/
/*		scanf(" %19s " ,porto  );}*/

              fgets(porto, 20, stdin);
              c = strtok(porto, " ");
              while (c != NULL)
              {
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
		
/*		p.porto=porto;*/
/*		p.chave=chave;*/
/*		p.ip=ip;*/
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
