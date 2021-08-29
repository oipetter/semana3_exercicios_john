#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * insere(char *var);
char * apaga(char *start);
void listar(char *var);

int main(){
    char *var=NULL;
    for (;;){
        int opcao=0;
        do{
            printf("------MENU------\n[1] - Adicionar nome\n[2] - Remover nome\n[3] - Listar nomes\n[4] - Sair\nInforme valor: ");
            scanf("%d", &opcao);
        }while(opcao<=0 || opcao>4);

        switch (opcao){
            case 1:
                var = insere(var);
                break;
            case 2:     
                var = apaga(var);
                break;
            case 3:     
                listar(var);
                break;
            case 4:     
                free(var);
                exit(0);
                break;
        }
    }
    return 0;
}

void listar(char *var){
    char *x=var;
    printf("\n----NOMES-----\n");
    if (var == NULL){
        printf("LISTA SEM NOMES\n");
    }
    else{
        while (*x != '\0'){
            putchar(*x);
            x++;
        }
    }
    printf("\n--------------\n\n");
}

char * insere(char *var){
    char *auxiliar=NULL;
    int t, ta;
    if ((auxiliar = (char *) malloc(sizeof(char *) * 30)) == NULL){
            printf("FALTA DE MEMORIA\n");
            return var;
    }
    printf("Informe um nome: \n");
    setbuf(stdin,NULL);
    fgets(auxiliar, 30, stdin);
    t = strlen(auxiliar);
    if(var == NULL){
        if ((var = (char *) malloc((sizeof(char *) * t) +1)) == NULL){
            printf("FALTA DE MEMORIA\n");
            return var;
        }
    strcpy(var, auxiliar); 
    }else{
        ta=strlen(var);
        if ((var = (char *) realloc(var, sizeof(char *) * (ta+t+1))) == NULL){
			printf("FALTA DE MEMORIA\n");
			exit(0);
        }
        strcat(var, auxiliar);
    }
    free(auxiliar);
    return var;
}


char * apaga(char *start)
{
    int ind=-1, qtdSTR=0, qtdIni=0, qtdFim=0, op, TamTot=0, TamSTR=0;
    char *ini = start, *fim = start;

    if (start != NULL){
        for(ini; *ini != '\0'; ini++)
            if (*ini == '\n')
                qtdSTR++;

        do {
            printf("Informe o índice do nome que deseja remover, começando em 0: \n");
            scanf("%d", &ind);
            if (ind < 0 || ind >= qtdSTR)
                printf("ATENCAO - VALOR INCORRETO\n\n");
        } while (ind < 0 || ind >= qtdSTR);

        ini = start;

        for(op=0; op < ind; ini++){
            if (*ini == '\n')
                op++;
            qtdIni++;
        }
        
        for(op=0; op < (ind+1); fim++){
            if (*fim == '\n')
                op++;
            qtdFim++;
        }
        TamSTR = qtdFim - qtdIni;
        TamTot = strlen(start);

        for(fim; *fim != '\0';){
            *ini = *fim;
            ini++;
            fim++;
        }
        *ini = '\0';

        if (TamTot - TamSTR != 0){
            if ((start = (char *) realloc(start, sizeof(char *) * (TamTot - TamSTR))) == NULL){
                    printf("ERRO AO ALOCAR MEMORIA\n");
                    exit(0);
                }
        }
        else{
            free(start);
            start = NULL;
        }
        return start;
    }
    else{
        printf("SEM NOMES PARA REMOVER\n");
        return start;
    }
}


