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
int ajuda = 0;


typedef struct fila{
	int paginas;
	char nome[50];
}fila;
fila *_fila;
typedef struct impressora{
	char nome[50];
	int status;
	int dados_indice;
	fila *P;
}impressora;
impressora *impressora_localizacao;
impressora *global;


// Estrutura de elemento
typedef struct elemento{
	char nome[50];
	int pagina;
	struct elemento *P;
}elemento;
elemento *temporario;
elemento *imprimir;
elemento *fim = NULL;

// Estrutura de pilha
typedef struct pilha {
	char nome[50];
	elemento* topo;
}pilha;

void pilhaEntrega(int indice){
	if(fim == NULL){
		fim = (elemento *)malloc(sizeof(elemento));	
		fim->P = NULL;
		strcpy(fim->nome, _fila->nome);
		fim->pagina = _fila->paginas;
	}else{
		elemento *aux;
		aux = (elemento *)malloc(sizeof(elemento));
		aux->P = fim;
		strcpy(aux->nome, _fila->nome);
		aux->pagina = _fila->paginas;
		fim = aux;
	}
}

void impressao_final(){
		while(fim != NULL){
			fprintf(saida, "%s-%dp\n", fim->nome, fim->pagina);
			fflush(saida);
			fim = fim->P;
		}
}

int impressora_status(){
	impressora *documentos;
	int i;
	if(inicio == 0){
		documentos = (impressora *)malloc(qtdImpressora*sizeof(impressora));
		for(i=0; i<qtdImpressora; i++){
			documentos[i].status = 0;
		}
		documentos[0].P = (fila *)malloc(sizeof(fila));
		strcpy(documentos[0].P->nome, _fila[inicio].nome);
		return 0;
	}else{
		//verifica status
		for(i=0; i<qtdImpressora; i++){
			if(documentos[i].status == 0){
				return i;
			}
		}
		
	
}

void impressora_impressao(){
	pilha *aux;
	impressora *aux1;
	aux = (pilha *)malloc(qtdImpressora*sizeof(pilha));
	int i;
	for(i=0; i<qtdImpressora; i++){
		strcpy(aux[i].nome, impressora_localizacao[i].nome);
		aux[i].topo = NULL;
	}
	int inded = 0;
	fila *temp;
	temp = _fila;
		while(tamanho != 0){
				inded = impressora_status();
				aux1[inded].P = &temp[inicio];
				//empilhamento vazio
				if(aux[inded].topo == NULL){
					aux[inded].topo = (elemento *)malloc(sizeof(elemento));
					aux[inded].topo->P = NULL;
					strcpy(aux[inded].topo->nome,temp[inicio].nome);
					aux[inded].topo->pagina = temp[inicio].paginas;
					fprintf(saida, "[%s] %s-%dp\n",aux[inded].nome, aux[inded].topo->nome, aux[inded].topo->pagina);
				}else{
					temporario = (elemento *)malloc(sizeof(elemento));
					temporario->P = aux[inded].topo;
					strcpy(temporario->nome,temp[inicio].nome);
					temporario->pagina = temp[inicio].paginas;
					aux[inded].topo = temporario;
						fprintf(saida, "[%s] ", aux[inded].nome);
						imprimir = aux[inded].topo;
						while(imprimir != NULL){
							if(imprimir->P == NULL){
								fprintf(saida, "%s-%dp",imprimir->nome, imprimir->pagina);
							}else{
								fprintf(saida, "%s-%dp, ",imprimir->nome, imprimir->pagina);
							}
								imprimir = imprimir->P;
						}fprintf(saida, "\n");
						fflush(saida);
							imprimir = NULL;
				}
				//pilhaEntrega(temp[inicio].paginas ,temp[inicio].nome);
				inicio+=1;
				tamanho-=1;
				aux1[inded].status = 1;
				impressora_localizacao = aux1;
		}
}

int main(int argc, char* argv[]){
	fila *arquivo;
	impressora *impr;
	int flag = 0;
	int qtd = 0;
	entrada = fopen(argv[1], "r");
	saida = fopen(argv[2], "w");
    if(entrada == NULL){
        printf("ENTRADA INVALIDA\n");
        exit(4);
        }else{
           // ler arquivo
            while(fscanf(entrada, "%d", &qtd)!=EOF){
				//arquivo no formato da impressora
				if(flag==0){
					qtdImpressora = qtd;
					impr = (impressora *)malloc(qtd*sizeof(impressora));
					int i;
					for(i=0; i<qtd; i++){
						fscanf(entrada, "%s", impr[i].nome);
						impr[i].status = 0;
						impr[i].P = NULL;
						flag=1;
					}
				//arquivo no formato paginas	
				}else{
					capacidade = qtd;
					arquivo = (fila *)malloc(capacidade*sizeof(fila));
					int i;
					for(i=0; i<qtd; i++){
						//Formato de Fila
						fscanf(entrada, "%s %d", arquivo[(inicio+tamanho)%capacidade].nome, &arquivo[(inicio+tamanho)%capacidade].paginas);
						totalpaginas += arquivo[(inicio+tamanho)%capacidade].paginas;
						tamanho++;
						}
					}
				//salvando os dados
				impressora_localizacao = impr;
				global = impr;
				_fila = arquivo;
			}
		}
	impressora_impressao();
	fprintf(saida, "%dp\n", totalpaginas);
	impressao_final();
	fclose(entrada);
	fclose(saida);
	return 0;
}
	
			
		
			
