#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "expressao.h"

// Pilha definida
typedef struct {
    float elementos[512];
    int topo;
} Pilha;

// Funções manipulação da pilha
void inicializaPilha(Pilha *pilha) {
    pilha->topo = -1;
}

int pilhaVazia(Pilha *pilha) {
    return pilha->topo == -1;
}

void empilha(Pilha *pilha, float valor) {
    pilha->elementos[++pilha->topo] = valor;
}

float desempilha(Pilha *pilha) {
    return pilha->elementos[pilha->topo--];
}

// Função para calcular o valor de uma expressão pós-fixada
float getValor(char *str) {
    Pilha pilha;
    inicializaPilha(&pilha);
    char *token = strtok(str, " "); // Divide a string por espaços

    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            empilha(&pilha, atof(token));
        } else if (strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0 ||
                   strcmp(token, "tg") == 0 || strcmp(token, "log") == 0 || strcmp(token, "raiz") == 0) {
            // Operadores unários
            float a = desempilha(&pilha);
            float resultado;

            if (strcmp(token, "sen") == 0) {
                resultado = sin(a * M_PI / 180); // Converte para radianos
            } else if (strcmp(token, "cos") == 0) {
                resultado = cos(a * M_PI / 180); // Converte para radianos
            } else if (strcmp(token, "tg") == 0) {
                resultado = tan(a * M_PI / 180); // Converte para radianos
            } else if (strcmp(token, "log") == 0) {
                if (a <= 0) {
                    printf("Erro: logaritmo de numero nao positivo.\n");
                    exit(1);
                }
                resultado = log10(a);
            } else if (strcmp(token, "raiz") == 0) {
                if (a < 0) {
                    printf("Erro: raiz quadrada de numero negativo.\n");
                    exit(1);
                }
                resultado = sqrt(a);
            }

            empilha(&pilha, resultado);
        } else if (strchr("+-*/^", token[0]) && strlen(token) == 1) {
            // Operadores binários
            float b = desempilha(&pilha);
            float a = desempilha(&pilha);
            float resultado;

            switch (token[0]) {
                case '+': resultado = a + b; break;
                case '-': resultado = a - b; break;
                case '*': resultado = a * b; break;
                case '/': 
                    if (b == 0) {
                        printf("Erro: divisao por zero.\n");
                        exit(1);
                    }
                    resultado = a / b; 
                    break;
                case '^': resultado = pow(a, b); break;
                default: 
                    printf("Operador invalido: %s\n", token);
                    exit(1);
            }

            empilha(&pilha, resultado);
        } else {
            printf("Operador invalido: %s\n", token);
            exit(1);
        }

        token = strtok(NULL, " ");
    }

    return desempilha(&pilha); // Retorna o valor final
}

// Função para converter notação pós-fixada para infixada
char *getFormaInFixa(char *str) {
    char pilha[512][512];
    int topo = -1;

    char *token = strtok(str, " "); // Divide a string por espaços

    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            strcpy(pilha[++topo], token);
        } else if (strcmp(token, "sen") == 0 || strcmp(token, "cos") == 0 ||
                   strcmp(token, "tg") == 0 || strcmp(token, "log") == 0 || strcmp(token, "raiz") == 0) {
            // Operadores unários
            if (topo < 0) {
                printf("Erro: expressao invalida.\n");
                exit(1);
            }
            char operando[512], subExpr[512];
            strcpy(operando, pilha[topo--]);

            // Formata a subexpressão com o operador unário
            sprintf(subExpr, "%s(%s)", token, operando);

            strcpy(pilha[++topo], subExpr);
        } else if (strchr("+-*/^", token[0]) && strlen(token) == 1) {
            // Operadores binários
            if (topo < 1) {
                printf("Erro: expressao invalida.\n");
                exit(1);
            }
            char operando2[512], operando1[512], subExpr[512];
            strcpy(operando2, pilha[topo--]);
            strcpy(operando1, pilha[topo--]);

            sprintf(subExpr, "(%s %s %s)", operando1, token, operando2);
            strcpy(pilha[++topo], subExpr);
        } else {
            printf("Operador invalido: %s\n", token);
            exit(1);
        }
        token = strtok(NULL, " ");
    }

    if (topo != 0) {
        printf("Erro: expressao pos-fixada invalida.\n");
        exit(1);
    }

    return strdup(pilha[topo]); // Retorna a expressão como string alocada dinamicamente
}
