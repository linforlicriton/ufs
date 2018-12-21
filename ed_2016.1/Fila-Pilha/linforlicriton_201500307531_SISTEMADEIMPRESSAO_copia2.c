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
	fila *P;
}impressora;
impressora *impressora_localizacao;
impressora *global;
impressora *proximo = NULL;


// Estrutura de elemento
typedef struct elemento{
	char nome[50];
	int pagina;
	struct elemento *P;
}elemento;
elemento *fim = NULL;

// Estrutura de pilha
typedef struct pilha {
	// Topo da pilha
	char nome[50];
	elemento *topo;
}pilha;

//Verificação
int impressora_status(){
	impressora *aux;
	int menor = 9999999;
	int flag = 0;
	int pag[qtdImpressora];
	aux = global;
	//Verifica se alguma impressora esta livre
	if(ajuda >= qtdImpressora){
		//Copiando as paginas
			for(int i=0; i<qtdImpressora; i++){
				pag[i] = aux[i].P->paginas;
			}
		}
		if(flag == 0){
			ajuda += 1;
			for(int i=0; i<qtdImpressora; i++){
				if(aux[i].status == 0){
					return (i);
				}
				flag = 1;
			}
		}
		if(flag == 1){
		//Faz o tempo "Andar"
			for(int i = 0; i<qtdImpressora; i++){
				if(pag[i] < menor){
					menor = aux[i].P->paginas;
					}
				}
				for(int i = 0; i<qtdImpressora; i++){
					if(aux[i].P->paginas == menor){
						for(int j=0; j<qtdImpressora; j++){
							aux[j].P->paginas -= menor;
							if(pag[j] == 0){
								aux[j].status = 0;
							}else{
								aux[j].status = 1;
							}
						}
					}
				}
				flag = 1;
			}
	for(int i=0; i<qtdImpressora; i++){
		if(pag[i]==0){
			return i;
			}
		}
	return impressora_status();
}

void imprimir(){
		while(fim != NULL){
			fprintf(saida, "%s-%dp\n", fim->nome, fim->pagina);
			fflush(saida);
			fim = fim->P;
		}
}

void pilhaEntrega(int pag, char nome[], int in){
	elemento *aux;
	aux = (elemento *)malloc(sizeof(elemento));
	aux->P = fim;
	aux->pagina = pag;
	//printf("[%s] ", impressora_localizacao->nome);
	while(fim != NULL){
			//printf("%s-%dp, ", fim->nome, fim->pagina);
			fim = fim->P;
		}
	strcpy(aux->nome, nome);
	fim = aux;
}

void empilhamento(fila *help){
	pilha *auxx;
	elemento *auxi;
	if(inicio == 0){
	auxx = (pilha *)malloc(qtdImpressora*sizeof(pilha));
		for(int i=0; i<qtdImpressora; i++){
			strcpy(auxx[i].nome, aux[i].nome);
		}
	}
	auxi = (elemento *)malloc(sizeof(elemento));
		auxx[inded].topo = (elemento *)malloc(sizeof(elemento));
		strcpy(auxi->nome, temp[inicio].nome);
		auxi->pagina = temp[inicio].paginas;
		auxx[inded].topo = auxi;
		printf("[%s] %s-%dp\n", auxx[inded].nome, auxx[inded].topo->nome, auxx[inded].topo->pagina);
}

void impressora_impressao(){
	impressora *aux;
	fila *temp;
	//pilha *phi;
	//elemento *phi_aux;
	int inded;
	aux = impressora_localizacao;
	temp = _fila;
		while(tamanho != 0){
			inded = impressora_status();
			//phi_aux = (elemento *)malloc(sizeof(elemento));
			//strcpy(auxx[inded].nome, aux[inded].nome);
			//strcpy(phi_aux->nome, temp[inicio].nome);
			//phi_aux->pagina = temp[inicio].paginas;
			//phi_aux->P = fim;
			//fim = phi_aux;
			//pilhaEntrega(temp[inicio].paginas ,temp[inicio].nome, inded);
			inicio+=1;
			tamanho-=1;
			aux[inded].status = 1;
			//printf("[%s] %s-%dp\n",aux[inded].nome, aux[inded].P->nome, aux[inded].P->paginas);
			impressora_localizacao = aux;
		}
		//imprimir(phi_aux);
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
					
					for(int i=0; i<qtd; i++){
						fscanf(entrada, "%s", impr[i].nome);
						impr[i].status = 0;
						impr[i].P = NULL;
						flag=1;
					}
				//arquivo no formato paginas	
				}else{
					capacidade = qtd;
					arquivo = (fila *)malloc(capacidade*sizeof(fila));
					for(int i=0; i<qtd; i++){
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
	fflush(saida);
	imprimir();
	fclose(entrada);
	fclose(saida);
	return 0;
}
	
			
		
			
