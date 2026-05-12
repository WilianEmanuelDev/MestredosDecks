#include <stdio.h>
#include <string.h> // Necessário para strcmp(), usado no critério por nome

// ====================================================================
// ESTRUTURA DE DADOS
// Representa uma carta do jogo com todos os atributos necessários
// ====================================================================

struct Carta {
    int id;             // Identificador único da carta
    char nome[50];      // Nome da carta
    int ataque;         // Poder de ataque
    int defesa;         // Poder de defesa
    int energia;        // Custo de energia
    int raridade;       // Grau de raridade (1 = comum, 4 = lendária)
};

// ====================================================================
// FUNÇÃO AUXILIAR
// Imprime uma lista de cartas em formato de tabela
// ====================================================================

void imprimirCartas(struct Carta lista[], int tamanho) {
    // Cabeçalho da tabela
    printf("%-5s | %-25s | %-7s | %-7s | %-8s | %-8s\n",
           "ID", "Nome", "Ataque", "Defesa", "Energia", "Raridade");
    printf("----------------------------------------------------------------------\n");

    // Percorre o vetor imprimindo cada carta
    for (int i = 0; i < tamanho; i++) {
        printf("%-5d | %-25s | %-7d | %-7d | %-8d | %-8d\n",
               lista[i].id,
               lista[i].nome,
               lista[i].ataque,
               lista[i].defesa,
               lista[i].energia,
               lista[i].raridade);
    }
    printf("\n");
}

// ====================================================================
// NÍVEL NOVATO — INSERTION SORT
// Ordenação por ENERGIA em ordem crescente
// ====================================================================

void insertionSortEnergia(struct Carta mao[], int n) {
    // Começa no índice 1 pois o primeiro elemento já está ordenado
    for (int i = 1; i < n; i++) {
        struct Carta chave = mao[i]; // Carta a ser inserida
        int j = i - 1;

        // Desloca cartas com energia maior para a direita
        while (j >= 0 && mao[j].energia > chave.energia) {
            mao[j + 1] = mao[j];
            j--;
        }

        // Insere a carta na posição correta
        mao[j + 1] = chave;
    }
}

// ====================================================================
// NÍVEL AVENTUREIRO — SHELL SORT
// Ordenação por ATAQUE em ordem decrescente
// ====================================================================

void shellSortAtaque(struct Carta deck[], int n) {
    int h = 1;

    // Calcula o gap inicial usando a sequência de Knuth
    while (h < n / 3) {
        h = 3 * h + 1;
    }

    // Executa o Shell Sort reduzindo o gap gradativamente
    while (h >= 1) {
        for (int i = h; i < n; i++) {
            struct Carta temp = deck[i];
            int j = i;

            // Ordenação por ataque DECRESCENTE
            while (j >= h && deck[j - h].ataque < temp.ataque) {
                deck[j] = deck[j - h];
                j -= h;
            }

            deck[j] = temp;
        }
        h /= 3;
    }
}

// ====================================================================
// NÍVEL MESTRE — QUICK SORT MULTICRITÉRIO
// 1º critério: Raridade (decrescente)
// 2º critério: Nome (alfabético crescente)
// ====================================================================

// Função de comparação customizada
int compararCartas(const struct Carta* c1, const struct Carta* c2) {
    // Primeiro critério: raridade
    if (c1->raridade != c2->raridade) {
        return c2->raridade - c1->raridade;
    }

    // Critério de desempate: nome
    return strcmp(c1->nome, c2->nome);
}

// Função de particionamento do Quick Sort
int particionar(struct Carta registro[], int baixo, int alto) {
    struct Carta pivo = registro[alto]; // Escolhe o último como pivô
    int i = baixo - 1;

    for (int j = baixo; j < alto; j++) {
        // Usa a função de comparação multicritério
        if (compararCartas(&registro[j], &pivo) < 0) {
            i++;
            struct Carta temp = registro[i];
            registro[i] = registro[j];
            registro[j] = temp;
        }
    }

    // Coloca o pivô na posição correta
    struct Carta temp = registro[i + 1];
    registro[i + 1] = registro[alto];
    registro[alto] = temp;

    return i + 1;
}

// Quick Sort recursivo
void quickSortRegistro(struct Carta registro[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionar(registro, baixo, alto);
        quickSortRegistro(registro, baixo, pi - 1);
        quickSortRegistro(registro, pi + 1, alto);
    }
}

// ====================================================================
// FUNÇÃO PRINCIPAL
// Executa os três níveis do desafio
// ====================================================================

