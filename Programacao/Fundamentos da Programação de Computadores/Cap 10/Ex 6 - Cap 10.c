#include <stdio.h>
#include <string.h>

#define MAX_CLIENTES 100
#define MAX_CONTAS 100

typedef struct {
    int numeroCliente;
    char nome[100];
    char telefone[20];
    char endereco[150];
} Cliente;

typedef struct {
    int numeroConta;
    int numeroCliente;
    float saldo;
} ContaBancaria;

int buscarCliente(Cliente clientes[], int n, int numeroCliente) {
    for (int i = 0; i < n; i++) {
        if (clientes[i].numeroCliente == numeroCliente) {
            return i;
        }
    }
    return -1;
}

void cadastrarCliente(Cliente clientes[], int *n) {
    printf("Cadastro de novo cliente:\n");
    printf("Numero do cliente: ");
    scanf("%d", &clientes[*n].numeroCliente);
    printf("Nome: ");
    scanf(" %[^\n]", clientes[*n].nome);
    printf("Telefone: ");
    scanf(" %[^\n]", clientes[*n].telefone);
    printf("Endereco: ");
    scanf(" %[^\n]", clientes[*n].endereco);
    (*n)++;
    printf("Cliente cadastrado com sucesso!\n");
}

void cadastrarConta(ContaBancaria contas[], int *m, Cliente clientes[], int nClientes) {
    int numeroCliente;
    printf("Cadastro de conta bancaria:\n");
    printf("Numero do cliente titular da conta: ");
    scanf("%d", &numeroCliente);

    int indiceCliente = buscarCliente(clientes, nClientes, numeroCliente);
    if (indiceCliente == -1) {
        printf("Cliente nao cadastrado. Deseja cadastrar? (1 - Sim / 0 - Nao): ");
        int opcao;
        scanf("%d", &opcao);
        if (opcao == 1) {
            cadastrarCliente(clientes, &nClientes);
            numeroCliente = clientes[nClientes - 1].numeroCliente;
        } else {
            printf("Operacao cancelada.\n");
            return;
        }
    }

    contas[*m].numeroCliente = numeroCliente;
    printf("Numero da conta: ");
    scanf("%d", &contas[*m].numeroConta);
    printf("Saldo inicial: ");
    scanf("%f", &contas[*m].saldo);
    (*m)++;
    printf("Conta bancaria cadastrada com sucesso!\n");
}

void listarContas(ContaBancaria contas[], int m, Cliente clientes[], int nClientes) {
    printf("\nContas cadastradas:\n");
    for (int i = 0; i < m; i++) {
        printf("Conta numero: %d\n", contas[i].numeroConta);
        printf("Titular: ");
        for (int j = 0; j < nClientes; j++) {
            if (clientes[j].numeroCliente == contas[i].numeroCliente) {
                printf("%s\n", clientes[j].nome);
                break;
            }
        }
        printf("Saldo: %.2f\n", contas[i].saldo);
        printf("---------------------------\n");
    }
}

int main() {
    Cliente clientes[MAX_CLIENTES];
    ContaBancaria contas[MAX_CONTAS];
    int nClientes = 0, nContas = 0;

    int opcao;
    do {
    	
        printf("\nMenu:\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Cadastrar conta bancaria\n");
        printf("3. Listar contas cadastradas\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCliente(clientes, &nClientes);
                break;
            case 2:
                cadastrarConta(contas, &nContas, clientes, nClientes);
                break;
            case 3:
                listarContas(contas, nContas, clientes, nClientes);
                break;
            case 4:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}
