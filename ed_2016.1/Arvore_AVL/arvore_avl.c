#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *entrada;
FILE *saida;

unsigned int num_palavras = 0;


typedef struct dados{
	char palavra[30];
}dados;
dados *data = NULL;

typedef struct definicao{
	dados *def;
	char nome[30];
	unsigned int qtdPalavra;
	struct definicao *D;
	struct definicao *E;
	int indice;
}definicao;
definicao **R = NULL;

void funcao_copiar(definicao **temp, char nome[], int palavras){
	strcpy((*temp)->nome, nome);
	for(int i=0; i<palavras; i++){
		strcpy((*temp)->def[i].palavra, data[i].palavra);
	}
	(*temp)->indice = 0;
	(*temp)->qtdPalavra = palavras;
}

void fator_balanceamento(definicao **raiz){
	if((*raiz) == NULL){
		
	}else{
		fator_balanceamento(&(*raiz)->E);
		if((*raiz)->E == NULL) (*raiz)->indice = 0;
		if((*raiz)->E != NULL) (*raiz)->indice +=1;
		fator_balanceamento(&(*raiz)->D);
		if((*raiz)->D == NULL) (*raiz)->indice = 0;
		if((*raiz)->D != NULL) (*raiz)->indice -= 1;
		if((*raiz)->D != NULL && (*raiz)->E != NULL){
			(*raiz)->indice = (*raiz)->E->indice - (*raiz)->D->indice;
		}
		
	}
	
}

void rotacao_esq(definicao **raiz) {
	definicao *eixo = (definicao *)malloc(sizeof(definicao));
	eixo = (*raiz)->D;
	(*raiz)->D = eixo->E;
	eixo->E = (*raiz);
	(*raiz) = eixo;
	fator_balanceamento(raiz);
	eixo = NULL;
	free(eixo);
}

void rotacao_dir(definicao **raiz) {
	definicao *eixo = (*raiz)->E;
	(*raiz)->E = eixo->D;
	eixo->D = (*raiz);
	(*raiz) = eixo;
	fator_balanceamento(raiz);
}

void rotacao_dir_esq(definicao **raiz){
	rotacao_dir(&(*raiz)->D);
	rotacao_esq(raiz);
}
	
void rotacao_esq_dir(definicao **raiz){
	rotacao_esq(&(*raiz)->E);
	rotacao_dir(raiz);
}

void funcao_compara(definicao **Raiz,char nome[], int palavras){
	if((*Raiz) == NULL){
		(*Raiz) = (definicao *)malloc(sizeof(definicao));
		(*Raiz)->def = (dados *)malloc(palavras*sizeof(dados));
		(*Raiz)->D = NULL;
		(*Raiz)->E = NULL;
		
		funcao_copiar(&(*Raiz), nome, palavras);
		
	}else{
		if(strncmp((*Raiz)->nome, nome, sizeof((*Raiz)->nome))==0) return;
		if(strncmp(nome, (*Raiz)->nome, sizeof((*Raiz)->nome)) < 0){
			funcao_compara(&(*Raiz)->E, nome, palavras);
			if((*Raiz)->D == NULL) (*Raiz)->indice -= 1;
			if((*Raiz)->D != NULL) (*Raiz)->indice -=1;
		}
		if(strncmp(nome,(*Raiz)->nome, sizeof((*Raiz)->nome)) > 0){
			funcao_compara(&(*Raiz)->D, nome, palavras);
			if((*Raiz)->E == NULL) (*Raiz)->indice += 1;
			if((*Raiz)->E != NULL) (*Raiz)->indice +=1;
		}
		if((*Raiz)->D != NULL && (*Raiz)->E != NULL){
			(*Raiz)->indice = (*Raiz)->E->indice - (*Raiz)->D->indice;
		}
	}
	if((*Raiz)->indice == 2 && ((*Raiz)->D->indice == -1)) rotacao_dir_esq(&(*Raiz));
	if((*Raiz)->indice == -2 && ((*Raiz)->E->indice == 1)) rotacao_esq_dir(&(*Raiz));
	if((*Raiz)->indice == 2) rotacao_esq(&(*Raiz));
	if((*Raiz)->indice == -2) rotacao_dir(&(*Raiz));
}

void funcao_imprimir(definicao *aux, char nome[]){
	if(aux == NULL){
		fprintf(saida, "?:\n");
		fprintf(saida, "[-]\n");
	}else{
		
		if(strncmp(nome, aux->nome, sizeof(aux->nome)) > 0) fprintf(saida, "%s->", aux->nome), fflush(saida), funcao_imprimir(aux->D, nome);
		if(strncmp(nome, aux->nome, sizeof(aux->nome)) < 0) fprintf(saida, "%s->", aux->nome), fflush(saida), funcao_imprimir(aux->E, nome);
		if(strncmp(nome, aux->nome, sizeof(aux->nome)) == 0){
			fprintf(saida, "%s:\n", aux->nome);
			int temp = aux->qtdPalavra;
			fprintf(saida, "[");
			for(int i=0; i<temp-1; i++){
				fprintf(saida, "%s, ", aux->def[i].palavra);
			}fprintf(saida, "%s]", aux->def[temp-1].palavra);
			fprintf(saida, "\n");
		}
		fflush(saida);	
	}
	fflush(saida);
}

void inicializar(){
	R = (definicao **)malloc(sizeof(definicao));
	*R = NULL;
}

int main(int argc, char* argv[]){
	entrada = fopen(argv[1], "r");
	saida = fopen(argv[2], "w");
    if(entrada == NULL) exit(1);
    int palavras = 0;
    int busca = 0;
    char nome[30];
    fscanf(entrada, "%d", &num_palavras);
    inicializar();
    for(int i=0; i<num_palavras; i++){
		fscanf(entrada, "%s", nome);
		fscanf(entrada, "%d", &palavras);
		data = (dados *)malloc(palavras*sizeof(dados));
		for(int j=0; j<palavras; j++){
			fscanf(entrada, "%s", data[j].palavra);
		}
		funcao_compara(R,nome,palavras);
	}
	fscanf(entrada, "%d", &busca);
	for(int i=0; i<busca; i++){
		fscanf(entrada, "%s", nome);
		funcao_imprimir(*R, nome);
	}
	
    fclose(entrada);
	fclose(saida);
	return 0;
}
	
