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
#include <time.h>

//INFORMAÇÕES DO NO
typedef struct _no {
    int chave;
    char  *ip, *porto ;
    int fd;
}no;

//ESTRUTURA DO ANEL VISTA PELO NO
typedef struct _anel {
    no eu;//EU
    no next;//SUCESSOR
    no prec;//PREDECESSOR
    no atalho;//CORDA
    
     int fdTCP;//FD TCP DO SERVIDOR
    int fdUDP;//FD UDP DO SERVIDOR
    int AUX;//FD AUXILIAR
    
    //VARIAVEIS PARA O FIND
    int n_find;//NUMERO DA PROCURA
    int k[100];//CHAVE PROCURADA &&  FLAG PARA O BENTRY
    
    //VARIAVEIS PARA BENTRY
    struct sockaddr addr;
    socklen_t addrlen;
    //
    
    int leave;//FLAG PARA COMANDO LEAVE
    
   
    
}anel;

char *ACK(int fdTCP, int fdUDP);//PROGRAMA DO ACK


anel sub_processo(anel i, char buffer[]);//PROCESSO INTERNOS(buffer-mensagem recebida)

anel interface(anel i,char str[]);//INTEFACE DO USUARIO(comando recebido)

int mensagem_tcp(char *opt, no dest, no envio,int k, int n_find,int fd);//MESSAGEM TCP(opt-opçao (SELF,PRED),dest-destino da mensagem,envio-de onde vem o envio,nbits-tamanho da mensagem,k-chave procurada,n_find-numero da pesquiça )

char *mensagem_udp(char *opt, no dest, no envio,int k, int n_find);//MENSAGEM UDP(opt-opçao (SELF,PRED),dest-destino da mensagem,envio-de onde vem o envio,nbits-tamanho da mensagem,k-chave procurada,n_find-numero da pesquiça )

int d(int d1,int d2);//CALCULAR A DISTANCIA(d2-d1)mod

int max(int x, int y);//CALCULA O MAIOR SOCKET PARA SELECT

anel ERRO(anel i);//QUEBRA DE ANEL 


#endif /* ANEL_DOT_H */
