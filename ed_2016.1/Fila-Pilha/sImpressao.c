#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *entrada;
FILE *saida;
size_t tamanho;
size_t capacidade;
size_t inicio;
int qtdImpressora = 0;
int totalpaginas = 0;

typedef struct fila{
	int paginas;
	char nome[50];
}fila;

typedef struct impressora{
	char nome[50];
	int status;
	int indice;
	fila *P;
}impressora;
impressora *localizacao;


/*
 O elemento E 1 do início da fila é removido, com o
incremento do Inicio + 1 mod Capacidade e
decremento do Tamanho − 1
*/

//Imprime os arquivos
void impressao(fila *temp){
	impressora *aux;
	aux = localizacao;
	int pagina[qtdImpressora];
	for(int i=0; i<qtdImpressora; i++){
		pagina[i] = 0;
	}
	//pagina[0] = aux[0]
	//pagina[1] = aux[1]
	printf("%dp\n", totalpaginas);
			while(tamanho != 0){
				if(aux[0].status==0){
					printf("[%s] %s-%dp\n",aux[0].nome, temp[inicio].nome, temp[inicio].paginas);
					aux[0].P = &temp[inicio];
					aux[0].indice = inicio;
					pagina[0] = temp[inicio].paginas;
					inicio+=1;
					tamanho-=1;
					aux[0].status=1;
				}
				if(aux[1].status == 0){
					printf("[%s] %s-%dp\n",aux[1].nome, temp[inicio].nome, temp[inicio].paginas);
					aux[1].P = &temp[inicio];
					aux[1].indice = inicio;
					pagina[1] = temp[inicio].paginas;
					inicio+=1;
					tamanho-=1;
					aux[1].status=1;
				}
				if((aux[0].status && aux[1].status)!=0){
						if((pagina[0]) < (pagina[1])){
							pagina[1] -= pagina[0];
							pagina[0] = 0;
							aux[0].status = 0;
						}
						if((pagina[0]) > (pagina[1])){
							pagina[0] -= pagina[1];
							pagina[1] = 0;
							aux[1].status = 0;
						}
						if((pagina[0]) == (pagina[1])){
							pagina[0] = pagina[1] = 0;			
							aux[0].status = 0;
							aux[1].status = 0;
						}
					}
			}
}

int main(int argc, char* argv[]){
	impressora *impr;
	fila *arquivo;
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
					impr = (impressora *)malloc(qtd*sizeof(impressora));
					for(int i=0; i<qtd; i++){
						fscanf(entrada, "%s", impr[i].nome);
						impr[i].status = 0;
						impr[i].P = NULL;
						flag=1;
					}
					
				}else{
					capacidade = qtd;
					arquivo = (fila *)malloc(capacidade*sizeof(fila));
					for(int i=0; i<qtd; i++){
						fscanf(entrada, "%s %d", arquivo[(inicio+tamanho)%capacidade].nome, &arquivo[(inicio+tamanho)%capacidade].paginas);
						totalpaginas += arquivo[(inicio+tamanho)%capacidade].paginas;
						tamanho++;
					}
					localizacao = impr;
					impressao(arquivo);
				}
			}   
        }
	fclose(entrada);
	fclose(saida);
	return 0;
}
	
