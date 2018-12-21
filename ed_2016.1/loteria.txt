#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

FILE *entrada;
FILE *saida;
unsigned int premio = 0;
unsigned int qtdApostas = 0;
unsigned int ganhadores_maior = 0;
unsigned int ganhadores_menor = 0;
unsigned int premio_maior = 0;
unsigned int premio_menor = 0;

typedef struct dados{
	char codigo[17];
	int numEscolhidos[15];
	unsigned int indice;
}dados;
dados *heap_min;
dados *heap_max;


dados *funcao_troca(dados *arvore, unsigned P, unsigned indice){
	dados *aux = (dados *)malloc(sizeof(dados));
	aux[0] = arvore[indice];
	arvore[indice] = arvore[P];
	arvore[P] = aux[0];
	aux = NULL;
	free(aux);
	return arvore;
}

unsigned int direita(unsigned int indice){
	indice = (2*indice) + 2;
	return indice;
}

unsigned int esquerda(unsigned int indice){
	indice = (2*indice)+1;
	return indice;
}

dados *funcao_heap_maior(dados *arvore, unsigned int tamanho, unsigned int indice){
	unsigned int P = indice;
	unsigned int E = esquerda(indice);
	unsigned int D = direita(indice);
	if(E < tamanho && arvore[E].indice > arvore[P].indice) P = E;
	if(D < tamanho && arvore[D].indice > arvore[P].indice) P = D;
	if(P != indice) {
		arvore = funcao_troca(arvore, P, indice);
		arvore = funcao_heap_maior(arvore, tamanho, P);
	}
	return arvore;
}

dados *funcao_heap_menor(dados *arvore, unsigned int tamanho, unsigned int indice){
	unsigned int P = indice;
	unsigned int E = esquerda(indice);
	unsigned int D = direita(indice);
	if(E < tamanho && arvore[E].indice < arvore[P].indice) P = E;
	if(D < tamanho && arvore[D].indice < arvore[P].indice) P = D;
	if(P != indice) {
		arvore = funcao_troca(arvore, P, indice);
		arvore = funcao_heap_menor(arvore, tamanho, P);
	}
	return arvore;
}

unsigned int funcao_busca(int *arvore, int tamanho, int *vetor){
	int acertos = 0;
	for(int i=0; i<tamanho; i++){
		for(int j=0; j<15; j++){
			if(arvore[i] == vetor[j]){
				acertos++;
			}
		}
	}
	return acertos;
}

void criar_heap_min(dados *arvore, unsigned int tamanho){
	for(int i=(tamanho-1)/2; i>0; i--){
		arvore = funcao_heap_menor(arvore, tamanho, i);
	}
	for(int i=0; i<tamanho; i++){
		arvore = funcao_heap_menor(arvore, tamanho, i);
	}
}

void criar_heap_max(dados *arvore, unsigned int tamanho){
	for(int i=(tamanho-1)/2; i>0; i--){
		arvore = funcao_heap_maior(arvore, tamanho, i);
	}
	for(int i=0; i<tamanho; i++){
		arvore = funcao_heap_maior(arvore, tamanho, i);
	}
}

void funcao_imprimir_maior(dados *arvore, unsigned int tamanho, unsigned int valor){
	while(arvore[0].indice == valor){
		ganhadores_maior++;
		fprintf(saida, "%s\n", arvore[0].codigo);
		arvore[0].indice = 0;
		funcao_heap_maior(arvore, tamanho, 0);
	}
	fflush(saida);
}

void funcao_imprimir_menor(dados *arvore, unsigned int tamanho, unsigned int valor){
	while(arvore[0].indice == valor){
		ganhadores_menor++;
		fprintf(saida, "%s\n", arvore[0].codigo);
		arvore[0].indice = 100;
		funcao_heap_menor(arvore, tamanho, 0);
	}
	fflush(saida);
}

void funcao_imprimir(dados *heap_max, dados *heap_min){
	//imprimir ganhador com maior acertos
	if(heap_max[0].indice > 1){
		fprintf(saida, "Faixa: %d acertos\n", heap_max[0].indice);
	}else{
		fprintf(saida, "Faixa: %d acerto\n", heap_max[0].indice);
	}
	fflush(saida);
	funcao_imprimir_maior(heap_max, qtdApostas, heap_max[0].indice);
	premio_maior = premio/2;
	premio_maior = premio_maior/ganhadores_maior;
	if(ganhadores_maior > 1)fprintf(saida, "%d ganhadores de R$%d\n", ganhadores_maior, premio_maior);
	if(ganhadores_maior == 1)fprintf(saida, "%d ganhador de R$%d\n", ganhadores_maior, premio_maior);
	
	fprintf(saida, "\n");
	//imprimir ganhador com menor acertos
	if(heap_min[0].indice > 1){
		fprintf(saida, "Faixa: %d acertos\n", heap_min[0].indice);
	}else{
		fprintf(saida, "Faixa: %d acerto\n", heap_min[0].indice);
	}
	fflush(saida);
	funcao_imprimir_menor(heap_min, qtdApostas, heap_min[0].indice);
	premio_menor = premio/2;
	premio_menor = premio_menor/ganhadores_menor;
	if(ganhadores_menor > 1)fprintf(saida, "%d ganhadores de R$%d\n", ganhadores_menor, premio_menor);
	if(ganhadores_menor == 1)fprintf(saida, "%d ganhador de R$%d\n", ganhadores_menor, premio_menor);
}

int main(int argc, char* argv[]){
	int numSorteados[10];
	entrada = fopen(argv[1], "r");
	saida = fopen(argv[2], "w");
	if(entrada == NULL){
        printf("ENTRADA INVALIDA\n");
        exit(1);
	}else{
		fscanf(entrada, "%d", &premio);
		fscanf(entrada, "%d", &qtdApostas);
		heap_max = (dados *)malloc(qtdApostas*sizeof(dados));
		heap_min = (dados *)malloc(qtdApostas*sizeof(dados));
		for(int i=0; i<10; i++){
			fscanf(entrada, "%d", &numSorteados[i]);
		}
		for(int i=0; i<qtdApostas; i++){
			fscanf(entrada, "%s", heap_max[i].codigo);
			strcpy(heap_min[i].codigo, heap_max[i].codigo);
			heap_max[i].indice = 0;
			for(int j=0; j<15; j++){
				fscanf(entrada, "%d", &heap_min[i].numEscolhidos[j]);
				//heap_max[i].indice+=funcao_busca(numSorteados,10, heap_max[i].numEscolhidos[j]);
			}
			heap_min[i].indice = funcao_busca(numSorteados, 10, heap_min[i].numEscolhidos);
			heap_max[i].indice = heap_min[i].indice;
		}
	}
	criar_heap_min(heap_min, qtdApostas);
	criar_heap_max(heap_max, qtdApostas);
	funcao_imprimir(heap_max, heap_min);
	fclose(entrada);
	fclose(saida);
	return 0;
}
