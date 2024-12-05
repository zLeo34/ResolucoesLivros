#include <stdio.h>

#define NUM_HABITANTES 20

typedef struct {
    int idade;
    char sexo;        
    float rendaFamiliar;
    int numFilhos;
} Habitante;

float calcularMediaSalario(Habitante habitantes[], int n) {
    float somaRenda = 0;
    for (int i = 0; i < n; i++) {
        somaRenda += habitantes[i].rendaFamiliar;
    }
    return somaRenda / n;
}

void calcularIdadeExtremos(Habitante habitantes[], int n, int *menorIdade, int *maiorIdade) {
    *menorIdade = habitantes[0].idade;
    *maiorIdade = habitantes[0].idade;
    for (int i = 1; i < n; i++) {
        if (habitantes[i].idade < *menorIdade) {
            *menorIdade = habitantes[i].idade;
        }
        if (habitantes[i].idade > *maiorIdade) {
            *maiorIdade = habitantes[i].idade;
        }
    }
}

int contarMulheresEspecificas(Habitante habitantes[], int n) {
    int contador = 0;
    for (int i = 0; i < n; i++) {
        if (habitantes[i].sexo == 'F' && habitantes[i].numFilhos > 2 && habitantes[i].rendaFamiliar < 600.0) {
            contador++;
        }
    }
    return contador;
}

int main() {
    Habitante habitantes[NUM_HABITANTES];

    for (int i = 0; i < NUM_HABITANTES; i++) {
        printf("Habitante %d:\n", i + 1);
        printf("  Idade: ");
        scanf("%d", &habitantes[i].idade);
        printf("  Sexo (M/F): ");
        scanf(" %c", &habitantes[i].sexo);
        printf("  Renda familiar: ");
        scanf("%f", &habitantes[i].rendaFamiliar);
        printf("  Numero de filhos: ");
        scanf("%d", &habitantes[i].numFilhos);
    }

    float mediaSalario = calcularMediaSalario(habitantes, NUM_HABITANTES);
    int menorIdade, maiorIdade;
    calcularIdadeExtremos(habitantes, NUM_HABITANTES, &menorIdade, &maiorIdade);
    int mulheresEspecificas = contarMulheresEspecificas(habitantes, NUM_HABITANTES);

    printf("\nResultados:\n");
    printf("  Media de salario entre os habitantes: R$ %.2f\n", mediaSalario);
    printf("  Menor idade: %d\n", menorIdade);
    printf("  Maior idade: %d\n", maiorIdade);
    printf("  Mulheres com mais de 2 filhos e renda inferior a R$ 600,00: %d\n", mulheresEspecificas);

    return 0;
}
