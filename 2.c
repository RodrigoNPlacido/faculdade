#include <stdio.h>

int main(int argc, char** argv) {
	FILE *input;
	int c;
	int count[256] = {0};

	if(argc != 2) {
		fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr,"Uso: %s [ARQUIVO].\n", argv[0]);
		return 1;
	}

	input = fopen(argv[1],"rb");
	if(!input) {
		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
		return 1;
	}

	c = fgetc(input);
	while(c != EOF) {
		count[c]++;
		c = fgetc(input);
	}

	fclose(input);

	for(c = 0; c < 256; c++) {
		if(count[c] > 0 && c >= 32 && c <= 126) {
			printf("%c %d\n", c, count[c]);
		}
	}

	return 0;
}