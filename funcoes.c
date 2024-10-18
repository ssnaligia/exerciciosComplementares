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
    novaConta.numero = codigoAtual;  
    codigoAtual++; 

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
    
    printf("Digite seu saldo inicial: ");
    scanf("%f", &novaConta.saldo); 
    while (getchar() != '\n'); 

    if (novaConta.saldo < 0) {
        printf("Saldo inicial não pode ser negativo!\n");
        return;
    }

    Contas[numContas++] = novaConta; 
    printf("\nConta cadastrada com sucesso!\n");
    printf("O número da sua conta é: %ld.\n", novaConta.numero);
}

void depositar(Conta *conta) {
    float valorDeposito;
    printf("\nDigite o valor a ser depositado: ");
    scanf("%f", &valorDeposito);
    while (getchar() != '\n'); 
    
    if (valorDeposito <= 0) {
        printf("\n\nValor de depósito deve ser positivo.\n");
        return;
    }

    conta->saldo += valorDeposito;
    printf("\n\nDepósito realizado com sucesso! Novo saldo: %.2f\n", conta->saldo);
}