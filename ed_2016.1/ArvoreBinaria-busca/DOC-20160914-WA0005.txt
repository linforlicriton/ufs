#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Wesley_No{
	int baterias;
    int kaneki;
    char arq [51];
    char moloko [3];
    struct Wesley_No *esq;
    struct Wesley_No *dir;
};
typedef struct Wesley_No* MinhaArvoreMinhaVida;

MinhaArvoreMinhaVida* cria(){
    MinhaArvoreMinhaVida* Wesleyraiz = (MinhaArvoreMinhaVida*) malloc(sizeof(MinhaArvoreMinhaVida));
    if(Wesleyraiz != NULL)
        *Wesleyraiz = NULL;
    return Wesleyraiz;
}


int IntroduzLoko(MinhaArvoreMinhaVida* Wesleyraiz, char*arq,char*moloko, int baterias, int kaneki){
    if(Wesleyraiz == NULL)
        return 0;
    struct Wesley_No* olokowesley;
    olokowesley = (struct Wesley_No*) malloc(sizeof(struct Wesley_No));
    if(olokowesley == NULL)
        return 0;
    strcpy(olokowesley->arq ,arq);
    strcpy(olokowesley->moloko ,moloko);
    olokowesley->baterias = baterias;
    olokowesley->kaneki = kaneki;
    olokowesley->dir = NULL;
    olokowesley->esq = NULL;

    if(*Wesleyraiz == NULL)
        *Wesleyraiz = olokowesley;
    else{
        struct Wesley_No* here = *Wesleyraiz;
        struct Wesley_No* wesleyant = NULL;
        int band = 0;
        while(here != NULL){
            wesleyant = here;
            if(strcmp(arq, here->arq)==0 && strcmp(here->moloko, "rw")==0 ){
                here = olokowesley;
                band = 1;
                break;
            }
			if(strcmp(arq,here->arq) > 0)
                here = here->dir;
            else if (strcmp(arq,here->arq) < 0)
                here = here->esq;
        }
        if ( band == 0){
			if(strcmp(arq,wesleyant->arq) > 0)
            wesleyant->dir = olokowesley;
			else if (strcmp(arq,wesleyant->arq) < 0)
            wesleyant->esq = olokowesley;
		}

    }
    return 1;
}


void WesleyPED(MinhaArvoreMinhaVida *WesleyBest,FILE * output){
    if(WesleyBest == NULL)
        return;
    if(*WesleyBest != NULL){
        if((*WesleyBest)->baterias < 2){
            fprintf(output,"%d %s %s %d byte\n",(*WesleyBest)->kaneki, (*WesleyBest)->arq,(*WesleyBest)->moloko,(*WesleyBest)->baterias);
        }else{
            fprintf(output,"%d %s %s %d bytes\n",(*WesleyBest)->kaneki, (*WesleyBest)->arq,(*WesleyBest)->moloko,(*WesleyBest)->baterias);
        }
        WesleyPED(&((*WesleyBest)->esq),output);
        WesleyPED(&((*WesleyBest)->dir),output);
    }
}

void WesleyEPD(MinhaArvoreMinhaVida *WesleyBest,FILE * output){
    if(WesleyBest == NULL)
        return;
    if(*WesleyBest != NULL){
        WesleyEPD(&((*WesleyBest)->esq),output);
        if((*WesleyBest)->baterias < 2){
            fprintf(output,"%d %s %s %d byte\n",(*WesleyBest)->kaneki, (*WesleyBest)->arq,(*WesleyBest)->moloko,(*WesleyBest)->baterias);
        }else{
            fprintf(output,"%d %s %s %d bytes\n",(*WesleyBest)->kaneki, (*WesleyBest)->arq,(*WesleyBest)->moloko,(*WesleyBest)->baterias);
        }
        WesleyEPD(&((*WesleyBest)->dir),output);
    }
}

void WesleyEDP(MinhaArvoreMinhaVida *WesleyBest,FILE * output){
    if(WesleyBest == NULL)
        return;
    if(*WesleyBest != NULL){
        WesleyEDP(&((*WesleyBest)->esq),output);
        WesleyEDP(&((*WesleyBest)->dir),output);
        if((*WesleyBest)->baterias < 2){
            fprintf(output,"%d %s %s %d byte\n",(*WesleyBest)->kaneki, (*WesleyBest)->arq,(*WesleyBest)->moloko,(*WesleyBest)->baterias);
        }else{
            fprintf(output,"%d %s %s %d bytes\n",(*WesleyBest)->kaneki, (*WesleyBest)->arq,(*WesleyBest)->moloko,(*WesleyBest)->baterias);
        }
    }
}
    int main(int argc, char* argv[])
{
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");
	if(input == NULL){
        printf("Arquivo invalido!");
	}else{
		MinhaArvoreMinhaVida* wesleyraiz = cria();
       int arquivos,kaneki,j,baterias;
       char arq [51] = {0};
       char moloko [3] = {0};
       fscanf(input, "%d\n", &arquivos);
       for(kaneki=0; kaneki<arquivos; kaneki++){
            for(j=0; j<51; j++){
                fscanf(input,"%c",&arq[j]);
                if(arq[j] == ' '){
                   arq[j] = '\0';
                   break;
                }
            }
            for(j=0; j<3; j++){
                fscanf(input,"%c",&moloko[j]);
                if(moloko[j] == ' '){
                   moloko[j] = '\0';
                   break;
                }
            }
            fscanf(input,"%d\n",&baterias);
            IntroduzLoko(wesleyraiz,arq,moloko,baterias,kaneki);
            memset(arq, 0, sizeof(arq));
            memset(moloko, 0, sizeof(moloko));
        }
        fprintf(output,"EPD:\n");
        WesleyEPD(wesleyraiz,output);
        fprintf(output,"PED:\n");
        WesleyPED(wesleyraiz,output);
        fprintf(output,"EDP:\n");
        WesleyEDP(wesleyraiz,output);
    }
	fclose(input);
	fclose(output);
	return 0;
}
