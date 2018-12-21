#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *entrada;
FILE *saida;

size_t capacidade;
size_t inicio = 0;
size_t tamanho = 0;

int qtdImpressora;

typedef struct impressora{
	char nome[50];
	int status;
}impressora;

typedef struct elemento {
	int paginas;
	char nome[50];
} elemento;

impressora *localizacao;

/*
 O elemento E 1 do início da fila é removido, com o
incremento do Inicio + 1 mod Capacidade e
decremento do Tamanho − 1
*/


int main(int argc, char* argv[]){
	elemento *arquivo;
	impressora *impr;
	int flag = 0;
	int qtd;
	entrada = fopen(argv[1], "r");
	saida = fopen(argv[2], "w");
    if(entrada == NULL){
        printf("ENTRADA INVALIDA\n");
        exit(4);
        }else{
            // lê linha do arquivo
            while(fscanf(entrada, "%d", &qtd)!=EOF){
				if(flag==0){
					qtdImpressora = qtd;
					printf("%d\n", qtd);
					impr = (impressora *)malloc(qtd*sizeof(impressora));
					for(int i=0; i<qtd; i++){
						fscanf(entrada, "%s", impr[i].nome);
						impr[i].status = 0;
						flag=1;
					}
					localizacao = impr;
				}else{
					capacidade = qtd;
					arquivo = (elemento *)malloc(qtd*sizeof(elemento));
					printf("%d\n", qtd);
					for(int i=0; i<qtd; i++){
						fscanf(entrada, "%s %d", arquivo[(inicio+tamanho)%capacidade].nome, &arquivo[(inicio+tamanho)%capacidade].paginas);
						tamanho++;
					}
				}
			}   
        }
	fclose(entrada);
	fclose(saida);
	return 0;
}
