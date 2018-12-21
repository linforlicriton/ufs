#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *entrada;
FILE *saida;
FILE *in;

unsigned int num_palavras = 0;
int E = 0;
int D = 0;

typedef struct dados{
	char palavra[40];
}dados;
dados *data;

typedef struct definicao{
	dados *def;
	char nome[40];
	unsigned char altura;
	unsigned int qtdPalavra;
	struct definicao *D;
	struct definicao *E;
}definicao;
struct definicao **R;

unsigned char altura(definicao* r){
    return r?r->altura:0;
}

int bfactor(definicao* r){
    return altura(r->D)-altura(r->E);
}

void fixheight(definicao* r){
    unsigned char altura_E = altura(r->E);
    unsigned char altura_D = altura(r->D);
    r->altura = (altura_E>altura_D?altura_E:altura_D)+1;
}

definicao *funcao_copiar(definicao *temp,char nome[], int palavras){
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
	fixheight(eixo);
	fixheight(raiz);
	return eixo;
}

definicao *rotacao_dir(definicao *raiz) {
	definicao *eixo = raiz->E;
	raiz->E = eixo->D;
	eixo->D = raiz;
	fixheight(eixo);
	fixheight(raiz);
	return eixo;
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

definicao *fator_balanceamento(definicao* p) // p node balance
{
    fixheight(p);
    if( bfactor(p)==2 )
    {
        if(bfactor(p->D) > 0){
            p = rotacao_dir(p);
		}else{
			p = rotacao_dir_esq(p);
		}
    }
    if( bfactor(p)==-2 )
    {
        if(bfactor(p->E) < 0){
            p = rotacao_dir(p);
		}else{
			p = rotacao_esq_dir(p);
		}
    }
    fixheight(p);
    return p; // no balance needed
}

void funcao_compara(definicao **Raiz,char nome[], int palavras){
	if((*Raiz) == NULL){
		(*Raiz) = (definicao *)malloc(sizeof(definicao));
		(*Raiz)->def = (dados *)malloc(15*sizeof(dados));
		(*Raiz)->D = NULL;
		(*Raiz)->E = NULL;
		(*Raiz) = funcao_copiar((*Raiz), nome, palavras);
		(*Raiz)->altura = 1;
		return;
	}else{
		if(strncmp((*Raiz)->nome, nome, sizeof((*Raiz)->nome))==0) return;
		if(strncmp(nome, (*Raiz)->nome, sizeof((*Raiz)->nome)) < 0){
			funcao_compara(&(*Raiz)->E, nome, palavras);
			
		}
		if(strncmp(nome,(*Raiz)->nome, sizeof((*Raiz)->nome)) > 0){
			funcao_compara(&(*Raiz)->D, nome, palavras);
		}
		(*Raiz) = fator_balanceamento(*Raiz);
	}
	fprintf(in, "%s\n", (*Raiz)->nome);
	fflush(in); 
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
    char nome[40];
    fscanf(entrada, "%d", &num_palavras);
    inicializar();
		for(int i=0; i<num_palavras; i++){
			fscanf(entrada, "%s", nome);
			fscanf(entrada, "%d", &palavras);
			data = (dados *)calloc(10,(sizeof(dados)));
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
	
