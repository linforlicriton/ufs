#include <stdio.h>
#include <stdlib.h>

int in = 1;

typedef struct med3{
	int x;
	unsigned int indice;
}med3;

void trocar(int *V1, int *V2){
	int *aux = (int *)malloc(sizeof(int));
	aux[0] = V1[0];
	V1[0] = V2[0];
	V2[0] = aux[0];
	in++;
}

int hoare(int V[], int inicio, int fim) {
	in++;
	int pivo = V[inicio];
	int i = inicio;
	int j = fim;
	while(i < j) {
		while(j > i && V[j] >= pivo) j--;
		while(i < j && V[i] < pivo) i++;
		if(i < j) trocar(&V[i], &V[j]);
	}
	return j;
}

void med3_trocar(med3 *V1, med3 *V2){
	med3 *aux = (med3 *)malloc(sizeof(med3));
	aux[0] = V1[0];
	V1[0] = V2[0];
	V2[0] = aux[0];
}

void ordenacao_por_insercao(med3 *V, int n) {
	int i, j;
	for(i = 1; i < n; i = i + 1)
		for(j = i; j > 0 && V[j - 1].x > V[j].x; j--)
	med3_trocar(&V[j], &V[j - 1]);
}

int funcao_mediana2(int *V, int inicio, int fim){
	int n = fim - inicio + 1;
	int x = n/4 + inicio;
	int y = n/2 + inicio;
	int z = 3*n/4 + inicio;
	med3 *a = (med3 *)malloc(3*sizeof(med3));
	a[0].x = V[x]; a[0].indice = x;
	a[1].x = V[y]; a[1].indice = y;
	a[2].x = V[z]; a[2].indice = z;
	ordenacao_por_insercao(a, 3);
	int k = a[1].indice;
	trocar(&V[k], &V[inicio]);
	return hoare(V, inicio, fim);
}

void quicksort_hoare(int V[], int inicio, int fim) {
	if(inicio < fim) {
		in++;
		int pivo = funcao_mediana2(V, inicio, fim);
		quicksort_hoare(V, inicio, pivo);
		quicksort_hoare(V, pivo + 1, fim);
	}
}

int main(){
	int vetor1[6] = {-23, 10, 7, -34, 432, 3};
	int vetor2[4] = {955, -32, 1, 9};
	int vetor3[7] = {834, 27, 39, 19, 3, -1, -33};
	int vetor4[10] = {847, 38, -183, -13, 94, -2, -42, 54, 28, 100};
	
	quicksort_hoare(vetor1, 0, 5);
	for(int i=0; i<6; i++){
		printf("%d ", vetor1[i]);
	}printf("\n");
	printf("%d\n", in); in = 1;
	
	quicksort_hoare(vetor2, 0, 3);
	for(int i=0; i<4; i++){
		printf("%d ", vetor2[i]);
	}printf("\n");
	printf("%d\n", in); in = 1;
	
	quicksort_hoare(vetor3, 0, 6);
	for(int i=0; i<7; i++){
		printf("%d ", vetor3[i]);
	}printf("\n");
	printf("%d\n", in); in = 1;
	
	quicksort_hoare(vetor4, 0, 9);
	for(int i=0; i<10; i++){
		printf("%d ", vetor4[i]);
	}printf("\n");
	printf("%d\n", in);
	return 0;
}

