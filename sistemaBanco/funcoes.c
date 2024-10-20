#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX_CONTAS 15

typedef struct {
    int numero;
    char cpf[12];
    char nomeCliente[60];
    char senha[15];
    float saldo;
} Conta;

Conta Contas[MAX_CONTAS];
int numContas = 0;
int codigoAtual = 1;

void cadastroConta() {
    srand(time(0));
    if (numContas >= MAX_CONTAS) {
        printf("Limite de contas atingido!\n");
        return;
    }

    Conta novaConta;
    long numero = 10000000 + rand() % 90000000;
    novaConta.numero = numero;

    printf("\nDigite seu CPF: ");
    scanf(" %[^\n]", novaConta.cpf);

    for (int i = 0; i < numContas; i++) {
        if (strcmp(Contas[i].cpf, novaConta.cpf) == 0) {
            printf("CPF '%s' já cadastrado! Cadastro não permitido.\n", novaConta.cpf);
            return;
        }
    }

    printf("Digite seu nome: ");
    scanf(" %[^\n]", novaConta.nomeCliente);
    printf("Digite sua senha [5 dígitos]: ");
    scanf(" %[^\n]", novaConta.senha);

    do {
        printf("Digite seu saldo inicial: ");
        scanf("%f", &novaConta.saldo);
        while (getchar() != '\n');

        if (novaConta.saldo <= 0) {
            printf("Saldo inicial deve ser positivo!\n");
        }
    } while (novaConta.saldo <= 0);

    Contas[numContas++] = novaConta;
    printf("\nConta cadastrada com sucesso!\n");
    printf("O número da sua conta é: %ld.\n", novaConta.numero);
}

void depositar(Conta *conta) {
    float valorDeposito;

    do {
        printf("\nDigite o valor a ser depositado: ");
        scanf("%f", &valorDeposito);
        while (getchar() != '\n');

        if (valorDeposito <= 0) {
            printf("\n\nValor de depósito deve ser positivo.\n");
        }
    } while (valorDeposito <= 0);

    conta->saldo += valorDeposito;
    printf("\n\nDepósito realizado com sucesso! Novo saldo: R$%.2f\n", conta->saldo);
}


void sacar(Conta *conta) {
    float valorSaque;

    do {
        printf("\nDigite o valor a ser sacado: ");
        scanf("%f", &valorSaque);
        while (getchar() != '\n');  

        if (valorSaque <= 0) {
            printf("\nValor de saque deve ser positivo.\n");
        } else if (valorSaque > conta->saldo) {
            printf("\nSaldo insuficiente para o saque. Saldo Atual: R$%.2f.\n", conta->saldo);
        }
    } while (valorSaque <= 0 || valorSaque > conta->saldo); 

    conta->saldo -= valorSaque;  
    printf("\n\nSaque realizado com sucesso! Novo saldo: R$%.2f\n", conta->saldo); 
}
