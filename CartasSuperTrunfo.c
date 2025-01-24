#include <stdio.h>

// Desafio Super Trunfo - Países
// Tema 1 - Cadastro das Cartas
// Este código inicial serve como base para o desenvolvimento do sistema de cadastro de cartas de cidades.
// Siga os comentários para implementar cada parte do desafio.

long double card();

int main() {
    long double card1, card2;
    int winner;

    card1 = card();
    card2 = card();
    
    printf("Carta 1: %.5Lf\nCarta 2: %.5Lf\n", card1, card2);
    winner = card1 < card2;
    if (winner) {
      printf("Carta 2 vencedora!\n");
      return 0;
    }

    printf("Carta 1 vencedora!\n");

    return 0;
}

long double card() {
    // Sugestão: Defina variáveis separadas para cada atributo da cidade.
    // Exemplos de atributos: código da cidade, nome, população, área, PIB, número de pontos turísticos.
    char name[20];
    char code[20];
    unsigned int population, area, tourist_attractions;
    float population_density, pib_per_capta;
    long int pib; // long int usado para calcular o pib per capita corretamente
    long double super_power; // long double usado por erro em declaração de long float
    
    // Cadastro das Cartas:
    // Sugestão: Utilize a função scanf para capturar as entradas do usuário para cada atributo.
    // Solicite ao usuário que insira as informações de cada cidade, como o código, nome, população, área, etc.
    printf("Digite o nome da cidade: ");
    scanf("%s", name);

    printf("Digite o código da cidade: ");
    scanf("%s", code);

    printf("Digite a população: ");
    scanf("%d", &population);

    printf("Digite a área (em km²): ");
    scanf("%d", &area);

    printf("Digite o PIB (em bilhões): ");
    scanf("%ld", &pib);
    pib = pib * 1000000000;

    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &tourist_attractions);

    population_density = population / area;
    pib_per_capta = pib / population;

    // Cada carta terá um super poder que é a soma de todas as propriedades (população, área, PIB, PIB per capta e 
    // densidade populacional invertida para comparação e número de pontos turísticos).
    super_power = population + area + (pib / 1000000000) + pib_per_capta + (population_density * -1) + tourist_attractions;

    // Exibição dos Dados das Cartas:
    // Sugestão: Utilize a função printf para exibir as informações das cartas cadastradas de forma clara e organizada.
    // Exiba os valores inseridos para cada atributo da cidade, um por linha.
    printf("-------------------------------------\n");
    printf("Estado: A\n");
    printf("Código da Carta: %s\n", code);
    printf("Nome da Cidade: %s\n", name);
    printf("População: %d\n", population);
    printf("Area: %d km²\n", area);
    printf("PIB: %ld\n", pib);
    printf("PIB per Capita: %.2f\n", pib_per_capta);
    printf("Densidade Populacional: %.2f\n", population_density);
    printf("Número de Pontos Turísticos: %d\n", tourist_attractions);
    printf("Super Poder: %.5Lf\n", super_power);
    printf("-------------------------------------\n");

    return super_power;
}