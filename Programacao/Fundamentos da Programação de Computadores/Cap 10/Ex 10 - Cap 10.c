#include <stdio.h>
#include <string.h>

#define NUM_DOCUMENTOS 15

typedef struct {
    int numeroDocumento;
    int codigoCliente;
    int diaVencimento, mesVencimento, anoVencimento;
    int diaPagamento, mesPagamento, anoPagamento;
    float valorConta;
    float juros;
} Documento;

int calcularDiasAtraso(int diaV, int mesV, int anoV, int diaP, int mesP, int anoP) {
    int diasVenc = diaV + mesV * 30 + anoV * 365;
    int diasPag = diaP + mesP * 30 + anoP * 365;
    return diasPag - diasVenc;
}

void lerDados(Documento documentos[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Documento %d:\n", i + 1);
        printf("Numero do documento: ");
        scanf("%d", &documentos[i].numeroDocumento);
        printf("Codigo do cliente: ");
        scanf("%d", &documentos[i].codigoCliente);
        printf("Data de vencimento (DD MM AAAA): ");
        scanf("%d %d %d", &documentos[i].diaVencimento, &documentos[i].mesVencimento, &documentos[i].anoVencimento);
        printf("Data de pagamento (DD MM AAAA): ");
        scanf("%d %d %d", &documentos[i].diaPagamento, &documentos[i].mesPagamento, &documentos[i].anoPagamento);
        printf("Valor da conta: ");
        scanf("%f", &documentos[i].valorConta);

        int diasAtraso = calcularDiasAtraso(
            documentos[i].diaVencimento, documentos[i].mesVencimento, documentos[i].anoVencimento,
            documentos[i].diaPagamento, documentos[i].mesPagamento, documentos[i].anoPagamento
        );

        if (diasAtraso > 0) {
            documentos[i].juros = documentos[i].valorConta * diasAtraso * 0.0002;
        } else {
            documentos[i].juros = 0;
        }
    }
}

void mostrarDocumentos(Documento documentos[], int n) {
    float totalReceber = 0;
    float somaJuros = 0;

    printf("\nDocumentos cadastrados:\n");
    for (int i = 0; i < n; i++) {
        printf("\nDocumento %d:\n", i + 1);
        printf("Numero do documento: %d\n", documentos[i].numeroDocumento);
        printf("Codigo do cliente: %d\n", documentos[i].codigoCliente);
        printf("Data de vencimento: %02d/%02d/%04d\n", documentos[i].diaVencimento, documentos[i].mesVencimento, documentos[i].anoVencimento);
        printf("Data de pagamento: %02d/%02d/%04d\n", documentos[i].diaPagamento, documentos[i].mesPagamento, documentos[i].anoPagamento);
        printf("Valor da conta: R$ %.2f\n", documentos[i].valorConta);
        printf("Juros: R$ %.2f\n", documentos[i].juros);

        totalReceber += documentos[i].valorConta + documentos[i].juros;
        somaJuros += documentos[i].juros;
    }

    printf("\nTotal geral a receber: R$ %.2f\n", totalReceber);
    printf("Media dos juros: R$ %.2f\n", somaJuros / n);
}

int main() {
    Documento documentos[NUM_DOCUMENTOS];

    printf("Cadastro de documentos:\n");
    lerDados(documentos, NUM_DOCUMENTOS);
    mostrarDocumentos(documentos, NUM_DOCUMENTOS);

    return 0;
}
