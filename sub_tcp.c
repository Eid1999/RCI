#include "Anel.h"

anel sub_tcp(anel i, char buffer[])
{
       char *c;
       int j=0;
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
	                            mensagem_tcp(opt,i.prec,i.eu,24);
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
		              if(d(i.eu.chave,i.next.chave)>d(i.eu.chave,p.chave))mensagem_tcp(opt,i.next,p,24);
		               memcpy(i.next.ip,p.ip,50);
		               memcpy(i.next.porto,p.porto,50);
		               i.next.chave=p.chave;
		               return i;
		               
		              
		              
                            } 
		              
	
			}
		 if (strcmp(opt,"PRED")==0){
		       opt="SELF";
		       memcpy(i.prec.porto,p.porto,50);
	              memcpy(i.prec.ip,p.ip,50);
                     i.prec.chave=p.chave;
		       mensagem_tcp(opt,i.prec,i.eu,24);
		       
			 }
		else if(strcmp(opt,"PREB")==0) {
		       printf("new");
	              }
	       else if(strcmp(opt,"pentry")==0) {
		              
			}
       return i;
}
