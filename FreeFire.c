// ===================================================
// DESAFIO CÓDIGO DA ILHA – FREE FIRE
// Nível: Mestre
// Ordenação, Busca Binária e Análise de Desempenho
// ===================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// ---------------------------------------------------
// Struct Componente
// ---------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // 1 a 10
} Componente;

// ---------------------------------------------------
// Variáveis globais
// ---------------------------------------------------
Componente torre[MAX_COMPONENTES];
int total = 0;
int comparacoes = 0;

// ---------------------------------------------------
// Funções utilitárias
// ---------------------------------------------------
void mostrarComponentes(Componente v[], int n) {
    printf("\n--- Componentes ---\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] Nome: %s | Tipo: %s | Prioridade: %d\n",
               i+1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

// ---------------------------------------------------
// Algoritmos de Ordenação
// ---------------------------------------------------

// Bubble Sort por nome
void bubbleSortNome(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j+1].nome) > 0) {
                Componente tmp = v[j];
                v[j] = v[j+1];
                v[j+1] = tmp;
            }
        }
    }
}

// Insertion Sort por tipo
void insertionSortTipo(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;
        while (j >= 0 && (comparacoes++, strcmp(v[j].tipo, chave.tipo) > 0)) {
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = chave;
    }
}

// Selection Sort por prioridade
void selectionSortPrioridade(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[min].prioridade) min = j;
        }
        if (min != i) {
            Componente tmp = v[i];
            v[i] = v[min];
            v[min] = tmp;
        }
    }
}

// ---------------------------------------------------
// Busca Binária (após ordenar por nome)
// ---------------------------------------------------
int buscaBinariaPorNome(Componente v[], int n, char chave[]) {
    int ini = 0, fim = n - 1;
    comparacoes = 0;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        comparacoes++;
        int cmp = strcmp(v[meio].nome, chave);
        if (cmp == 0) return meio;
        else if (cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// ---------------------------------------------------
// Função para medir tempo de execução
// ---------------------------------------------------
void medirTempo(void (*algoritmo)(Componente[], int), Componente v[], int n) {
    clock_t inicio, fim;
    inicio = clock();
    algoritmo(v, n);
    fim = clock();

    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.6f segundos\n", tempo);
    printf("Comparações: %d\n", comparacoes);
}

// ---------------------------------------------------
// Funções de Entrada
// ---------------------------------------------------
void inserirComponente() {
    if (total >= MAX_COMPONENTES) {
        printf("⚠️ Limite de componentes atingido!\n");
        return;
    }
    Componente c;
    printf("Nome: "); scanf(" %[^\n]", c.nome);
    printf("Tipo: "); scanf(" %[^\n]", c.tipo);
    printf("Prioridade (1-10): "); scanf("%d", &c.prioridade);

    torre[total++] = c;
    printf("✅ Componente adicionado!\n");
}

// ---------------------------------------------------
// Menu Principal
// ---------------------------------------------------
int main() {
    int opcao;
    char chave[30];

    do {
        printf("\n============================\n");
        printf(" NIVEL MESTRE - FREE FIRE\n");
        printf("============================\n");
        printf("1. Inserir componente\n");
        printf("2. Listar componentes\n");
        printf("3. Ordenar por nome (Bubble Sort)\n");
        printf("4. Ordenar por tipo (Insertion Sort)\n");
        printf("5. Ordenar por prioridade (Selection Sort)\n");
        printf("6. Busca binária por nome (após ordenação por nome)\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: inserirComponente(); break;
            case 2: mostrarComponentes(torre, total); break;
            case 3: medirTempo(bubbleSortNome, torre, total); mostrarComponentes(torre, total); break;
            case 4: medirTempo(insertionSortTipo, torre, total); mostrarComponentes(torre, total); break;
            case 5: medirTempo(selectionSortPrioridade, torre, total); mostrarComponentes(torre, total); break;
            case 6:
                printf("Nome do componente-chave: "); scanf(" %[^\n]", chave);
                {
                    int pos = buscaBinariaPorNome(torre, total, chave);
                    if (pos != -1) {
                        printf("✅ Encontrado! %s | Tipo: %s | Prioridade: %d\n",
                               torre[pos].nome, torre[pos].tipo, torre[pos].prioridade);
                    } else {
                        printf("❌ Não encontrado!\n");
                    }
                    printf("Comparações: %d\n", comparacoes);
                }
                break;
            case 0: printf("👋 Saindo do jogo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
