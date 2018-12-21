#include <stdio.h>
#include <stdlib.h>

int in = 1;

void trocar(int *V1, int *V2){
	int *aux = (int *)malloc(sizeof(int));
	aux[0] = V1[0];
	V1[0] = V2[0];
	V2[0] = aux[0];
	in++;
}

int absolute(int x){
	if(x<0) x = x*(-1);
	return x;
}

int particionar(int V[], int inicio, int fim) {
	in++;
	int pivo = V[fim];
	int i = inicio - 1;
	int j;
	for(j = inicio; j < fim; j++) {
		if(V[j] <= pivo) {
			i = i + 1;
			trocar(&V[i], &V[j]);
		}
	}
	trocar(&V[i + 1], &V[fim]);
	return i + 1;
}

int randomico(int V[], int inicio, int fim){
	int k = absolute(V[inicio]);
	int i = inicio + k%(fim - inicio + 1);
	trocar(&V[fim], &V[i]);
	return particionar(V, inicio, fim);
}

int funcao_mediana(int *V, int inicio, int fim){
	int n = fim - inicio + 1;
	int V1 = V[n/4];
	int V2 = V[n/2];
	int V3 = V[(3*n)/4];
	if((V1 >= V2 && V1 <= V3)||(V1 >= V3 && V1 <= V2)){
		trocar(&V[fim], &V[n/4]);
		
	}else if((V2 >= V1 && V2 <= V3) || (V2 >= V3 && V2 <= V1)){
		trocar(&V[fim], &V[n/2]);
	}else if((V3 >= V1 && V3 <= V2) || (V3 >= V2 && V3 <= V1)){
		trocar(&V[fim], &V[(3*n)/4]);
	}
	return particionar(V, inicio, fim);
}

void quicksort_particionar(int V[], int inicio, int fim) {
	if(inicio < fim) {
		in++;
		int pivo = funcao_mediana(V, inicio, fim);
		//int pivo = particionar(V, inicio, fim);
		//int pivo = randomico(V, inicio, fim);
		quicksort_particionar(V, inicio, pivo - 1);
		quicksort_particionar(V, pivo + 1, fim);
	}
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

int funcao_mediana2(int *V, int inicio, int fim){
	int n = fim - inicio + 1;
	int V1 = V[n/4];
	int V2 = V[n/2];
	int V3 = V[(3*n)/4];
	if((V1 > V2 && V1 < V3)||(V1 > V3 && V1 < V2)){
		trocar(&V[n/4], &V[inicio]);
	}else if((V2 > V1 && V2 < V3) || (V2 > V3 && V2 < V1)){
		trocar(&V[n/2], &V[inicio]);
	}else if((V3 > V1 && V3 < V2) || (V3 > V2 && V3 < V1)){
		trocar(&V[(3*n)/4], &V[inicio]);
	}else if(V1 == V2 && V2 == V3){
		trocar(&V[n/4], &V[inicio]);
	}
	return hoare(V, inicio, fim);
}


int randomico2(int V[], int inicio, int fim){
	int k = absolute(V[inicio]);
	int i = inicio + k%(fim - inicio + 1);
	trocar(&V[inicio], &V[i]);
	return hoare(V, inicio, fim);
}

void quicksort_hoare(int V[], int inicio, int fim) {
	if(inicio < fim) {
		in++;
		//int pivo = hoare(V, inicio, fim);
		//int pivo = randomico2(V, inicio, fim);
		int pivo = funcao_mediana2(V, inicio, fim);
		quicksort_hoare(V, inicio, pivo);
		quicksort_hoare(V, pivo + 1, fim);
	}
}

int main(){
	int vetor[6] = {-23, 10, 7, -34, 432, 3};
	quicksort_hoare(vetor, 0, 5);
	for(int i=0; i<6; i++){
		printf("%d ", vetor[i]);
	}printf("\n");
	printf("%d\n", in);
	return 0;
}
