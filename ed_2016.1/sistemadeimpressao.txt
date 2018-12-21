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
	unsigned int paginas;
	fila *P;
	char nome_doc[50];
	unsigned int pag_doc;
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
elemento *fim;

// Estrutura de pilha
typedef struct pilha {
	char nome[50];
	elemento* topo;
}pilha;
pilha *emp;
void empilhamento(char *nome, int pag){
	if(ajuda == 0){
		
		emp = (pilha *)malloc(sizeof(pilha));
		emp->topo = (elemento *)malloc(sizeof(elemento));
		strcpy(emp->topo->nome, nome);
		emp->topo->pagina = pag;
		emp->topo->P = NULL;
		ajuda = 1;
	}else{
		fim = (elemento *)malloc(sizeof(elemento));
		fim->P = emp->topo;
		strcpy(fim->nome,nome);
		fim->pagina = pag;
		emp->topo = fim;
	}
}

void impressao_final(){
	while(fim != NULL){
		fprintf(saida, "%s-%dp\n", fim->nome, fim->pagina);
		fim = fim->P;
		fflush(saida);
	}
}

//Verificação
int impressora_status(){
	impressora *aux;
	int menor = 9999999;
	int flag = 0;
	
	//Verifica se alguma impressora esta livre
	if(inicio == 0){
		aux = (impressora *)malloc(qtdImpressora*sizeof(impressora));
	}
	aux = impressora_localizacao;
	if(tamanho == 0){
		for(int i=0; i<qtdImpressora; i++){
			if(aux[i].paginas != 0){
				empilhamento(aux[i].nome_doc, aux[i].pag_doc);
			}
		}
		return 0;
	}
	if(flag == 0){
		for(int i=0; i<qtdImpressora; i++){
			if(aux[i].status == 0){
				strcpy(aux[i].nome_doc, _fila[inicio].nome);
				aux[i].pag_doc = _fila[inicio].paginas;
				aux[i].paginas = _fila[inicio].paginas;
				aux[i].status = 1;
				//printf("%s %dp\n", aux[i].nome_doc, aux[i].pag_doc);
				return i;
			}
			flag = 1;
		}
	}
	if(flag == 1){
	//Faz o tempo "Andar"
		for(int i = 0; i<qtdImpressora; i++){
			if(aux[i].paginas < menor){
				menor = aux[i].paginas;
				
				}
			}
			for(int i = 0; i<qtdImpressora; i++){
				aux[i].paginas -= menor;
			}
			flag = 1;
		}
	for(int i = 0; i<qtdImpressora; i++){
		if(aux[i].paginas == 0){
			empilhamento(aux[i].nome_doc, aux[i].pag_doc);
			aux[i].status = 0;
		}
	}
		
	return impressora_status();
}

void impressora_impressao(){
	pilha *aux;
	impressora *aux1;
	aux = (pilha *)malloc(qtdImpressora*sizeof(pilha));
	for(int i=0; i<qtdImpressora; i++){
		strcpy(aux[i].nome, impressora_localizacao[i].nome);
		aux[i].topo = NULL;
	}
	fila *temp;
	int inded;
	aux1 = impressora_localizacao;
	temp = _fila;
		while(tamanho != 0){
			inded = impressora_status();
			aux1[inded].P = &temp[inicio];
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
							fprintf(saida, " %s-%dp",imprimir->nome, imprimir->pagina);
						}else{
							fprintf(saida, "%s-%dp, ",imprimir->nome, imprimir->pagina);
						}
							imprimir = imprimir->P;
					}fprintf(saida, "\n");
						imprimir = NULL;
			}
			//printf("[%s] %s-%dp\n",aux[inded].nome, aux[inded].topo->nome, aux[inded].topo->pagina);
			inicio+=1;
			tamanho-=1;
			aux1[inded].status = 1;
			impressora_localizacao = aux1;
			fflush(saida);
		}impressora_status();
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
	impressao_final();
	fclose(entrada);
	fclose(saida);
	return 0;
}
	
			
		
			
