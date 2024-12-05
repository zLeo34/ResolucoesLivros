#include <stdio.h>

#define NUM_HABITANTES 20

float calcularMedia(float soma, int quantidade) {
    return soma / quantidade;
}

float calcularPercentual(int totalMulheres, int mulheresCondicao) {
    return (mulheresCondicao * 100.0) / totalMulheres;
}

int main() {
    float salarios[NUM_HABITANTES], somaSalarios = 0, maiorSalario = 0;
    int idades[NUM_HABITANTES], filhos[NUM_HABITANTES], somaFilhos = 0, mulheresComSalarioAlto = 0, totalMulheres = 0;
    char generos[NUM_HABITANTES];
    
    for (int i = 0; i < NUM_HABITANTES; i++) {
        printf("Habitante %d:\n", i + 1);
        printf("  Genero (M/F): ");
        scanf(" %c", &generos[i]);
        printf("  Salario: ");
        scanf("%f", &salarios[i]);
        printf("  Idade: ");
        scanf("%d", &idades[i]);
        printf("  Numero de filhos: ");
        scanf("%d", &filhos[i]);
        
        somaSalarios += salarios[i];
        somaFilhos += filhos[i];
        if (salarios[i] > maiorSalario) {
            maiorSalario = salarios[i];
        }
        if (generos[i] == 'F'|| generos[i] == 'f') {
            totalMulheres++;
            if (salarios[i] > 1000.0) {
                mulheresComSalarioAlto++;
            }
        }
    }
    
    float mediaSalarios = calcularMedia(somaSalarios, NUM_HABITANTES);
    float mediaFilhos = calcularMedia(somaFilhos, NUM_HABITANTES);
    float percentualMulheresSalarioAlto = totalMulheres > 0 ? calcularPercentual(totalMulheres, mulheresComSalarioAlto) : 0;
    
    printf("\nResultados:\n");
    printf("  Media de salarios: R$ %.2f\n", mediaSalarios);
    printf("  Media do numero de filhos: %.2f\n", mediaFilhos);
    printf("  Maior salario: R$ %.2f\n", maiorSalario);
    printf("  Percentual de mulheres com salario superior a R$ 1.000,00: %.2f%%\n", percentualMulheresSalarioAlto);

    return 0;
}
