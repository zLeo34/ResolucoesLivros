#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OS 100

typedef struct {
    int numero_os;
    char data[11];
    float valor;
    char servico_realizado[100];
    char cliente[50];
} OrdemServico;

OrdemServico ordens[MAX_OS];
int totalOrdens = 0;

void cadastrarOS() {
    if (totalOrdens >= MAX_OS) {
        printf("Numero maximo de ordens de servico atingido.\n");
        return;
    }

    OrdemServico *os = &ordens[totalOrdens];

    printf("Digite o numero da OS: ");
    scanf("%d", &os->numero_os);

    printf("Digite a data da OS (DD/MM/AAAA): ");
    scanf(" %[^\n]", os->data);

    printf("Digite o valor da OS: ");
    scanf("%f", &os->valor);

    printf("Digite o servico realizado: ");
    scanf(" %[^\n]", os->servico_realizado);

    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", os->cliente);

    totalOrdens++;
    printf("Ordem de servico cadastrada com sucesso!\n");
}

void calcularEstatisticas() {
    if (totalOrdens == 0) {
        printf("Nenhuma ordem de servico cadastrada.\n");
        return;
    }

    float somaValores = 0, mediaValores;
    float maiorValor = -1;
    char clienteMaisCaro[50], servicoMaisCaro[100], dataMaisCaro[11];

    for (int i = 0; i < totalOrdens; i++) {
        somaValores += ordens[i].valor;

        if (ordens[i].valor > maiorValor) {
            maiorValor = ordens[i].valor;
            strcpy(clienteMaisCaro, ordens[i].cliente);
            strcpy(servicoMaisCaro, ordens[i].servico_realizado);
            strcpy(dataMaisCaro, ordens[i].data);
        }
    }

    mediaValores = somaValores / totalOrdens;

    printf("\n===== Estatisticas =====\n");
    printf("Media dos valores: %.2f\n", mediaValores);
    printf("Servico mais caro:\n");
    printf("  Cliente: %s\n", clienteMaisCaro);
    printf("  Servico: %s\n", servicoMaisCaro);
    printf("  Data: %s\n", dataMaisCaro);
    printf("  Valor: %.2f\n", maiorValor);
    printf("========================\n");
}

void listarOrdens() {
    if (totalOrdens == 0) {
        printf("Nenhuma ordem de servico cadastrada.\n");
        return;
    }

    printf("\nLista de Ordens de Servico:\n");
    for (int i = 0; i < totalOrdens; i++) {
        printf("OS %d | Data: %s | Valor: %.2f | Servico: %s | Cliente: %s\n",
               ordens[i].numero_os, ordens[i].data, ordens[i].valor,
               ordens[i].servico_realizado, ordens[i].cliente);
    }
}

int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar ordem de servico\n");
        printf("2. Calcular estatisticas\n");
        printf("3. Listar ordens de servico\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarOS();
                break;
            case 2:
                calcularEstatisticas();
                break;
            case 3:
                listarOrdens();
                break;
            case 4:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 4);

    return 0;
}
