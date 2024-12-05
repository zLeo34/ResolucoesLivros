#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_CLIENTES 15000

typedef struct {
    char nome[50];
    char cpf[15];
    char rg[15];
    char endereco[100];
    struct tm data_primeira_compra;
    double total_gasto;
    int vip; 
} Cliente;

Cliente clientes[MAX_CLIENTES];
int totalClientes = 0;

void cadastrarCliente() {
    if (totalClientes >= MAX_CLIENTES) {
        printf("Numero maximo de clientes atingido.\n");
        return;
    }

    Cliente *c = &clientes[totalClientes];

    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", c->nome);

    printf("Digite o CPF do cliente: ");
    scanf(" %[^\n]", c->cpf);

    printf("Digite o RG do cliente: ");
    scanf(" %[^\n]", c->rg);

    printf("Digite o endereco do cliente: ");
    scanf(" %[^\n]", c->endereco);

    printf("Digite a data da primeira compra (DD MM YYYY): ");
    int dia, mes, ano;
    scanf("%d %d %d", &dia, &mes, &ano);
    c->data_primeira_compra.tm_mday = dia;
    c->data_primeira_compra.tm_mon = mes - 1; 
    c->data_primeira_compra.tm_year = ano - 1900; 

    c->total_gasto = 0.0;
    c->vip = 0; 

    printf("Cliente cadastrado com sucesso!\n");
    totalClientes++;
}

void atualizarGasto() {
    char rg[15];
    printf("Digite o RG do cliente: ");
    scanf(" %[^\n]", rg);

    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].rg, rg) == 0) {
            printf("Digite o valor da nova compra: ");
            double valor;
            scanf("%lf", &valor);

            clientes[i].total_gasto += valor;
            printf("Novo total gasto: %.2f\n", clientes[i].total_gasto);

            if (!clientes[i].vip && clientes[i].total_gasto >= 5000.0) {
                clientes[i].vip = 1;
                printf("Cliente agora e VIP!\n");
            }
            return;
        }
    }

    printf("Cliente nao encontrado.\n");
}

void verificarSeisMeses() {
    time_t agora = time(NULL);
    struct tm *data_atual = localtime(&agora);

    for (int i = 0; i < totalClientes; i++) {
        if (!clientes[i].vip) {
            double diferenca = difftime(mktime(data_atual), mktime(&clientes[i].data_primeira_compra));
            double dias = diferenca / (60 * 60 * 24);

            if (dias > 180) { 
                clientes[i].total_gasto = 0.0;
                printf("Cliente %s teve o total gasto zerado.\n", clientes[i].nome);
            }
        }
    }
}

void listarClientes() {
    printf("\nLista de clientes:\n");
    for (int i = 0; i < totalClientes; i++) {
        printf("Nome: %s, CPF: %s, RG: %s, VIP: %s, Total Gasto: %.2f\n",
               clientes[i].nome, clientes[i].cpf, clientes[i].rg,
               clientes[i].vip ? "SIM" : "NAO", clientes[i].total_gasto);
    }
}

int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Atualizar gasto\n");
        printf("3. Verificar clientes nao VIP com mais de 6 meses\n");
        printf("4. Listar clientes\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                atualizarGasto();
                break;
            case 3:
                verificarSeisMeses();
                break;
            case 4:
                listarClientes();
                break;
            case 5:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    return 0;
}
