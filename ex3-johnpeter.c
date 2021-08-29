#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void buscar(void *var);
void * insere(void *var);
void * apaga(void *var);
void imprime(void *var);

typedef struct end{
char nome[10];
int idade;
int telefone;
} INFO;

int contagem=0;

int main(){
    void *var=NULL;
    for (;;){
        int opcao=0;
        do{
            printf("------MENU------\n[1] - Adicionar nome\n[2] - Remover nome\n[3] - Buscar nome\n[4] - Listar nomes\n[5] - Sair\nInforme valor: ");
            scanf("%d", &opcao);
        }while(opcao<=0 || opcao>5);
        switch (opcao){
            case 1:     
                var=insere(var);
                break;
            case 2:
                var=apaga(var);
                break;
            case 3:
                buscar(var);
                break;
            case 4:     
                imprime(var);
                break;
            case 5:     
                free(var);
                exit(0);
        }
    }
    return 0;
}

void * insere(void *var){
    contagem++;
    void *x = var;
    INFO aux;
    printf("Nome: ");
    setbuf(stdin,NULL);
    fgets(aux.nome, 10, stdin);
    printf("Idade: ");
    setbuf(stdin,NULL);
    scanf("%d", &aux.idade);
    printf("Telefone: ");
    scanf("%d", &aux.telefone);
    if(var == NULL){
        if ((var = (void *) malloc((sizeof(INFO))+sizeof(int))) == NULL){
            printf("\nFALTA DE MEMORIA\n\n");
            contagem--;
            return var;
        }
        *(int *)var = contagem;
    }else{
        if ((var = (void *) realloc(var, ((sizeof(INFO) * contagem)+sizeof(int)))) == NULL){
			printf("\nFALTA DE MEMORIA\n");
            contagem--;
			return var;
        }
    }
    x=var;
    *(int *)x =contagem;
    x =x+(sizeof(int))+(sizeof(INFO) * (contagem-1));
    *(INFO *)x = aux;
    return var;
}

void imprime(void *var){
    void *ini = var;
    int aux;
    INFO temp;
    ini = ini + sizeof(int);
    for(aux=0; aux < contagem; aux++){
        temp = *(INFO *)ini;
        printf("\n%dº Contato:\nNome: %s\nIdade: %d.\nTelefone: %d.\n\n", aux+1, temp.nome, temp.idade, temp.telefone);
        ini = ini + sizeof(INFO);
    }
}

void * apaga(void *var){
    int contador;
    int p=-2;
    void *aux1 = var, *aux_final = var;
    if (contagem != 0){
        contagem--;
        do{
            printf("INFORME A POSICAO DO NOME (SENDO 1=0, 2=1, ....): ");
            scanf("%d", &p);
        }while (p<0 || p>contagem);
        aux1=aux1+(sizeof(int))+(sizeof(INFO) * (p));
        aux_final=aux1 + sizeof(INFO);

        for (contador=p; contador < contagem; contador++){
            *(INFO *)aux1 = *(INFO *)aux_final;
            aux1 = aux1 + sizeof(INFO);
            aux_final = aux_final + sizeof(INFO);
        }   
        if ((var = (void *) realloc(var, ((sizeof(INFO) * contagem) + sizeof(int)))) == NULL){
			printf("\nERRO AO ALOCAR MEMORIA\n");
			return var;
            exit(1);
        }
    } else
        printf("\nSEM CONTATOS PARA REMOVER.\n");
    return var;
}

void buscar(void *var){
    int tel, cont;
    int ocorre=0;
    int op=-1;
    void *ini=var+sizeof(int);
    char nome[10];
    INFO aux;
    do{
        printf("----Menu de busca: \n[1] - Nome\n[2] - Telefone\nInforme valor: ");
        scanf("%d", &op);
    }while (op<=0 || op>2);

    switch (op){
        case 1: 
            printf("Nome: \n");
            setbuf(stdin, NULL);
            fgets(nome, 10, stdin);
            printf("Encontrado: \n");
            for (cont=0; cont < contagem; cont++){
                aux= *(INFO *)ini;
                if (strcmp (aux.nome, nome) == 0){
                    printf("\n\n%dº Contato:\nNome: %s\nIdade: %d.\nTelefone: %d.\n\n", cont+1, aux.nome, aux.idade, aux.telefone);
                    ocorre++;
                }
                ini = ini + sizeof(INFO);
            }
            if (ocorre == 0)
                printf("NADA ENCONTRADO.");
            break;
        case 2:
            printf("Telefone: \n");
            scanf("%d", &tel);       
            printf("Encontrado: \n");
            for (cont=0; cont < contagem; cont++){
                aux= *(INFO *)ini;
                if (aux.telefone == tel){
                    printf("\n%dº Contato:\nNome: %s\nIdade: %d.\nTelefone: %d.\n\n", cont+1, aux.nome, aux.idade, aux.telefone);
                    ocorre++;
                }
                ini = ini + sizeof(INFO);
                }
                if (ocorre == 0)
                    printf("NADA ENCONTRADO.");
                break;
    }
}

