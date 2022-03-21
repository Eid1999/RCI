#ifndef ANEL_DOT_H
#define ANEL_DOT_H  


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



anel interface(anel i);
anel pentry(anel i);

#endif /* ANEL_DOT_H */
