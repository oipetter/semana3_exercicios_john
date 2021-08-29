#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include <locale.h>
#include<conio.h>

struct end{
    int idade;
    float altura;
    char nome[30];
    struct end *prox;
};
typedef struct end dados;

dados *lista(void);
int menu(void);
dados *livre(void);
void insere(dados *ponteiro);
void imprime(dados *a);
void remove_ponteiro(dados *p);


int main(){
    dados *var=NULL;
    var=lista();
    int op;
    for(;;){
        op=menu();
        switch(op){
            case 1:
                insere(var);
                break;
            case 2:
                imprime(var);
                remove_ponteiro(var);
                exit(0);  
                break;
        }
    }
    return 0;
}

void insere(dados *ponteiro){
    dados *nova;
    nova=livre();
    printf("\nNome: "); 
    scanf("%s",&nova->nome);
    printf("\nIdade: ");
    scanf("%d",&nova->idade);
    printf("\nAltura: ");
    scanf("%f",&nova->altura);
    nova->prox=ponteiro->prox;
    ponteiro->prox=nova;
}

dados *livre(void){
	dados *u;
	if((u = (dados *) malloc(sizeof(dados))) == NULL){
		printf("FALTA DE MEMORIA");
		exit (1);
	}
	return u;
}

dados *lista(void){
	dados *start;
	start = (dados *) malloc(sizeof(dados));
	start->prox = NULL;
	return start;
}

int menu(void){
	int c = 0;
	do {
		printf("-- MENU:\n");
		printf("\t [ 1 ] - Inserir um nome\n");
		printf("\t [ 2 ] - Sair\n");
		printf("-- Digite sua escolha: ");
		scanf("%d", &c);
	} while (c <= 0 || c > 2);
	getchar();
	return c;
}

void imprime(dados *a){
	dados *p;
	for (p = a->prox; p != NULL; p = p->prox){
		printf("\nNome: %s", p->nome);
        printf("\nIdade: %d",p->idade);
        printf("\nAltura: %.2f\n\n",p->altura);
	}
}

void remove_ponteiro(dados *p)
{
	dados *morta;
	morta = p->prox;
	p->prox = morta->prox;
	free(morta);
}