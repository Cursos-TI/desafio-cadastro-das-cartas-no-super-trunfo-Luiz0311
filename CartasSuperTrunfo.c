#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEN_THOUSAND 10000
#define MILLION 1000000
#define BILLION 1000000000L
#define MAX_CARDS 10

struct Card
{
    char state[3];
    char city[20];
    char code[20];
    unsigned int population;
    unsigned int area;
    unsigned long GPD; // PIB geralmente passa de 4 bilhõoes nas grandes cidades
    float GPD_per_capita;
    float population_density;
    unsigned short tourist_attractions;
    float super_power;
};

/*
Formata o número de forma que de para entender.
O algorítimo funciona colocando os "." de trás para frente, contanto 3 casas
decimais e depois revertendo a string novamente. Assim, retornando a string
formatada

input: uint num
output: char num[(num len) + 1]

ex:
  in: 2999999.4324
  out: 2.999.999
*/
char *format_number(unsigned long num)
{
  static char formatted[30];
  char temp[20];
  snprintf(temp, 20, "%lu", num);

  int len = strlen(temp);
  int count = 0;
  int j = 0;

  // coloca os pontos de trás para frente
  for (int i = len - 1; i >= 0; i--)
  {
    if (count == 3)
    {
      formatted[j++] = '.';
      count = 0;
    }
    formatted[j++] = temp[i];
    count++;
  }

  formatted[j] = '\0';

  // reverte a string formatada
  int formatted_len = strlen(formatted);
  for (int i = 0; i < formatted_len / 2; i++)
  {
    char tmp = formatted[i];
    formatted[i] = formatted[formatted_len - 1 - i];
    formatted[formatted_len - 1 - i] = tmp;
  }

  return formatted;
}

// https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c
void clear_terminal()
{
  printf("\e[1;1H\e[2J");
}

// Recebe o ponteiro de uma carta e printa ela de forma organizada
void print_card(struct Card *card) 
{
  int GPD_reduced;
  char *b_or_m;

  // Condicional se o pib for maior que 1 bilhão
  if (card->GPD > BILLION)
  {
    b_or_m = "bilhões";
    GPD_reduced = card->GPD / BILLION;
  }
  else
  {
    b_or_m = "milhões";
    GPD_reduced = card->GPD / MILLION;
  }

  clear_terminal();
  printf("=== Estado: %s, Cidade: %s, Código: %s ===\n", card->state, card->city, card->code);
  printf("População: %s habitantes\n", format_number(card->population));
  printf("Área: %s km²\n", format_number(card->area));
  printf("PIB: R$ %s %s\n", format_number(GPD_reduced), b_or_m);
  printf("PIB per Capita: R$ %s\n", format_number(card->GPD_per_capita));
  printf("Densidade Populacional: %s habitantes/km²\n", format_number(card->population_density));
  printf("Pontos Turísticos: %d\n", card->tourist_attractions);
  printf("Super Poder: %s\n", format_number(card->super_power));
  printf("=================================================\n");
}

// Função para calcular os atributos: (1) PIB per capita; (2) Densidade populacional; (3) Super poder.
void calc_attr(struct Card *card)
{
  card->GPD_per_capita = card->GPD / card->population;
  card->population_density = card->population / card->area;

  card->super_power = card->population +
                     card->area +
                     (card->GPD / MILLION) + // Para não ficar um número gigante, dividimos por um milhão
                     card->GPD_per_capita +
                     (card->population_density * -1) +
                     card->tourist_attractions; 
}

// Printa o menu
void menu(const char *title)
{
  clear_terminal();
  const char *opt[] =
  {
    "Cadastrar carta",
    "Listar cartas",
    "Comparar cartas",
    "Sair do jogo"
  };

  printf("=== %s ===\n", title);
  
  // https://www.geeksforgeeks.org/length-of-array-in-c/
  int len = sizeof(opt) / sizeof(opt[0]);
  for (int i = 0; i < len; i++)
    printf("%d. %s\n", i + 1, opt[i]);
  printf("R: ");
}

