#include <stdio.h>
#include <string.h>

#define MAX_COZINHEIROS 3
#define MAX_INGREDIENTES 15
#define MAX_RECEITAS 20
#define MAX_INGREDIENTES_RECEITA 3

typedef struct {
    int codigo;
    char nome[50];
} Cozinheiro;

typedef struct {
    int codigo;
    char descricao[50];
} Ingrediente;

typedef struct {
    int codigo_receita;
    char nome_receita[50];
    float calorias_por_100g;
    int codigo_cozinheiro;
    int ingredientes[MAX_INGREDIENTES_RECEITA];
    float quantidades[MAX_INGREDIENTES_RECEITA];
    char unidades[MAX_INGREDIENTES_RECEITA][10];
    int total_ingredientes;
} Receita;

Cozinheiro cozinheiros[MAX_COZINHEIROS];
Ingrediente ingredientes[MAX_INGREDIENTES];
Receita receitas[MAX_RECEITAS];

int totalCozinheiros = 0;
int totalIngredientes = 0;
int totalReceitas = 0;

void cadastrarCozinheiro() {
    if (totalCozinheiros >= MAX_COZINHEIROS) {
        printf("Numero maximo de cozinheiros atingido.\n");
        return;
    }

    Cozinheiro *c = &cozinheiros[totalCozinheiros];
    c->codigo = totalCozinheiros + 1;
    printf("Digite o nome do cozinheiro: ");
    scanf(" %[^\n]", c->nome);

    totalCozinheiros++;
    printf("Cozinheiro cadastrado com sucesso!\n");
}

void cadastrarIngrediente() {
    if (totalIngredientes >= MAX_INGREDIENTES) {
        printf("Numero maximo de ingredientes atingido.\n");
        return;
    }

    Ingrediente *i = &ingredientes[totalIngredientes];
    i->codigo = totalIngredientes + 1;
    printf("Digite a descricao do ingrediente: ");
    scanf(" %[^\n]", i->descricao);

    totalIngredientes++;
    printf("Ingrediente cadastrado com sucesso!\n");
}

void cadastrarReceita() {
    if (totalReceitas >= MAX_RECEITAS) {
        printf("Numero maximo de receitas atingido.\n");
        return;
    }

    Receita *r = &receitas[totalReceitas];
    r->codigo_receita = totalReceitas + 1;
    printf("Digite o nome da receita: ");
    scanf(" %[^\n]", r->nome_receita);

    printf("Digite o total de calorias por 100g: ");
    scanf("%f", &r->calorias_por_100g);

    printf("Digite o codigo do cozinheiro: ");
    scanf("%d", &r->codigo_cozinheiro);

    if (r->codigo_cozinheiro < 1 || r->codigo_cozinheiro > MAX_COZINHEIROS) {
        printf("Cozinheiro invalido.\n");
        return;
    }

    printf("Digite o numero de ingredientes (maximo %d): ", MAX_INGREDIENTES_RECEITA);
    scanf("%d", &r->total_ingredientes);

    if (r->total_ingredientes > MAX_INGREDIENTES_RECEITA) {
        printf("Numero de ingredientes excede o limite permitido.\n");
        return;
    }

    for (int i = 0; i < r->total_ingredientes; i++) {
        printf("Digite o codigo do ingrediente %d: ", i + 1);
        scanf("%d", &r->ingredientes[i]);

        printf("Digite a quantidade do ingrediente %d: ", i + 1);
        scanf("%f", &r->quantidades[i]);

        printf("Digite a unidade de medida do ingrediente %d: ", i + 1);
        scanf(" %[^\n]", r->unidades[i]);
    }

    totalReceitas++;
    printf("Receita cadastrada com sucesso!\n");
}

void mostrarReceitasPorCozinheiro() {
    int codigo;
    printf("Digite o codigo do cozinheiro: ");
    scanf("%d", &codigo);

    printf("Receitas elaboradas pelo cozinheiro %d:\n", codigo);
    for (int i = 0; i < totalReceitas; i++) {
        if (receitas[i].codigo_cozinheiro == codigo) {
            printf("- %s\n", receitas[i].nome_receita);
        }
    }
}

void mostrarReceitasPorCalorias() {
    float minCalorias, maxCalorias;
    printf("Digite o intervalo de calorias (min max): ");
    scanf("%f %f", &minCalorias, &maxCalorias);

    printf("Receitas com calorias entre %.2f e %.2f:\n", minCalorias, maxCalorias);
    for (int i = 0; i < totalReceitas; i++) {
        if (receitas[i].calorias_por_100g >= minCalorias && receitas[i].calorias_por_100g <= maxCalorias) {
            printf("- %s\n", receitas[i].nome_receita);
        }
    }
}

void mostrarTotalReceitasPorCozinheiro() {
    int total[MAX_COZINHEIROS] = {0};

    for (int i = 0; i < totalReceitas; i++) {
        total[receitas[i].codigo_cozinheiro - 1]++;
    }

    for (int i = 0; i < totalCozinheiros; i++) {
        printf("Cozinheiro %s elaborou %d receitas.\n", cozinheiros[i].nome, total[i]);
    }
}

int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar cozinheiro\n");
        printf("2. Cadastrar ingrediente\n");
        printf("3. Cadastrar receita\n");
        printf("4. Mostrar receitas por cozinheiro\n");
        printf("5. Mostrar receitas por calorias\n");
        printf("6. Mostrar total de receitas por cozinheiro\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCozinheiro();
                break;
            case 2:
                cadastrarIngrediente();
                break;
            case 3:
                cadastrarReceita();
                break;
            case 4:
                mostrarReceitasPorCozinheiro();
                break;
            case 5:
                mostrarReceitasPorCalorias();
                break;
            case 6:
                mostrarTotalReceitasPorCozinheiro();
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 7);

    return 0;
}
