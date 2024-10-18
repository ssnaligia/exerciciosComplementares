#include <stdio.h>


int main() {
    // Inicializa o gerador de números aleatórios
    srand(time(0));

    // Gera um número aleatório entre 10000000 e 99999999 (8 dígitos)
    long numero_conta = 10000000 + rand() % 90000000;

    // Exibe o número da conta gerado
    printf("Número da conta gerado: %ld\n", numero_conta);

    return 0;
}
