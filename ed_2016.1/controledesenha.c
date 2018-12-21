//Nota: Alocar primeiramente espaço para um vetor e depois utilizar a ideia de heap

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *entrada = NULL;
FILE *saida = NULL;

int size = 0;

typedef struct data{
	char nomeOrgao[51];
	unsigned int numAtendentes;
}data;

typedef struct data_input{
	char nome[51];
	char orgao[51];
	unsigned int idade;
	char hora[10];
}data_input;
data_input *input;

typedef struct org{
	data *dados;
	data_input *dados_input;
	int temp;
}org;
org *O = NULL;

data_input *funcao_troca(data_input *arvore, unsigned P, unsigned indice){
	data_input *aux = (data_input *)malloc(sizeof(data_input));
	aux[0] = arvore[indice];
	arvore[indice] = arvore[P];
	arvore[P] = aux[0];
	aux = NULL;
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

data_input *funcao_heapfy(data_input *arvore, unsigned int tamanho, unsigned int indice){
	unsigned int P = indice;
	unsigned int E = esquerda(indice);
	unsigned int D = direita(indice);
	if(arvore[P].idade != 0){
		if(E < tamanho){
			if(arvore[P].idade >= 60 && arvore[E].idade >=60){
				if(strcmp(arvore[P].hora, arvore[E].hora) > 0){
					P = E;
				}else if(strcmp(arvore[P].hora, arvore[E].hora) == 0){
					if(arvore[P].idade < arvore[E].idade){
						P = E;
					}
				}
			}else if(arvore[P].idade < 60 && arvore[E].idade >= 60){
				P = E;
			}else if(arvore[P].idade < 60 && arvore[E].idade < 60){
				if(strcmp(arvore[P].hora, arvore[E].hora) > 0){
					P = E;
				}else if(strcmp(arvore[P].hora, arvore[E].hora) == 0){
					if(arvore[P].idade < arvore[E].idade){
						P = E;
					}
				}
			}
		}
		if(D < tamanho){
			if(arvore[P].idade >= 60 && arvore[D].idade >=60){
				if(strcmp(arvore[P].hora, arvore[D].hora) > 0){
					P = D;
				}else if(strcmp(arvore[P].hora, arvore[D].hora) == 0){
					if(arvore[P].idade < arvore[D].idade){
						P = D;
					}
				}
			}else if(arvore[P].idade < 60 && arvore[D].idade >= 60){
				P = D;
			}else if(arvore[P].idade < 60 && arvore[D].idade < 60){
				if(strcmp(arvore[P].hora, arvore[D].hora) > 0){
					P = D;
				}else if(strcmp(arvore[P].hora, arvore[D].hora) == 0){
					if(arvore[P].idade < arvore[D].idade){
						P = D;
					}
				}
			}
		}
	}else{
		if(arvore[E].idade != 0 && arvore[D].idade != 0){
			if(arvore[E].idade >= 60 && arvore[D].idade >= 60){
				if(strcmp(arvore[E].hora, arvore[D].hora)>0){
					P = D;
				}else if(strcmp(arvore[E].hora, arvore[D].hora)<0){
					P = E;
				}else if(strcmp(arvore[E].hora, arvore[D].hora) == 0){
					if(arvore[E].idade < arvore[D].idade){
						P = D;
					}else{
						P = E;
					}
				}
			}else if(arvore[E].idade >= 60 && arvore[D].idade < 60){
				P = E;
			}else if(arvore[E].idade < 60 && arvore[D].idade >=60){
				P = D;
			}else if(arvore[E].idade < 60 && arvore[D].idade < 60){
				if(strcmp(arvore[E].hora, arvore[D].hora)>0){
					P = D;
				}else if(strcmp(arvore[E].hora, arvore[D].hora)<0){
					P = E;
				}else if(strcmp(arvore[E].hora, arvore[D].hora)==0){
					if(arvore[E].idade < arvore[D].idade){
						P = D;
					}else{
						P = E;
					}
				}
			}
		}else if(arvore[E].idade != 0){
			P = E;
		}else if(arvore[D].idade != 0){
			P = D;
		}
	}
	if(P != indice) {
		arvore = funcao_troca(arvore, P, indice);
		arvore = funcao_heapfy(arvore, tamanho, P);
	}
	return arvore;
}

data_input *ordenar_lista(data_input *arvore, unsigned int tamanho){
	for(int i=(tamanho-1)/2; i>0; i--){
		arvore = funcao_heapfy(arvore, tamanho, i);
	}
	for(int i=0; i<tamanho; i++){
		arvore = funcao_heapfy(arvore, tamanho, i);
	}
	return arvore;
}

org *funcao_inserir(char or[], char n[], int id, char h[], org *o, int cont){
	for(int i=0; i<cont; i++){
		int cmp = strncmp(or, o[i].dados->nomeOrgao, 50);
		if(cmp == 0){
			int aux = o[i].temp;
			if(aux >= size)size+=2, o[i].dados_input = (data_input *)realloc(o[i].dados_input, size*sizeof(data_input));
			strcpy(o[i].dados_input[aux].orgao, or);
			strcpy(o[i].dados_input[aux].nome, n);
			strcpy(o[i].dados_input[aux].hora, h);
			o[i].dados_input[aux].idade = id;
			o[i].temp++;
		}
	}
	return o;
}

org *funcao_tempo(org *o, int indice){
	int tamanho = o[indice].temp;
	//printf("[%s] %s\n", o[indice].dados->nomeOrgao, o[indice].dados_input[0].nome);
	o[indice].dados_input[0].idade = 0;
	funcao_heapfy(o[indice].dados_input, tamanho, 0);
	fflush(saida);
	return o;
}

int main(int argc, char* argv[]){
	entrada = fopen(argv[1], "r");
	saida = fopen(argv[2], "w");
    if(entrada == NULL){
        printf("ENTRADA INVALIDA\n");
        exit(1);
    }else{
		//inicializator();
		int qtdOrgaos;
		int people;
		fscanf(entrada, "%d", &qtdOrgaos);
		O = (org *)malloc(qtdOrgaos*sizeof(org));
		for(int i=0; i<qtdOrgaos; i++){
			O[i].dados = (data *)malloc(sizeof(data));
			O[i].dados_input = (data_input *)calloc(10000,sizeof(data_input));
			O[i].temp = 0;
			fscanf(entrada, "%s %d", O[i].dados->nomeOrgao, &O[i].dados->numAtendentes);
		}
		size = 10000;
		fscanf(entrada, "%d", &people);
		for(int i=0; i<people; i++){
			char aux;
			char n[51];
			char or[10];
			unsigned int id;
			char h[10];
			fscanf(entrada, "%c", &aux);
			fscanf(entrada, "%[^:]s", or);
			//printf("%s\n", input[i].orgao);
			fscanf(entrada, "%c", &aux);
			fscanf(entrada, "%[^-]s", n);
			//printf("%s\n", input[i].nome);
			fscanf(entrada, "%c", &aux);
			fscanf(entrada, "%d", &id);
			//printf("%d\n", input[i].idade);
			fscanf(entrada, "%c", &aux);
			fscanf(entrada, "%s", h);
			//printf("%s\n", input[i].hora);
			
			O = funcao_inserir(or, n, id, h, O, qtdOrgaos);
		}
		for(int i=0; i<qtdOrgaos; i++){
			O[i].dados_input = ordenar_lista(O[i].dados_input, O[i].temp);
		}
		int flag = 1;
		while(flag != 0){
			flag = 0;
			for(int i=0; i<qtdOrgaos; i++){
				int aux = 0;
				for(int j=0; j<O[i].dados->numAtendentes; j++){
					if(O[i].dados_input[0].idade != 0){
						if(j == 0){
							fprintf(saida, "[%s] %s", O[i].dados->nomeOrgao, O[i].dados_input[0].nome);
						}else{
							fprintf(saida, ", %s", O[i].dados_input[0].nome);
						}
						O = funcao_tempo(O, i);
						flag = 1;
						aux = 1;
					}
					if(aux != 0 && (j+1) == O[i].dados->numAtendentes){
						fprintf(saida, "\n");
						fflush(saida);
					}
				}
			}
		}
		
	}
    fclose(entrada);
	fclose(saida);
	return 0;
}
