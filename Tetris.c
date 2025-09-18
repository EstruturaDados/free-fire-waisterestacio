#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5   // tamanho fixo da fila
#define TAM_PILHA 3  // tamanho maximo da pilha de reserva

// Struct que representa uma peca do Tetris
typedef struct {
    char nome;  // tipo da peca (I, O, T, L)
    int id;     // identificador unico
} Peca;

// ---------------- FILA CIRCULAR ----------------
typedef struct {
    Peca elementos[TAM_FILA];
    int inicio;
    int fim;
    int qtd;
} Fila;

void inicializarFila(Fila *fila) {
    fila->inicio = 0;
    fila->fim = -1;
    fila->qtd = 0;
}

int filaCheia(Fila *fila) {
    return (fila->qtd == TAM_FILA);
}

int filaVazia(Fila *fila) {
    return (fila->qtd == 0);
}

void enqueue(Fila *fila, Peca p) {
    if (filaCheia(fila)) return; // nao deve acontecer
    fila->fim = (fila->fim + 1) % TAM_FILA;
    fila->elementos[fila->fim] = p;
    fila->qtd++;
}

Peca dequeue(Fila *fila) {
    Peca removida = {'-', -1};
    if (filaVazia(fila)) return removida;
    removida = fila->elementos[fila->inicio];
    fila->inicio = (fila->inicio + 1) % TAM_FILA;
    fila->qtd--;
    return removida;
}

void exibirFila(Fila *fila) {
    printf("Fila de pecas\t");
    if (filaVazia(fila)) {
        printf("[vazia]");
    } else {
        int i, pos = fila->inicio;
        for (i = 0; i < fila->qtd; i++) {
            printf("[%c %d] ", fila->elementos[pos].nome, fila->elementos[pos].id);
            pos = (pos + 1) % TAM_FILA;
        }
    }
    printf("\n");
}

// ---------------- PILHA LINEAR ----------------
typedef struct {
    Peca elementos[TAM_PILHA];
    int topo;
} Pilha;

void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

int pilhaVazia(Pilha *pilha) {
    return (pilha->topo == -1);
}

int pilhaCheia(Pilha *pilha) {
    return (pilha->topo == TAM_PILHA - 1);
}

void push(Pilha *pilha, Peca p) {
    if (pilhaCheia(pilha)) {
        printf("Pilha cheia! Nao e possivel reservar mais pecas.\n");
        return;
    }
    pilha->elementos[++pilha->topo] = p;
}

Peca pop(Pilha *pilha) {
    Peca removida = {'-', -1};
    if (pilhaVazia(pilha)) {
        printf("Pilha vazia! Nenhuma peca reservada.\n");
        return removida;
    }
    return pilha->elementos[pilha->topo--];
}

void exibirPilha(Pilha *pilha) {
    printf("Pilha de reserva \t(Topo -> Base): ");
    if (pilhaVazia(pilha)) {
        printf("[vazia]");
    } else {
        for (int i = pilha->topo; i >= 0; i--) {
            printf("[%c %d] ", pilha->elementos[i].nome, pilha->elementos[i].id);
        }
    }
    printf("\n");
}

// ---------------- GERADOR DE PECAS ----------------
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// ---------------- MAIN ----------------
int main() {
    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    srand(time(NULL));

    int contadorId = 0;

    // Preenche a fila inicial
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(contadorId++));
    }

    int opcao;
    do {
        printf("\n===== ESTADO ATUAL =====\n");
        exibirFila(&fila);
        exibirPilha(&pilha);

        printf("\nOpcoes de acao:\n");
        printf("1 - Jogar peca\n");
        printf("2 - Reservar peca\n");
        printf("3 - Usar peca reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: { // Jogar peca
                Peca jogada = dequeue(&fila);
                if (jogada.id != -1) {
                    printf("Peca jogada: [%c %d]\n", jogada.nome, jogada.id);
                    enqueue(&fila, gerarPeca(contadorId++)); // sempre mantem cheia
                }
                break;
            }
            case 2: { // Reservar peca
                if (!filaVazia(&fila)) {
                    Peca reservada = dequeue(&fila);
                    push(&pilha, reservada);
                    printf("Peca reservada: [%c %d]\n", reservada.nome, reservada.id);
                    enqueue(&fila, gerarPeca(contadorId++)); // sempre mantem cheia
                }
                break;
            }
            case 3: { // Usar peca reservada
                Peca usada = pop(&pilha);
                if (usada.id != -1) {
                    printf("Peca usada da reserva: [%c %d]\n", usada.nome, usada.id);
                }
                break;
            }
            case 0:
                printf("Encerrando jogo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
