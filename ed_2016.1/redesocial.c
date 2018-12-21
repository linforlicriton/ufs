#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//int i
// i = 1 Adicionar usuario
// i = 2 Mostrar usuario
// i = 3 Remover usuario

const char add[] = {"ADD"};
const char show[] = {"SHOW"};
const char remover[] = {"REMOVE"};

FILE *entrada;
FILE *saida;

typedef struct elemento{
	char nome[50];
	struct elemento *Ant;
	struct elemento *Prox;
}elemento;


elemento *inicio = NULL;
elemento *fim = NULL;


void imprimir(elemento *temp, int i)
{	
	if(temp == NULL){
        printf("ERRO3\n");
        exit(3);
    }
    if(saida == NULL){
        exit(3);
        }else{
            //Registra usuario
            switch(i){
                case 1:
                fprintf(saida, "[%s] ADD-OK\n", temp->nome);
                break;
            //Mostra amigos do usuario
            case 2:
				fprintf(saida, "[%s]<-[%s]->[%s]\n",temp->Ant->nome, temp->nome, temp->Prox->nome);
                break;
            //Remover usuario
            case 3:
				fprintf(saida, "[%s] REMOVE-OK\n", temp->nome);
                break;
            default:
                break;
        }
    }
    temp=NULL;
    fflush(saida);
}

void usuario(char nome[])
{
	elemento *aux;
	aux = (elemento *)malloc(sizeof(elemento));
	if(aux==NULL){
		exit(1);
	}
	strcpy(aux->nome, nome);
		
	if(inicio == NULL)
	{
		aux->Ant = aux;
		aux->Prox = aux;
		inicio = aux;
		imprimir(aux, 1);
		
	}else{
			if(fim == NULL){
			
				aux->Prox = inicio;
				aux->Ant = inicio;
				fim = aux;
				inicio->Ant = aux;
				inicio->Prox = aux;
				imprimir(aux, 1);
				
			}else{
				fim->Prox = aux;
				aux->Prox = inicio;
				aux->Ant = fim;
				fim = aux;
				inicio->Ant = fim;
				imprimir(aux, 1);
				}
		}
		
}

void delete(char nome[])
{
	elemento *aux;
	elemento *temp;
	temp = (elemento *)malloc(sizeof(elemento));
	int posicao = 0;
	temp = inicio;
	//printf("%s\n", nome);
	if(inicio == NULL)
	{
		fprintf(saida, "[%s] REMOVE-ERROR\n", nome);
		fflush(saida);
	}else if(fim == NULL && strcmp(temp->nome,nome)!=0){
		fprintf(saida, "[%s] REMOVE-ERROR\n", nome);
		fflush(saida);
	}else if(strcmp(temp->nome,nome)==0){
			if(inicio == fim){
			//Elemento unico
			temp->Prox = NULL;
			temp->Ant = NULL;
			//printf("Erro aki\n");
			imprimir(temp, 3);
			free(temp);
			inicio = fim = NULL;
			return;
		}else{
			//Elemento no inicio
			temp->Prox->Ant = fim;
			fim->Prox = temp->Prox;
			inicio = temp->Prox;
			temp->Prox = NULL;
			temp->Ant = NULL;
			imprimir(temp, 3);
			free(temp);
			return;
			}
	}else{
		//printf("%s\n", nome);
			do{
				if(strcmp(temp->nome, nome)==0){
					aux = temp;
					posicao = 1;
					break;
				}else{
					
					temp = temp->Prox;
					}
				}while(strcmp(temp->nome, fim->Prox->nome)!=0);
					if(posicao != 1)
					{
						
						fprintf(saida, "[%s] REMOVE-ERROR\n", nome);
						fflush(saida);
						posicao = 1;
						return;
					}
			if(temp->Prox == inicio)
			{
				//printf("Erro aki\n");
				aux = temp;
				temp->Ant->Prox = temp->Prox;
				temp->Prox->Ant = temp->Ant;
				fim = temp->Ant;
				//inicio = temp->Prox;
				temp->Prox = NULL;
				temp->Ant = NULL;
				imprimir(aux, 3);
				free(temp);
				return;
			}else if(temp->Prox != inicio)
			{
				//printf("Erro aki\n");
				aux->Prox = temp->Prox;
				temp->Prox->Ant = temp->Ant;
				temp->Ant->Prox = temp->Prox;
				temp->Ant = NULL;
				temp->Prox = NULL;
				imprimir(aux, 3);
				free(temp);
				
				return;
			}
	}
			
}
	

void ADD(char nome[])
{
	int posicao = 0;
	elemento *aux;
	elemento *temp;
	temp = fim;
	aux = inicio;
	
		if(inicio == NULL)
		{
			posicao = 1;
			usuario(nome);
		}else{
			if(temp == NULL)
			{
				if(strcmp(aux->nome, nome)!=0)
				{
					usuario(nome);
				}else{
					fprintf(saida, "[%s] ADD-ERROR\n", nome);
					fflush(saida);
				}
			}else{
				do{
					if(strcmp(aux->nome, nome)==0)
					{
						posicao = 1;
						fprintf(saida, "[%s] ADD-ERROR\n", nome);
						fflush(saida);
						break;
					}else{
						aux = aux->Prox;
					}
				}while(strcmp(aux->nome, temp->Prox->nome)!=0);
				if(posicao != 1)
				{
					usuario(nome);
					posicao = 1;
				}
			}		
					
		}
	aux = NULL;
	temp = NULL;
}

void shoW(char nome[])
{
	int posicao = 0;
	elemento *aux;
	elemento *temp;
	temp = fim;
	aux = inicio;
	if(inicio == NULL)
		{
			fprintf(saida, "[%s] SHOW-ERROR\n", nome);
			fflush(saida);
		}else
		{
			do{
					if(strcmp(aux->nome, nome)==0)
					{
						posicao = 1;
						imprimir(aux, 2);
						break;
					}else{
						aux = aux->Prox;
					}
				}while(strcmp(aux->nome, temp->Prox->nome)!=0);
			if(posicao != 1)
			{
				fprintf(saida, "[%s] SHOW-ERROR\n", nome);
				posicao = 1;
				fflush(saida);
			}
		}
	aux = temp = NULL;
}
		
	
int main(int argc, char* argv[]){
	char nome[50];
	char opc[7];
	entrada = fopen(argv[1], "r");
	saida = fopen(argv[2], "w");
    if(entrada == NULL){
        printf("ENTRADA INVALIDA\n");
        exit(4);
        }else{
            // lê linha do arquivo
            while(fscanf(entrada, "%s %[^\n]s", opc, nome)!=EOF){
                if(strcmp (opc, add) == 0){              
					ADD(nome);
                }
                if(strcmp (opc, show) == 0){
					
					shoW(nome);
                }
                if(strcmp (opc, remover) == 0){
					
					delete(nome);
                }
                if(strcmp (opc, add)!=0 && strcmp (opc, show)!=0 && strcmp (opc, remover)!=0){
					
				}
            }
        }
	fclose(entrada);
	fclose(saida);
	return 0;
}
	
