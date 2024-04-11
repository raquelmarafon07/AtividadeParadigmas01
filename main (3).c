#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMERO_DE_LANCES 10
#define NUMERO_DE_PINOS 10

// Função para gerar um número aleatório de pinos derrubados, com base no número de pinos restantes
int derrubar_pinos(int pinos_restantes) {
    return rand() % (pinos_restantes + 1);
}

int main() {
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    int pontuacao_total = 0;
    int lance_anterior = 0; // Armazena o número de pinos derrubados no lance anterior

    printf("=============================================================================\n");
    printf("|                     Regras do Jogo de Boliche                              |\n");
    printf("=============================================================================\n");
    printf("| - O objetivo é derrubar o maior número possível de pinos com uma bola em   |\n");
    printf("|   cada lance, em um total de 10 lances por jogo.                           |\n");
    printf("| - Pinos: Há 10 pinos dispostos em uma formação triangular na extremidade  |\n");
    printf("|   oposta da pista de boliche.                                              |\n");
    printf("| - Lances: Cada jogador tem a oportunidade de fazer dois lances por frame   |\n");
    printf("|   (exceto em strikes e spares, que têm regras especiais).                   |\n");
    printf("| - Strike: Se o jogador derrubar todos os 10 pinos com o primeiro lance, é  |\n");
    printf("|   chamado de 'strike'. Nesse caso, não há segundo lance no frame atual e a  |\n");
    printf("|   pontuação do próximo frame é adicionada ao strike.                        |\n");
    printf("| - Spare: Se o jogador derrubar todos os 10 pinos com os dois lances de um   |\n");
    printf("|   frame, é chamado de 'spare'. Nesse caso, a pontuação do próximo lance é  |\n");
    printf("|   adicionada ao spare.                                                      |\n");
    printf("| - Pontuação: A pontuação de cada lance é igual ao número de pinos          |\n");
    printf("|   derrubados. A pontuação total de um frame é a soma dos pinos derrubados  |\n");
    printf("|   nos dois lances, com bônus adicionais para strikes e spares.             |\n");
    printf("| - Pontuação de Strike: Se o jogador faz um strike, a pontuação do próximo  |\n");
    printf("|   frame (os próximos dois lances) é adicionada ao strike.                   |\n");
    printf("| - Pontuação de Spare: Se o jogador faz um spare, a pontuação do próximo    |\n");
    printf("|   lance (o primeiro lance do próximo frame) é adicionada ao spare.          |\n");
    printf("| - Pontuação Máxima: A pontuação máxima em um jogo de boliche é de 300      |\n");
    printf("|   pontos, que seria obtida com 12 strikes seguidos (cada strike recebe a   |\n");
    printf("|   pontuação máxima de 30 pontos).                                           |\n");
    printf("=============================================================================\n\n");

    printf("  Bem-vindo ao jogo de Boliche!\n\n");

    for (int frame = 0; frame < NUMERO_DE_LANCES; frame++) {
        // Primeiro lance
        int pinos_derrubados_1 = derrubar_pinos(NUMERO_DE_PINOS);

        printf("    ╔═════════════╗\n");
        printf("    ║   Frame %2d  ║\n", frame + 1);
        printf("    ╚═════════════╝\n");
        printf("      Lance 1: %2d pinos derrubados\n", pinos_derrubados_1);

        // Verifica se foi strike ou spare no lance anterior e adiciona os bônus, se aplicável
        if (lance_anterior == NUMERO_DE_PINOS) {
            pontuacao_total += pinos_derrubados_1; // Adiciona bônus de spare
        } else if (lance_anterior == NUMERO_DE_PINOS * 2) {
            pontuacao_total += 2 * pinos_derrubados_1; // Adiciona bônus de strike
        }

        // Atualiza a pontuação total com o lance atual
        pontuacao_total += pinos_derrubados_1;

        // Verifica se foi strike
        if (pinos_derrubados_1 == NUMERO_DE_PINOS) {
            printf("      Strike!\n");

            // Se foi strike, não há segundo lance neste frame
            lance_anterior = NUMERO_DE_PINOS * 2; // Define o lance anterior como 2 vezes o número de pinos
        } else {
            // Segundo lance apenas se não foi strike
            int pinos_restantes = NUMERO_DE_PINOS - pinos_derrubados_1;
            int pinos_derrubados_2 = derrubar_pinos(pinos_restantes);

            printf("      Lance 2: %2d pinos derrubados\n", pinos_derrubados_2);

            // Atualiza a pontuação total com o segundo lance
            pontuacao_total += pinos_derrubados_2;

            // Verifica se foi spare
            if (pinos_derrubados_1 + pinos_derrubados_2 == NUMERO_DE_PINOS) {
                printf("      Spare!\n");

                // Se foi spare, define o lance anterior como o número de pinos derrubados no lance anterior
                lance_anterior = NUMERO_DE_PINOS;
            } else {
                lance_anterior = pinos_derrubados_1 + pinos_derrubados_2; // Define o lance anterior como a soma dos pinos derrubados
            }
        }

        printf("      Pontuação total até agora: %d\n\n", pontuacao_total);
    }

    printf("  Pontuação final: %d\n", pontuacao_total);
    printf("\n  Obrigado por jogar!\n");

    return 0;
}
