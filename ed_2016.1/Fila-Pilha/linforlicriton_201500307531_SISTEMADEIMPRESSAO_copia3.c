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
fila *_fila2;
typedef struct impressora{
	char nome[50];
	int status;
	fila *P;
}impressora;
impressora *impressora_localizacao = NULL;
impressora *global = NULL;


// Estrutura de elemento
typedef struct elemento{
	char nome[50];
	int pagina;
	struct elemento *P;
}elemento;
elemento *fim = NULL;
elemento *topo = NULL;

// Estrutura de pilha
typedef struct pilha {
	char nome[50];
	// Topo da pilha
	elemento *topo;
}pilha;

typedef struct impressao_pilha{
	char nome[50];
	elemento *p;
}impressao_pilha;

//Verificação
int impressora_status(){
	printf("Teste\n");
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

void empilhamento(int indice){
	impressao_pilha *aux;
	elemento *copia;
	fila *tmp;
	tmp = _fila2;
	copia = (elemento *)malloc(sizeof(elemento));
	if(inicio == 0){
		aux = (impressao_pilha *)malloc(qtdImpressora*sizeof(impressao_pilha));
			for(int i=0; i<qtdImpressora; i++){
				strcpy(aux[i].nome, impressora_localizacao[i].nome);
				topo = aux->p;
			}
		}
	aux[indice].p = (elemento *)malloc(sizeof(elemento));
	aux[indice].p->P = topo;
	strcpy(copia->nome, tmp[inicio].nome);
	copia->pagina = tmp[inicio].paginas;
	aux[indice].p = copia;
	
	topo = aux[indice].p;
	copia = NULL;
	tmp = NULL;
	free(copia);
	
	printf("%s\n", aux[indice].p->nome);
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
			aux[inded].P = &temp[inicio];
			printf("[%s] %s-%dp\n",aux[inded].nome, aux[inded].P->nome, aux[inded].P->paginas);
			empilhamento(inded);
			inicio+=1;
			tamanho-=1;
			aux[inded].status = 1;
			impressora_localizacao = aux;
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
				_fila2 = arquivo;
			}
		}
		impressora_impressao();
	fclose(entrada);
	fclose(saida);
	return 0;
}
	
			
		
			
