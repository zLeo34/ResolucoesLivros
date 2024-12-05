#include <stdio.h>
#include <string.h>

#define MAX_CLIENTES 12
#define MAX_CONTAS 48
#define MAX_CONTAS_POR_CLIENTE 15

typedef struct {
    int numero_conta;
    double saldo_atual;
} Conta;

typedef struct {
    char nome[50];
    int idade;
    char endereco[100];
    char cpf_cnpj[20];
    int contas[MAX_CONTAS_POR_CLIENTE];
    int total_contas;
} Cliente;

Cliente clientes[MAX_CLIENTES];
Conta contas[MAX_CONTAS];
int totalClientes = 0;
int totalContas = 0;

void cadastrarCliente() {
    if (totalClientes >= MAX_CLIENTES) {
        printf("Numero maximo de clientes atingido.\n");
        return;
    }

    Cliente *c = &clientes[totalClientes];

    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", c->nome);

    printf("Digite a idade do cliente: ");
    scanf("%d", &c->idade);

    printf("Digite o endereco do cliente: ");
    scanf(" %[^\n]", c->endereco);

    printf("Digite o CPF/CNPJ do cliente: ");
    scanf(" %[^\n]", c->cpf_cnpj);

    c->total_contas = 0;

    printf("Cliente cadastrado com sucesso!\n");
    totalClientes++;
}

void cadastrarConta() {
    if (totalContas >= MAX_CONTAS) {
        printf("Numero maximo de contas atingido.\n");
        return;
    }

    int codigo_cliente;
    printf("Digite o codigo do cliente (0 a %d): ", totalClientes - 1);
    scanf("%d", &codigo_cliente);

    if (codigo_cliente < 0 || codigo_cliente >= totalClientes) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    Cliente *c = &clientes[codigo_cliente];
    if (c->total_contas >= MAX_CONTAS_POR_CLIENTE) {
        printf("Numero maximo de contas por cliente atingido.\n");
        return;
    }

    Conta *conta = &contas[totalContas];
    printf("Digite o numero da conta: ");
    scanf("%d", &conta->numero_conta);

    if (conta->numero_conta <= 0) {
        printf("Numero da conta invalido.\n");
        return;
    }

    printf("Digite o saldo atual da conta: ");
    scanf("%lf", &conta->saldo_atual);

    c->contas[c->total_contas] = totalContas;
    c->total_contas++;
    totalContas++;

    printf("Conta cadastrada com sucesso!\n");
}

void mostrarContas() {
    printf("Todas as contas cadastradas:\n");
    for (int i = 0; i < totalContas; i++) {
        printf("Conta %d: Saldo: %.2f\n", contas[i].numero_conta, contas[i].saldo_atual);
    }
}

void mostrarContasCliente() {
    int codigo_cliente;
    printf("Digite o codigo do cliente (0 a %d): ", totalClientes - 1);
    scanf("%d", &codigo_cliente);

    if (codigo_cliente < 0 || codigo_cliente >= totalClientes) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    Cliente *c = &clientes[codigo_cliente];
    printf("Contas do cliente %s:\n", c->nome);
    for (int i = 0; i < c->total_contas; i++) {
        int conta_id = c->contas[i];
        printf("Conta %d: Saldo: %.2f\n", contas[conta_id].numero_conta, contas[conta_id].saldo_atual);
    }
}

void somatorioContasCliente() {
    int codigo_cliente;
    printf("Digite o codigo do cliente (0 a %d): ", totalClientes - 1);
    scanf("%d", &codigo_cliente);

    if (codigo_cliente < 0 || codigo_cliente >= totalClientes) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    Cliente *c = &clientes[codigo_cliente];
    double soma = 0;

    for (int i = 0; i < c->total_contas; i++) {
        int conta_id = c->contas[i];
        soma += contas[conta_id].saldo_atual;
    }

    printf("Somatorio das contas do cliente %s: %.2f\n", c->nome, soma);
}

void mostrarContasSaldoNegativo() {
    printf("Contas com saldo negativo:\n");
    for (int i = 0; i < totalContas; i++) {
        if (contas[i].saldo_atual < 0) {
            printf("Conta %d: Saldo: %.2f\n", contas[i].numero_conta, contas[i].saldo_atual);
        }
    }
}

void ativoBancario() {
    double soma = 0;

    for (int i = 0; i < totalContas; i++) {
        soma += contas[i].saldo_atual;
    }

    printf("Ativo bancario total: %.2f\n", soma);
}

int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Cadastrar conta\n");
        printf("3. Mostrar todas as contas cadastradas\n");
        printf("4. Mostrar todas as contas de determinado cliente\n");
        printf("5. Mostrar somatorio das contas de determinado cliente\n");
        printf("6. Mostrar contas com saldo negativo\n");
        printf("7. Mostrar ativo bancario\n");
        printf("8. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                cadastrarConta();
                break;
            case 3:
                mostrarContas();
                break;
            case 4:
                mostrarContasCliente();
                break;
            case 5:
                somatorioContasCliente();
                break;
            case 6:
                mostrarContasSaldoNegativo();
                break;
            case 7:
                ativoBancario();
                break;
            case 8:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 8);

    return 0;
}