/*
Menu para registrar cartas

TODO: função muito propensa a erros, adicionar segurança e validações
*/
int register_menu(struct Card *cards, int *card_count)
{
  if (*card_count > MAX_CARDS)
  {
    printf("Limite de cartas atingido!\n");
    return 1;
  }

  clear_terminal();
  struct Card new_card;
  printf("Estado: ");
  scanf("%s", new_card.state);

  /*
  https://stackoverflow.com/questions/29957033/how-to-read-multiple-words-in-a-line-in-c
  usa-se "%[^\n]" e "getchar()" para ler nomes compostos de cidades
  */
  getchar();
  printf("Cidade: ");
  scanf("%[^\n]", new_card.city);

  printf("Código: ");
  scanf("%s", new_card.code);
  printf("População: ");
  scanf("%d", &new_card.population);
  printf("Área: ");
  scanf("%d", &new_card.area);
  printf("PIB (em milhões): ");
  scanf("%ld", &new_card.GPD);
  new_card.GPD *= MILLION;
  printf("Pontos turísticos: ");
  scanf("%hd", &new_card.tourist_attractions);

  calc_attr(&new_card);
  cards[(*card_count)++] = new_card;

  return 0;
}

// Lista todas as cartas disponíveis
void listCards(struct Card *cards, int card_count)
{
  clear_terminal();
  unsigned int opt;

  printf("Número de cartas: %d\n", card_count);
  while (1)
  {
    for (int i = 0; i < card_count; i++)
      printf("%d. %s\n", i + 1, cards[i].code);

    printf("Escolha uma carta (0 para sair): ");
    scanf("%d", &opt);

    if (opt < 1) break;
    if (opt > card_count)
    {
      clear_terminal();
      printf("Carta indisponível. Tente novamente.\n");
      continue;
    }

    print_card(&cards[opt-1]);
  }
}

/*
Retorna o valor do atributo convertido em long
*/
long get_attr(struct Card *card, unsigned int opt)
{
  switch (opt)
  {
    case 1: return (long)card->population;
    case 2: return (long)card->area;
    case 3: return (long)card->GPD;
    case 4: return (long)card->GPD_per_capita;
    case 5: return (long)card->population_density;
    case 6: return (long)card->tourist_attractions;
    case 7: return (long)card->super_power;
    default: return 0L;
  }
}


