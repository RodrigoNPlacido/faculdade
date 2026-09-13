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

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        printf("Uso: %s <arquivo_a> <arquivo_b> <arquivo_saida>\n", argv[0]);
        return 1;
    }

    FILE *a, *b, *saida;
    Endereco ea, eb;

    a     = fopen(argv[1], "rb");
    b     = fopen(argv[2], "rb");
    saida = fopen(argv[3], "wb");

    if (!a || !b || !saida)
    {
        printf("Erro ao abrir um dos arquivos\n");
        return 1;
    }

    fread(&ea, sizeof(Endereco), 1, a);
    fread(&eb, sizeof(Endereco), 1, b);

    // eof -> End Of File
    while (!feof(a) && !feof(b))
    {
        if (compara(&ea, &eb) < 0) // ea < eb
        {
            fwrite(&ea, sizeof(Endereco), 1, saida);
            fread(&ea, sizeof(Endereco), 1, a);
        }
        else // ea >= eb
        {
            fwrite(&eb, sizeof(Endereco), 1, saida);
            fread(&eb, sizeof(Endereco), 1, b);
        }
    }

    while (!feof(a))
    {
        fwrite(&ea, sizeof(Endereco), 1, saida);
        fread(&ea, sizeof(Endereco), 1, a);
    }

    while (!feof(b))
    {
        fwrite(&eb, sizeof(Endereco), 1, saida);
        fread(&eb, sizeof(Endereco), 1, b);
    }

    fclose(a);
    fclose(b);
    fclose(saida);

    return 0;
}