int main() {
    printf("=== ARENA DE CODIGO - MESTRE DOS DECKS ===\n\n");

    // -------------------------
    // NÍVEL NOVATO
    // -------------------------
    struct Carta mao_inicial[7] = {
        {105, "Ogro Esmagador", 5, 4, 5, 2},
        {102, "Elfa Arqueira", 2, 1, 2, 1},
        {107, "Anjo da Furia", 6, 5, 6, 3},
        {101, "Goblin Batedor", 1, 1, 1, 1},
        {103, "Guardiao de Pedra", 2, 5, 4, 1},
        {106, "Cavaleiro de Aco", 3, 3, 3, 2},
        {104, "Dragao das Cinzas", 7, 7, 8, 3}
    };

    printf("--- Nivel Novato: Mao Inicial ---\n");
    imprimirCartas(mao_inicial, 7);

    insertionSortEnergia(mao_inicial, 7);

    printf("--- Nivel Novato: Mao Organizada (Energia Crescente) ---\n");
    imprimirCartas(mao_inicial, 7);

    // -------------------------
    // NÍVEL AVENTUREIRO
    // -------------------------
    struct Carta deck_torneio[40] = {
        {401, "Lich King", 10, 10, 10, 4},
        {305, "Hidra de Nove Cabecas", 8, 8, 9, 4},
        {405, "Fenix Imortal", 9, 9, 9, 4},
        {104, "Dragao das Cinzas", 7, 7, 8, 3},
        {215, "Minotauro Guerreiro", 5, 6, 5, 2},
        {205, "Ciclope Brutal", 7, 5, 6, 2},
        {107, "Anjo da Furia", 6, 5, 6, 3},
        {315, "Paladino da Ordem", 5, 7, 7, 3},
        {310, "Feiticeira Arcana", 4, 2, 5, 3},
        {225, "Elemental de Fogo", 6, 2, 5, 2},
        {301, "Mago de Gelo", 2, 4, 3, 2},
        {106, "Cavaleiro de Aco", 3, 3, 3, 2},
        {201, "Lobo das Sombras", 3, 2, 2, 1},
        {210, "Grifo Veloz", 4, 3, 4, 1},
        {220, "Basilisco Petrificante", 3, 5, 4, 2},
        {110, "Clerigo Iluminado", 1, 3, 2, 1},
        {101, "Goblin Batedor", 1, 1, 1, 1},
        {102, "Elfa Arqueira", 2, 1, 2, 1},
        {103, "Guardiao de Pedra", 2, 5, 4, 1},
        {105, "Ogro Esmagador", 5, 4, 5, 2},

        {401, "Lich King", 10, 10, 10, 4},
        {305, "Hidra de Nove Cabecas", 8, 8, 9, 4},
        {405, "Fenix Imortal", 9, 9, 9, 4},
        {104, "Dragao das Cinzas", 7, 7, 8, 3},
        {215, "Minotauro Guerreiro", 5, 6, 5, 2},
        {205, "Ciclope Brutal", 7, 5, 6, 2},
        {107, "Anjo da Furia", 6, 5, 6, 3},
        {315, "Paladino da Ordem", 5, 7, 7, 3},
        {310, "Feiticeira Arcana", 4, 2, 5, 3},
        {225, "Elemental de Fogo", 6, 2, 5, 2},
        {301, "Mago de Gelo", 2, 4, 3, 2},
        {106, "Cavaleiro de Aco", 3, 3, 3, 2},
        {201, "Lobo das Sombras", 3, 2, 2, 1},
        {210, "Grifo Veloz", 4, 3, 4, 1},
        {220, "Basilisco Petrificante", 3, 5, 4, 2},
        {110, "Clerigo Iluminado", 1, 3, 2, 1},
        {101, "Goblin Batedor", 1, 1, 1, 1},
        {102, "Elfa Arqueira", 2, 1, 2, 1},
        {103, "Guardiao de Pedra", 2, 5, 4, 1},
        {105, "Ogro Esmagador", 5, 4, 5, 2}
    };

    printf("--- Nivel Aventureiro: Deck do Torneio (Desordenado) ---\n");
    imprimirCartas(deck_torneio, 40);

    shellSortAtaque(deck_torneio, 40);

    printf("--- Nivel Aventureiro: Deck Otimizado (Ataque Decrescente) ---\n");
    imprimirCartas(deck_torneio, 40);

    printf("Deck otimizado e pronto para o torneio!\n\n");

    // -------------------------
    // NÍVEL MESTRE
    // -------------------------
    struct Carta grande_registro[20] = {
        {225, "Elemental de Fogo", 6, 2, 5, 2},
        {105, "Ogro Esmagador", 5, 4, 5, 2},
        {102, "Elfa Arqueira", 2, 1, 2, 1},
        {315, "Paladino da Ordem", 5, 7, 7, 3},
        {201, "Lobo das Sombras", 3, 2, 2, 1},
        {401, "Lich King", 10, 10, 10, 4},
        {107, "Anjo da Furia", 6, 5, 6, 3},
        {301, "Mago de Gelo", 2, 4, 3, 2},
        {101, "Goblin Batedor", 1, 1, 1, 1},
        {205, "Ciclope Brutal", 7, 5, 6, 2},
        {103, "Guardiao de Pedra", 2, 5, 4, 1},
        {305, "Hidra de Nove Cabecas", 8, 8, 9, 4},
        {106, "Cavaleiro de Aco", 3, 3, 3, 2},
        {210, "Grifo Veloz", 4, 3, 4, 1},
        {104, "Dragao das Cinzas", 7, 7, 8, 3},
        {215, "Minotauro Guerreiro", 5, 6, 5, 2},
        {310, "Feiticeira Arcana", 4, 2, 5, 3},
        {220, "Basilisco Petrificante", 3, 5, 4, 2},
        {110, "Clerigo Iluminado", 1, 3, 2, 1},
        {405, "Fenix Imortal", 9, 9, 9, 4}
    };

    printf("--- Nivel Mestre: Registro Desordenado ---\n");
    imprimirCartas(grande_registro, 20);

    quickSortRegistro(grande_registro, 0, 19);

    printf("--- Nivel Mestre: Registro Ordenado (Raridade ↓ Nome ↑) ---\n");
    imprimirCartas(grande_registro, 20);

    printf("O grande registro da arena foi restaurado!\n");

    return 0;
}