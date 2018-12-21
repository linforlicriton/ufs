#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct dados{
	char data[256];
}dados;

typedef struct pacotes{
	int num;
	int tam;
	int indice;
	dados *p;
}pacotes;

FILE *input = NULL;
FILE *output = NULL;

unsigned int inicio = 0;
unsigned int ultimo = 0;
unsigned int indicador = 0;
unsigned int tamanho = 0;
unsigned int remover = 0;

pacotes *funcao_troca(pacotes *arvore, unsigned P, unsigned indice){
	pacotes *aux = (pacotes *)malloc(sizeof(pacotes));
	aux[0] = arvore[indice];
	arvore[indice] = arvore[P];
	arvore[P] = aux[0];
	return arvore;
}

unsigned int direita(int i){
	return (2*i + 2);
}

unsigned int esquerda(int i){
	return (2*i + 1);
}

pacotes *funcao_heap(pacotes *arvore, unsigned int tamanho, unsigned int indice){
	unsigned int P = indice;
	unsigned int E = esquerda(indice);
	unsigned int D = direita(indice);
	if(E < tamanho && arvore[E].num < arvore[P].num) P = E;
	if(D < tamanho && arvore[D].num < arvore[P].num) P = D;
	if(P != indice) {
		arvore = funcao_troca(arvore, P, indice);
		arvore = funcao_heap(arvore, tamanho, P);
	}
	return arvore;
}

pacotes *criar_heap(pacotes *arvore, int n){
	for(int i=(n-1)/2; i>0; i--){
		arvore = funcao_heap(arvore, n, i);
	}
	arvore = funcao_heap(arvore, n, 0);
	return arvore;
}

int detector(pacotes *p, int total){
	for(int i=0; i<total; i++){
		if(p[i].num == 9999999){
			return i;
		}
	}
	return -1;
}

pacotes *heapsort(pacotes *arvore, int n){
	arvore = criar_heap(arvore, n);
	if(arvore[0].num == inicio){
		fprintf(output, "[%d]", indicador);
		while(arvore[0].num == inicio){
			if(arvore[0].tam >= 512) arvore[0].tam = 512;
			int aux = arvore[0].tam;
			for(int i=0; i<aux; i++){
				fprintf(output, " %s", arvore[0].p[i].data);
			}
			arvore = funcao_troca(arvore, n-1, 0);
			arvore = funcao_heap(arvore, n-1, 0);
			n--;
			tamanho--;
			remover++;
			inicio++;
		}
		fprintf(output, "\n");
		fflush(output);
		indicador++;
	}
	return arvore;
}

void inicializar(pacotes *p, int tam){
	for(int i=0; i<tam; i++){
		p[i].num = 9999999;
		p[i].indice = i;
	}
}	

int main(int argc, char* argv[]){
	input = fopen(argv[1], "r");
	output = fopen(argv[2], "w");
	if(input == NULL){
        printf("ENTRADA INVALIDA\n");
        exit(1);
	}else{
		int total_pacotes;
		int qtd_pacotes;
		int flag = 0;
		pacotes *pac;
		fscanf(input, "%d %d", &total_pacotes, &qtd_pacotes);
		pac = (pacotes *)malloc(total_pacotes*sizeof(pacotes));
		inicializar(pac, total_pacotes);
		tamanho = total_pacotes;
		for(int i=0; i<total_pacotes; i++){
			flag++;
			fscanf(input, "%d %d", &pac[ultimo].num, &pac[ultimo].tam);
			//if(pac[ultimo].tam >= 512) pac[ultimo].tam = 512;
			int aux = pac[ultimo].tam;
			pac[ultimo].p = (dados *)malloc(aux*sizeof(dados));
			for(int j=0; j<aux; j++){
				fscanf(input, "%s", pac[ultimo].p[j].data);
			}
			if(flag == qtd_pacotes){
				pac = heapsort(pac, tamanho);
				flag = 0;
				remover = 0;
			}
			ultimo = detector(pac, total_pacotes);
		}
		if(tamanho != 0) pac = heapsort(pac, tamanho);
	}
	fclose(input);
	fclose(output);
	input = output = NULL;
	return 0;
}
