#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sinonimo{
	char palavra[31];
	struct Sinonimo* p;
}Sinonimo;

typedef struct Palavra{
	char nome[31];
	int numBalance;
	int numSin;
	Sinonimo* vetSin;
	struct Palavra* d;
	struct Palavra* e;
}Palavra;

typedef struct Arvore{
	Palavra* raiz;
}Arvore;

int altura(Palavra *);

//Função add de lista de sinonimos.
void buscaAddSinonimo(Sinonimo* cabeca, Sinonimo no){
	if(cabeca->p == NULL){
		Sinonimo* a = (Sinonimo*) malloc(sizeof(no));
		*a = no;
		cabeca->p = a;
	}else{
		Sinonimo* p = cabeca->p;
		
		while(p->p != NULL){
			p = p->p;
		}
		
		Sinonimo* b = (Sinonimo*) malloc(sizeof(no));
		*b = no;
		p->p = b;
	}
}

void addSinonimo(Palavra* cabeca, Sinonimo no){
	if(cabeca->vetSin == NULL){
		Sinonimo* a = (Sinonimo*) malloc(sizeof(no));
		*a = no;
		cabeca->vetSin = a;
	}else{
		buscaAddSinonimo(cabeca->vetSin, no);
	}
}
//Fim funções de add Lista de sinonimos.

//Funções para add na árvore avl.

void fb(Palavra* pai){
	if(pai != NULL){
		fb(pai->e);
		
		int d = altura(pai->d);
		int e = altura(pai->e);
		pai->numBalance = d-e;
		
		fb(pai->d);
	}
}

int altura(Palavra* raiz){
	if(raiz == NULL){
		return -1;
	}else{
		int he = altura(raiz->e);
		int hd = altura(raiz->d);
		if(he > hd){
			return he+1;
		}else{
			return hd+1;
		}
	}
}

Palavra* rE(Palavra* pai) {
	Palavra* t = pai->d;
	pai->d = t->e;
	t->e = pai;
	pai = t;
	return pai;
}

Palavra* rD(Palavra* pai) {
	Palavra* t = pai->e;
	pai->e = t->d;
	t->d = pai;
	pai = t;
	return pai;
}

Palavra* rDE(Palavra* pai){
	pai->d = rD(pai->d);
	pai = rE(pai);
	fb(pai);
	return pai;
}

Palavra* rED(Palavra* pai){
	pai->e = rE(pai->e);
	pai = rD(pai);
	fb(pai);
	return pai;
}

Palavra* buscaAddArvore(Palavra* pai, Palavra no){
	if(strcmp(pai->nome, no.nome) == 1){//Vai para a esquerda
		if(pai->e == NULL){
			Palavra* a = (Palavra*) malloc(sizeof(no));
			*a = no;
			pai->e = a;
			pai->numBalance--;
		}else{
			int n = pai->e->numBalance;
			pai->e = buscaAddArvore(pai->e, no);
			
			if(pai->e->numBalance != 0 && pai->e->numBalance != n){
				pai->numBalance--;
			}
			
			if(pai->numBalance == -2 && pai->e->numBalance == -1){
				pai = rD(pai);
				fb(pai);
			}else if(pai->numBalance == -2 && pai->e->numBalance == 1){
				pai = rED(pai);
			}
		}
	}else{//Vai para a direita
		if(pai->d == NULL){
			Palavra* a = (Palavra*) malloc(sizeof(no));
			*a = no;
			pai->d = a;
			pai->numBalance++;
		}else{
			int n = pai->d->numBalance;
			pai->d = buscaAddArvore(pai->d, no);
			
			if(pai->d->numBalance != n && pai->d->numBalance != 0){
				pai->numBalance++;
			}
			
			if(pai->numBalance == 2 && pai->d->numBalance == 1){
				pai = rE(pai);
				fb(pai);
			}else if(pai->numBalance == 2 && pai->d->numBalance == -1){
				pai = rDE(pai);
			}
		}
	}
	
	return pai;
}

void addArvore(Arvore* avl, Palavra no){
	if(avl->raiz == NULL){
		Palavra* a = (Palavra*) malloc(sizeof(no));
		*a = no;
		avl->raiz = a;
	}else{
		avl->raiz = buscaAddArvore(avl->raiz, no);
	}
}
//Fim das funções de add na árvore avl.

