#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

int compara(const void *e1, const void *e2)
{
    return strncmp(((Endereco*)e1)->cep, ((Endereco*)e2)->cep, 8);
}

#define NUM_BLOCOS 8

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Uso: %s <arquivo_original.dat>\n", argv[0]);
        return 1;
    }

    FILE *original = fopen(argv[1], "rb");
    if (!original)
    {
        perror("Erro ao abrir arquivo original");
        return 1;
    }

    // Descobre quantos registros existem no arquivo
    fseek(original, 0, SEEK_END);
    long tamanho = ftell(original);
    rewind(original);

    long totalRegistros    = tamanho / sizeof(Endereco);
    long registrosPorBloco = totalRegistros / NUM_BLOCOS;
    long resto             = totalRegistros % NUM_BLOCOS;

    char nomeArquivo[30];
    long registrosLidos = 0;

    for (int i = 1; i <= NUM_BLOCOS; i++)
    {
        // o ultimo bloco absorve o resto da divisao
        long qtdEsteBloco = registrosPorBloco + (i == NUM_BLOCOS ? resto : 0);

        Endereco *bloco = (Endereco*) malloc(qtdEsteBloco * sizeof(Endereco));
        if (!bloco)
        {
            printf("Erro de alocacao de memoria\n");
            return 1;
        }

        fread(bloco, sizeof(Endereco), qtdEsteBloco, original);

        qsort(bloco, qtdEsteBloco, sizeof(Endereco), compara);

        sprintf(nomeArquivo, "bloco%d.dat", i);
        FILE *saida = fopen(nomeArquivo, "wb");
        fwrite(bloco, sizeof(Endereco), qtdEsteBloco, saida);
        fclose(saida);

        free(bloco);
        registrosLidos += qtdEsteBloco;

        printf("Bloco %d gerado e ordenado (%ld registros) -> %s\n", i, qtdEsteBloco, nomeArquivo);
    }

    fclose(original);
    printf("Total de registros processados: %ld\n", registrosLidos);

    return 0;
}