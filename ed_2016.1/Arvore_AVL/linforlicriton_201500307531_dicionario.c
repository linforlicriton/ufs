#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

FILE *entrada = NULL;
FILE *saida = NULL;

unsigned int num_palavras = 0;
int E = 0;
int D = 0;

typedef struct dados{
	char palavra[31];
}dados;
dados *data;

typedef struct definicao{
	dados *def;
	char nome[31];
	unsigned int altura;
	unsigned int qtdPalavra;
	struct definicao *D;
	struct definicao *E;
}definicao;
struct definicao **R = NULL;

void inicializar(){
	R = (definicao **)malloc(sizeof(definicao));
	*R = NULL;
}

unsigned int altura(definicao* r){
    return r?r->altura:0;
}

int fator(definicao* r){
    return altura(r->D)-altura(r->E);
}

void indice(definicao* r){
    unsigned int altura_E = altura(r->E);
    unsigned int altura_D = altura(r->D);
    r->altura = (altura_E>altura_D?altura_E:altura_D)+1;
}

definicao *funcao_copiar(definicao *temp,char nome[], int palavras){
	strcpy(temp->nome, nome);
	int i;
	for(i=0; i<palavras; i++){
		strcpy(temp->def[i].palavra, data[i].palavra);
	}
	temp->qtdPalavra = palavras;
	return temp;
}

definicao* rotacao_esq(definicao* q){
    definicao* p = q->D;
    q->D = p->E;
    p->E = q;
    indice(q);
    indice(p);
    return p;
}

definicao *rotacao_dir(definicao* p){
    definicao* q = p->E;
    p->E = q->D;
    q->D = p;
    indice(p);
    indice(q);
    return q;
}

definicao *fator_balanceamento(definicao* p){
    indice(p);
    if(fator(p)==2)
    {
        if(fator(p->D) < 0) p->D = rotacao_dir(p->D);
        return rotacao_esq(p);
    }
    if(fator(p)==-2)
    {
        if(fator(p->E) > 0) p->E = rotacao_esq(p->E);
        return rotacao_dir(p);
    }
   indice(p);
   return p;
}

void funcao_compara(definicao **Raiz,char nome[], int palavras){
	if((*Raiz) == NULL){
		(*Raiz) = (definicao *)malloc(sizeof(definicao));
		(*Raiz)->def = (dados *)malloc(palavras*sizeof(dados));
		(*Raiz)->D = NULL;
		(*Raiz)->E = NULL;
		(*Raiz) = funcao_copiar((*Raiz), nome, palavras);
		(*Raiz)->altura = 1;
		return;
	}else{
		int cmp = strncmp(nome, (*Raiz)->nome, 30);
		if(cmp < 0){
			funcao_compara(&(*Raiz)->E, nome, palavras);
			
		}
		if(cmp > 0){
			funcao_compara(&(*Raiz)->D, nome, palavras);
		}
		(*Raiz) = fator_balanceamento(*Raiz);
	}
}

void funcao_imprimir(definicao *aux, char nome[]){
	int i;
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
			for(i=0; i<temp-1; i++){
				fprintf(saida, "%s, ", aux->def[i].palavra);
			}fprintf(saida, "%s]", aux->def[temp-1].palavra);
			fprintf(saida, "\n");
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
		int palavras = 0;
		int i, j;
		char nome[31];
		inicializar();
		fscanf(entrada, "%d", &num_palavras);
		for(i=0; i<num_palavras; i++){
			fscanf(entrada, "%s", nome);
			fscanf(entrada, "%d", &palavras);
			data = (dados *)malloc(palavras*(sizeof(dados)));
				for(j=0; j<palavras; j++){
					fscanf(entrada, "%s", data[j].palavra);
				}
			funcao_compara(R,nome,palavras);
		}
		int busca = 0;
		fscanf(entrada, "%d", &busca);
		for(i=0; i<busca; i++){
			fscanf(entrada, "%s", nome);
			funcao_imprimir(*R, nome);
		}
	}
	fclose(entrada);
	fclose(saida);
	return 0;
}
	
