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
    int fd;
}no;

//ESTRUTURA DO ANEL VISTA DO NO
typedef struct _anel {
    no eu;
    no next;
    no prec;
    no atalho;
    
     int fdTCP;//FD TCP DO SERVIDOR
    int fdUDP;//FD UDP DO SERVIDOR
    int AUX;//FD AUXILIAR
    
    //VARIAVEIS PARA O FIND
    int n_find;//NUMERO DA PROCURA
    int k;//CHAVE PROCURADA &&  FLAG PARA O BENTRY
    
    //VARIAVEIS PARA BENTRY
    struct sockaddr addr;
    socklen_t addrlen;
    //
    
    int leave;//FLAG PARA COMANDO LEAVE
    
   
    
}anel;

char *ACK(int fdTCP, int fdUDP);//PROGRAMA PARA VALIDAÇÃO DE RECEBIMENTO
anel sub_processo(anel i, char buffer[]);//SUB PROCESSOS(FORA DO CONTROLE DO USUARIO)
anel interface(anel i,char str[]);//INTEFACE DO USUARIO
int mensagem_tcp(char *opt, no dest, no envio,int nbits,int k, int n_find,int fd);//MESSAGEM TCP
char *mensagem_udp(char *opt, no dest, no envio,int nbits,int k, int n_find);//MENSAGEM UDP
int d(int d1,int d2);//CALCULAR A DISTANCIA
int max(int x, int y);
#endif /* ANEL_DOT_H */