// Função para comparar as cartas com um menu interativo
void compare_cards(struct Card *cards, int card_count)
{
  const char *options[] = 
  {
		"População",
		"Área",
		"PIB",
		"PIB per Capita",
		"Densidade Populacional",
		"Pontos Turísticos",
		"Super Poder",
  };

  unsigned short result, c1, c2;

  clear_terminal();
  printf("Número de cartas: %d\n", card_count);
  while (1)
  {
    for (int i = 0; i < card_count; i++)
      printf("%d. %s\n", i + 1, cards[i].code);

    printf("Escolha duas cartas para comparar (0 para sair): ");
    scanf("%hd", &c1);

    if (c1 == 0) break;

    scanf("%hd", &c2);

    if (c1 > card_count || c2 > card_count)
    {
      clear_terminal();
      printf("Uma das cartas está indisponível. Tente novamente.\n");
      continue;
    }

    if (c1 == c2)
    {
      clear_terminal();
      printf("As cartas são iguais. Tente novamente.\n");
      continue;
    }

    struct Card card1 = cards[--c1], card2 = cards[--c2];
    clear_terminal();
    printf("Cartas escolhidas: %s e %s\n", card1.code, card2.code);
  
    while (1)
    {
      unsigned short a1, a2;

      int len = sizeof(options) / sizeof(options[0]);
      for (int i = 0; i < len; i++)
        printf("%d. %s\n", i + 1, options[i]);


      printf("Escolha dois atributos para comparar (0 para sair): ");
      scanf("%hd", &a1);

      if (a1 == 0) break;

      scanf("%hd", &a2);

      if (a2 == 0) a2 = 0;
      if (a2 == a1) a2 = 0;

      long c1_attr_1 = get_attr(&card1, a1);
      long c1_attr_2 = get_attr(&card1, a2);
      long c2_attr_1 = get_attr(&card2, a1);
      long c2_attr_2 = get_attr(&card2, a2);

      long c1_sum = c1_attr_1 + c1_attr_2;
      long c2_sum = c2_attr_1 + c2_attr_2;


      clear_terminal();
      const char *attr_name_1, *attr_name_2;
      printf("Comparação de cartas ");
      if (a2 == 0)
      {
        attr_name_1 = options[a1 - 1];

        printf("(Atributo: %s)\n", attr_name_1);

        printf("Carta 1 - %s (%s): ", card1.city, card1.state);
        printf("%s: %s, ", attr_name_1, format_number(c1_attr_1));
        
        printf("Carta 2 - %s (%s): ", card2.city, card2.state);
        printf("%s: %s, ", attr_name_1, format_number(c1_attr_2));
      }
      else
      {
        attr_name_1 = options[a1 - 1];
        attr_name_2 = options[a2 - 1];

        printf("(Atributos: %s e %s)\n", attr_name_1, attr_name_2);
      
        printf("Carta 1 - %s (%s): ", card1.city, card1.state);
        printf("%s: %s, ", attr_name_1, format_number(c1_attr_1));
        printf("%s: %s, ", attr_name_2, format_number(c1_attr_2));
        printf("Soma: %s\n", format_number(c1_sum));

        printf("Carta 2 - %s (%s): ", card2.city, card2.state);
        printf("%s: %s, ", attr_name_1, format_number(c2_attr_1));
        printf("%s: %s, ", attr_name_2, format_number(c2_attr_2));
        printf("Soma: %s\n", format_number(c2_sum));
      }

      /*
      Lógica para calcular o vencedor — se o atributo for densidade populacional,
      vence o que tem menor pontuação:

      se é densidade populacional, então o menor valor vence
      se não, então o maior vence
      */
      const char *population_density = options[4];
      int is_population_density = 
        (attr_name_1 == population_density) || (attr_name_2 == population_density);
      int gt_or_ls = is_population_density ? c1_sum > c2_sum : c1_sum < c2_sum;
      int winner = c1_sum == c2_sum ? 2 : (gt_or_ls ? 1 : 0);
      printf("Resultado: ");
      switch (winner)
      {
        case 0: printf("Carta 1 (%s) venceu!\n", card1.city); break;
        case 1: printf("Carta 2 (%s) venceu!\n", card2.city); break;
        case 2: printf("Empate!\n"); break;
      }

      unsigned short ex;
      printf("(1) Voltar ao menu (2) Sair do jogo: ");
      scanf("%hd", &ex);

      if (ex == 1) break;
      exit(EXIT_SUCCESS);
    }
  
    break;
  }
}

// funcção main — menu principal do jogo
int main(void)
{
  int option;
  int card_count = 0;
  struct Card cards[MAX_CARDS];

  // MOCK #######################################
  struct Card curitiba = 
    {
      "PR",
      "Curitiba",
      "C1",
      1700000,
      432,
      98 * BILLION,
      0.0,
      0.0,
      30,       
      0.0L     
    };
  calc_attr(&curitiba);
  cards[card_count++] = curitiba;

  struct Card sao_paulo =
  {
    "SP",
    "Sao Paulo",
    "S1",
    11451999,
    1521,
    (long)(828 * BILLION),
    0.0,
    0.0,
    36,
    0.0L
  };
  calc_attr(&sao_paulo);
  cards[card_count++] = sao_paulo;
  // ###########################################

  while (option != 4)
  {
    menu("Cartas Super Trunfo");

    // Condição para validar entrada e limpar o buffer.
    if (scanf("%d", &option) != 1)
    {
      printf("Entrada inválida. Tente novamente.\n");
      while (getchar() != '\n');
      continue;
    }

    switch (option)
    {
      case 1:
        register_menu(cards, &card_count);
        break;
      case 2:
        listCards(cards, card_count);
        break;
      case 3:
        compare_cards(cards, card_count);
        break;
      case 4:
        printf("Jogo encerrado.\n");
        break;
      default:
        printf("Por favor, digite uma opção válida.\n");
        break;
    }
  }
}
