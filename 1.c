#include <stdio.h>

int main(int argc, char** argv) {
	FILE *input;
	int c;
	int lines = 0;

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
		if(c == '\n') {
			lines++;
		}

		c = fgetc(input);
	}

	fclose(input);

	printf("Linhas: %d\n", lines);

	return 0;
}