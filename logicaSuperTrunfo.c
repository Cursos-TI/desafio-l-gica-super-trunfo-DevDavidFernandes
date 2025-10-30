#include <stdio.h>
#include <string.h>

// Definições dos atributos das duas cartas
// Carta 1: São Paulo (SP)
#define CARTA1_ESTADO "SP"
#define CARTA1_CODIGO "SP001"
#define CARTA1_CIDADE "Sao Paulo"
#define CARTA1_POPULACAO 12300000
#define CARTA1_AREA 1521.11
#define CARTA1_PIB 763800000000.00
#define CARTA1_PONTOS_TURISTICOS 35

// Carta 2: Rio de Janeiro (RJ)
#define CARTA2_ESTADO "RJ"
#define CARTA2_CODIGO "RJ001"
#define CARTA2_CIDADE "Rio de Janeiro"
#define CARTA2_POPULACAO 6718903
#define CARTA2_AREA 1200.27
#define CARTA2_PIB 359000000000.00
#define CARTA2_PONTOS_TURISTICOS 42

// Variável para escolher o atributo de comparacao (1 a 5)
// 1: População
// 2: Área
// 3: PIB
// 4: Densidade Populacional (Regra: Menor valor vence)
// 5: PIB per capita
#define ATRIBUTO_ESCOLHIDO 4 // Escolhemos a Densidade Populacional para demonstrar a regra de "menor valor vence"

int main() {
    
    // 1. DECLARAÇÃO DE VARIÁVEIS PARA CÁLCULOS

    // Variáveis para armazenar os atributos calculados da Carta 1
    float densidade_populacional_1;
    float pib_per_capita_1;

    // Variáveis para armazenar os atributos calculados da Carta 2
    float densidade_populacional_2;
    float pib_per_capita_2;
    
    // Variáveis para armazenar os valores do atributo escolhido para comparação
    float valor_carta_1 = 0.0;
    float valor_carta_2 = 0.0;
    
    // Variáveis para armazenar o nome do atributo e a regra de vitória
    char nome_atributo[50];
    int maior_vence = 1; // Flag: 1 se maior valor vence, 0 se menor valor vence

    // 2. CÁLCULO DOS ATRIBUTOS DERIVADOS

    // Cálculo para Carta 1
    // Densidade Populacional = População / Área
    densidade_populacional_1 = (float)CARTA1_POPULACAO / CARTA1_AREA;
    // PIB per capita = PIB / População
    pib_per_capita_1 = CARTA1_PIB / (float)CARTA1_POPULACAO;

    // Cálculo para Carta 2
    // Densidade Populacional = População / Área
    densidade_populacional_2 = (float)CARTA2_POPULACAO / CARTA2_AREA;
    // PIB per capita = PIB / População
    pib_per_capita_2 = CARTA2_PIB / (float)CARTA2_POPULACAO;
    
    // 3. SELEÇÃO DO ATRIBUTO PARA COMPARAÇÃO
    
    // A seleção é feita com base na constante ATRIBUTO_ESCOLHIDO (pré-definida no código)
    if (ATRIBUTO_ESCOLHIDO == 1) {
        // População
        strcpy(nome_atributo, "População");
        valor_carta_1 = (float)CARTA1_POPULACAO;
        valor_carta_2 = (float)CARTA2_POPULACAO;
        maior_vence = 1; // Maior valor vence
    } else if (ATRIBUTO_ESCOLHIDO == 2) {
        // Área
        strcpy(nome_atributo, "Área (km²)");
        valor_carta_1 = CARTA1_AREA;
        valor_carta_2 = CARTA2_AREA;
        maior_vence = 1; // Maior valor vence
    } else if (ATRIBUTO_ESCOLHIDO == 3) {
        // PIB
        strcpy(nome_atributo, "PIB (R$)");
        valor_carta_1 = CARTA1_PIB;
        valor_carta_2 = CARTA2_PIB;
        maior_vence = 1; // Maior valor vence
    } else if (ATRIBUTO_ESCOLHIDO == 4) {
        // Densidade Populacional
        strcpy(nome_atributo, "Densidade Populacional (hab/km²)");
        valor_carta_1 = densidade_populacional_1;
        valor_carta_2 = densidade_populacional_2;
        maior_vence = 0; // MENOR valor vence (Regra especial!)
    } else if (ATRIBUTO_ESCOLHIDO == 5) {
        // PIB per capita
        strcpy(nome_atributo, "PIB per capita (R$)");
        valor_carta_1 = pib_per_capita_1;
        valor_carta_2 = pib_per_capita_2;
        maior_vence = 1; // Maior valor vence
    } else {
        // Trata caso de atributo não selecionado corretamente
        printf("Erro: Atributo de comparação não selecionado corretamente.\n");
        return 1;
    }

    // 4. EXIBIÇÃO DA COMPARAÇÃO
    
    printf("========================================================\n");
    printf("         SIMULAÇÃO DE RODADA SUPER TRUNFO CIDADES\n");
    printf("========================================================\n\n");
    
    printf("Comparação de cartas (Atributo: %s):\n\n", nome_atributo);
    
    // Exibe os valores das cartas para o atributo escolhido
    printf("Carta 1 - %s (%s): %.2f\n", CARTA1_CIDADE, CARTA1_ESTADO, valor_carta_1);
    printf("Carta 2 - %s (%s): %.2f\n\n", CARTA2_CIDADE, CARTA2_ESTADO, valor_carta_2);
    
    // 5. LÓGICA DE COMPARAÇÃO E DETERMINAÇÃO DO VENCEDOR

    // Verifica se a regra de vitória é "Maior valor vence"
    if (maior_vence == 1) {
        // Regra padrão: Maior valor vence
        if (valor_carta_1 > valor_carta_2) {
            printf("Resultado: Carta 1 (%s) venceu!\n", CARTA1_CIDADE);
        } else if (valor_carta_2 > valor_carta_1) {
            printf("Resultado: Carta 2 (%s) venceu!\n", CARTA2_CIDADE);
        } else {
            printf("Resultado: Empate!\n");
        }
    } else {
        // Regra especial: Menor valor vence (usada para Densidade Populacional)
        if (valor_carta_1 < valor_carta_2) {
            printf("Resultado: Carta 1 (%s) venceu!\n", CARTA1_CIDADE);
        } else if (valor_carta_2 < valor_carta_1) {
            printf("Resultado: Carta 2 (%s) venceu!\n", CARTA2_CIDADE);
        } else {
            printf("Resultado: Empate!\n");
        }
    }
    
    printf("\n========================================================\n");
    
    // Exibe os atributos calculados para fins de conferência
    printf("\n--- Atributos Calculados (Conferência) ---\n");
    printf("Carta 1 (%s): Densidade = %.2f, PIB per capita = %.2f\n", CARTA1_CIDADE, densidade_populacional_1, pib_per_capita_1);
    printf("Carta 2 (%s): Densidade = %.2f, PIB per capita = %.2f\n", CARTA2_CIDADE, densidade_populacional_2, pib_per_capita_2);
    printf("------------------------------------------\n");

    return 0;
}
