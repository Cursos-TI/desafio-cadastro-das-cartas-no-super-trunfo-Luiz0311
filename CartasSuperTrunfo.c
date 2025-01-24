#include <stdio.h>

// Desafio Super Trunfo - Países
// Tema 1 - Cadastro das Cartas
// Este código inicial serve como base para o desenvolvimento do sistema de cadastro de cartas de cidades.
// Siga os comentários para implementar cada parte do desafio.
//Teste larissa

int main() {
    // Sugestão: Defina variáveis separadas para cada atributo da cidade.
    // Exemplos de atributos: código da cidade, nome, população, área, PIB, número de pontos turísticos.
    char name[20];
    char code[20];
    int population, area, tourist_attractions;
    float population_density, pib_per_capta;
    long pib;
    
    // Cadastro das Cartas:
    // Sugestão: Utilize a função scanf para capturar as entradas do usuário para cada atributo.
    // Solicite ao usuário que insira as informações de cada cidade, como o código, nome, população, área, etc.
    printf("Digite o nome da cidade: ");
    scanf("%s", &name);

    printf("Digite o código da cidade:");
    scanf("%s", &code);

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
    // Exibição dos Dados das Cartas:
    // Sugestão: Utilize a função printf para exibir as informações das cartas cadastradas de forma clara e organizada.
    // Exiba os valores inseridos para cada atributo da cidade, um por linha.
    printf(
        "Estado: A\nCódigo da Carta: %s\nNome da Cidade: %s\nPopulação: %d\nArea: %d km²\nPIB: %ld bilhões de reais\n"
        "PIB per Capita: %.2f reais\nNúmero de pontos turísticos: %d\n",
        code, name, population, area, pib / 1000000000, pib_per_capta, tourist_attractions
    );

    return 0;
}
