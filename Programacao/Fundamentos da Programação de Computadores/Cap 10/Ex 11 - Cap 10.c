#include <stdio.h>
#include <string.h>

#define MAX_MEDICOS 50
#define MAX_PACIENTES 50
#define MAX_CONSULTAS 100

typedef struct {
    int cod_medico;
    char nome[50];
    char endereco[100];
    float salario;
} Medico;

typedef struct {
    int cod_paciente;
    char nome[50];
    char endereco[100];
    int idade;
} Paciente;

typedef struct {
    int num_prontuario;
    char data_consulta[11];
    char diagnostico[100];
    int cod_medico;
    int cod_paciente;
} Consulta;

Medico medicos[MAX_MEDICOS];
Paciente pacientes[MAX_PACIENTES];
Consulta consultas[MAX_CONSULTAS];
int totalMedicos = 0, totalPacientes = 0, totalConsultas = 0;

void incluirAlterarMedico() {
    int cod, encontrado = 0;
    printf("Digite o codigo do medico (para incluir ou alterar): ");
    scanf("%d", &cod);

    for (int i = 0; i < totalMedicos; i++) {
        if (medicos[i].cod_medico == cod) {
            encontrado = 1;
            printf("Medico encontrado. Digite os novos dados:\n");
            printf("Nome: ");
            scanf(" %[^\n]", medicos[i].nome);
            printf("Endereco: ");
            scanf(" %[^\n]", medicos[i].endereco);
            printf("Salario: ");
            scanf("%f", &medicos[i].salario);
            break;
        }
    }

    if (!encontrado && totalMedicos < MAX_MEDICOS) {
        medicos[totalMedicos].cod_medico = cod;
        printf("Medico nao encontrado. Incluindo novo medico:\n");
        printf("Nome: ");
        scanf(" %[^\n]", medicos[totalMedicos].nome);
        printf("Endereco: ");
        scanf(" %[^\n]", medicos[totalMedicos].endereco);
        printf("Salario: ");
        scanf("%f", &medicos[totalMedicos].salario);
        totalMedicos++;
    }
}

void excluirMedico() {
    int cod, encontrado = 0, podeExcluir = 1;
    printf("Digite o codigo do medico a ser excluido: ");
    scanf("%d", &cod);

    for (int i = 0; i < totalConsultas; i++) {
        if (consultas[i].cod_medico == cod) {
            podeExcluir = 0;
            break;
        }
    }

    if (!podeExcluir) {
        printf("Exclusao nao permitida. Existem consultas associadas a este medico.\n");
        return;
    }

    for (int i = 0; i < totalMedicos; i++) {
        if (medicos[i].cod_medico == cod) {
            encontrado = 1;
            for (int j = i; j < totalMedicos - 1; j++) {
                medicos[j] = medicos[j + 1];
            }
            totalMedicos--;
            printf("Medico excluido com sucesso.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Medico nao encontrado.\n");
    }
}

void consultasPorData() {
    char data[11];
    printf("Digite a data para listar as consultas (formato DD/MM/AAAA): ");
    scanf(" %[^\n]", data);

    printf("\nConsultas realizadas na data %s:\n", data);
    for (int i = 0; i < totalConsultas; i++) {
        if (strcmp(consultas[i].data_consulta, data) == 0) {
            printf("Prontuario: %d\n", consultas[i].num_prontuario);
            printf("Diagnostico: %s\n", consultas[i].diagnostico);
           
            for (int j = 0; j < totalMedicos; j++) {
                if (medicos[j].cod_medico == consultas[i].cod_medico) {
                    printf("Medico: %s\n", medicos[j].nome);
                    break;
                }
            }

            for (int j = 0; j < totalPacientes; j++) {
                if (pacientes[j].cod_paciente == consultas[i].cod_paciente) {
                    printf("Paciente: %s\n", pacientes[j].nome);
                    break;
                }
            }

            printf("\n");
        }
    }
}

int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Incluir ou alterar medico\n");
        printf("2. Excluir medico\n");
        printf("3. Consultas por data\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                incluirAlterarMedico();
                break;
            case 2:
                excluirMedico();
                break;
            case 3:
                consultasPorData();
                break;
            case 4:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 4);

    return 0;
}
