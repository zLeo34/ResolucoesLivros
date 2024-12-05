#include <stdio.h>
#include <string.h>

#define MAX_TOMBOS 20
#define MAX_OBRAS 3

typedef struct {
    int numero_tombo;
    char nome_obra[50];
    char nome_autor[50];
    char nome_editora[50];
    int codigo_area;
} Tombo;

typedef struct {
    int numero_tombo;
    int numero_exemplar;
    char data_compra[11];
} Obra;

Tombo tombos[MAX_TOMBOS];
Obra obras[MAX_TOMBOS][MAX_OBRAS];
int totalTombos = 0;
int totalObras[MAX_TOMBOS] = {0};

void cadastrarTombo() {
    if (totalTombos >= MAX_TOMBOS) {
        printf("Numero maximo de tombos cadastrados.\n");
        return;
    }

    Tombo *t = &tombos[totalTombos];
    t->numero_tombo = totalTombos + 1;

    printf("Digite o nome da obra: ");
    scanf(" %[^\n]", t->nome_obra);

    printf("Digite o nome do autor: ");
    scanf(" %[^\n]", t->nome_autor);

    printf("Digite o nome da editora: ");
    scanf(" %[^\n]", t->nome_editora);

    printf("Digite o codigo da area (1-Exatas, 2-Humanas e Sociais, 3-Biomedicas): ");
    scanf("%d", &t->codigo_area);

    if (t->codigo_area < 1 || t->codigo_area > 3) {
        printf("Codigo de area invalido.\n");
        return;
    }

    totalTombos++;
    printf("Tombo cadastrado com sucesso!\n");
}

void cadastrarObra() {
    int numero_tombo;
    printf("Digite o numero do tombo para associar a obra: ");
    scanf("%d", &numero_tombo);

    if (numero_tombo < 1 || numero_tombo > totalTombos) {
        printf("Tombo nao encontrado.\n");
        return;
    }

    if (totalObras[numero_tombo - 1] >= MAX_OBRAS) {
        printf("Numero maximo de exemplares atingido para este tombo.\n");
        return;
    }

    Obra *o = &obras[numero_tombo - 1][totalObras[numero_tombo - 1]];
    o->numero_tombo = numero_tombo;
    o->numero_exemplar = totalObras[numero_tombo - 1] + 1;

    printf("Digite a data de compra (DD/MM/AAAA): ");
    scanf(" %[^\n]", o->data_compra);

    totalObras[numero_tombo - 1]++;
    printf("Obra cadastrada com sucesso!\n");
}

void mostrarObrasPorArea() {
    int codigo_area;
    printf("Digite o codigo da area (1-Exatas, 2-Humanas e Sociais, 3-Biomedicas): ");
    scanf("%d", &codigo_area);

    printf("Obras da area %d:\n", codigo_area);
    for (int i = 0; i < totalTombos; i++) {
        if (tombos[i].codigo_area == codigo_area) {
            printf("- %s, Autor: %s, Editora: %s\n", tombos[i].nome_obra, tombos[i].nome_autor, tombos[i].nome_editora);
        }
    }
}

void mostrarObrasPorAutor() {
    char autor[50];
    printf("Digite o nome do autor: ");
    scanf(" %[^\n]", autor);

    printf("Obras do autor %s:\n", autor);
    for (int i = 0; i < totalTombos; i++) {
        if (strcmp(tombos[i].nome_autor, autor) == 0) {
            printf("- %s, Editora: %s, Area: %d\n", tombos[i].nome_obra, tombos[i].nome_editora, tombos[i].codigo_area);
        }
    }
}

void mostrarObrasPorEditora() {
    char editora[50];
    printf("Digite o nome da editora: ");
    scanf(" %[^\n]", editora);

    printf("Obras da editora %s:\n", editora);
    for (int i = 0; i < totalTombos; i++) {
        if (strcmp(tombos[i].nome_editora, editora) == 0) {
            printf("- %s, Autor: %s, Area: %d\n", tombos[i].nome_obra, tombos[i].nome_autor, tombos[i].codigo_area);
        }
    }
}

int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar tombos\n");
        printf("2. Cadastrar obras\n");
        printf("3. Mostrar obras por area\n");
        printf("4. Mostrar obras por autor\n");
        printf("5. Mostrar obras por editora\n");
        printf("6. Encerrar o programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarTombo();
                break;
            case 2:
                cadastrarObra();
                break;
            case 3:
                mostrarObrasPorArea();
                break;
            case 4:
                mostrarObrasPorAutor();
                break;
            case 5:
                mostrarObrasPorEditora();
                break;
            case 6:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 6);

    return 0;
}

