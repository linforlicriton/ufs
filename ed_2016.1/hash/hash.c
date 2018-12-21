#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *entrada;
FILE *saida;

typedef struct lista{
	char nome[100];
}lista;

typedef struct servidores{
	lista *P;
	int status;
	int indice;
}servidores;


int calculo_hash(char nome[],int servers){
	int i;
	int resultado = nome[0];
	for(i=1; i<100; i++){
	if(nome[i] == '\0'){
		break;
		}else if(nome[i] == ' '){
			}else{
				resultado = resultado ^ nome[i];
			}
		}
	return resultado;
}

int main(int argc, char* argv[]){
	entrada = fopen(argv[1], "r");
	saida = fopen(argv[2], "w");
	servidores *serv;
	int servers;
	int capacidade;
	int qtd;
	int aux;
	int indice = 0;
	int checksum = 0;
	char aux_nome[100];
	if(entrada == NULL){
        printf("ENTRADA INVALIDA\n");
        exit(4);
    }else{
		fscanf(entrada, "%d %d", &servers, &capacidade);
		serv = (servidores *)malloc(servers*sizeof(servidores));
		int i;
		for(i=0; i<servers; i++){
			serv[i].P = (lista *)malloc(capacidade*sizeof(lista));
		}
		fscanf(entrada, "%d", &qtd);
		int posicao = 0;
		lista *temp;
		temp = (lista *)malloc(sizeof(lista));
		for(i=0; i<qtd; i++){
			fscanf(entrada, "%d", &aux);
			for(int j=0; j<aux; i++){
				fscanf(entrada, "%[^' ']s", aux_nome);
				checksum += calculo_hash(aux_nome,servers);
			}
			indice = (33*checksum*aux)%servers;
			//indice = calculo_hash(aux_nome,servers);
			posicao = serv[indice].indice;
			if(serv[indice].status == 1){
				int resultado = aux_nome[0];
				for(i=1; i<100; i++){
				if(aux_nome[i] == '\0'){
					break;
					}else if(aux_nome[i] == ' '){
						}else{
							resultado = resultado ^ aux_nome[i];
						}
					}
				int indice1 = 0;
				indice1 = (104729*resultado + 123)%(servers-1);
				strcpy(temp->nome, aux_nome);
				serv[indice1].P[posicao] = *temp;
				if(serv[indice1].status == 0){
					fprintf(saida, "S%d->S%d\n", indice, indice1);
					fprintf(saida, "[S%d] %s\n", indice1, serv[indice1].P[posicao].nome);
				}else{
					exit(1);
				}
			}else{
				strcpy(temp->nome, aux_nome);
				serv[indice].P[posicao] = *temp;
				if(serv[indice].indice == 0){
					fprintf(saida, "[S%d] %s\n", indice, serv[indice].P[posicao].nome);
				}else{
					fprintf(saida, "[S%d] %s,", indice, serv[indice].P[0].nome);
					for(i=1; i<=posicao; i++){
						fprintf(saida, " %s", serv[indice].P[i].nome);
					}
					fprintf(saida, "\n");
				}
			}
			serv[indice].indice+=1;
			if(serv[indice].indice == capacidade){
				serv[indice].status = 1;
			}
			fflush(saida);
			checksum = 0;
		}
	}
	fclose(entrada);
	fclose(saida);
	return 0;
}
