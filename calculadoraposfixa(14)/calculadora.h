#ifndef CALCULADORA_H
#define CALCULADORA_H

typedef struct {
    char posFixa[100];
    char inFixa[100];
    float Valor;
} Expressao;

char *getFormaInFixa(char *Str);
float getValor(char *Str);

#endif