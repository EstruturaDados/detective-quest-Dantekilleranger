#include <stdio.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------
// Estrutura da árvore binária de salas
// Cada sala tem:
// - nome
// - pista (se houver)
// - ponteiros para esquerda e direita
// ---------------------------
typedef struct Sala {
    char nome[50];
    char pista[50]; // pista encontrada nesta sala (string simples)
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// ---------------------------
// Estrutura da árvore de busca (BST) para pistas
// Cada nodo guarda:
// - uma pista
// - ponteiros para esquerda e direita
// ---------------------------
typedef struct NodoBST {
    char pista[50];
    struct NodoBST *esquerda;
    struct NodoBST *direita;
} NodoBST;

// ---------------------------
// Função para criar uma sala dinamicamente
// Recebe nome e pista (se não houver pista, passa string vazia)
// ---------------------------
Sala* criarSala(const char* nome, const char* pista) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// ---------------------------
// Funções da BST de pistas
// ---------------------------

// Inserção de uma pista na BST (ordem alfabética)
NodoBST* inserirBST(NodoBST* raiz, const char* pista) {
    if (raiz == NULL) {
        NodoBST* novo = (NodoBST*) malloc(sizeof(NodoBST));
        strcpy(novo->pista, pista);
        novo->esquerda = novo->direita = NULL;
        return novo;
    }
    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirBST(raiz->esquerda, pista);
    } else if (strcmp(pista, raiz->pista) > 0) {
        raiz->direita = inserirBST(raiz->direita, pista);
    }
    // se for igual, não insere duplicado
    return raiz;
}

// Percorre a BST em ordem (alfabética) e imprime as pistas
void emOrdem(NodoBST* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        emOrdem(raiz->direita);
    }
}

// Busca uma pista específica na BST
NodoBST* buscarBST(NodoBST* raiz, const char* pista) {
    if (raiz == NULL) return NULL;
    if (strcmp(pista, raiz->pista) == 0) return raiz;
    if (strcmp(pista, raiz->pista) < 0)
        return buscarBST(raiz->esquerda, pista);
    else
        return buscarBST(raiz->direita, pista);
}

// ---------------------------
// Função de exploração da mansão
// O jogador navega pela árvore binária de salas
// Ao entrar em uma sala com pista, ela é inserida na BST
// ---------------------------
void explorarSalas(Sala* atual, NodoBST** pistas) {
    char opcao;

    while (atual != NULL) {
        printf("\nVocê está na sala: %s\n", atual->nome);

        // Se a sala tiver pista, adiciona na BST
        if (strlen(atual->pista) > 0) {
            printf("Você encontrou uma pista: %s\n", atual->pista);
            *pistas = inserirBST(*pistas, atual->pista);
        }

        // Menu de opções
        printf("Escolha:\n");
        printf("e - Ir para a esquerda\n");
        printf("d - Ir para a direita\n");
        printf("p - Listar todas as pistas\n");
        printf("s - Sair da exploração\n");
        printf("Opção: ");
        scanf(" %c", &opcao);

        if (opcao == 's') {
            printf("\nVocê decidiu sair da mansão.\n");
            break;
        } else if (opcao == 'e') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("\nFim do caminho à esquerda. Sala sem saída!\n");
                break;
            }
        } else if (opcao == 'd') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("\nFim do caminho à direita. Sala sem saída!\n");
                break;
            }
        } else if (opcao == 'p') {
            printf("\nPistas coletadas (em ordem alfabética):\n");
            emOrdem(*pistas);
        } else {
            printf("\nOpção inválida!\n");
        }
    }
}

// ---------------------------
// Programa principal
// ---------------------------

int main() {

    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    //
    // - Crie uma struct Sala com nome, e dois ponteiros: esquerda e direita.
    // - Use funções como criarSala(), conectarSalas() e explorarSalas().
    // - A árvore pode ser fixa: Hall de Entrada, Biblioteca, Cozinha, Sótão etc.
    // - O jogador deve poder explorar indo à esquerda (e) ou à direita (d).
    // - Finalize a exploração com uma opção de saída (s).
    // - Exiba o nome da sala a cada movimento.
    // - Use recursão ou laços para caminhar pela árvore.
    // - Nenhuma inserção dinâmica é necessária neste nível.

    // 🔍 Nível Aventureiro: Armazenamento de Pistas com Árvore de Busca
    //
    // - Crie uma struct Pista com campo texto (string).
    // - Crie uma árvore binária de busca (BST) para inserir as pistas coletadas.
    // - Ao visitar salas específicas, adicione pistas automaticamente com inserirBST().
    // - Implemente uma função para exibir as pistas em ordem alfabética (emOrdem()).
    // - Utilize alocação dinâmica e comparação de strings (strcmp) para organizar.
    // - Não precisa remover ou balancear a árvore.
    // - Use funções para modularizar: inserirPista(), listarPistas().
    // - A árvore de pistas deve ser exibida quando o jogador quiser revisar evidências.

    // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
    //
    // - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
    // - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
    // - A chave pode ser o nome do suspeito ou derivada das pistas.
    // - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
    // - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
    // - Adicione um contador para saber qual suspeito foi mais citado.
    // - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
    // - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
    // - Em caso de colisão, use lista encadeada para tratar.
    // - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().

    // Construção estática da mansão (árvore binária de salas)
    Sala* hall = criarSala("Hall de Entrada", "");
    Sala* salaEstar = criarSala("Sala de Estar", "Chave dourada");
    Sala* biblioteca = criarSala("Biblioteca", "Livro antigo");
    Sala* cozinha = criarSala("Cozinha", "Copo quebrado");
    Sala* jardim = criarSala("Jardim", "");

    // Ligações da árvore binária
    hall->esquerda = salaEstar;
    hall->direita = biblioteca;
    salaEstar->esquerda = cozinha;
    salaEstar->direita = jardim;

    // Árvore de pistas (BST) começa vazia
    NodoBST* pistas = NULL;

    // Início da exploração
    explorarSalas(hall, &pistas);

    return 0;
}

