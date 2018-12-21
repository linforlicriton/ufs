#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *entrada;
FILE *saida;
unsigned int premio = 0;
unsigned int qtdApostas = 0;
unsigned int ganhadores_maior = 0;
unsigned int ganhadores_menor = 0;
unsigned int premio_maior = 0;
unsigned int premio_menor = 0;

typedef struct dados{
	unsigned long long int codigo;
	int numEscolhidos[15];
	unsigned int indice;
}dados;
dados *data;

void funcao_troca(dados *arvore, unsigned P, unsigned indice){
	dados *aux = (dados *)malloc(sizeof(dados));
	aux[0] = arvore[indice];
	arvore[indice] = arvore[P];
	arvore[P] = aux[0];
	aux = NULL;
	free(aux);
}

unsigned int direita(unsigned int indice){
	indice = (2*indice) + 2;
	return indice;
}

unsigned int esquerda(unsigned int indice){
	indice = (2*indice)+1;
	return indice;
}

void funcao_heap(dados *arvore, unsigned int tamanho, unsigned int indice){
	unsigned int P = indice;
	unsigned int E = esquerda(indice);
	unsigned int D = direita(indice);
	if(E < tamanho && arvore[E].indice > arvore[P].indice) P = E;
	if(D < tamanho && arvore[D].indice > arvore[P].indice) P = D;
	if(P != indice) {
		funcao_troca(arvore, P, indice);
		funcao_heap(arvore, tamanho, P);
	}
}

unsigned int funcao_busca(int *arvore, int tamanho, int valor){
	for(int i=0; i<tamanho; i++){
		if(valor == arvore[i]){
			return 1;
		}
	}
	return 0;
}

void funcao_imprimir_maior(dados *arvore, unsigned int tamanho, unsigned int indice, unsigned int valor){
	unsigned int P = indice;
	if(arvore[P].indice == valor){
		ganhadores_maior++;
		fprintf(saida, "%llx\n", arvore[P].codigo);
		fflush(saida);
	}
	P++;
	if(P < (tamanho-1)) {
		funcao_imprimir_maior(arvore, tamanho, P, valor);
	}
}

void funcao_imprimir_menor(dados *arvore, unsigned int tamanho, unsigned int indice, unsigned int valor){
	unsigned int P = indice;
	if(arvore[P].indice == valor){
		ganhadores_menor++;
		fprintf(saida, "%llx\n", arvore[P].codigo);
		fflush(saida);
	}
	P = P-1;
	if(P >= 1) {
		funcao_imprimir_menor(arvore, tamanho, P, valor);
	}
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
		fscanf(entrada, "%d %d %d %d %d %d %d %d %d %d", &numSorteados[0], &numSorteados[1], &numSorteados[2], &numSorteados[3], &numSorteados[4],
		&numSorteados[5], &numSorteados[6], &numSorteados[7], &numSorteados[8], &numSorteados[9]);
		data = (dados *)malloc(qtdApostas*sizeof(dados));
		for(int i=0; i<5; i++){
			fscanf(entrada, "%llx %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &data[i].codigo, &data[i].numEscolhidos[0], &data[i].numEscolhidos[1],
			&data[i].numEscolhidos[2], &data[i].numEscolhidos[3], &data[i].numEscolhidos[4], &data[i].numEscolhidos[5], &data[i].numEscolhidos[6],
			&data[i].numEscolhidos[7], &data[i].numEscolhidos[8], &data[i].numEscolhidos[9], &data[i].numEscolhidos[10], &data[i].numEscolhidos[11],
			&data[i].numEscolhidos[12], &data[i].numEscolhidos[13], &data[i].numEscolhidos[14]);
			
			data[i].indice = 0;
			/*
			printf("%llx %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", data[i].codigo, data[i].numEscolhidos[0], data[i].numEscolhidos[1],
			data[i].numEscolhidos[2], data[i].numEscolhidos[3], data[i].numEscolhidos[4], data[i].numEscolhidos[5], data[i].numEscolhidos[6],
			data[i].numEscolhidos[7], data[i].numEscolhidos[8], data[i].numEscolhidos[9], data[i].numEscolhidos[10], data[i].numEscolhidos[11],
			data[i].numEscolhidos[12], data[i].numEscolhidos[13], data[i].numEscolhidos[14]);
			*/
		}
	}
	
	for(int i = 0; i<qtdApostas; i++){
		
		for(int j = 0; j<15; j++){
			data[i].indice += funcao_busca(numSorteados, 10, data[i].numEscolhidos[j]);
		}
		
	}
	funcao_heap(data, qtdApostas, 0);
	//imprimir ganhador com maior acertos
	fprintf(saida, "Faixa: %d acertos\n", data[0].indice);
	fflush(saida);
	printf("%d\n", data[0].indice);
	funcao_imprimir_maior(data, qtdApostas, 0, data[0].indice);
	premio_maior = premio/2;
	premio_maior = premio_maior/ganhadores_maior;
	if(ganhadores_maior > 1)fprintf(saida, "%d ganhadores de R$%d\n", ganhadores_maior, premio_maior);
	if(ganhadores_maior == 1)fprintf(saida, "%d ganhador de R$%d\n", ganhadores_maior, premio_maior);
	
	fprintf(saida, "\n");
	
	//imprimir ganhador com menor acertos
	fprintf(saida, "Faixa: %d acertos\n", data[qtdApostas-1].indice);
	fflush(saida);
	funcao_imprimir_menor(data, qtdApostas, qtdApostas-1, data[qtdApostas-1].indice);
	premio_menor = premio/2;
	premio_menor = premio_menor/ganhadores_menor;
	if(ganhadores_menor > 1)fprintf(saida, "%d ganhadores de R$%d\n", ganhadores_menor, premio_menor);
	if(ganhadores_menor == 1)fprintf(saida, "%d ganhador de R$%d\n", ganhadores_menor, premio_menor);
	
	fclose(entrada);
	fclose(saida);
	return 0;
}
