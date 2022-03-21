#include "Anel.h"

anel sub_tcp(anel i, char buffer[])
{
       char *c;
       int j=0;
   	 char *opt;
   	 no p;
    	
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
		              
				return i;
			}
			else if(strcmp(opt,"PREB")==0) {
			       printf("new");
		       }
		       else if(strcmp(opt,"pentry")==0) {
		              i.prec.ip=p.ip;
		              i.prec.porto=p.porto;
		              i=pentry(i);
			}
       return i;
}
