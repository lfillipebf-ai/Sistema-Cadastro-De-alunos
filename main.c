#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 100
#define ARQUIVO "data/alunos.dat"

// ========================
// ESTRUTURA DE DADOS
// ========================
typedef struct {
    int    matricula;
    char   nome[60];
    char   email[60];
    float  nota1;
    float  nota2;
} Aluno;

void   menu();
void   cadastrar(Aluno alunos[], int *total);
void   listar(Aluno alunos[], int total);
void   buscar(Aluno alunos[], int total);
void   remover(Aluno alunos[], int *total);
void   salvar(Aluno alunos[], int total);
int    carregar(Aluno alunos[]);
float  calcularMedia(float n1, float n2);
void   exibirAluno(Aluno a);
void   limparBuffer();

// ========================
// FUNÇÃO PRINCIPAL
// ========================
int main() {
    Aluno alunos[MAX_ALUNOS];
    int total = 0;
    int opcao;

    total = carregar(alunos);

    do {
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: cadastrar(alunos, &total); break;
            case 2: listar(alunos, total);     break;
            case 3: buscar(alunos, total);     break;
            case 4: remover(alunos, &total);   break;
            case 0:
                salvar(alunos, total);
                printf("\nDados salvos. Ate logo!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// ========================
// MENU
// ========================
void menu() {
    printf("\n========================================\n");
    printf("     SISTEMA DE CADASTRO DE ALUNOS      \n");
    printf("========================================\n");
    printf(" 1. Cadastrar novo aluno\n");
    printf(" 2. Listar todos os alunos\n");
    printf(" 3. Buscar aluno por matricula\n");
    printf(" 4. Remover aluno\n");
    printf(" 0. Sair\n");
    printf("========================================\n");
}

// ========================
// CADASTRAR
// ========================
void cadastrar(Aluno alunos[], int *total) {
    if (*total >= MAX_ALUNOS) {
        printf("\nCapacidade maxima atingida!\n");
        return;
    }

    Aluno novo;

    printf("\n--- CADASTRAR ALUNO ---\n");
    printf("Matricula: ");
    scanf("%d", &novo.matricula);
    limparBuffer();

    // Verifica se matricula já existe
    for (int i = 0; i < *total; i++) {
        if (alunos[i].matricula == novo.matricula) {
            printf("Erro: matricula %d ja cadastrada!\n", novo.matricula);
            return;
        }
    }

    printf("Nome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Email: ");
    fgets(novo.email, sizeof(novo.email), stdin);
    novo.email[strcspn(novo.email, "\n")] = '\0';

    printf("Nota 1 (0-10): ");
    scanf("%f", &novo.nota1);
    printf("Nota 2 (0-10): ");
    scanf("%f", &novo.nota2);
    limparBuffer();

    alunos[*total] = novo;
    (*total)++;

    printf("\nAluno cadastrado com sucesso!\n");
    printf("Media calculada: %.1f\n", calcularMedia(novo.nota1, novo.nota2));
}

// ========================
// LISTAR
// ========================
void listar(Aluno alunos[], int total) {
    printf("\n--- LISTA DE ALUNOS (%d cadastrado(s)) ---\n", total);

    if (total == 0) {
        printf("Nenhum aluno cadastrado ainda.\n");
        return;
    }

    printf("%-10s %-30s %-25s %6s %6s %7s %s\n",
           "Matricula", "Nome", "Email", "Nota1", "Nota2", "Media", "Situacao");
    printf("-----------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < total; i++) {
        float media = calcularMedia(alunos[i].nota1, alunos[i].nota2);
        printf("%-10d %-30s %-25s %6.1f %6.1f %7.1f %s\n",
               alunos[i].matricula,
               alunos[i].nome,
               alunos[i].email,
               alunos[i].nota1,
               alunos[i].nota2,
               media,
               media >= 6.0 ? "APROVADO" : "REPROVADO");
    }
}

// ========================
// BUSCAR
// ========================
void buscar(Aluno alunos[], int total) {
    int mat;
    printf("\n--- BUSCAR ALUNO ---\n");
    printf("Digite a matricula: ");
    scanf("%d", &mat);
    limparBuffer();

    for (int i = 0; i < total; i++) {
        if (alunos[i].matricula == mat) {
            printf("\nAluno encontrado:\n");
            exibirAluno(alunos[i]);
            return;
        }
    }
    printf("Aluno com matricula %d nao encontrado.\n", mat);
}

// ========================
// REMOVER
// ========================
void remover(Aluno alunos[], int *total) {
    int mat;
    printf("\n--- REMOVER ALUNO ---\n");
    printf("Digite a matricula: ");
    scanf("%d", &mat);
    limparBuffer();

    for (int i = 0; i < *total; i++) {
        if (alunos[i].matricula == mat) {
            printf("Removendo: %s\n", alunos[i].nome);
            // Desloca os elementos para preencher o buraco
            for (int j = i; j < *total - 1; j++) {
                alunos[j] = alunos[j + 1];
            }
            (*total)--;
            printf("Aluno removido com sucesso!\n");
            return;
        }
    }
    printf("Aluno com matricula %d nao encontrado.\n", mat);
}

// ========================
// SALVAR EM ARQUIVO
// ========================
void salvar(Aluno alunos[], int total) {
    FILE *arq = fopen(ARQUIVO, "wb");
    if (!arq) {
        printf("Erro ao salvar arquivo!\n");
        return;
    }
    fwrite(&total, sizeof(int), 1, arq);
    fwrite(alunos, sizeof(Aluno), total, arq);
    fclose(arq);
}

// ========================
// CARREGAR DE ARQUIVO
// ========================
int carregar(Aluno alunos[]) {
    FILE *arq = fopen(ARQUIVO, "rb");
    if (!arq) return 0; // Arquivo ainda nao existe

    int total = 0;
    fread(&total, sizeof(int), 1, arq);
    fread(alunos, sizeof(Aluno), total, arq);
    fclose(arq);

    printf("(%d aluno(s) carregado(s) do arquivo)\n", total);
    return total;
}

// ========================
// AUXILIARES
// ========================
float calcularMedia(float n1, float n2) {
    return (n1 + n2) / 2.0;
}

void exibirAluno(Aluno a) {
    float media = calcularMedia(a.nota1, a.nota2);
    printf("  Matricula : %d\n", a.matricula);
    printf("  Nome      : %s\n", a.nome);
    printf("  Email     : %s\n", a.email);
    printf("  Nota 1    : %.1f\n", a.nota1);
    printf("  Nota 2    : %.1f\n", a.nota2);
    printf("  Media     : %.1f\n", media);
    printf("  Situacao  : %s\n", media >= 6.0 ? "APROVADO" : "REPROVADO");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