void busca(Palavra* pai, char palavra[31], FILE* arqOutput){
	Palavra* aux = pai;
	
	int t;
	while(aux != NULL){
		t = strcmp(aux->nome, palavra);
		if(t == 0){
			fprintf(arqOutput, "%s:\n", aux->nome);
			int i;
			fprintf(arqOutput, "[");
			
			Sinonimo sin = *(aux->vetSin);
			if(sin.p != NULL){
				fprintf(arqOutput, "%s, ", sin.palavra);
				do{
					sin = *(sin.p);
					if(sin.p != NULL){
						fprintf(arqOutput, "%s, ", sin.palavra);
					}else{
						fprintf(arqOutput, "%s]", sin.palavra);
					}
				}while(sin.p != NULL);
			}else{
				fprintf(arqOutput, "%s]", sin.palavra);
			}
			
			break;
		}else if(t == 1){
			if(aux->e == NULL){
				fprintf(arqOutput, "%s->", aux->nome);
				fprintf(arqOutput, "?:\n[-]");
				break;
			}else{
				fprintf(arqOutput, "%s->", aux->nome);
				aux = aux->e;
			}
		}else if(t == -1){
			if(aux->d == NULL){
				fprintf(arqOutput, "%s->", aux->nome);
				fprintf(arqOutput, "?:\n[-]");
				break;
			}else{
				fprintf(arqOutput, "%s->", aux->nome);
				aux = aux->d;
			}
		}
	}
	
	
	/*
	if(strcmp(pai->nome, palavra) == 1){
		if(pai->e != NULL){
			fprintf(arqOutput, "%s->", pai->nome);
			busca(pai->e, palavra, arqOutput);
		}else{
			fprintf(arqOutput, "?:\n[-]");
		}
	}else if(strcmp(pai->nome, palavra) == -1){
		if(pai->d != NULL){
			fprintf(arqOutput, "%s->", pai->nome);
			busca(pai->d, palavra, arqOutput);
		}else{
			fprintf(arqOutput, "%s->", pai->nome);
			fprintf(arqOutput, "?:\n[-]");
		}
	}else if(strcmp(pai->nome, palavra) == 0){
		fprintf(arqOutput, "%s:\n", pai->nome);
		int i;
		fprintf(arqOutput, "[");
		
		Sinonimo aux = *(pai->vetSin);
		if(aux.p != NULL){
			fprintf(arqOutput, "%s, ", aux.palavra);
			do{
				aux = *(aux.p);
				if(aux.p != NULL){
					fprintf(arqOutput, "%s, ", aux.palavra);
				}else{
					fprintf(arqOutput, "%s]", aux.palavra);
				}
			}while(aux.p != NULL);
		}else{
			fprintf(arqOutput, "%s]", aux.palavra);
		}
	}*/
}

int main(int argc, char* argv[]){
	FILE* arqInput = fopen(argv[1], "r");
	FILE* arqOutput = fopen(argv[2], "w");
	int numPalavras;
	int i, j, k;
	
	fscanf(arqInput, "%d\n", &numPalavras);
	
	Arvore avl;
	avl.raiz = NULL;
	Palavra aux;
	Sinonimo sin;
	sin.palavra[30] = '\0';
	
	char c = '\0';
	char num[4] = {'0','0','0','\0'}; 
	for(i = 0; i < numPalavras; i++){
		memset(aux.nome, 0, sizeof((aux.nome)));
		aux.nome[30] = '\0';
		aux.vetSin = NULL;
		aux.numBalance = 0;
		aux.d = NULL;
		aux.e = NULL;
		j = 0;
		num[2] = '0';
		num[1] = '0';
		num[0] = '0';
		do{
			c = fgetc(arqInput);
			if(c != ' '){
				aux.nome[j] = c;
				j++;
			}
		}while(c != ' ');
		
		j = 0;
		do{
			c = fgetc(arqInput);
			if(c != ' '){
				num[j] = c;
				j++;
				num[j] = '\0';
			}
		}while(c != ' ');
		aux.numSin = atoi(num);
		
		for(j = 0; j < aux.numSin; j++){
			memset(sin.palavra, 0, sizeof((sin.palavra)));
			sin.p = NULL;
			k = 0;
			do{
				c = fgetc(arqInput);
				if(c != ' ' && c != '\n' && c != '\0'){
					sin.palavra[k] = c;
					k++;
				}
			}while(c != ' ' && c != '\n' && c != EOF);
			addSinonimo(&aux, sin);
		}
		
		sin.p = aux.vetSin;
		do{
			sin = *(sin.p);
		}while(sin.p != NULL);
		
		addArvore(&avl, aux);
	}
	
	//Busca por palavras.
	int numBusca;
	fscanf(arqInput, "%d\n", &numBusca);
	char nome[31];
	for(i = 0; i < numBusca; i++){
		memset(nome, 0, sizeof(nome));
		nome[30] = '\0';
		fscanf(arqInput, "%s\n", nome);
		
		busca(avl.raiz, nome, arqOutput);
		if(i+1 != numBusca){
			fprintf(arqOutput, "\n");
		}
	}
	
	fflush(arqInput);
	fclose(arqInput);
	fflush(arqOutput);
	fclose(arqOutput);
	return 0;
}
