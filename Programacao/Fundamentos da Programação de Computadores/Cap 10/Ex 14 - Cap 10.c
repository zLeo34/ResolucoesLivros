#include <stdio.h>
#include <string.h>

#define MAX_MEDICOS 3
#define MAX_PACIENTES 5
#define MAX_CONSULTAS 10
#define DIAS_SEMANA 5

typedef struct {
    int cod_pac;
    char nome[50];
    char endereco[100];
    char fone[20];
} Paciente;

typedef struct {
    int cod_med;
    char nome[50];
    char fone[20];
    char endereco[100];
} Medico;

typedef struct {
    int num_consulta;
    char dia_semana[10]; 
    char hora[6];        
    int cod_med;
    int cod_pac;
} Consulta;

Paciente pacientes[MAX_PACIENTES];
Medico medicos[MAX_MEDICOS];
Consulta consultas[MAX_CONSULTAS];
int totalPacientes = 0, totalMedicos = 0, totalConsultas = 0;

int buscarPacientePorCodigo(int cod_pac) {
    for (int i = 0; i < totalPacientes; i++) {
        if (pacientes[i].cod_pac == cod_pac) {
            return i;
        }
    }
    return -1;
}

int buscarMedicoPorCodigo(int cod_med) {
    for (int i = 0; i < totalMedicos; i++) {
        if (medicos[i].cod_med == cod_med) {
            return i;
        }
    }
    return -1;
}

void cadastrarPaciente() {
    if (totalPacientes >= MAX_PACIENTES) {
        printf("Numero maximo de pacientes atingido.\n");
        return;
    }

    int cod_pac;
    printf("Digite o codigo do paciente: ");
    scanf("%d", &cod_pac);

    if (buscarPacientePorCodigo(cod_pac) != -1) {
        printf("Paciente com este codigo ja cadastrado.\n");
        return;
    }

    Paciente *p = &pacientes[totalPacientes];
    p->cod_pac = cod_pac;
    printf("Digite o nome do paciente: ");
    scanf(" %[^\n]", p->nome);
    printf("Digite o endereco do paciente: ");
    scanf(" %[^\n]", p->endereco);
    printf("Digite o telefone do paciente: ");
    scanf(" %[^\n]", p->fone);

    totalPacientes++;
    printf("Paciente cadastrado com sucesso!\n");
}

void cadastrarMedico() {
    if (totalMedicos >= MAX_MEDICOS) {
        printf("Numero maximo de medicos atingido.\n");
        return;
    }

    int cod_med;
    printf("Digite o codigo do medico: ");
    scanf("%d", &cod_med);

    if (buscarMedicoPorCodigo(cod_med) != -1) {
        printf("Medico com este codigo ja cadastrado.\n");
        return;
    }

    Medico *m = &medicos[totalMedicos];
    m->cod_med = cod_med;
    printf("Digite o nome do medico: ");
    scanf(" %[^\n]", m->nome);
    printf("Digite o endereco do medico: ");
    scanf(" %[^\n]", m->endereco);
    printf("Digite o telefone do medico: ");
    scanf(" %[^\n]", m->fone);

    totalMedicos++;
    printf("Medico cadastrado com sucesso!\n");
}

void cadastrarConsulta() {
    if (totalConsultas >= MAX_CONSULTAS) {
        printf("Numero maximo de consultas atingido.\n");
        return;
    }

    int cod_med, cod_pac;
    char dia[10];
    printf("Digite o codigo do medico: ");
    scanf("%d", &cod_med);

    if (buscarMedicoPorCodigo(cod_med) == -1) {
        printf("Medico nao encontrado.\n");
        return;
    }

    printf("Digite o codigo do paciente: ");
    scanf("%d", &cod_pac);

    if (buscarPacientePorCodigo(cod_pac) == -1) {
        printf("Paciente nao encontrado.\n");
        return;
    }

    printf("Digite o dia da semana (segunda a sexta): ");
    scanf(" %[^\n]", dia);

    int consultasDia = 0;
    for (int i = 0; i < totalConsultas; i++) {
        if (strcmp(consultas[i].dia_semana, dia) == 0 && consultas[i].cod_med == cod_med) {
            consultasDia++;
        }
    }

    if (consultasDia >= 2) {
        printf("O medico ja possui duas consultas para este dia.\n");
        return;
    }

    Consulta *c = &consultas[totalConsultas];
    c->num_consulta = totalConsultas + 1;
    strcpy(c->dia_semana, dia);
    printf("Digite o horario da consulta (HH:MM): ");
    scanf(" %[^\n]", c->hora);
    c->cod_med = cod_med;
    c->cod_pac = cod_pac;

    totalConsultas++;
    printf("Consulta cadastrada com sucesso!\n");
}

void pesquisarConsultasMedico() {
    int cod_med;
    char dia[10];
    printf("Digite o codigo do medico: ");
    scanf("%d", &cod_med);
    printf("Digite o dia da semana (segunda a sexta): ");
    scanf(" %[^\n]", dia);

    printf("Consultas do medico %d no dia %s:\n", cod_med, dia);
    for (int i = 0; i < totalConsultas; i++) {
        if (consultas[i].cod_med == cod_med && strcmp(consultas[i].dia_semana, dia) == 0) {
            printf("Consulta %d - Paciente %d - Hora: %s\n",
                   consultas[i].num_consulta,
                   consultas[i].cod_pac,
                   consultas[i].hora);
        }
    }
}

void listarConsultasDia() {
    char dia[10];
    printf("Digite o dia da semana (segunda a sexta): ");
    scanf(" %[^\n]", dia);

    printf("Consultas realizadas no dia %s:\n", dia);
    for (int i = 0; i < totalConsultas; i++) {
        if (strcmp(consultas[i].dia_semana, dia) == 0) {
            int medIndex = buscarMedicoPorCodigo(consultas[i].cod_med);
            int pacIndex = buscarPacientePorCodigo(consultas[i].cod_pac);
            printf("Consulta %d - Hora: %s - Medico: %s - Paciente: %s\n",
                   consultas[i].num_consulta,
                   consultas[i].hora,
                   medicos[medIndex].nome,
                   pacientes[pacIndex].nome);
        }
    }
}

int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar paciente\n");
        printf("2. Cadastrar medico\n");
        printf("3. Cadastrar consulta\n");
        printf("4. Pesquisar consultas de medico\n");
        printf("5. Listar consultas do dia\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarPaciente();
                break;
            case 2:
                cadastrarMedico();
                break;
            case 3:
                cadastrarConsulta();
                break;
            case 4:
                pesquisarConsultasMedico();
                break;
            case 5:
                listarConsultasDia();
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 6);

    return 0;
}
