#ifndef ANEL_DOT_H
#define ANEL_DOT_H  


typedef struct _anel {
    int chave;
    char *ip,*porto ;
}anel;
void newAnel(anel i);
void bentry(anel i, anel p);
void pentry(anel i, anel p);

#endif /* ANEL_DOT_H */
