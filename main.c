#include <stdio.h>
#include <string.h>
#include "expressao.h"

int main() {
    char expressao[512];
    int escolha;

    printf("Escolha uma opcao:\n");
    printf("1 - Avaliar valor da expressao pos-fixada\n");
    printf("2 - Converter para notacao infixada\n");
    printf("Opcao: ");
    scanf("%d", &escolha);
    getchar(); // Para consumir o '\n' deixado pelo scanf

    printf("Digite a expressao em notacao pos-fixada (ex: 3 4 + 5 *):\n");
    fgets(expressao, sizeof(expressao), stdin);

    // Remove o caractere de nova linha, se existir
    expressao[strcspn(expressao, "\n")] = '\0';

    if (escolha == 1) {
        // Avaliar valor da expressão
        float resultado = getValor(expressao);
        printf("O resultado da expressao '%s' eh: %.2f\n", expressao, resultado);
    } else if (escolha == 2) {
        // Converter para notação infixada
        char *infixa = getFormaInFixa(expressao);
        printf("A expressao infixada eh: %s\n", infixa);
        free(infixa); // Libera memória alocada em strdup (dentro da função getFormaInFixa)
    } else {
        printf("Opcao invalida.\n");
    }

    return 0;
}
