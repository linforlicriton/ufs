#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *entrada;
FILE *saida;
size_t tamanho;
size_t capacidade;
size_t inicio;
int qtdImpressora = 0;
int totalpaginas = 0;

typedef struct fila{
	int paginas;
	char nome[50];
}fila;

typedef struct impressora{
	char nome[50];
	int status;
	int tempo;//paginas
	elemento *E;
}impressora;
impressora *impr;


// Estrutura de elemento
typedef struct elemento{
	char nome[50];
	int paginas;
	struct elemento *P;
}elemento;

// Estrutura de pilha
typedef struct pilha {
	// Topo da pilha
	elemento* topo;
}pilha;

void sistema_impressao(fila *aux){
	for(int i=0; i<qtdImpressora; i++){
		if(impr[i].status == 0){
			impr[i].status = 1;
			impr[i].tempo = aux->paginas;
			//Empilhando
			impr[i].E = (elemento *)malloc(sizeof(elemento));
			strcpy(impr[i].E.nome, aux[inicio].nome);
			impr[i].E->paginas = aux->paginas;
			printf("%s %dp\n", impr[i].E->nome, impr[i].E->paginas);
			return;
		}
	}
	
}

int main(int argc, char* argv[]){
	//impressora *impr;
	fila *arquivo;
	int flag = 0;
	int qtd;
	entrada = fopen(argv[1], "r");
	saida = fopen(argv[2], "w");
    if(entrada == NULL){
        printf("ENTRADA INVALIDA\n");
        exit(4);
        }else{
            // lê linha do arquivo
            while(fscanf(entrada, "%d", &qtd)!=EOF){
				if(flag==0){
					qtdImpressora = qtd;
					impr = (impressora *)malloc(qtd*sizeof(impressora));
					for(int i=0; i<qtd; i++){
						fscanf(entrada, "%s", impr[i].nome);
						impr[i].status = 0;
						flag=1;
					}
				}else{
					capacidade = qtd;
					arquivo = (fila *)malloc(capacidade*sizeof(fila));
					for(int i=0; i<qtd; i++){
						fscanf(entrada, "%s %d", arquivo[(inicio+tamanho)%capacidade].nome, &arquivo[(inicio+tamanho)%capacidade].paginas);
						totalpaginas += arquivo[(inicio+tamanho)%capacidade].paginas;
						tamanho++;
						sistema_impressao(arquivo);
					}
				}
			}   
        }
	fclose(entrada);
	fclose(saida);
	return 0;
}
