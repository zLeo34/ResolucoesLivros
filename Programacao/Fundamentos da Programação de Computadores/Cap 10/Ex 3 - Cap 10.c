#include <stdio.h>
#include <string.h>

#define NUM_HABITANTES 50

typedef struct {
    char sexo;
    float altura;
    int idade;
    char corOlhos;
} Habitante;

float calcularMediaIdade(Habitante habitantes[], int n) {
    int somaIdades = 0, contador = 0;
    for (int i = 0; i < n; i++) {
        if (habitantes[i].corOlhos == 'C' && habitantes[i].altura > 1.60) {
            somaIdades += habitantes[i].idade;
            contador++;
        }
    }
    return contador > 0 ? (float)somaIdades / contador : 0;
}

int encontrarMaiorIdade(Habitante habitantes[], int n) {
    int maiorIdade = habitantes[0].idade;
    for (int i = 1; i < n; i++) {
        if (habitantes[i].idade > maiorIdade) {
            maiorIdade = habitantes[i].idade;
        }
    }
    return maiorIdade;
}

int contarMulheresEspecificas(Habitante habitantes[], int n) {
    int contador = 0;
    for (int i = 0; i < n; i++) {
        if (habitantes[i].sexo == 'F' && 
           ((habitantes[i].idade >= 20 && habitantes[i].idade <= 45) || 
           (habitantes[i].corOlhos == 'V' && habitantes[i].altura < 1.70))) {
            contador++;
        }
    }
    return contador;
}

float calcularPercentualHomens(Habitante habitantes[], int n) {
    int totalHomens = 0;
    for (int i = 0; i < n; i++) {
        if (habitantes[i].sexo == 'M') {
            totalHomens++;
        }
    }
    return n > 0 ? ((float)totalHomens * 100.0) / n : 0.0;
}

int main() {
    Habitante habitantes[NUM_HABITANTES];
    for (int i = 0; i < NUM_HABITANTES; i++) {
        printf("Habitante %d:\n", i + 1);
        printf("  Sexo (M/F): ");
        scanf(" %c", &habitantes[i].sexo);
        printf("  Altura: ");
        scanf("%f", &habitantes[i].altura);
        printf("  Idade: ");
        scanf("%d", &habitantes[i].idade);
        printf("  Cor dos olhos (A/V/C): ");
        scanf(" %c", &habitantes[i].corOlhos);
    }

    float mediaIdade = calcularMediaIdade(habitantes, NUM_HABITANTES);
    int maiorIdade = encontrarMaiorIdade(habitantes, NUM_HABITANTES);
    int mulheresEspecificas = contarMulheresEspecificas(habitantes, NUM_HABITANTES);
    float percentualHomens = calcularPercentualHomens(habitantes, NUM_HABITANTES);

    printf("\nResultados:\n");
    printf("  Media de idade (olhos castanhos e altura > 1.60 m): %.2f\n", mediaIdade);
    printf("  Maior idade: %d\n", maiorIdade);
    printf("  Mulheres com idade entre 20 e 45 anos ou olhos verdes e altura < 1.70 m: %d\n", mulheresEspecificas);
    printf("  Percentual de homens: %.2f%%\n", percentualHomens);

    return 0;
}

