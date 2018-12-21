#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *entrada;
FILE *saida;
unsigned int tamanho = 0;
unsigned int posicao = 0;

typedef struct dados{
	int posicao;
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
no **arvore = NULL;

void criar_arvore(){
	arvore = (no**)malloc(sizeof(no));
	*arvore = NULL;
}

void adicionar_elementos(no **temp, dados *aux){
	
	if(*temp == NULL){
		*temp = (no*)malloc(sizeof(no));
		(*temp)->E = NULL;
		(*temp)->D = NULL;
		(*temp)->data = aux;
		(*temp)->data->posicao = posicao;
	}else{
		if(strncmp(aux->nome,(*temp)->data->nome, sizeof((*temp)->data->nome)) < 0){
			adicionar_elementos(&(*temp)->E, aux);
		}else if(strncmp(aux->nome, (*temp)->data->nome, sizeof((*temp)->data->nome)) == 0){
			if(strcmp((*temp)->data->tipo, "rw") == 0){
				(*temp)->data = aux;
				(*temp)->data->posicao = posicao;
			}
		}else{
			adicionar_elementos(&(*temp)->D, aux);
		}
	}
}

void imprimir_epd(no *Topo){
	if(Topo != NULL){
		imprimir_epd(Topo->E);
		if(Topo->data->tamanho == 1){
			fprintf(saida, "%d %s %s %d byte\n",Topo->data->posicao, Topo->data->nome, Topo->data->tipo, Topo->data->tamanho);
		}else{
			fprintf(saida, "%d %s %s %d bytes\n",Topo->data->posicao, Topo->data->nome, Topo->data->tipo, Topo->data->tamanho);
		}
		imprimir_epd(Topo->D);
	}
	fflush(saida);
}
void imprimir_ped(no *Topo){
	if(Topo != NULL){
		if(Topo->data->tamanho == 1){
			fprintf(saida, "%d %s %s %d byte\n",Topo->data->posicao, Topo->data->nome, Topo->data->tipo, Topo->data->tamanho);
		}else{
			fprintf(saida, "%d %s %s %d bytes\n",Topo->data->posicao, Topo->data->nome, Topo->data->tipo, Topo->data->tamanho);
		}
		imprimir_ped(Topo->E);
		imprimir_ped(Topo->D);
	}
	fflush(saida);
}
void imprimir_edp(no *Topo){
	if(Topo != NULL){
		imprimir_edp(Topo->E);
		imprimir_edp(Topo->D);
		if(Topo->data->tamanho == 1){
			fprintf(saida, "%d %s %s %d byte\n",Topo->data->posicao, Topo->data->nome, Topo->data->tipo, Topo->data->tamanho);
		}else{
			fprintf(saida, "%d %s %s %d bytes\n",Topo->data->posicao, Topo->data->nome, Topo->data->tipo, Topo->data->tamanho);
		}
	}
	fflush(saida);
}

int main(int argc, char* argv[]){
	entrada = fopen(argv[1], "r");
	saida = fopen(argv[2], "w");
	if(entrada == NULL){
        printf("ENTRADA INVALIDA\n");
        exit(1);
	}else{
		fscanf(entrada, "%d", &tamanho);
		criar_arvore();
		for(int i=0; i<tamanho; i++){
			posicao = i;
			global = (dados *)malloc(sizeof(dados));
			fscanf(entrada, "%s %s %d", global->nome, global->tipo, &global->tamanho);
			adicionar_elementos(arvore, global);
		}
	}
	fprintf(saida, "EPD:\n");
	imprimir_epd(*arvore);
	fprintf(saida, "PED:\n");
	imprimir_ped(*arvore);
	fprintf(saida, "EDP:\n");
	imprimir_edp(*arvore);
	fclose(entrada);
	fclose(saida);
	return 0;
}
