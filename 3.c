#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco {
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int main(int argc, char** argv) {
	FILE *f;
	Endereco e;
	int begin, end, middle;
	int qt;
	int c;

	if(argc != 2) {
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

	f = fopen("cep_ordenado.dat", "r");
	if(!f) {
		fprintf(stderr, "Arquivo cep_ordenado.dat não pode ser aberto\n");
		return 1;
	}

	fseek(f, 0, SEEK_END);
	end = ftell(f) / sizeof(Endereco);
	begin = 0;
	c = 0;

	while(begin <= end) {
		middle = (begin + end) / 2;

		fseek(f, middle * sizeof(Endereco), SEEK_SET);
		qt = fread(&e, sizeof(Endereco), 1, f);

		if(qt != 1) {
			break;
		}

		c++;

		if(strncmp(argv[1], e.cep, 8) == 0) {
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",
				e.logradouro, e.bairro, e.cidade, e.uf, e.sigla, e.cep);
			break;
		}

		if(strncmp(argv[1], e.cep, 8) < 0) {
			end = middle - 1;
		} else {
			begin = middle + 1;
		}
	}

	printf("Total Lido: %d\n", c);

	fclose(f);

	return 0;
}