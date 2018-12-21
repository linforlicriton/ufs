#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *entrada;
FILE *saida;

unsigned int num_palavras = 0;

typedef struct dados{
	char palavra[31];
}dados;

typedef struct definicao{
	dados *def;
	char nome[31];
	unsigned int qtdPalavra;
	struct definicao *D;
	struct definicao *E;
}definicao;
definicao *R = NULL;
definicao *fator_balanceamento(definicao *);

int calculo_altura(definicao *temp){
	int height = 0;
	if(temp != NULL){
		int altura_E = altura_E = calculo_altura(temp->E);
		int altura_D = altura_D = calculo_altura(temp->D);
		int max = (altura_D > altura_E)?altura_D:altura_E;
		height = 1 + max;
	}
	return height;
}

definicao *funcao_copiar(definicao *temp,char nome[], int palavras, dados *data){
	strcpy(temp->nome, nome);
	for(int i=0; i<palavras; i++){
		strcpy(temp->def[i].palavra, data[i].palavra);
	}
	temp->qtdPalavra = palavras;
	return temp;
}

definicao *rotacao_esq(definicao *raiz) {
	definicao *eixo = raiz->D;
	raiz->D = eixo->E;
	eixo->E = raiz;
	raiz = eixo;
	raiz = fator_balanceamento(raiz);
	return raiz;
}

definicao *rotacao_dir(definicao *raiz) {
	definicao *eixo = raiz->E;
	raiz->E = eixo->D;
	eixo->D = raiz;
	raiz = eixo;
	raiz = fator_balanceamento(raiz);
	return raiz;
}

definicao *rotacao_dir_esq(definicao *raiz){
	definicao *eixo = raiz->D;
	raiz->D = rotacao_dir(eixo);
	return rotacao_esq(raiz);
}
	
definicao *rotacao_esq_dir(definicao *raiz){
	definicao *eixo = raiz->E;
	raiz->E = rotacao_esq(eixo);
	return rotacao_dir(raiz);
}

int dir_esq(definicao *temp){
	int altura_E = calculo_altura(temp->E);
	int altura_D = calculo_altura(temp->D);
	int result = altura_D - altura_E;
	return result;
}

definicao *fator_balanceamento(definicao *raiz){
	int indice = dir_esq(raiz);
	if(indice > 1){
		if(dir_esq(raiz->D)>0){
			raiz = rotacao_esq(raiz);
		}else{
			raiz = rotacao_dir_esq(raiz);
		}
	}else if(indice < -1){
		if(dir_esq(raiz->E) > 0 ){
			raiz = rotacao_esq_dir(raiz);
		}else{
			raiz = rotacao_dir(raiz);
		}
	}
	//printf("%s \n", raiz->nome);
	return (raiz);
}

definicao *funcao_compara(definicao *Raiz,char nome[], int palavras, dados *data){
	if(Raiz == NULL){
		Raiz = (definicao *)malloc(sizeof(definicao));
		Raiz->def = (dados *)malloc(palavras*sizeof(dados));
		Raiz->D = NULL;
		Raiz->E = NULL;
		Raiz = funcao_copiar(Raiz, nome, palavras, data);
		return Raiz;
	}else{
		int cmp = strncmp(nome, Raiz->nome, 30);
		if(cmp < 0){
			Raiz->E = funcao_compara(Raiz->E, nome, palavras, data);
			
		}
		if(cmp > 0){
			Raiz->D = funcao_compara(Raiz->D, nome, palavras, data);
			
		}
		Raiz = fator_balanceamento(Raiz);
	}
	return Raiz;
}

void funcao_imprimir(definicao *aux, char nome[]){
	if(aux == NULL){
		fprintf(saida, "?:\n");
		fprintf(saida, "[-]\n");
	}else{
		int cmp = strncmp(nome, aux->nome, 30);
		if(cmp > 0) fprintf(saida, "%s->", aux->nome), funcao_imprimir(aux->D, nome);
		if(cmp < 0) fprintf(saida, "%s->", aux->nome), funcao_imprimir(aux->E, nome);
		if(cmp == 0){
			fprintf(saida, "%s:\n", aux->nome);
			int temp = aux->qtdPalavra;
			fprintf(saida, "[");
				for(int i=0; i<temp-1; i++){
					fprintf(saida, "%s, ", aux->def[i].palavra);
				}fprintf(saida, "%s]\n", aux->def[temp-1].palavra);
		}
	}
	fflush(saida);
}

void inicializar(){
	R = (definicao *)malloc(sizeof(definicao));
}

int main(int argc, char* argv[]){
	entrada = fopen(argv[1], "r");
	saida = fopen(argv[2], "w");
    int palavras = 0;
    int busca = 0;
    char nome[30];
    fscanf(entrada, "%d", &num_palavras);
    if(entrada == NULL){
		printf("ENTRADA INVALIDA\n");
		exit(1);
	}else{
		inicializar();
		for(int i=0; i<num_palavras; i++){
			fscanf(entrada, "%s", nome);
			fscanf(entrada, "%d", &palavras);
			dados *data = (dados *)malloc(palavras*sizeof(dados));
			for(int j=0; j<palavras; j++){
				fscanf(entrada, "%s", data[j].palavra);
			}
			R = funcao_compara(R,nome,palavras, data);
		}
		fscanf(entrada, "%d", &busca);
		for(int i=0; i<busca; i++){
			fscanf(entrada, "%s", nome);
			funcao_imprimir(R, nome);
		}
	}
    fclose(entrada);
	fclose(saida);
	return 0;
}
	
