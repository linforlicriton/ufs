#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	//5051 32
	//80000
	//3 
	char nome[] = {"9Yfo4K7gXB5S68xhPB4A7626OoW8SB6o sgR905gKoQq94 4I1QK2drlZ9N76XCVzWdu9WR70Vk3"};
	int i;
	int resultado = nome[0];
	for(i=1; i<100; i++){
		if(nome[i] == '\0'){
			break;
			}else if(nome[i] == ' '){
				}else{
					//printf("%d ", resultado);
					resultado = resultado ^ nome[i];
				}
		}
	//resultado = (resultado*1)%3;
	int checksum = 0;
	checksum = (3*resultado*33)%5051;
	//checksum = (7919*resultado + 0*(104729*resultado) + 123)%3;
	printf("%d\n", checksum);
	return 0;
}
