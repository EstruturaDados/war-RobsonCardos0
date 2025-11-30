// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
// ============================================================================
#include <stdio.h>
#include <string.h> // Necessário para manipular strings (remover o \n)

// 1. Definição da Struct (O Molde da nossa "Ficha")
typedef struct {
    char nome[50];
    char corExercito[20];
    int numeroTropas;
} Territorio;

int main() {
    // 2. Vetor Estático (O "Fichário" com 5 espaços)
    Territorio mapa[5];
    int i;

    printf("=== 🌍 CONFIGURAÇÃO INICIAL DO MAPA ===\n\n");

    // 3. Loop de Cadastro
    for (i = 0; i < 5; i++) {
        printf("--- Território %d ---\n", i + 1);

        // Lendo o Nome (fgets permite espaços, ex: "America do Sul")
        printf("Nome do Território: ");
        fgets(mapa[i].nome, 50, stdin);
        // Remove o "enter" (\n) que o fgets captura no final
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        // Lendo a Cor
        printf("Cor do Exército (ex: Azul, Vermelho): ");
        fgets(mapa[i].corExercito, 20, stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = 0;

        // Lendo as Tropas
        printf("Número de Tropas: ");
        scanf("%d", &mapa[i].numeroTropas);

        // IMPORTANTE: Limpar o buffer do teclado após o scanf
        // O scanf deixa um '\n' sobrando que pularia o próximo fgets
        getchar(); 
        
        printf("\n");
    }

    // 4. Exibição do Mapa (Output formatado)
    printf("=== 🗺️ ESTADO ATUAL DO MUNDO ===\n");
    printf("%-20s | %-15s | %s\n", "NOME", "EXÉRCITO", "TROPAS");
    printf("----------------------------------------------------\n");

    for (i = 0; i < 5; i++) {
        printf("%-20s | %-15s | %d Batalhões\n", 
               mapa[i].nome, 
               mapa[i].corExercito, 
               mapa[i].numeroTropas);
    }

    return 0;
}