#ifndef EXPRESSAO_H
#define EXPRESSAO_H

typedef struct {
    char posFixa[512];     // Expressão na forma pós-fixada, como "3 12 4 + *"
    char inFixa[512];      // Expressão na forma infixada, como "3 * (12 + 4)"
    float valor;           // Valor numérico da expressão
} Expressao;

// Protótipo: Converte uma expressão pós-fixada para infixada
char *getFormaInFixa(char *str);

// Protótipo: Calcula o valor de uma expressão pós-fixada
float getValor(char *str);

#endif
