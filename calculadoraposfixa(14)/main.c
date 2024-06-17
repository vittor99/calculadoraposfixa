#include <stdio.h>
#include <string.h>
#include "calculadora.h"

#define MAX_LINE_LENGTH 100

int main() {
    FILE *file = fopen("testes.txt", "r");
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo testes.txt\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        // Remove o caractere de nova linha, se houver
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        char posFixaCopy[MAX_LINE_LENGTH];
        strcpy(posFixaCopy, line);

        char *inFixa = getFormaInFixa(posFixaCopy);
        printf("Expressão Infixa: %s\n", inFixa);

        strcpy(posFixaCopy, line);
        char *preFixa = getFormaPreFixa(posFixaCopy);
        printf("Expressão Pré-fixada: %s\n", preFixa);

        strcpy(posFixaCopy, line);
        float valor = getValor(posFixaCopy);
        printf("Valor da Expressão: %.8g\n", valor);
    }

    fclose(file);
    return 0;
}