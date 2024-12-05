#include <stdio.h>
#include <string.h>

#define NUM_ESTADOS 15

typedef struct {
    char nome[50];
    int numVeiculos;
    int numAcidentes;
} Estado;

void lerDados(Estado estados[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Digite o nome do estado %d: ", i + 1);
        scanf(" %[^\n]", estados[i].nome);
        printf("Digite o numero de veiculos no estado %d (em 2012): ", i + 1);
        scanf("%d", &estados[i].numVeiculos);
        printf("Digite o numero de acidentes no estado %d (em 2012): ", i + 1);
        scanf("%d", &estados[i].numAcidentes);
    }
}

void calcularMaiorMenorIndice(Estado estados[], int n) {
    int maiorIndice = estados[0].numAcidentes;
    int menorIndice = estados[0].numAcidentes;
    char estadoMaior[50], estadoMenor[50];

    strcpy(estadoMaior, estados[0].nome);
    strcpy(estadoMenor, estados[0].nome);

    for (int i = 1; i < n; i++) {
        if (estados[i].numAcidentes > maiorIndice) {
            maiorIndice = estados[i].numAcidentes;
            strcpy(estadoMaior, estados[i].nome);
        }
        if (estados[i].numAcidentes < menorIndice) {
            menorIndice = estados[i].numAcidentes;
            strcpy(estadoMenor, estados[i].nome);
        }
    }

    printf("\nMaior indice de acidentes: %d, Estado: %s\n", maiorIndice, estadoMaior);
    printf("Menor indice de acidentes: %d, Estado: %s\n", menorIndice, estadoMenor);
}

void calcularPercentualVeiculos(Estado estados[], int n) {
    int totalVeiculos = 0;
    for (int i = 0; i < n; i++) {
        totalVeiculos += estados[i].numVeiculos;
    }

    printf("\nPercentual de veiculos por estado:\n");
    for (int i = 0; i < n; i++) {
        float percentual = (estados[i].numVeiculos / (float)totalVeiculos) * 100;
        printf("%s: %.2f%%\n", estados[i].nome, percentual);
    }
}

void calcularMediaAcidentes(Estado estados[], int n) {
    printf("\nMedia de acidentes por estado:\n");
    for (int i = 0; i < n; i++) {
        float media = estados[i].numAcidentes / (float)estados[i].numVeiculos;
        printf("%s: %.2f\n", estados[i].nome, media);
    }
}

int main() {
    Estado estados[NUM_ESTADOS];

    printf("Coleta de dados sobre acidentes de transito em 15 estados:\n");
    lerDados(estados, NUM_ESTADOS);

    calcularMaiorMenorIndice(estados, NUM_ESTADOS);
    calcularPercentualVeiculos(estados, NUM_ESTADOS);
    calcularMediaAcidentes(estados, NUM_ESTADOS);

    return 0;
}
