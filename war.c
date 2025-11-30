//  Desafio WAR Estruturado – Conquista de Territórios


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ============================
//   CONSTANTES E ESTRUTURAS
// ============================
typedef struct {
    char nome[50];
    char corExercito[20];
    int numeroTropas;
} Territorio;

#define QTD_TERRITORIOS 5
#define MISAO_TERRITORIOS 3
#define COR_ALVO "Verde"

// ============================
//        FUNÇÕES AUXILIARES
// ============================

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int dado() { 
    return (rand() % 6) + 1; 
}

// ============================
//   INICIALIZAÇÃO DO MAPA
// ============================

void inicializarTerritorios(Territorio mapa[]) {
    strcpy(mapa[0].nome, "EUA");
    strcpy(mapa[0].corExercito, "Azul");
    mapa[0].numeroTropas = 5;

    strcpy(mapa[1].nome, "Japão");
    strcpy(mapa[1].corExercito, "Vermelho");
    mapa[1].numeroTropas = 4;

    strcpy(mapa[2].nome, "Brasil");
    strcpy(mapa[2].corExercito, "Verde");
    mapa[2].numeroTropas = 6;

    strcpy(mapa[3].nome, "Mexico");
    strcpy(mapa[3].corExercito, "Amarelo");
    mapa[3].numeroTropas = 3;

    strcpy(mapa[4].nome, "China");
    strcpy(mapa[4].corExercito, "Vermelho");
    mapa[4].numeroTropas = 4;
}

// ============================
//       EXIBIR O MAPA
// ============================

void exibirMapa(const Territorio mapa[]) {
    printf("\n===== 🌍 MAPA ATUAL =====\n");
    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("[%d] %-15s (%s) - %d tropas\n",
            i + 1, mapa[i].nome, mapa[i].corExercito, mapa[i].numeroTropas);
    }
}

// ============================
//       SISTEMA DE ATAQUE
// ============================

void realizarAtaque(Territorio *atacante, Territorio *defensor) {

    if (atacante->numeroTropas <= 1) {
        printf("\n🚫 Tropas insuficientes para atacar! (mínimo = 2)\n");
        return;
    }

    printf("\n⚔️  %s (%s) está atacando %s (%s)\n",
        atacante->nome, atacante->corExercito,
        defensor->nome, defensor->corExercito);

    int dAtk = dado();
    int dDef = dado();

    printf("🎲 Ataque: %d | 🛡 Defesa: %d\n", dAtk, dDef);

    if (dAtk > dDef) {
        printf("💥 Ataque vence! Defesa perde 1 tropa.\n");
        defensor->numeroTropas--;

        if (defensor->numeroTropas == 0) {
            printf("🏳️ %s foi conquistado!\n", defensor->nome);
            strcpy(defensor->corExercito, atacante->corExercito);
            defensor->numeroTropas = 1;
            atacante->numeroTropas--;
        }
    } else {
        printf("🛡 Defesa segura! Atacante perde 1 tropa.\n");
        atacante->numeroTropas--;
    }
}

// ============================
//      MISSÕES / VITÓRIA
// ============================

int verificarMissao_DestruirVerde(const Territorio mapa[]) {
    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        if (strcmp(mapa[i].corExercito, COR_ALVO) == 0)
            return 0; // Ainda existe território verde
    }
    return 1; // Missão cumprida
}

int verificarMissao_Conquistar3(const Territorio mapa[], const char *corJogador) {
    int contador = 0;

    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        if (strcmp(mapa[i].corExercito, corJogador) == 0)
            contador++;
    }
    return contador >= MISAO_TERRITORIOS;
}

void verificarMissoes(const Territorio mapa[], const char *corJogador) {
    printf("\n===== 📋 VERIFICADOR DE MISSÕES =====\n");

    int m1 = verificarMissao_DestruirVerde(mapa);
    int m2 = verificarMissao_Conquistar3(mapa, corJogador);

    printf("1️⃣ Destruir o exército Verde: %s\n", m1 ? "✔️ CONCLUÍDA" : "❌ Pendente");
    printf("2️⃣ Conquistar 3 territórios: %s\n", m2 ? "✔️ CONCLUÍDA" : "❌ Pendente");

    if (m1 && m2) {
        printf("\n🎉🎉 PARABÉNS! VOCÊ COMPLETOU TODAS AS MISSÕES! 🎉🎉\n");
    }
}

// ============================
//            MENU
// ============================

void menu(Territorio mapa[], const char *corJogador) {
    int opcao = -1;

    while (opcao != 0) {
        printf("\n====== 🎮 MENU PRINCIPAL ======\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missões\n");
        printf("0 - Sair\n");
        printf("👉 Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: {
                exibirMapa(mapa);

                int atk, def;

                printf("\nQuem ataca? ");
                scanf("%d", &atk);
                printf("Quem defende? ");
                scanf("%d", &def);
                limparBuffer();

                atk--; def--;

                if (atk >= 0 && atk < QTD_TERRITORIOS &&
                    def >= 0 && def < QTD_TERRITORIOS &&
                    atk != def) 
                {
                    realizarAtaque(&mapa[atk], &mapa[def]);
                } else {
                    printf("⚠️ Escolha inválida!\n");
                }
                break;
            }

            case 2:
                verificarMissoes(mapa, corJogador);
                break;

            case 0:
                printf("👋 Saindo do jogo...\n");
                break;

            default:
                printf("❌ Opção inválida!\n");
        }
    }
}

// ============================
//        FUNÇÃO PRINCIPAL
// ============================

int main() {
    srand(time(NULL));

    Territorio mapa[QTD_TERRITORIOS];
    const char corJogador[] = "Azul";  // jogador principal

    inicializarTerritorios(mapa);
    menu(mapa, corJogador);

    return 0;
}
