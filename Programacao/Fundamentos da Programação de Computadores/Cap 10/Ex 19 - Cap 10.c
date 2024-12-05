#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CLIENTES 9999

typedef struct {
    int registro;
    char nome[50];
    char data_nascimento[11];
    char cpf[15];
    char rg[15];
    char cidade[50];
    char endereco[100];
    int quantidade_produtos;
} Cliente;

Cliente clientes[MAX_CLIENTES];
int totalClientes = 0;

void cadastrarCliente() {
    if (totalClientes >= MAX_CLIENTES) {
        printf("Numero maximo de clientes atingido.\n");
        return;
    }

    Cliente *c = &clientes[totalClientes];
    c->registro = totalClientes + 1;

    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", c->nome);

    printf("Digite a data de nascimento (DD/MM/AAAA): ");
    scanf(" %[^\n]", c->data_nascimento);

    printf("Digite o CPF do cliente: ");
    scanf(" %[^\n]", c->cpf);

    printf("Digite o RG do cliente: ");
    scanf(" %[^\n]", c->rg);

    printf("Digite a cidade do cliente: ");
    scanf(" %[^\n]", c->cidade);

    printf("Digite o endereco do cliente: ");
    scanf(" %[^\n]", c->endereco);

    printf("Digite a quantidade de produtos adquiridos: ");
    scanf("%d", &c->quantidade_produtos);

    totalClientes++;
    printf("Cliente cadastrado com sucesso! Registro: %d\n", c->registro);
}

void realizarSorteio() {
    if (totalClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    int participantes[MAX_CLIENTES];
    int totalParticipantes = 0;

    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].quantidade_produtos > 5) {
            participantes[totalParticipantes++] = clientes[i].registro;
        }
    }

    if (totalParticipantes == 0) {
        printf("Nenhum cliente elegivel para o sorteio.\n");
        return;
    }

    srand(time(NULL));
    int indiceSorteado = rand() % totalParticipantes;
    int registroGanhador = participantes[indiceSorteado];

    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].registro == registroGanhador) {
            printf("\n===== GANHADOR DO SORTEIO =====\n");
            printf("Registro: %d\n", clientes[i].registro);
            printf("Nome: %s\n", clientes[i].nome);
            printf("CPF: %s\n", clientes[i].cpf);
            printf("Quantidade de Produtos: %d\n", clientes[i].quantidade_produtos);
            printf("================================\n");
            return;
        }
    }
}

void listarClientes() {
    if (totalClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    printf("\nLista de Clientes:\n");
    for (int i = 0; i < totalClientes; i++) {
        printf("Registro: %d | Nome: %s | CPF: %s | Produtos: %d\n",
               clientes[i].registro, clientes[i].nome, clientes[i].cpf, clientes[i].quantidade_produtos);
    }
}

int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Realizar sorteio\n");
        printf("3. Listar clientes\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                realizarSorteio();
                break;
            case 3:
                listarClientes();
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
