//Edit: status do transporte e tamanho do vetor carga e usar realloc na capacidade da carga

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *entrada = NULL;
FILE *saida = NULL;

int estado = 0;
int acabou = 0;
unsigned int carga = 0;

typedef struct entrega{
	char nivel[15];
	unsigned int peso;
	unsigned int ordem;
	unsigned int prioridade;
}entrega;

typedef struct veiculo{
	entrega *pacote;
	unsigned int size;
	unsigned int ocupado;
	unsigned int peso;
	unsigned int posicao;
}veiculo;

void copiar(entrega *S, entrega *E, unsigned int tamanho){
	for(int i=0; i<tamanho; i++){
		S[i] = E[i];
	}
}

void intercalar(entrega *S, entrega *E, int ini, int meio, int fim) {
	int i = ini, j = meio + 1, k = ini;
	while(i <= meio && j <= fim) {
		if(E[i].prioridade <= E[j].prioridade){
			if(E[i].prioridade == E[j].prioridade){
				if(E[i].ordem < E[j].ordem){
					S[k++] = E[i++];
				}else{
					S[k++] = E[j++];
				}
			}else{
				S[k++] = E[i++];
			}
		}else{
		 S[k++] = E[j++];
	 }
	}
	if(i > meio) copiar(&S[k], &E[j], fim - j + 1);
	else copiar(&S[k], &E[i], meio - i + 1);
	copiar(&E[ini], &S[ini], fim - ini + 1);
}

void mergesort(entrega *S, entrega *E, int ini, int fim) {
	int meio = ini + (fim - ini) / 2;
	if(ini < fim) {
		mergesort(S, E, ini, meio);
		mergesort(S, E, meio + 1, fim);
	}
	intercalar(S, E, ini, meio, fim);
}

veiculo *esvaziar(veiculo *V, unsigned int qtd){
	for(int i=0; i<qtd; i++){
		if(V[i].posicao != 0){
			int n = V[i].posicao + 1;
			entrega *S = (entrega *)calloc(n,sizeof(entrega));
			mergesort(S, V[i].pacote, 0, V[i].posicao);
			fprintf(saida, "[V%d]", i);
				for(int j=0; j<=V[i].posicao; j++){
					if(j==0) fprintf(saida, "%s",V[i].pacote[j].nivel);
					else fprintf(saida, " %s",V[i].pacote[j].nivel);
				}fprintf(saida, "\n");
			free(V[i].pacote);
			V[i].pacote = (entrega *)calloc(1000, sizeof(entrega));
			V[i].peso = 0;
			V[i].posicao = 0;
			V[i].ocupado = 0;
		}
	}
	fflush(saida);
	return V;
}

veiculo *andamento(entrega *E, veiculo *V, unsigned int qtdV){
	for(int i=0; i<qtdV; i++){
		if((E->peso + V[i].peso) <= carga && V[i].ocupado != 1){
			int aux = V[i].posicao;
			if(aux >= 1000) V[i].pacote = (entrega *)realloc(V[i].pacote, (aux+1)*sizeof(entrega));
			V[i].pacote[aux] = E[0];
			V[i].posicao++;
			V[i].peso += E->peso;
			return V;
		}else{
			V[i].ocupado = 1;
		}
	}
	V = esvaziar(V, qtdV);
	V = andamento(E, V, qtdV);
	return V;
}

int main(int argc, char* argv[]){
	entrada = fopen(argv[1], "r");
	saida = fopen(argv[2], "w");
    if(entrada == NULL){
        printf("ENTRADA INVALIDA\n");
        exit(1);
	}else{
		unsigned int qtdVeiculo;
		unsigned int qtdPacotes;
		char prio[3];
		entrega *dados;
		veiculo *transporte;
		fscanf(entrada, "%d %d", &qtdVeiculo, &carga);
        fscanf(entrada, "%d", &qtdPacotes);
        dados = (entrega *)malloc(qtdPacotes*sizeof(entrega));
        transporte = (veiculo *)malloc(qtdVeiculo*sizeof(veiculo));
        for(int i=0; i<qtdVeiculo; i++){
			transporte[i].ocupado = 0;
			transporte[i].peso = 0;
			transporte[i].posicao = 0;
			transporte[i].pacote = (entrega *)calloc(1000, sizeof(entrega));
		}
        for(int i=0; i<qtdPacotes; i++){
			fscanf(entrada, "%s %d", dados[i].nivel, &dados[i].peso);
			prio[0] = dados[i].nivel[0];
			prio[1] = dados[i].nivel[1];
			prio[2] = '\0';
			if(strcmp(prio, "XP")==0) dados[i].prioridade = 3;
			if(strcmp(prio, "PT")==0) dados[i].prioridade = 2;
			if(strcmp(prio, "EC")==0) dados[i].prioridade = 1;
			transporte = andamento(&dados[i], transporte, qtdVeiculo);
		}
		transporte = esvaziar(transporte, qtdVeiculo);
	}
    fclose(entrada);
	fclose(saida);
	return 0;
}
