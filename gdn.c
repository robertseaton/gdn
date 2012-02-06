#include <stdio.h>
#include <string.h>
#include <gmp.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX 100

const char SYMBOLS[] = "1234567890./+=-()*^ ";

void usage()
{
     printf("usage: gdn\n");
     printf("       -d, --decode [number]\n");
     printf("       -e, --encode [expression]\n");
}

void decode(const char *input)
{
     mpz_t n, prime;
     unsigned long occurs = 1;

     mpz_init_set_str(n, input, 10);
     mpz_init_set_ui(prime, 0);
     while (occurs != 0) {
          mpz_nextprime(prime, prime);
          occurs = mpz_remove(n, n, prime);
          if (occurs != 0)
               printf("%c", SYMBOLS[occurs - 1]);
     }
     printf("\n");

     if (mpz_get_ui(n) > 1)
          printf("Error: Not a valid Godel number.\n");
          
}

const char *get_expr(int argc, char *expr[])
{
     char *str;
     int length = 0;
     
     int i;
     for (i = 2; i < argc; i++) {
          length += strlen(expr[i]);
          length += 1; /* for space */
     }

     length += 1; /* trailing null */

     str = malloc(length);
     *str = '\0'; /* for strcat */

     for (i = 2; i < argc; i++) {
          strcat(str, expr[i]);
          strcat(str, " ");
     }

     return str;
}


void encode(int argc, char *expr[])
{
     const char *complete_expr = get_expr(argc, expr);
     unsigned char *table = malloc(strlen(complete_expr));

     int i, j;
     for (i = 0; i < strlen(complete_expr); i++) {
          table[i] = 0;
          for (j = 0; j < sizeof(SYMBOLS); j++) {
               if (complete_expr[i] == SYMBOLS[j])
                    table[i] = j + 1;
          }
          if (table[i] == 0) {
               printf("Unsupported symbol: %c\n", complete_expr[i]);
               exit(EXIT_FAILURE);
          }
     }
     
     mpz_t godel_number, prime, tmp;

     mpz_inits(prime, tmp, NULL);
     mpz_init_set_ui(godel_number, 1);
     for (i = 0; i < strlen(complete_expr); i++) {
          mpz_nextprime(prime, prime);
          mpz_pow_ui(tmp, prime, table[i]);
          mpz_mul(godel_number, godel_number, tmp);
     }

     gmp_printf("%Zd\n", godel_number);
}

int main(int argc, char *argv[])
{

     if (argc < 3)
          usage();
     else if (strstr("-d", argv[1]) != NULL)
          decode(argv[2]);
     else if (strstr("-e", argv[1]) != NULL)
          encode(argc, argv);

     return 0;
}
