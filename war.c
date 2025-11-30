#include <stdio.h>
#include <stdlib.h> // Para calloc, free, rand, srand
#include <string.h>
#include <time.h>   // Para time() - semente do aleatório

typedef struct {
    char nome[50];
    char corExercito[20];
    int numeroTropas;
} Territorio;

// Função Auxiliar para Limpar Buffer
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função de Batalha (Lógica de Jogo)
void realizarAtaque(Territorio *atacante, Territorio *defensor) {
    printf("\n⚔️  INICIANDO BATALHA: %s vs %s ⚔️\n", atacante->nome, defensor->nome);
    
    // Regra básica: Precisa de mais de 1 tropa para atacar
    if (atacante->numeroTropas <= 1) {
        printf("🚫 O atacante não tem tropas suficientes para atacar (Mínimo: 2)!\n");
        return;
    }

    // Rolagem de Dados (1 a 6)
    int dadoAtaque = (rand() % 6) + 1;
    int dadoDefesa = (rand() % 6) + 1;

    printf("🎲 Dado Ataque: %d\n", dadoAtaque);
    printf("🛡️ Dado Defesa: %d\n", dadoDefesa);

    // Comparação
    if (dadoAtaque > dadoDefesa) {
        printf("💥 VITORIA DO ATACANTE! Defensor perde 1 tropa.\n");
        defensor->numeroTropas--;

        // Verifica Conquista
        if (defensor->numeroTropas == 0) {
            printf("🏳️  TERRITÓRIO CONQUISTADO! %s agora pertence ao exército %s!\n", 
                   defensor->nome, atacante->corExercito);
            // Muda a cor e move 1 tropa para ocupar
            strcpy(defensor->corExercito, atacante->corExercito);
            defensor->numeroTropas = 1;
            atacante->numeroTropas--;
        }
    } else {
        printf("🛡️ DEFESA SEGUROU! (Empates favorecem a defesa). Atacante perde 1 tropa.\n");
        atacante->numeroTropas--;
    }
}

int main() {
    // 1. Inicializa o gerador de números aleatórios
    srand(time(NULL));

    int qtdTerritorios = 5;
    
    // 2. Alocação Dinâmica com CALLOC
    // calloc(quantidade, tamanho) -> Limpa a memória (zera tudo) ao alocar
    Territorio *mapa = (Territorio*) calloc(qtdTerritorios, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro: Memória insuficiente!\n");
        return 1;
    }

    printf("=== 🏗️ CONFIGURAÇÃO DOS TERRITÓRIOS ===\n");
    for (int i = 0; i < qtdTerritorios; i++) {
        printf("\nTerritório %d:\n", i + 1);
        
        printf("Nome: ");
        fgets(mapa[i].nome, 50, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Cor do Exército: ");
        fgets(mapa[i].corExercito, 20, stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = 0;

        printf("Tropas Iniciais: ");
        scanf("%d", &mapa[i].numeroTropas);
        limparBuffer();
    }

    // 3. Loop do Jogo
    int atk, def;
    char continuar = 's';

    while (continuar == 's' || continuar == 'S') {
        printf("\n=== 🗺️ SITUAÇÃO ATUAL ===\n");
        for (int i = 0; i < qtdTerritorios; i++) {
            printf("[%d] %-15s (%s) - %d Tropas\n", 
                   i+1, mapa[i].nome, mapa[i].corExercito, mapa[i].numeroTropas);
        }

        printf("\nESCOLHA A BATALHA:\n");
        printf("Quem ataca? (Digite o número 1-5): ");
        scanf("%d", &atk);
        printf("Quem defende? (Digite o número 1-5): ");
        scanf("%d", &def);
        limparBuffer();

        // Ajuste de índice (usuário digita 1, vetor é 0)
        atk--; 
        def--;

        if (atk >= 0 && atk < 5 && def >= 0 && def < 5 && atk != def) {
            // Passamos os ENDEREÇOS (&) dos territórios específicos do vetor
            realizarAtaque(&mapa[atk], &mapa[def]);
        } else {
            printf("⚠️ Escolha inválida!\n");
        }

        printf("\nContinuar jogando? (s/n): ");
        scanf("%c", &continuar);
        limparBuffer();
    }

    // 4. Liberação de Memória
    free(mapa);
    printf("Jogo encerrado. Memória liberada.\n");

    return 0;
}