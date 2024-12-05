#include <stdio.h>

int main() {
    float salarioFixo, valorVendas, comissao, salarioFinal;

    printf("Digite o salario fixo do funcionario: ");
    scanf("%f", &salarioFixo);

    printf("Digite o valor total das vendas do funcionario: ");
    scanf("%f", &valorVendas);

    comissao = valorVendas * 0.06;
    salarioFinal = salarioFixo + comissao;

    printf("\nSalario fixo: R$ %.2f\n", salarioFixo);
    printf("Valor total das vendas: R$ %.2f\n", valorVendas);
    printf("Comissao (6%% das vendas): R$ %.2f\n", comissao);
    printf("Salario final: R$ %.2f\n", salarioFinal);

    return 0;
}
