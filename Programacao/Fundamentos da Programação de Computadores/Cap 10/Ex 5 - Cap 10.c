#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUM_PRODUTOS 50
#define MAX_DESC 100

typedef struct {
    int codigo;
    char descricao[MAX_DESC];
    float valorUnitario;
    int quantidadeEstoque;
} Produto;

void ordenarProdutos(Produto produtos[], int n) {
    Produto temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (produtos[j].codigo > produtos[j + 1].codigo) {
                temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
            }
        }
    }
}

void alterarProduto(Produto produtos[], int n, int codigo) {
    for (int i = 0; i < n; i++) {
        if (produtos[i].codigo == codigo) {
            printf("Produto encontrado: %s\n", produtos[i].descricao);
            printf("Nova descricao: ");
            scanf(" %[^\n]s", produtos[i].descricao);
            printf("Novo valor unitario: ");
            scanf("%f", &produtos[i].valorUnitario);
            printf("Nova quantidade em estoque: ");
            scanf("%d", &produtos[i].quantidadeEstoque);
            printf("Alteracoes realizadas com sucesso!\n");
            return;
        }
    }
    printf("Produto com codigo %d nao encontrado.\n", codigo);
}

void mostrarProdutosPorLetra(Produto produtos[], int n, char letra) {
    printf("Produtos que comecam com '%c':\n", letra);
    int encontrou = 0;
    for (int i = 0; i < n; i++) {
        if (toupper(produtos[i].descricao[0]) == toupper(letra)) {
            printf("Codigo: %d, Descricao: %s, Valor: %.2f, Estoque: %d\n",
                   produtos[i].codigo, produtos[i].descricao, produtos[i].valorUnitario, produtos[i].quantidadeEstoque);
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhum produto encontrado.\n");
    }
}

void mostrarProdutosBaixoEstoque(Produto produtos[], int n) {
    printf("Produtos com estoque inferior a 5 unidades:\n");
    int encontrou = 0;
    for (int i = 0; i < n; i++) {
        if (produtos[i].quantidadeEstoque < 5) {
            printf("Codigo: %d, Descricao: %s, Valor: %.2f, Estoque: %d\n",
                   produtos[i].codigo, produtos[i].descricao, produtos[i].valorUnitario, produtos[i].quantidadeEstoque);
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhum produto com estoque baixo encontrado.\n");
    }
}

int main() {
    Produto produtos[NUM_PRODUTOS];

    for (int i = 0; i < NUM_PRODUTOS; i++) {
        printf("Produto %d:\n", i + 1);
        printf("Codigo: ");
        scanf("%d", &produtos[i].codigo);
        printf("Descricao: ");
        scanf(" %[^\n]s", produtos[i].descricao);
        printf("Valor unitario: ");
        scanf("%f", &produtos[i].valorUnitario);
        printf("Quantidade em estoque: ");
        scanf("%d", &produtos[i].quantidadeEstoque);
    }

    ordenarProdutos(produtos, NUM_PRODUTOS);

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Alterar produto\n");
        printf("2. Mostrar produtos por letra inicial\n");
        printf("3. Mostrar produtos com estoque baixo\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int codigo;
                printf("Informe o codigo do produto: ");
                scanf("%d", &codigo);
                alterarProduto(produtos, NUM_PRODUTOS, codigo);
                break;
            }
            case 2: {
                char letra;
                printf("Informe a letra inicial: ");
                scanf(" %c", &letra);
                mostrarProdutosPorLetra(produtos, NUM_PRODUTOS, letra);
                break;
            }
            case 3:
                mostrarProdutosBaixoEstoque(produtos, NUM_PRODUTOS);
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 4);

    return 0;
}
