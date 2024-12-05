#include <stdio.h>
#include <string.h>

#define MAX_CLIENTES 100
#define MAX_CONTAS 100

typedef struct {
    int codigoCliente;
    char nomeCliente[100];
} Cliente;

typedef struct {
    int numeroConta;
    float valorCompra;
    int codigoCliente;
} Conta;

int buscarCliente(Cliente clientes[], int n, int codigoCliente) {
    for (int i = 0; i < n; i++) {
        if (clientes[i].codigoCliente == codigoCliente) {
            return i;
        }
    }
    return -1;
}

int clientePossuiContas(Conta contas[], int n, int codigoCliente) {
    for (int i = 0; i < n; i++) {
        if (contas[i].codigoCliente == codigoCliente) {
            return 1;
        }
    }
    return 0;
}

void incluirCliente(Cliente clientes[], int *n) {
    int codigoCliente;
    printf("Codigo do cliente: ");
    scanf("%d", &codigoCliente);

    if (buscarCliente(clientes, *n, codigoCliente) != -1) {
        printf("Erro: Ja existe um cliente com este codigo.\n");
        return;
    }

    clientes[*n].codigoCliente = codigoCliente;
    printf("Nome do cliente: ");
    scanf(" %[^\n]", clientes[*n].nomeCliente);
    (*n)++;
    printf("Cliente cadastrado com sucesso!\n");
}

void incluirConta(Conta contas[], int *m, Cliente clientes[], int nClientes) {
    int codigoCliente;
    printf("Codigo do cliente: ");
    scanf("%d", &codigoCliente);

    if (buscarCliente(clientes, nClientes, codigoCliente) == -1) {
        printf("Erro: Cliente nao cadastrado. Inclusao de conta nao permitida.\n");
        return;
    }

    contas[*m].codigoCliente = codigoCliente;
    printf("Numero da conta: ");
    scanf("%d", &contas[*m].numeroConta);
    printf("Valor da compra: ");
    scanf("%f", &contas[*m].valorCompra);
    (*m)++;
    printf("Conta cadastrada com sucesso!\n");
}

void removerCliente(Cliente clientes[], int *nClientes, Conta contas[], int nContas) {
    int codigoCliente;
    printf("Codigo do cliente a ser removido: ");
    scanf("%d", &codigoCliente);

    int indiceCliente = buscarCliente(clientes, *nClientes, codigoCliente);

    if (indiceCliente == -1) {
        printf("Erro: Cliente nao encontrado.\n");
        return;
    }

    if (clientePossuiContas(contas, nContas, codigoCliente)) {
        printf("Exclusao nao permitida: Cliente vinculado a uma ou mais contas.\n");
        return;
    }

    for (int i = indiceCliente; i < (*nClientes) - 1; i++) {
        clientes[i] = clientes[i + 1];
    }
    (*nClientes)--;
    printf("Cliente removido com sucesso!\n");
}

void listarClientes(Cliente clientes[], int n) {
    printf("\nClientes cadastrados:\n");
    for (int i = 0; i < n; i++) {
        printf("Codigo: %d, Nome: %s\n", clientes[i].codigoCliente, clientes[i].nomeCliente);
    }
}

void listarContas(Conta contas[], int m) {
    printf("\nContas cadastradas:\n");
    for (int i = 0; i < m; i++) {
        printf("Numero da conta: %d, Codigo do cliente: %d, Valor da compra: %.2f\n",
               contas[i].numeroConta, contas[i].codigoCliente, contas[i].valorCompra);
    }
}

int main() {
    Cliente clientes[MAX_CLIENTES];
    Conta contas[MAX_CONTAS];
    int nClientes = 0, nContas = 0;

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Incluir cliente\n");
        printf("2. Incluir conta\n");
        printf("3. Remover cliente\n");
        printf("4. Listar clientes\n");
        printf("5. Listar contas\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                incluirCliente(clientes, &nClientes);
                break;
            case 2:
                incluirConta(contas, &nContas, clientes, nClientes);
                break;
            case 3:
                removerCliente(clientes, &nClientes, contas, nContas);
                break;
            case 4:
                listarClientes(clientes, nClientes);
                break;
            case 5:
                listarContas(contas, nContas);
                break;
            case 6:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}
