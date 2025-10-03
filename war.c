#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura para representar um território.
// Contém o nome do território, a cor do jogador que o domina e a quantidade de tropas.
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Protótipos das funções para organizar o código
void atribuirMissao(char** missaoJogador, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int tamanho, const char* corJogador);
void atacar(Territorio* atacante, Territorio* defensor);
void exibirMapa(Territorio* mapa, int tamanho);
void liberarMemoria(Territorio* mapa, char* missaoJogador, int tamanho);

int main() {
    // Inicializa o gerador de números aleatórios com o tempo atual.
    // Isso garante que os resultados de 'rand()' sejam diferentes a cada execução.
    srand(time(NULL));

    int numTerritorios = 5; // Define um número fixo de territórios para simplicidade.

    // Alocação dinâmica de memória para o vetor de territórios usando malloc.
    // 'mapa' será um ponteiro para o primeiro território.
    Territorio* mapa = (Territorio*) malloc(numTerritorios * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria para os territorios.\n");
        return 1;
    }

    // Cadastro inicial dos territórios (dados de exemplo)
    strcpy(mapa[0].nome, "Brasil");
    strcpy(mapa[0].cor, "Verde");
    mapa[0].tropas = 10;

    strcpy(mapa[1].nome, "Argentina");
    strcpy(mapa[1].cor, "Azul");
    mapa[1].tropas = 8;

    strcpy(mapa[2].nome, "Peru");
    strcpy(mapa[2].cor, "Verde");
    mapa[2].tropas = 5;

    strcpy(mapa[3].nome, "Chile");
    strcpy(mapa[3].cor, "Azul");
    mapa[3].tropas = 3;

    strcpy(mapa[4].nome, "Colombia");
    strcpy(mapa[4].cor, "Vermelho");
    mapa[4].tropas = 7;

    // Criação do vetor de missões estratégicas.
    char* missoes[] = {
        "Conquistar 3 territorios.",
        "Eliminar todas as tropas da cor Vermelha.",
        "Conquistar a Colombia.",
        "Ter 15 tropas em um unico territorio.",
        "Conquistar a Argentina e o Chile."
    };
    int totalMissoes = 5;

    // A missão do jogador (cor "Verde") será armazenada dinamicamente.
    char* missaoJogadorVerde = NULL;

    // Sorteia e atribui uma missão para o jogador.
    atribuirMissao(&missaoJogadorVerde, missoes, totalMissoes);

    // Exibe a missão do jogador no início do jogo.
    printf("==================================================\n");
    printf("               JOGO WAR ESTRUTURADO               \n");
    printf("==================================================\n\n");
    printf("Sua missao, jogador Verde: %s\n\n", missaoJogadorVerde);

    int indiceAtacante, indiceDefensor;
    int turno = 1;
    int vitoria = 0;

    // Loop principal do jogo (simulação de alguns turnos)
    while (turno <= 3 && !vitoria) {
        printf("---------- TURNO %d ----------\n", turno);
        exibirMapa(mapa, numTerritorios);

        // Lógica de ataque do jogador "Verde"
        printf("\nJogador Verde, escolha seu territorio para atacar (0 a %d): ", numTerritorios - 1);
        scanf("%d", &indiceAtacante);

        printf("Escolha o territorio inimigo para atacar (0 a %d): ", numTerritorios - 1);
        scanf("%d", &indiceDefensor);

        // Valida o ataque: o jogador só pode atacar com seus territórios
        // e não pode atacar a si mesmo.
        if (indiceAtacante >= 0 && indiceAtacante < numTerritorios &&
            indiceDefensor >= 0 && indiceDefensor < numTerritorios &&
            strcmp(mapa[indiceAtacante].cor, "Verde") == 0 &&
            strcmp(mapa[indiceDefensor].cor, "Verde") != 0) {

            // A função 'atacar' recebe ponteiros para os territórios.
            atacar(&mapa[indiceAtacante], &mapa[indiceDefensor]);
        } else {
            printf("\nAtaque invalido! Verifique os territorios escolhidos.\n");
        }

        // Exibe o mapa atualizado após o ataque.
        printf("\n--- Mapa apos o ataque ---\n");
        exibirMapa(mapa, numTerritorios);

        // Verifica se a missão foi cumprida ao final do turno.
        vitoria = verificarMissao(missaoJogadorVerde, mapa, numTerritorios, "Verde");
        if (vitoria) {
            printf("\nParabens, Jogador Verde! Voce cumpriu sua missao e venceu o jogo!\n");
        }

        turno++;
        printf("\n");
    }

    if (!vitoria) {
        printf("Fim de jogo. Ninguem cumpriu a missao nos turnos simulados.\n");
    }

    // Libera toda a memória alocada dinamicamente.
    liberarMemoria(mapa, missaoJogadorVerde, numTerritorios);

    return 0;
}

