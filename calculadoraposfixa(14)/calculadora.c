#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calculadora.h"

#define MAX_STACK_SIZE 100

typedef struct {
    float stack[MAX_STACK_SIZE];
    int top;
} FloatStack;

typedef struct {
    char stack[MAX_STACK_SIZE][MAX_STACK_SIZE];
    int top;
} StringStack;

void push(FloatStack *s, float value) {
    if (s->top < MAX_STACK_SIZE) {
        s->stack[s->top++] = value;
    } else {
        printf("Stack overflow\n");
    }
}

float pop(FloatStack *s) {
    if (s->top > 0) {
        return s->stack[--s->top];
    } else {
        printf("Stack underflow\n");
        return 0;
    }
}

void pushString(StringStack *s, const char *str) {
    if (s->top < MAX_STACK_SIZE) {
        strcpy(s->stack[s->top++], str);
    } else {
        printf("Stack overflow\n");
    }
}

char *popString(StringStack *s) {
    if (s->top > 0) {
        return s->stack[--s->top];
    } else {
        printf("Stack underflow\n");
        return NULL;
    }
}

float getValor(char *Str) {
  
    FloatStack stack;
    stack.top = 0;
    char expr[100];
    strcpy(expr, Str);
    char *token = strtok(expr, " ");

    while (token != NULL) {
        if (strcmp(token, "+") == 0) {
            float b = pop(&stack);
            float a = pop(&stack);
            push(&stack, a + b);
        } else if (strcmp(token, "-") == 0) {
            float b = pop(&stack);
            float a = pop(&stack);
            push(&stack, a - b);
        } else if (strcmp(token, "*") == 0) {
            float b = pop(&stack);
            float a = pop(&stack);
            push(&stack, a * b);
        } else if (strcmp(token, "/") == 0) {
            float b = pop(&stack);
            float a = pop(&stack);
            push(&stack, a / b);
        } else if (strcmp(token, "^") == 0) {
            float b = pop(&stack);
            float a = pop(&stack);
            push(&stack, pow(a, b));
        } else if (strcmp(token, "raiz") == 0) {
            float a = pop(&stack);
            push(&stack, sqrt(a));
        } else if (strcmp(token, "sen") == 0) {
            float a = pop(&stack);
            push(&stack, sin(a * M_PI / 180));
        } else if (strcmp(token, "cos") == 0) {
            float a = pop(&stack);
            push(&stack, cos(a * M_PI / 180));
        } else if (strcmp(token, "tg") == 0) {
            float a = pop(&stack);
            push(&stack, tan(a * M_PI / 180));
        } else if (strcmp(token, "log") == 0) {
            float a = pop(&stack);
            push(&stack, log10(a));
        } else {
            push(&stack, atof(token));
        }
        token = strtok(NULL, " ");
    }
    return pop(&stack);
}

char *getFormaInFixa(char *Str) {
    static char result[100];
    StringStack stack;
    stack.top = 0;
    char expr[100];
    strcpy(expr, Str);
    char *token = strtok(expr, " ");

    while (token != NULL) {
        if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0 ||
            strcmp(token, "/") == 0 || strcmp(token, "^") == 0) {
            char b[100], a[100], exp[100];
            strcpy(b, popString(&stack));
            strcpy(a, popString(&stack));
            sprintf(exp, "(%s %s %s)", a, token, b);
            pushString(&stack, exp);
        } else if (strcmp(token, "raiz") == 0 || strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0 ||
                   strcmp(token, "tg") == 0 || strcmp(token, "log") == 0) {
            char a[100], exp[100];
            strcpy(a, popString(&stack));
            sprintf(exp, "%s(%s)", token, a);
            pushString(&stack, exp);
        } else {
            pushString(&stack, token);
        }
        token = strtok(NULL, " ");
    }
    strcpy(result, popString(&stack));
    return result;
}

char *getFormaPreFixa(char *Str) {
    static char result[100];
    StringStack stack;
    stack.top = 0;
    char expr[100];
    strcpy(expr, Str);
    char *token = strtok(expr, " ");

    while (token != NULL) {
        if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0 ||
            strcmp(token, "/") == 0 || strcmp(token, "^") == 0) {
            char b[100], a[100], exp[100];
            strcpy(b, popString(&stack));
            strcpy(a, popString(&stack));
            sprintf(exp, "%s %s %s", token, a, b);
            pushString(&stack, exp);
        } else if (strcmp(token, "raiz") == 0 || strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0 ||
                   strcmp(token, "tg") == 0 || strcmp(token, "log") == 0) {
            char a[100], exp[100];
            strcpy(a, popString(&stack));
            sprintf(exp, "%s %s", token, a);
            pushString(&stack, exp);
        } else {
            pushString(&stack, token);
        }
        token = strtok(NULL, " ");
    }
    strcpy(result, popString(&stack));
    return result;
}
