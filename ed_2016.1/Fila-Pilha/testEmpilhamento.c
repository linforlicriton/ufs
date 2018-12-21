#include <stdio.h>
#include <stdlib.h>

// Estrutura de elemento
typedef struct elemento{
	char nome[50];
	int pagina;
	struct elemento *P;
}elemento;

// Estrutura de pilha
typedef struct pilha {
	int p;
	// Topo da pilha
	elemento *topo;
}pilha;

typedef struct fila{
	int paginas;
	char nome[50];
}fila;
fila *_fila;
typedef struct impressora{
	char nome[50];
	int status;
	pilha *P;
}impressora;

void empilhamento(){
	impressora *teste;
	teste = (impressora *)malloc(2*sizeof(impressora));
	for(int i=0; i<2; i++){
		scanf("%s", teste[i].nome);
		teste[i].P = NULL;
	}
	for(int i=0; i<2; i++){
		for(int j=0; j<5; j++){
			teste[i].P->paginas = (j+1);
		}
	}
}
	
