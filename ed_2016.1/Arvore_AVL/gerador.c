#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Wesley_Palavra{
    char palavra [31];
    char **sinonimos;
    int sin;
    int wesleyaltu;
    struct Wesley_Palavra * wesleyesq;
    struct Wesley_Palavra * wesleydir;
}Wesley_Palavra;
typedef Wesley_Palavra* Wesley_Arvore;
Wesley_Arvore* Iniciar(){
    Wesley_Arvore* wesleycabeca = (Wesley_Arvore*) malloc(sizeof(Wesley_Arvore));
    *wesleycabeca = NULL;
    return wesleycabeca;
}
int Wesley_alt(Wesley_Palavra* wesleyzinho){
    if(wesleyzinho == NULL)
        return -1;
    else
    return wesleyzinho->wesleyaltu;
}
int wesleydesbuga(Wesley_Palavra* wesleyzinho){
    return labs(Wesley_alt(wesleyzinho->wesleyesq) - Wesley_alt(wesleyzinho->wesleydir));
}
int WesleyHumanas(int wesleyfilo, int wesleysofia){
    if(wesleyfilo > wesleysofia) return wesleyfilo;
    else return wesleysofia;
}
void WesleyViraDir(Wesley_Arvore *wesleycabeca){
    Wesley_Palavra *wesleyzinho;
    wesleyzinho = (*wesleycabeca)->wesleyesq;
    (*wesleycabeca)->wesleyesq = wesleyzinho->wesleydir;
    wesleyzinho->wesleydir = *wesleycabeca;
    (*wesleycabeca)->wesleyaltu = WesleyHumanas(Wesley_alt((*wesleycabeca)->wesleyesq),Wesley_alt((*wesleycabeca)->wesleydir)) + 1;
    wesleyzinho->wesleyaltu = WesleyHumanas(Wesley_alt(wesleyzinho->wesleyesq),(*wesleycabeca)->wesleyaltu) + 1;
    *wesleycabeca = wesleyzinho;
}
void WesleyViraEsq(Wesley_Arvore *wesleycabeca){
    Wesley_Palavra *wesleyzinho;
    wesleyzinho = (*wesleycabeca)->wesleydir;
    (*wesleycabeca)->wesleydir = wesleyzinho->wesleyesq;
    wesleyzinho->wesleyesq = (*wesleycabeca);
    (*wesleycabeca)->wesleyaltu = WesleyHumanas(Wesley_alt((*wesleycabeca)->wesleyesq),Wesley_alt((*wesleycabeca)->wesleydir)) + 1;
    wesleyzinho->wesleyaltu = WesleyHumanas(Wesley_alt(wesleyzinho->wesleydir),(*wesleycabeca)->wesleyaltu) + 1;
    (*wesleycabeca) = wesleyzinho;
}
void WesleyViraEsqDir(Wesley_Arvore *wesleycabeca){
    WesleyViraEsq(&(*wesleycabeca)->wesleyesq);
    WesleyViraDir(wesleycabeca);
}
void WesleyViraDirEsq(Wesley_Arvore *wesleycabeca){
    WesleyViraDir(&(*wesleycabeca)->wesleydir);
    WesleyViraEsq(wesleycabeca);
}
int WesleyMeteBala(Wesley_Arvore *wesleycabeca, char* palavra,int sinonimos){
    int wesleyveri;
    if(*wesleycabeca == NULL){
        Wesley_Palavra *wesleynoob;
        wesleynoob = (Wesley_Palavra*)malloc(sizeof(Wesley_Palavra));
        if(wesleynoob == NULL)
            return 0;
        strcpy(wesleynoob->palavra,palavra);
        wesleynoob->wesleyaltu = 0;
        wesleynoob->sin = sinonimos;
        wesleynoob->wesleyesq = NULL;
        wesleynoob->wesleydir = NULL;
        *wesleycabeca = wesleynoob;
        return 1;
    }
    Wesley_Palavra *wesleyaqui = *wesleycabeca;
        if (strcmp(wesleyaqui->palavra,palavra) >= 0){
        if((wesleyveri = WesleyMeteBala(&(wesleyaqui->wesleyesq), palavra,sinonimos)) == 1){
            if(wesleydesbuga(wesleyaqui) >= 2){
                if(strcmp((*wesleycabeca)->wesleyesq->palavra,palavra) >= 0){
                    WesleyViraDir(wesleycabeca);
                }else{
                    WesleyViraEsqDir(wesleycabeca);
                }
            }
        }
        }
        if (strcmp(wesleyaqui->palavra,palavra) < 0){
            if((wesleyveri = WesleyMeteBala(&(wesleyaqui->wesleydir), palavra,sinonimos)) == 1){
                if(wesleydesbuga(wesleyaqui) >= 2){
                if(strcmp((*wesleycabeca)->wesleydir->palavra,palavra) < 0){
                        WesleyViraEsq(wesleycabeca);
                    }else{
                        WesleyViraDirEsq(wesleycabeca);
                    }
                }
            }
        }
    wesleyaqui->wesleyaltu = WesleyHumanas(Wesley_alt(wesleyaqui->wesleyesq),Wesley_alt(wesleyaqui->wesleydir)) + 1;
    return wesleyveri;
}
void Buscar(Wesley_Arvore * Wesley,char * palavra,FILE * output){ 
    Wesley_Palavra *wesleyaqui = *Wesley;
    while(wesleyaqui != NULL){
        if(strcmp(wesleyaqui->palavra,palavra) == 0){
            fprintf(output,"%s:\n",wesleyaqui->palavra);
            break;
        }
        if (strcmp(palavra,wesleyaqui->palavra) > 0){
			fprintf(output,"%s->",wesleyaqui->palavra);
            wesleyaqui = wesleyaqui->wesleydir;      
        }else{
            fprintf(output,"%s->",wesleyaqui->palavra);
            wesleyaqui = wesleyaqui->wesleyesq;
        }
        if(wesleyaqui == NULL)fprintf(output,"?:\n[-]\n");
    }
}
int main(int argc, char* argv[])
{
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");
	if(input == NULL){
        printf("Arquivo invalido!");
	}else{
        Wesley_Arvore * Wesley = Iniciar();
        int wesley_palavras,sinonimos,i,j,w;
        char palavra [31] = {0};
        fscanf(input,"%d\n",&wesley_palavras);
        Wesley_Palavra * Lol = (Wesley_Palavra*)malloc(sizeof(Wesley_Palavra)*wesley_palavras);
        for(i = 0; i<wesley_palavras;i++){
            for(j=0;j<31;j++){
                fscanf(input,"%c",&palavra[j]);
                if(palavra[j] == ' '){
                    palavra[j] = '\0';
                    break;
                }
            }
            fscanf(input,"%d ",&sinonimos);
            strcpy(Lol[i].palavra,palavra);
            Lol[i].sin = sinonimos;
            Lol[i].sinonimos = (char**)malloc(sizeof(char*)*sinonimos);
            for(j = 0;j<sinonimos;j++)  Lol[i].sinonimos[j] = (char*)malloc(sizeof(char)*30);
            WesleyMeteBala(Wesley,palavra,sinonimos);
            memset(palavra, 0, sizeof(palavra));
            char sinon [31] = {0};
            for(j=0;j<sinonimos;j++){
                for(w=0;w<31;w++){
                fscanf(input,"%c",&sinon[w]);
                if(sinon[w] == ' ' || sinon[w] == '\n'){
                   sinon[w] = '\0';
                   break;
                }
            }
            strcpy(Lol[i].sinonimos[j],sinon);
            memset(sinon, 0, sizeof(sinon));
            }
        }
        int wesley_consultas;
        char consu[31] = {0};
        fscanf(input,"%d\n",&wesley_consultas);
        for(i=0;i<wesley_consultas;i++){
            for(w=0;w<31;w++){
                fscanf(input,"%c",&consu[w]);
                if(consu[w] == '\n'){
                   consu[w] = '\0';
                   break;
                }
            }
            Buscar(Wesley,consu,output);
            for(j=0;j<wesley_palavras;j++){
                if(strcmp(Lol[j].palavra,consu) == 0){
                    fprintf(output,"["); for(w=0;w<Lol[j].sin;w++)
                    if(w == Lol[j].sin-1){
                        fprintf(output,"%s]\n",Lol[j].sinonimos[w]);
                    }else{
                        fprintf(output,"%s, ",Lol[j].sinonimos[w]);
                    }
                    break;
                }
            }
            memset(consu, 0, sizeof(consu));
        }
	}
	fclose(input);
	fclose(output);
    return 0;
}
