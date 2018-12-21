#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *entrada;
FILE *saida;
unsigned int tamanho = 0;


typedef struct dados{
	char nome[50];
	int tamanho;
	char tipo[5];
}dados;
dados *global = NULL;

typedef struct no {
	dados *data;
	// Filho da esquerda
	struct no* E;
	// Filho da direita
	struct no* D;
} no;

no *arvore_fim = NULL;

typedef struct raiz{
	no *P;
}raiz;
raiz *arvore = NULL;

void criar_arvore(){
	arvore = (raiz*)malloc(sizeof(raiz));
	arvore->P->data = global;
	arvore->P->D = NULL;
	arvore->P->E = NULL;
}

void inserir_arvore(no **temp, dados *aux){
	
	if(temp == NULL){
		temp = (no*)malloc(sizeof(no));
		temp->data = aux;
		temp->E = NULL;
		temp->D = NULL;
	}else{
		if(strncmp(temp->data->nome, aux->nome, sizeof(temp->data->nome)) < 0){
			inserir_arvore(temp->E, aux);
			arvore_fim = temp->E;
		}else if(strncmp(temp->data->nome, aux->nome, sizeof(temp->data->nome)) == 0){
			if(strcmp(temp->data->tipo, "rw") == 0){
				temp->data = aux;
			}
		}else{
			inserir_arvore(temp->D, aux);
		}
	}
}

void imprimir_epd(no *Topo){
	while(Topo != NULL){
		imprimir_epd(Topo->E);
		printf("%s %s %d \n", Topo->data->nome, Topo->data->tipo, Topo->data->tamanho);
		imprimir_epd(Topo->D);
	}
}

int main(int argc, char* argv[]){
	entrada = fopen(argv[1], "r");
	saida = fopen(argv[2], "w");
	if(entrada == NULL){
        printf("ENTRADA INVALIDA\n");
        exit(4);
	}else{
		fscanf(entrada, "%d", &tamanho);
		for(int i=0; i<tamanho; i++){
			global = (dados *)malloc(sizeof(dados));
			fscanf(entrada, "%s %s %d", global->nome, global->tipo, &global->tamanho);
				if(i==0){
					criar_arvore();
				}else{
					inserir_arvore(arvore->P, global);
				}
		}
	}
	imprimir_epd(arvore->P);
	fclose(entrada);
	fclose(saida);
	return 0;
}
