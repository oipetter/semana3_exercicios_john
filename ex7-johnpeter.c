#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct end{
    char nome[10];
}Pessoa;

Pessoa pessoas[10];
void *cria(void *p);
void *insere(void *p);


int main(){
    void *pBuffer;
    pBuffer = cria(pBuffer);
    for( *(int *)pBuffer = 0; *(int *)pBuffer <10; *(int *)pBuffer+1){
        pBuffer=insere(pBuffer);
    }
    free(pBuffer);
    exit(0);
}

void *insere(void *p){
    void *aux=p;
    *(int *)aux = *(int *)aux + 1;
    if((p=(void *)realloc(p, (sizeof(Pessoa) * (*(int *)aux)))) == NULL){
        printf("\n\n----ERRO EM ALOCAR MEMORIA----\n\n");
        exit(1);
    }

    aux = aux + ((sizeof(int)) + (sizeof(Pessoa) * (*(int *)aux)));

    printf("\nInforme nome: ");
    setbuf(stdin,NULL);
    scanf("%s",&pessoas[*(int *)aux]);
    return p;
}

void *cria(void *p){
    void *aux=p;
    aux=(void *)malloc(sizeof(int)+sizeof(Pessoa));
    if( aux == NULL){
        printf("\n-----FALTA DE MEMORIA----\n");
        exit(1);
    }
    *(int *)aux=0;
    return aux;
}