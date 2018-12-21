data_input *funcao_troca(data_input *arvore, unsigned P, unsigned indice){
	data_input *aux = (data_input *)malloc(sizeof(data_input));
	aux[0] = arvore[indice];
	arvore[indice] = arvore[P];
	arvore[P] = aux[0];
	aux = NULL;
	free(aux);
	return arvore;
}

unsigned int direita(unsigned int indice){
	indice = (2*indice) + 2;
	return indice;
}

unsigned int esquerda(unsigned int indice){
	indice = (2*indice)+1;
	return indice;
}

data_input *funcao_heapfy(data_input *arvore, unsigned int tamanho, unsigned int indice){
	unsigned int P = indice;
	unsigned int E = esquerda(indice);
	unsigned int D = direita(indice);
	if(E < tamanho && arvore[E].idade < 60 && (strncmp(arvore[P].hora, arvore[E].hora, 6) > 0)){
		P = E;
	}else if(E < tamanho && arvore[E].idade >= 60){
		if(arvore[P].idade < arvore[E].idade){
			P = E;
		}else if(arvore[P].idade == arvore[E].idade){
			if(strncmp(arvore[P].hora, arvore[E].hora, 6) > 0){
				P = E;
			}
		}
	}
	if(D < tamanho && arvore[D].idade < 60 && (strncmp(arvore[P].hora, arvore[D].hora, 6) > 0)){
		P = E;
	}else if(D < tamanho && arvore[D].idade >= 60){
		if(arvore[P].idade < arvore[D].idade){
			P = D;
		}else if(arvore[P].idade == arvore[D].idade){
			if(strncmp(arvore[P].hora, arvore[D].hora, 6) > 0){
				P = D;
			}
		}
	}
	if(P != indice) {
		arvore = funcao_troca(arvore, P, indice);
		arvore = funcao_heapfy(arvore, tamanho, P);
	}
	return arvore;
}

data_input *ordenar_lista(data_input *arvore, unsigned int tamanho){
	for(int i=(tamanho-1)/2; i>0; i--){
		printf("%s\n", arvore[i].nome);
		arvore = funcao_heapfy(arvore, tamanho, i);
	}
	for(int i=0; i<tamanho; i++){
		arvore = funcao_heapfy(arvore, tamanho, i);
	}
	return arvore;
}
