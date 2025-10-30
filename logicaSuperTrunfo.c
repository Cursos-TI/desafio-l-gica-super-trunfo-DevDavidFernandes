#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para a função exit()

// -------------------------------------------------------------------------
// DADOS DAS CARTAS (Reutilizados dos desafios anteriores)
// -------------------------------------------------------------------------

// Carta 1: São Paulo (SP)
#define CARTA1_CIDADE "Sao Paulo"
#define CARTA1_ESTADO "SP"
#define CARTA1_POPULACAO 12300000.0f
#define CARTA1_AREA 1521.11f
#define CARTA1_PIB 763800000000.0f
#define CARTA1_PONTOS_TURISTICOS 35.0f

// Carta 2: Rio de Janeiro (RJ)
#define CARTA2_CIDADE "Rio de Janeiro"
#define CARTA2_ESTADO "RJ"
#define CARTA2_POPULACAO 6718903.0f
#define CARTA2_AREA 1200.27f
#define CARTA2_PIB 359000000000.0f
#define CARTA2_PONTOS_TURISTICOS 42.0f

// -------------------------------------------------------------------------
// DEFINIÇÃO DOS ATRIBUTOS E SUAS REGRAS
// -------------------------------------------------------------------------

// Mapeamento dos atributos para facilitar a lógica
#define ATTR_POPULACAO 1
#define ATTR_AREA 2
#define ATTR_PIB 3
#define ATTR_PONTOS_TURISTICOS 4
#define ATTR_DENSIDADE 5
#define ATTR_PIB_PER_CAPITA 6

// Estrutura para armazenar os dados de cada atributo
typedef struct {
    int id;
    char nome[50];
    float valor1;
    float valor2;
    int maior_vence; // 1 para Maior, 0 para Menor
    float valor_ajustado1; // Valor ajustado para a soma final (normalizado se menor vence)
    float valor_ajustado2; // Valor ajustado para a soma final (normalizado se menor vence)
} Atributo;

// -------------------------------------------------------------------------
// FUNÇÃO AUXILIAR: EXIBE MENU DINÂMICO
// -------------------------------------------------------------------------

void exibir_menu(int excluido) {
    printf("--------------------------------------------------------\n");
    printf("Escolha o %s atributo para a comparação:\n", (excluido == 0) ? "PRIMEIRO" : "SEGUNDO");
    
    if (excluido != ATTR_POPULACAO) printf("1. População\n");
    if (excluido != ATTR_AREA) printf("2. Área\n");
    if (excluido != ATTR_PIB) printf("3. PIB\n");
    if (excluido != ATTR_PONTOS_TURISTICOS) printf("4. Número de Pontos Turísticos\n");
    if (excluido != ATTR_DENSIDADE) printf("5. Densidade Demográfica (Regra: MENOR valor vence)\n");
    if (excluido != ATTR_PIB_PER_CAPITA) printf("6. PIB per capita\n");
    
    printf("--------------------------------------------------------\n");
    printf("Digite o número do atributo desejado: ");
}

// -------------------------------------------------------------------------
// FUNÇÃO AUXILIAR: ATRIBUI VALORES E REGRAS
// -------------------------------------------------------------------------

// Esta função preenche a estrutura Atributo com os dados baseados na escolha (id)
// e calcula o valor ajustado para a soma final.
void atribuir_atributo(Atributo *attr, int id, float densidade1, float pib_pc1, float densidade2, float pib_pc2) {
    attr->id = id;
    attr->valor_ajustado1 = 0.0f;
    attr->valor_ajustado2 = 0.0f;
    
    switch (id) {
        case ATTR_POPULACAO:
            strcpy(attr->nome, "População");
            attr->valor1 = CARTA1_POPULACAO;
            attr->valor2 = CARTA2_POPULACAO;
            attr->maior_vence = 1;
            break;
        case ATTR_AREA:
            strcpy(attr->nome, "Área (km²)");
            attr->valor1 = CARTA1_AREA;
            attr->valor2 = CARTA2_AREA;
            attr->maior_vence = 1;
            break;
        case ATTR_PIB:
            strcpy(attr->nome, "PIB (R$)");
            attr->valor1 = CARTA1_PIB;
            attr->valor2 = CARTA2_PIB;
            attr->maior_vence = 1;
            break;
        case ATTR_PONTOS_TURISTICOS:
            strcpy(attr->nome, "Pontos Turísticos");
            attr->valor1 = CARTA1_PONTOS_TURISTICOS;
            attr->valor2 = CARTA2_PONTOS_TURISTICOS;
            attr->maior_vence = 1;
            break;
        case ATTR_DENSIDADE:
            strcpy(attr->nome, "Densidade Demográfica (hab/km²)");
            attr->valor1 = densidade1;
            attr->valor2 = densidade2;
            attr->maior_vence = 0; // Regra especial: MENOR valor vence
            break;
        case ATTR_PIB_PER_CAPITA:
            strcpy(attr->nome, "PIB per capita (R$)");
            attr->valor1 = pib_pc1;
            attr->valor2 = pib_pc2;
            attr->maior_vence = 1;
            break;
        default:
            // Trata entrada inválida
            printf("\nErro: Opção inválida para o atributo. Encerrando.\n");
            exit(1);
    }
    
    // -------------------------------------------------------------------------
    // CÁLCULO DO VALOR AJUSTADO PARA A SOMA (Normalização para a regra "Menor Vence")
    // -------------------------------------------------------------------------
    
    // Se a regra é "Maior Vence", o valor ajustado é o próprio valor.
    if (attr->maior_vence == 1) {
        attr->valor_ajustado1 = attr->valor1;
        attr->valor_ajustado2 = attr->valor2;
    } else {
        // Se a regra é "Menor Vence", o valor ajustado deve ser invertido para que
        // o menor valor original contribua mais para a soma final.
        // Usamos uma técnica de inversão simples: MaxValue - Valor.
        // O valor máximo deve ser maior que o maior valor possível para o atributo.
        float max_val = (attr->valor1 > attr->valor2) ? attr->valor1 : attr->valor2;
        max_val += 1.0f; // Garante que o max_val seja estritamente maior

        attr->valor_ajustado1 = max_val - attr->valor1;
        attr->valor_ajustado2 = max_val - attr->valor2;
    }
}

