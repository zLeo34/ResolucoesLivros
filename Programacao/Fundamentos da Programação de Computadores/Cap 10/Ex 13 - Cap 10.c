#include <stdio.h>
#include <string.h>

#define MAX_ESTILISTAS 3
#define MAX_ESTACOES 2
#define MAX_ROUPAS 10

typedef struct {
    int codigo;
    char nome[50];
    float salario;
} Estilista;

typedef struct {
    int codigo;
    char nome[50];
} Estacao;

typedef struct {
    int codigo;
    char descricao[100];
    int codigo_estilista;
    int codigo_estacao;
    int ano;
} Roupa;

Estilista estilistas[MAX_ESTILISTAS];
Estacao estacoes[MAX_ESTACOES];
Roupa roupas[MAX_ESTACOES][MAX_ROUPAS];
int totalRoupas[MAX_ESTACOES] = {0};

void cadastrarEstilistas() {
    for (int i = 0; i < MAX_ESTILISTAS; i++) {
        printf("Cadastro do estilista %d:\n", i + 1);
        printf("Codigo: ");
        scanf("%d", &estilistas[i].codigo);
        printf("Nome: ");
        scanf(" %[^\n]", estilistas[i].nome);
        printf("Salario: ");
        scanf("%f", &estilistas[i].salario);
        printf("Estilista cadastrado com sucesso!\n\n");
    }
}

void cadastrarEstacoes() {
    for (int i = 0; i < MAX_ESTACOES; i++) {
        printf("Cadastro da estacao %d:\n", i + 1);
        printf("Codigo: ");
        scanf("%d", &estacoes[i].codigo);
        printf("Nome: ");
        scanf(" %[^\n]", estacoes[i].nome);
        printf("Estacao cadastrada com sucesso!\n\n");
    }
}

int buscarEstilistaPorCodigo(int codigo) {
    for (int i = 0; i < MAX_ESTILISTAS; i++) {
        if (estilistas[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int buscarEstacaoPorCodigo(int codigo) {
    for (int i = 0; i < MAX_ESTACOES; i++) {
        if (estacoes[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void cadastrarRoupas() {
    int codigo_estacao;
    printf("Digite o codigo da estacao para cadastrar roupas: ");
    scanf("%d", &codigo_estacao);

    int indice_estacao = buscarEstacaoPorCodigo(codigo_estacao);
    if (indice_estacao == -1) {
        printf("Estacao nao cadastrada.\n");
        return;
    }

    if (totalRoupas[indice_estacao] >= MAX_ROUPAS) {
        printf("Limite de roupas atingido para esta estacao.\n");
        return;
    }

    Roupa *r = &roupas[indice_estacao][totalRoupas[indice_estacao]];
    printf("Codigo da roupa: ");
    scanf("%d", &r->codigo);
    printf("Descricao da roupa: ");
    scanf(" %[^\n]", r->descricao);
    printf("Codigo do estilista: ");
    scanf("%d", &r->codigo_estilista);

    int indice_estilista = buscarEstilistaPorCodigo(r->codigo_estilista);
    if (indice_estilista == -1) {
        printf("Estilista nao cadastrado.\n");
        return;
    }

    r->codigo_estacao = codigo_estacao;
    printf("Ano: ");
    scanf("%d", &r->ano);

    totalRoupas[indice_estacao]++;
    printf("Roupa cadastrada com sucesso!\n\n");
}

void listarRoupasPorEstacao() {
    int codigo_estacao;
    printf("Digite o codigo da estacao para listar roupas: ");
    scanf("%d", &codigo_estacao);

    int indice_estacao = buscarEstacaoPorCodigo(codigo_estacao);
    if (indice_estacao == -1) {
        printf("Estacao nao cadastrada.\n");
        return;
    }

    printf("\nRoupas da estacao %s:\n", estacoes[indice_estacao].nome);
    for (int i = 0; i < totalRoupas[indice_estacao]; i++) {
        Roupa *r = &roupas[indice_estacao][i];
        int indice_estilista = buscarEstilistaPorCodigo(r->codigo_estilista);
        printf("Codigo: %d\n", r->codigo);
        printf("Descricao: %s\n", r->descricao);
        printf("Ano: %d\n", r->ano);
        printf("Estilista: %s\n\n", estilistas[indice_estilista].nome);
    }
}

int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar estilistas\n");
        printf("2. Cadastrar estacoes\n");
        printf("3. Cadastrar roupas\n");
        printf("4. Listar roupas por estacao\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarEstilistas();
                break;
            case 2:
                cadastrarEstacoes();
                break;
            case 3:
                cadastrarRoupas();
                break;
            case 4:
                listarRoupasPorEstacao();
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
