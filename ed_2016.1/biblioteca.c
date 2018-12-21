#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *entrada;
FILE *saida;
int tamanho = 0;
unsigned int cont_binaria = 0;
unsigned int cont_interpolada = 0;
int indicador = 0;

typedef struct biblioteca{
	unsigned long long int codigo;
	char nome_autor[50];
	char nome_livro[100];
	int tamanho;
}biblioteca;
biblioteca *global;

typedef struct code{
	unsigned long long int codigo;
}code;

void busca_interpolada(unsigned long long int id){
	unsigned int inicio;
	inicio = 0;
	unsigned int fim;
	fim = tamanho-1;
	unsigned int long long h = 0;
	unsigned int flag = 0;
	cont_interpolada = 0;
		while(flag != 2){
			//funcao de herustica
			flag = 0;
			h = (inicio + (global[fim].codigo-global[inicio].codigo)%(fim-inicio+1));
			cont_interpolada++;
			if(global[h].codigo == id){
				return;
			}else if(inicio == fim){
				return;
			}else if(global[h].codigo > id){
				if(inicio != h){
					fim = h-1;
					flag = 1;
					//printf("%d %d\n", inicio, fim);
				}
			}else if(global[h].codigo < id){
				if(fim != h){
					inicio = h+1;
					flag = 1;
					//printf("%d %d\n", inicio, fim);
				}
			}
			if(flag == 0){
				break;
			}
		}
	return;
}

int busca_binaria(unsigned long long int id){
	int flag = 0;
	int indice = 0;
	int tam = tamanho-1;
	int h = 0;
		while(flag != 2){
			h = (indice+tam)/2;
			cont_binaria++;
			if(global[h].codigo == id){
				flag = 2;
			}else if(h == (indice-1)){
				h = -1;
				flag = 2;
			}else if(global[h].codigo>id){
				tam = h-1;
				flag = 1;
			}else if(global[h].codigo <id){
					indice = h+1;
					flag = 1;
			}
		}
	return h;
}

int main(int argc, char* argv[]){
	char vet[10];
	char vet1[10];
	int aux = 0;
	int flag = 0;
	code *cod;
	entrada = fopen(argv[1], "r");
	saida = fopen(argv[2], "w");
	if(entrada == NULL){
        printf("ENTRADA INVALIDA\n");
        exit(4);
	}else{
		if(flag == 0){
			fscanf(entrada, "%d", &aux);
			global = (biblioteca *)malloc(aux*sizeof(biblioteca));
			tamanho = aux;
			int i=0;
			for(i=0; i<aux; i++){
				fscanf(entrada, "%llu", &global[i].codigo);
				fscanf(entrada, "%[*' ']s", vet);
				fscanf(entrada, "%[^|]s", global[i].nome_autor);
				fscanf(entrada, "%[*|]s", vet1);
				fscanf(entrada, "%[^\n]s", global[i].nome_livro);
				}flag = 1;
			}
		if(flag == 1){
			fscanf(entrada, "%d", &aux);
			cod = (code *)malloc(aux*sizeof(code));
			int i = 0;
			while(i!=aux){
				fscanf(entrada, "%llu", &cod[i].codigo);
				i++;
				}
			}
		}
	int i;
	int temp;
	int binaria_vitorias = 0;
	int interpolada_vitorias = 0;
	int passos_binaria = 0;
	int passos_interpolada = 0;
	for(i=0; i<aux; i++){
		
			temp = (busca_binaria(cod[i].codigo));
			(busca_interpolada(cod[i].codigo));
			if(temp == -1){
				fprintf(saida, "[%llu] BINARY: %d, INTERPOLATION: %d\n", cod[i].codigo, cont_binaria, cont_interpolada);
				fprintf(saida, "ISBN NOT FOUND\n");
				//fflush(saida);
			}else{
			fprintf(saida, "[%llu] BINARY: %d, INTERPOLATION: %d\n", global[temp].codigo, cont_binaria, cont_interpolada);
			fprintf(saida, "Author: %s\n", global[temp].nome_autor);
			fprintf(saida, "Title: %s\n", global[temp].nome_livro);
			//fflush(saida);
			}
			passos_binaria+=cont_binaria;
			passos_interpolada+=cont_interpolada;
			if(cont_binaria == cont_interpolada){
				interpolada_vitorias++;
			}else if(cont_binaria < cont_interpolada){
				binaria_vitorias++;
			}else if(cont_binaria > cont_interpolada){
				interpolada_vitorias++;
			}
			cont_binaria = 0;
			//cont_interpolada = 0;
		fflush(saida);
	}
	passos_binaria = passos_binaria/aux;
	passos_interpolada = passos_interpolada/aux;
	fprintf(saida, "\n");
	fprintf(saida, "SEARCH RESULTS\n");
	fprintf(saida, "BINARY: %d @ ~%d STEPS\n", binaria_vitorias, passos_binaria);
	fprintf(saida, "INTERPOLATION: %d @ ~%d STEPS\n", interpolada_vitorias, passos_interpolada);
	fclose(entrada);
	fclose(saida);
	return 0;
}