// -------------------------------------------------------------------------
// FUNÇÃO PRINCIPAL
// -------------------------------------------------------------------------

int main() {
    int escolha1, escolha2;
    
    // 1. CÁLCULO DOS ATRIBUTOS DERIVADOS (Valores reais)
    float densidade_populacional_1 = CARTA1_POPULACAO / CARTA1_AREA;
    float pib_per_capita_1 = CARTA1_PIB / CARTA1_POPULACAO;
    float densidade_populacional_2 = CARTA2_POPULACAO / CARTA2_AREA;
    float pib_per_capita_2 = CARTA2_PIB / CARTA2_POPULACAO;

    // Estruturas para armazenar os dois atributos escolhidos
    Atributo attr1, attr2;
    
    printf("========================================================\n");
    printf("         SUPER TRUNFO CIDADES - NÍVEL MESTRE\n");
    printf("========================================================\n");

    // 2. ESCOLHA DO PRIMEIRO ATRIBUTO (Laço para garantir entrada válida)
    do {
        exibir_menu(0);
        if (scanf("%d", &escolha1) != 1) { // CORREÇÃO: Uso do & para scanf
            printf("\nErro: Entrada inválida. Por favor, digite um número.\n");
            return 1;
        }
        if (escolha1 < 1 || escolha1 > 6) {
            printf("\nOpção inválida! Escolha um número entre 1 e 6.\n");
        }
    } while (escolha1 < 1 || escolha1 > 6);
    
    atribuir_atributo(&attr1, escolha1, densidade_populacional_1, pib_per_capita_1, densidade_populacional_2, pib_per_capita_2);
    
    // 3. ESCOLHA DO SEGUNDO ATRIBUTO (Menu Dinâmico + Laço para garantir entrada válida e diferente)
    do {
        printf("\nPrimeiro atributo escolhido: %s\n", attr1.nome);
        exibir_menu(attr1.id); // Exclui o primeiro atributo
        
        if (scanf("%d", &escolha2) != 1) { // CORREÇÃO: Uso do & para scanf
            printf("\nErro: Entrada inválida. Por favor, digite um número.\n");
            return 1;
        }
        
        if (escolha2 == escolha1) {
            printf("\nOpção inválida! Você não pode escolher o mesmo atributo duas vezes.\n");
        } else if (escolha2 < 1 || escolha2 > 6) {
            printf("\nOpção inválida! Escolha um número entre 1 e 6.\n");
        }
    } while (escolha2 == escolha1 || escolha2 < 1 || escolha2 > 6);

    atribuir_atributo(&attr2, escolha2, densidade_populacional_1, pib_per_capita_1, densidade_populacional_2, pib_per_capita_2);

    // 4. CÁLCULO DA SOMA DOS ATRIBUTOS AJUSTADOS
    float soma_carta1 = attr1.valor_ajustado1 + attr2.valor_ajustado1;
    float soma_carta2 = attr1.valor_ajustado2 + attr2.valor_ajustado2;
    
    // 5. EXIBIÇÃO DO RESULTADO E OPERADOR TERNÁRIO
    printf("\n========================================================\n");
    printf("RESULTADO FINAL DA RODADA\n");
    printf("Atributos em Jogo: %s e %s\n", attr1.nome, attr2.nome);
    printf("--------------------------------------------------------\n");

    // Exibição detalhada dos valores
    printf("Carta 1: %s (%s)\n", CARTA1_CIDADE, CARTA1_ESTADO);
    printf("  -> %s: %.2f\n", attr1.nome, attr1.valor1);
    printf("  -> %s: %.2f\n", attr2.nome, attr2.valor1);
    printf("  -> SOMA PONTOS (AJUSTADA): %.2f\n", soma_carta1);

    printf("\nCarta 2: %s (%s)\n", CARTA2_CIDADE, CARTA2_ESTADO);
    printf("  -> %s: %.2f\n", attr1.nome, attr1.valor2);
    printf("  -> %s: %.2f\n", attr2.nome, attr2.valor2);
    printf("  -> SOMA PONTOS (AJUSTADA): %.2f\n", soma_carta2);
    printf("--------------------------------------------------------\n");

    // Uso do Operador Ternário para determinar o vencedor de forma elegante
    const char *vencedor = (soma_carta1 > soma_carta2) ? CARTA1_CIDADE : 
                           (soma_carta2 > soma_carta1) ? CARTA2_CIDADE : 
                           "Empate!";

    printf("VENCEDOR: %s\n", vencedor);
    printf("========================================================\n");

    return 0;
}
