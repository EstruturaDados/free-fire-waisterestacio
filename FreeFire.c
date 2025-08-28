// ===================================================
// DESAFIO CÓDIGO DA ILHA – FREE FIRE
// Nível: Aventureiro
// Comparação entre Vetor e Lista Encadeada
// ===================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10   // Capacidade da mochila (vetor)

// ---------------------------------------------------
// Struct Item
// ---------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ---------------------------------------------------
// Struct Nó da lista encadeada
// ---------------------------------------------------
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ---------------------------------------------------
// Variáveis globais
// ---------------------------------------------------
Item mochilaVetor[MAX_ITENS];
int totalVetor = 0;

No* mochilaLista = NULL;  // ponteiro inicial da lista

// Contador de comparações (para análise de desempenho)
int comparacoes = 0;

// ===================================================
// FUNÇÕES PARA VETOR
// ===================================================
void inserirItemVetor() {
    if (totalVetor >= MAX_ITENS) {
        printf("⚠️ Mochila (vetor) cheia!\n");
        return;
    }
    Item novo;
    printf("Nome: "); scanf(" %[^\n]", novo.nome);
    printf("Tipo: "); scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: "); scanf("%d", &novo.quantidade);

    mochilaVetor[totalVetor++] = novo;
    printf("✅ Item inserido no vetor!\n");
}

void removerItemVetor() {
    if (totalVetor == 0) {
        printf("⚠️ Mochila (vetor) vazia!\n");
        return;
    }
    char nome[30];
    printf("Nome do item a remover: "); scanf(" %[^\n]", nome);

    int pos = -1;
    for (int i = 0; i < totalVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        printf("❌ Item não encontrado no vetor!\n");
    } else {
        for (int i = pos; i < totalVetor - 1; i++) {
            mochilaVetor[i] = mochilaVetor[i+1];
        }
        totalVetor--;
        printf("🗑️ Item removido do vetor!\n");
    }
}

void listarItensVetor() {
    printf("\n--- Mochila (vetor) ---\n");
    if (totalVetor == 0) {
        printf("Vazia!\n");
        return;
    }
    for (int i = 0; i < totalVetor; i++) {
        printf("[%d] Nome: %s | Tipo: %s | Qtd: %d\n", 
               i+1, mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

int buscarSequencialVetor(char nome[]) {
    comparacoes = 0;
    for (int i = 0; i < totalVetor; i++) {
        comparacoes++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) return i;
    }
    return -1;
}

void ordenarVetor() {
    // Bubble Sort por nome
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = 0; j < totalVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j+1].nome) > 0) {
                Item tmp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j+1];
                mochilaVetor[j+1] = tmp;
            }
        }
    }
    printf("✅ Vetor ordenado por nome!\n");
}

int buscarBinariaVetor(char nome[]) {
    comparacoes = 0;
    int ini = 0, fim = totalVetor - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        comparacoes++;
        int cmp = strcmp(mochilaVetor[meio].nome, nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// ===================================================
// FUNÇÕES PARA LISTA ENCADEADA
// ===================================================
void inserirItemLista() {
    Item novo;
    printf("Nome: "); scanf(" %[^\n]", novo.nome);
    printf("Tipo: "); scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: "); scanf("%d", &novo.quantidade);

    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->dados = novo;
    novoNo->proximo = mochilaLista;
    mochilaLista = novoNo;

    printf("✅ Item inserido na lista!\n");
}

void removerItemLista() {
    if (mochilaLista == NULL) {
        printf("⚠️ Mochila (lista) vazia!\n");
        return;
    }
    char nome[30];
    printf("Nome do item a remover: "); scanf(" %[^\n]", nome);

    No* atual = mochilaLista;
    No* anterior = NULL;
    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("❌ Item não encontrado na lista!\n");
    } else {
        if (anterior == NULL) mochilaLista = atual->proximo;
        else anterior->proximo = atual->proximo;
        free(atual);
        printf("🗑️ Item removido da lista!\n");
    }
}

void listarItensLista() {
    printf("\n--- Mochila (lista encadeada) ---\n");
    if (mochilaLista == NULL) {
        printf("Vazia!\n");
        return;
    }
    No* atual = mochilaLista;
    int i = 1;
    while (atual != NULL) {
        printf("[%d] Nome: %s | Tipo: %s | Qtd: %d\n",
               i++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

No* buscarSequencialLista(char nome[]) {
    comparacoes = 0;
    No* atual = mochilaLista;
    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nome) == 0) return atual;
        atual = atual->proximo;
    }
    return NULL;
}

// ===================================================
// MENU PRINCIPAL
// ===================================================
int main() {
    int escolhaEstrutura, opcao;
    char nomeBusca[30];

    do {
        printf("\n============================\n");
        printf(" NIVEL AVENTUREIRO - FREE FIRE\n");
        printf("============================\n");
        printf("Escolha a estrutura:\n");
        printf("1. Mochila com Vetor\n");
        printf("2. Mochila com Lista Encadeada\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &escolhaEstrutura);

        if (escolhaEstrutura == 1) {
            do {
                printf("\n--- Mochila (vetor) ---\n");
                printf("1. Inserir item\n");
                printf("2. Remover item\n");
                printf("3. Listar itens\n");
                printf("4. Buscar (sequencial)\n");
                printf("5. Ordenar\n");
                printf("6. Buscar (binária)\n");
                printf("0. Voltar\n");
                printf("Opção: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1: inserirItemVetor(); break;
                    case 2: removerItemVetor(); break;
                    case 3: listarItensVetor(); break;
                    case 4:
                        printf("Nome a buscar: "); scanf(" %[^\n]", nomeBusca);
                        {
                            int pos = buscarSequencialVetor(nomeBusca);
                            if (pos != -1) printf("✅ Encontrado! Comparações: %d\n", comparacoes);
                            else printf("❌ Não encontrado! Comparações: %d\n", comparacoes);
                        }
                        break;
                    case 5: ordenarVetor(); break;
                    case 6:
                        printf("Nome a buscar: "); scanf(" %[^\n]", nomeBusca);
                        {
                            int pos = buscarBinariaVetor(nomeBusca);
                            if (pos != -1) printf("✅ Encontrado! Comparações: %d\n", comparacoes);
                            else printf("❌ Não encontrado! Comparações: %d\n", comparacoes);
                        }
                        break;
                }
            } while (opcao != 0);
        }
        else if (escolhaEstrutura == 2) {
            do {
                printf("\n--- Mochila (lista) ---\n");
                printf("1. Inserir item\n");
                printf("2. Remover item\n");
                printf("3. Listar itens\n");
                printf("4. Buscar (sequencial)\n");
                printf("0. Voltar\n");
                printf("Opção: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1: inserirItemLista(); break;
                    case 2: removerItemLista(); break;
                    case 3: listarItensLista(); break;
                    case 4:
                        printf("Nome a buscar: "); scanf(" %[^\n]", nomeBusca);
                        {
                            No* achado = buscarSequencialLista(nomeBusca);
                            if (achado != NULL) 
                                printf("✅ Encontrado! Comparações: %d\n", comparacoes);
                            else 
                                printf("❌ Não encontrado! Comparações: %d\n", comparacoes);
                        }
                        break;
                }
            } while (opcao != 0);
        }

    } while (escolhaEstrutura != 0);

    printf("\n👋 Saindo do jogo...\n");
    return 0;
}
