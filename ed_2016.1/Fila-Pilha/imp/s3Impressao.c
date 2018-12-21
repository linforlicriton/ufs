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


// Estrutura de elemento
typedef struct elemento{
	char nome[50];
	int pagina;
	struct elemento *P;
}elemento;

// Estrutura de pilha
typedef struct pilha {
	// Topo da pilha
	elemento* topo;
}pilha;

elemento *top = NULL;
elemento *top1 = NULL;
/*
 O elemento E 1 do início da fila é removido, com o
incremento do Inicio + 1 mod Capacidade e
decremento do Tamanho − 1
*/

/*
void imprimir(pilha *phi, char nome[50]){
	fprintf(saida, "[%s] %s-%dp\n", nome, phi->topo->nome, phi->topo->pagina);
	fflush(saida);
}
*/

void iPilha(pilha *phi, char nome[50]){
	
	if(strcmp(nome, localizacao->nome)==0){
		fprintf(saida, "[%s] ", nome);
		while(phi->topo != NULL){
			fprintf(saida, "%s-%dp, ", top->nome, top->pagina);
			fflush(saida);
			printf("%s-%dp\n", top->nome, top->pagina);
			phi->topo = phi->topo->P;
		}
		fprintf(saida, "\n");
		fflush(saida);
	}else{
		fprintf(saida, "[%s] ", nome);
		while(phi->topo != NULL){
			fprintf(saida, "%s-%dp, ", top->nome, top->pagina);
			fflush(saida);
			printf("%s-%dp\n", top->nome, top->pagina);
			phi->topo = phi->topo->P;
		}
		fprintf(saida, "\n");
		fflush(saida);
	}
}


//Imprime os arquivos
void impressao(fila *temp){
	impressora *aux;
	pilha *pi;
	elemento *ele;
	char impNome[50];
	aux = localizacao;
	int pagina[qtdImpressora];
	for(int i=0; i<qtdImpressora; i++){
		pagina[i] = 0;
	}
	//pagina[0] = aux[0]
	//pagina[1] = aux[1]
	fprintf(saida, "%dp\n", totalpaginas);
	fflush(saida);
			while(tamanho != 0){
				if(aux[0].status==0){
					aux[0].P = &temp[inicio];
					aux[0].indice = inicio;
					pagina[0] = temp[inicio].paginas;
					strcpy(impNome, aux[0].nome);
					pi = (pilha *)malloc(sizeof(pilha));
					ele = (elemento *)malloc(sizeof(elemento));
					strcpy(ele->nome, temp[inicio].nome);
					ele->pagina = temp[inicio].paginas;
					printf("Hello World!\n");
					pi->topo = ele;
					top = ele;
					iPilha(pi, impNome);
					//imprimir(pi, impNome);
					inicio+=1;
					tamanho-=1;
					aux[0].status=1;
				}
				if(aux[1].status == 0){
					printf("Hello World!\n");
					aux[1].P = &temp[inicio];
					aux[1].indice = inicio;
					pagina[1] = temp[inicio].paginas;
					strcpy(impNome, aux[1].nome);
					pi = (pilha *)malloc(sizeof(pilha));
					ele = (elemento *)malloc(sizeof(elemento));
					strcpy(ele->nome, temp[inicio].nome);
					ele->pagina = temp[inicio].paginas;
					top1 = ele;
					pi->topo = ele;
					iPilha(pi, impNome);
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
	
