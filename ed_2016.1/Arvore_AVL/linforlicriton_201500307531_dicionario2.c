#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *entrada;
FILE *saida;

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

int fator(definicao* r){
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

definicao* rotacao_esq(definicao* q) // the left rotation round q
{
    definicao* p = q->D;
    q->D = p->E;
    p->E = q;
    fixheight(q);
    fixheight(p);
    return p;
}

definicao *rotacao_dir(definicao* p) // the right rotation round p
{
    definicao* q = p->E;
    p->E = q->D;
    q->D = p;
    fixheight(p);
    fixheight(q);
    return q;
}

definicao *fator_balanceamento(definicao* p) // p node balance
{
    fixheight(p);
    if(fator(p)==2)
    {
        if(fator(p->D) < 0 )
            p->D = rotacao_dir(p->D);
        return rotacao_esq(p);
    }
    if(fator(p)==-2)
    {
        if(fator(p->E) > 0  )
            p->E = rotacao_esq(p->E);
        return rotacao_dir(p);
    }
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
	entrada = fopen(argv[1], "r+");
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
	
