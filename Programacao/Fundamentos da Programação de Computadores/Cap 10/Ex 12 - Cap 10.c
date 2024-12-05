#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_CLIENTES 50
#define MAX_RECEBIMENTOS 3

typedef struct {
    int num_doc;
    float valor_doc;
    char data_emissao[11];
    char data_vencimento[11];
    int cod_cli;
} Recebimento;

typedef struct {
    int cod_cli;
    char nome[50];
    char endereco[100];
    char fone[20];
    Recebimento recebimentos[MAX_RECEBIMENTOS];
    int total_recebimentos;
} Cliente;

Cliente clientes[MAX_CLIENTES];
int totalClientes = 0;

void incluirCliente() {
    int cod, encontrado = 0;
    printf("Digite o codigo do cliente: ");
    scanf("%d", &cod);

    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].cod_cli == cod) {
            encontrado = 1;
            printf("Cliente ja cadastrado.\n");
            return;
        }
    }

    if (!encontrado && totalClientes < MAX_CLIENTES) {
        clientes[totalClientes].cod_cli = cod;
        printf("Nome: ");
        scanf(" %[^\n]", clientes[totalClientes].nome);
        printf("Endereco: ");
        scanf(" %[^\n]", clientes[totalClientes].endereco);
        printf("Telefone: ");
        scanf(" %[^\n]", clientes[totalClientes].fone);
        clientes[totalClientes].total_recebimentos = 0;
        totalClientes++;
        printf("Cliente cadastrado com sucesso.\n");
    } else {
        printf("Limite de clientes atingido.\n");
    }
}

void alterarCliente() {
    int cod, encontrado = 0;
    printf("Digite o codigo do cliente a ser alterado: ");
    scanf("%d", &cod);

    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].cod_cli == cod) {
            encontrado = 1;
            printf("Cliente encontrado. Digite os novos dados:\n");
            printf("Nome: ");
            scanf(" %[^\n]", clientes[i].nome);
            printf("Endereco: ");
            scanf(" %[^\n]", clientes[i].endereco);
            printf("Telefone: ");
            scanf(" %[^\n]", clientes[i].fone);
            printf("Dados alterados com sucesso.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente nao encontrado.\n");
    }
}

void incluirRecebimento() {
    int cod, encontrado = 0;
    printf("Digite o codigo do cliente: ");
    scanf("%d", &cod);

    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].cod_cli == cod) {
            encontrado = 1;
            if (clientes[i].total_recebimentos < MAX_RECEBIMENTOS) {
                Recebimento *r = &clientes[i].recebimentos[clientes[i].total_recebimentos];
                printf("Numero do documento: ");
                scanf("%d", &r->num_doc);
                printf("Valor do documento: ");
                scanf("%f", &r->valor_doc);
                printf("Data de emissao (DD/MM/AAAA): ");
                scanf(" %[^\n]", r->data_emissao);
                printf("Data de vencimento (DD/MM/AAAA): ");
                scanf(" %[^\n]", r->data_vencimento);
                r->cod_cli = cod;
                clientes[i].total_recebimentos++;
                printf("Recebimento cadastrado com sucesso.\n");
            } else {
                printf("Limite de recebimentos atingido para este cliente.\n");
            }
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente nao encontrado.\n");
    }
}

int calcularDiasAtraso(const char *data_venc, const char *data_atual) {
    struct tm tm_venc = {0}, tm_atual = {0};
    sscanf(data_venc, "%d/%d/%d", &tm_venc.tm_mday, &tm_venc.tm_mon, &tm_venc.tm_year);
    sscanf(data_atual, "%d/%d/%d", &tm_atual.tm_mday, &tm_atual.tm_mon, &tm_atual.tm_year);

    tm_venc.tm_mon -= 1;
    tm_venc.tm_year -= 1900;
    tm_atual.tm_mon -= 1;
    tm_atual.tm_year -= 1900;

    time_t t_venc = mktime(&tm_venc);
    time_t t_atual = mktime(&tm_atual);

    double diff = difftime(t_atual, t_venc) / (60 * 60 * 24);
    return (int)(diff > 0 ? diff : 0);
}

void listarRecebimentosPorPeriodo() {
    char dataInicio[11], dataFim[11];
    printf("Digite a data inicial (DD/MM/AAAA): ");
    scanf(" %[^\n]", dataInicio);
    printf("Digite a data final (DD/MM/AAAA): ");
    scanf(" %[^\n]", dataFim);

    printf("\nRecebimentos no periodo de %s a %s:\n", dataInicio, dataFim);
    for (int i = 0; i < totalClientes; i++) {
        for (int j = 0; j < clientes[i].total_recebimentos; j++) {
            Recebimento *r = &clientes[i].recebimentos[j];
            if (strcmp(r->data_vencimento, dataInicio) >= 0 && strcmp(r->data_vencimento, dataFim) <= 0) {
                int diasAtraso = calcularDiasAtraso(r->data_vencimento, dataFim);
                printf("Cliente: %s\n", clientes[i].nome);
                printf("Documento: %d\n", r->num_doc);
                printf("Valor: %.2f\n", r->valor_doc);
                printf("Data de Vencimento: %s\n", r->data_vencimento);
                printf("Dias de atraso: %d\n\n", diasAtraso);
            }
        }
    }
}

int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Incluir cliente\n");
        printf("2. Alterar cliente\n");
        printf("3. Incluir recebimento\n");
        printf("4. Listar recebimentos por periodo\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                incluirCliente();
                break;
            case 2:
                alterarCliente();
                break;
            case 3:
                incluirRecebimento();
                break;
            case 4:
                listarRecebimentosPorPeriodo();
                break;
            case 5:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 5);

    return 0;
}
