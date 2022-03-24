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

//INFORMAÇÕES DO NO
typedef struct _no {
    int chave;
    char  *ip, *porto ;
}no;

//ESTRUTURA DO ANEL VISTA DO NO
typedef struct _anel {
    no eu;
    no next;
    no prec ;
    no atalho;
    int leave;
    int n_find;
    int fdTCP;
    int fdUDP;
}anel;

char *ACK(anel i);//PROGRAMA PARA VALIDAÇÃO DE RECEBIMENTO
anel sub_processo(anel i, char buffer[]);//SUB PROCESSOS(FORA DO CONTROLE DO USUARIO)
anel interface(anel i);//INTEFACE DO USUARIO
void mensagem_tcp(char *opt, no dest, no envio,int nbits,int k, int n_find);//MESSAGEM TCP
void mensagem_udp(char *opt, no dest, no envio,int nbits,int k, int n_find);//MENSAGEM UDP
int d(int d1,int d2);//CALCULAR A DISTANCIA
int max(int x, int y);
#endif /* ANEL_DOT_H */
