#include "Anel.h"

anel sub_udp(anel i, char buffer[])
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
              	i.atalho.porto= (char*) malloc(50);
                     i.atalho.ip= (char*) malloc(50);
                     //IMPOR PRECESSOR
	              i.atalho.chave=p.chave;
	              memcpy(i.atalho.ip,p.ip,50);
	              memcpy(i.atalho.porto,p.porto,50);  
			}
       return i;
}
