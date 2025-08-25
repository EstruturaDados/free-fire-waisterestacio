// ===================================================
// DESAFIO CÓDIGO DA ILHA – FREE FIRE
// Nível: Novato
// Sistema de inventário com structs e listas sequenciais
// ===================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10   // Capacidade máxima da mochila

// ---------------------------------------------------
// Definição da struct Item
// Armazena os dados de cada item coletado
// ---------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ---------------------------------------------------
// Variáveis globais
// ---------------------------------------------------
Item mochila[MAX_ITENS]; // Vetor que representa a mochila
int totalItens = 0;      // Quantidade atual de itens na mochila

// ---------------------------------------------------
// Função para inserir um novo item na mochila
// ---------------------------------------------------
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n⚠️ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\n--- Cadastro de Item ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);  // lê até o \n
    printf("Tipo (arma, municao, cura, etc): ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[totalItens] = novo;
    totalItens++;

    printf("\n✅ Item adicionado com sucesso!\n");
}

// ---------------------------------------------------
// Função para remover um item pelo nome
// ---------------------------------------------------
void removerItem() {
    if (totalItens == 0) {
        printf("\n⚠️ Mochila vazia! Nada para remover.\n");
        return;
    }

    char nome[30];
    printf("\n--- Remoção de Item ---\n");
    printf("Digite o nome do item a remover: ");
    scanf(" %[^\n]", nome);

    int encontrado = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\n❌ Item não encontrado!\n");
    } else {
        // "puxa" os itens seguintes para ocupar o espaço
        for (int i = encontrado; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        totalItens--;
        printf("\n🗑️ Item removido com sucesso!\n");
    }
}

// ---------------------------------------------------
// Função para listar todos os itens da mochila
// ---------------------------------------------------
void listarItens() {
    printf("\n--- Itens na Mochila ---\n");

    if (totalItens == 0) {
        printf("A mochila está vazia!\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("[%d] Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// ---------------------------------------------------
// Função de busca sequencial por nome
// ---------------------------------------------------
void buscarItem() {
    if (totalItens == 0) {
        printf("\n⚠️ Mochila vazia! Nada para buscar.\n");
        return;
    }

    char nome[30];
    printf("\n--- Busca de Item ---\n");
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", nome);

    int encontrado = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\n❌ Item não encontrado!\n");
    } else {
        printf("\n✅ Item encontrado!\n");
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila[encontrado].nome,
               mochila[encontrado].tipo,
               mochila[encontrado].quantidade);
    }
}

// ---------------------------------------------------
// Função principal com menu interativo
// ---------------------------------------------------
int main() {
    int opcao;

    do {
        printf("\n============================\n");
        printf(" MOCHILA DO JOGADOR - FREE FIRE\n");
        printf("============================\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("\n👋 Saindo do jogo... Até a próxima!\n");
                break;
            default:
                printf("\n⚠️ Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