/**
 * @brief Sorteia uma missão e a atribui a um jogador.
 * @param missaoJogador Ponteiro de referência para a string que armazenará a missão.
 * @param missoes Vetor com todas as missões disponíveis.
 * @param totalMissoes Número total de missões.
 */
// Implementação da função para sortear e copiar uma missão.
void atribuirMissao(char** missaoJogador, char* missoes[], int totalMissoes) {
    int indiceSorteado = rand() % totalMissoes;
    // Aloca memória dinamicamente para a missão do jogador.
    *missaoJogador = (char*) malloc((strlen(missoes[indiceSorteado]) + 1) * sizeof(char));
    if (*missaoJogador != NULL) {
        // Copia a missão sorteada para o espaço alocado.
        strcpy(*missaoJogador, missoes[indiceSorteado]);
    }
}

/**
 * @brief Simula um ataque entre dois territórios.
 * @param atacante Ponteiro para o território que está atacando.
 * @param defensor Ponteiro para o território que está se defendendo.
 */
// Implementação da função de ataque.
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\nAtaque de %s (%s) contra %s (%s)!\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    // Simula a rolagem de dados (valores de 1 a 6).
    int dadoAtaque = (rand() % 6) + 1;
    int dadoDefesa = (rand() % 6) + 1;

    printf("Dado do Atacante: %d\n", dadoAtaque);
    printf("Dado do Defensor: %d\n", dadoDefesa);

    if (dadoAtaque > dadoDefesa) {
        printf("VITORIA DO ATACANTE! %s conquistou %s.\n", atacante->nome, defensor->nome);
        // Se o atacante vencer, o defensor muda de cor e recebe metade das tropas do atacante.
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas = atacante->tropas - (atacante->tropas / 2);
    } else {
        printf("VITORIA DO DEFENSOR! %s perdeu uma tropa.\n", atacante->nome);
        // Se o defensor vencer, o atacante perde uma tropa.
        atacante->tropas--;
    }
}


/**
 * @brief Verifica se a condição de vitória da missão foi atingida.
 * @param missao A missão do jogador.
 * @param mapa Ponteiro para o vetor de territórios.
 * @param tamanho O número total de territórios.
 * @param corJogador A cor do jogador que está sendo verificado.
 * @return 1 se a missão foi cumprida, 0 caso contrário.
 */
// Implementação da função de verificação de missão (lógica simples).
int verificarMissao(char* missao, Territorio* mapa, int tamanho, const char* corJogador) {
    if (strcmp(missao, "Conquistar 3 territorios.") == 0) {
        int cont = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                cont++;
            }
        }
        return cont >= 3;
    }
    if (strcmp(missao, "Eliminar todas as tropas da cor Vermelha.") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0) {
                return 0; // Ainda existe um território vermelho
            }
        }
        return 1; // Não encontrou territórios vermelhos
    }
     if (strcmp(missao, "Conquistar a Colombia.") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].nome, "Colombia") == 0 && strcmp(mapa[i].cor, corJogador) == 0) {
                return 1;
            }
        }
        return 0;
    }
    // Adicione outras verificações simples aqui...
    return 0; // Retorno padrão
}


/**
 * @brief Exibe o estado atual de todos os territórios no mapa.
 * @param mapa Ponteiro para o vetor de territórios.
 * @param tamanho O número total de territórios.
 */
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("Estado atual do mapa:\n");
    for (int i = 0; i < tamanho; i++) {
        // Exibe as informações de cada território.
        printf("  [%d] Territorio: %-12s | Cor: %-8s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

/**
 * @brief Libera toda a memória alocada dinamicamente.
 * @param mapa Ponteiro para o vetor de territórios.
 * @param missaoJogador Ponteiro para a string da missão do jogador.
 * @param tamanho O número total de territórios.
 */
// Implementação da função para liberar memória.
void liberarMemoria(Territorio* mapa, char* missaoJogador, int tamanho) {
    printf("\nLiberando memoria alocada...\n");
    // Usa free() para liberar a memória do mapa e da missão.
    free(mapa);
    free(missaoJogador);
}