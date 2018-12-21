#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Wesley_Apostador{
    char codigo [50];
    int * numeros;
    int acertos;
    int impresso;
}Wesley_Apostador;
unsigned int best = 0;
unsigned int totalbest = 0;
unsigned int premiobest;
unsigned int bad = 0;
unsigned int totalbad = 0;
unsigned int premiobad ;
void verifica (int * loteria,int w,Wesley_Apostador * Viciado){
    int i,j;
    for(i=0;i<10;i++){
        for(j=0;j<15;j++){
            if(loteria[i] == Viciado[w].numeros[j]){
                Viciado[w].acertos++;
            }
        }
    }
}
unsigned int esquerda (int i){
    return (2*i)+1;
}
unsigned int direita (int i){
    return (2*i)+2;
}
unsigned int pai ( int i){
    return (i-1)/2;
}
void sharingan(Wesley_Apostador * Viciado,unsigned int pai, unsigned int i) {
    char codigo [50] = {0};
    int * numeros = (int*)malloc(sizeof(int)*15);
    int acertos;
    int impresso;
    strcpy(codigo,Viciado[i].codigo);
    impresso = Viciado[i].impresso;
    numeros = Viciado[i].numeros;
    acertos = Viciado[i].acertos;
    Viciado[i] = Viciado[pai];
    strcpy(Viciado[pai].codigo,codigo);
    Viciado[pai].numeros = numeros;
    Viciado[pai].acertos = acertos;
    Viciado[pai].impresso = impresso;
}

void heapifyMaximo(Wesley_Apostador * Viciado,unsigned int tamanho, unsigned int i) {
    unsigned int pai = i;
    unsigned int esquerdaloka = esquerda(i);
    unsigned int direitaloka = direita(i);
    if(esquerdaloka < tamanho && Viciado[esquerdaloka].acertos > Viciado[pai].acertos) pai = esquerdaloka;
    if(direitaloka < tamanho && Viciado[direitaloka].acertos > Viciado[pai].acertos) pai = direitaloka;
    if(pai != i) {
    sharingan(Viciado, pai, i);
    heapifyMaximo(Viciado, tamanho, pai);
    }
}
void heapifyMinimo(Wesley_Apostador * Viciado,unsigned int tamanho, unsigned int i) {
    unsigned int pai = i;
    unsigned int esquerdaloka = esquerda(i);
    unsigned int direitaloka = direita(i);
    if(esquerdaloka < tamanho && Viciado[esquerdaloka].acertos < Viciado[pai].acertos) pai = esquerdaloka;
    if(direitaloka < tamanho && Viciado[direitaloka].acertos < Viciado[pai].acertos) pai = direitaloka;
    if(pai != i) {
    sharingan(Viciado, pai, i);
    heapifyMinimo(Viciado, tamanho, pai);
    }
}
int main(int argc, char* argv[])
{
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");
    if(input == NULL){
        printf("Arquivo invalido!\n");
    }else{
        unsigned int premio;
        unsigned int apostas;
        int sorteados [10];
        char codigo [50] = {0};
        unsigned int i,j;
        fscanf(input,"%d",&premio);
        fscanf(input,"%d",&apostas);
        for(i = 0; i < 10; i++) fscanf(input,"%d\n",&sorteados[i]);
        Wesley_Apostador * Viciado = (Wesley_Apostador*)malloc(sizeof(Wesley_Apostador)*apostas);
        Wesley_Apostador * ViciadoLoko = (Wesley_Apostador*)malloc(sizeof(Wesley_Apostador)*apostas);
        for(j=0; j<apostas; j++){
            for(i=0; i<50; i++){
                fscanf(input,"%c",&codigo[i]);
                if(codigo[i] == ' '){
                   codigo[i] = '\0';
                   break;
                }
            }
            strcpy(Viciado[j].codigo,codigo);
            memset(codigo, 0, sizeof(codigo));
            Viciado[j].acertos = 0;
            Viciado[j].numeros = (int*)malloc(sizeof(int)*15);
            for(i = 0; i < 15; i++) fscanf(input,"%d\n",&Viciado[j].numeros[i]);
            verifica(sorteados,j,Viciado);
        }
        ViciadoLoko = Viciado;
        for(i = (apostas-1)/2 ; i > 0; i--) heapifyMaximo(Viciado,apostas,i);
        for(i = 0 ; i < apostas-1; i++) heapifyMaximo(Viciado,apostas,i);
        best = Viciado[0].acertos;
        for (i=0; i<apostas;i++) if(Viciado[i].acertos == best) totalbest++;
        premiobest = (premio/2)/totalbest;
        if(best >1)fprintf(output,"Faixa: %d acertos\n",best);
        else fprintf(output,"Faixa: %d acerto\n",best);
        int lol;
        for(lol=0;lol<totalbest;lol++){
           if(Viciado[0].acertos == best && Viciado[0].impresso == 0){
                fprintf(output,"%s\n",Viciado[0].codigo);
                Viciado[0].impresso = 1;
                Viciado[0].acertos = best-1;
            }
            heapifyMaximo(Viciado,apostas,0);
        }
        if(totalbest > 1){
            fprintf(output,"%d ganhadores de R$%d\n\n",totalbest,premiobest);
        }else{
            fprintf(output,"%d ganhador de R$%d\n\n",totalbest,premiobest);
        }
        for(i = (apostas-1)/2 ; i > 0; i--) heapifyMinimo(ViciadoLoko,apostas,i);
        for(i = 0 ; i < apostas; i++) heapifyMinimo(ViciadoLoko,apostas,i);
        bad = ViciadoLoko[0].acertos;
        for(i=0;i<apostas-1;i++) if(ViciadoLoko[i].acertos == bad) totalbad++;
        premiobad = (premio/2)/totalbad;
        if(bad > 1)fprintf(output,"Faixa: %d acertos\n",bad);
        else fprintf(output,"Faixa: %d acerto\n",bad);
        for(lol=0;lol<(apostas-1);lol++){
            if(ViciadoLoko[0].acertos == bad && ViciadoLoko[0].impresso !=2){
                fprintf(output,"%s\n",ViciadoLoko[0].codigo);
                ViciadoLoko[0].impresso = 2;
                ViciadoLoko[0].acertos = bad+1;
            }
              heapifyMinimo(ViciadoLoko,apostas,0);
        }
        if(totalbad > 1){
            fprintf(output,"%d ganhadores de R$%d\n",totalbad,premiobad);
        }else{
            fprintf(output,"%d ganhador de R$%d\n",totalbad,premiobad);
        }
    }
    return 0;
}

