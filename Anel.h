#ifndef ANEL_DOT_H
#define ANEL_DOT_H  


#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <arpa/inet.h>

typedef struct _no {
    int chave;
    char  *ip, *porto ;
}no;

typedef struct _anel {
    no eu;
    no next;
    no prec ;
    no atalho;
}anel;


anel sub_tcp(anel i, char buffer[]);
anel interface(anel i);
void mensagem_tcp(char *opt, no dest, no envio,int nbits);

#endif /* ANEL_DOT_H */
