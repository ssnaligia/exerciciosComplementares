#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define MAX_CONTAS 15

typedef struct {
    long numero;
    char cpf[12];
    char nomeCliente[60];
    char senha[15];
    float saldo;
    int isGerente;
} Conta;

Conta Contas[MAX_CONTAS];
int numContas = 0;

void criarContaGerente() {
    Conta gerente;
    gerente.numero = 12345678;  
    strcpy(gerente.cpf, "987654321");  
    strcpy(gerente.nomeCliente, "Gerente Master");  
    strcpy(gerente.senha, "admin123"); 
    gerente.saldo = 0; 
    gerente.isGerente = 1;  
    Contas[numContas++] = gerente;
}

void criarContaDemo() {
    Conta contaDemo;
    contaDemo.numero = 987654321;
    strcpy(contaDemo.cpf, "123456789"); 
    strcpy(contaDemo.nomeCliente, "Ricardo");
    strcpy(contaDemo.senha, "12345");      
    contaDemo.saldo = 1000.00;             
    contaDemo.isGerente = 0; 
    Contas[numContas++] = contaDemo;
}

int autenticarUsuario(char *cpf, Conta *contaEncontrada) {
    for (int i = 0; i < numContas; i++) {
        if (strcmp(Contas[i].cpf, cpf) == 0) {
            *contaEncontrada = Contas[i]; 
            char senhaLogin[15];
            printf("Digite sua senha: ");
            scanf(" %[^\n]", senhaLogin);
            getchar();
            if (strcmp(contaEncontrada->senha, senhaLogin) == 0) {
                return i; 
            } else {
                printf("Senha incorreta.\n");
                return -1; 
            }
        }
    }
    printf("CPF não encontrado.\n");
    return -1; 
}

void cadastroConta() {
    srand(time(0));
    if (numContas >= MAX_CONTAS) {
        printf("Limite de contas atingido!\n");
        return;
    }

    Conta novaConta;
    novaConta.numero = 10000000 + rand() % 90000000;

    printf("\nDigite seu CPF: ");
    scanf(" %[^\n]", novaConta.cpf);

    for (int i = 0; i < numContas; i++) {
        if (strcmp(Contas[i].cpf, novaConta.cpf) == 0) {
            printf("CPF '%s' já cadastrado!\n", novaConta.cpf);
            return;
        }
    }

    printf("Digite seu nome: ");
    scanf(" %[^\n]", novaConta.nomeCliente);
    printf("Digite sua senha [6 dígitos]: ");
    scanf(" %[^\n]", novaConta.senha);

    novaConta.saldo = 0;
    novaConta.isGerente = 0; 

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
            printf("\nValor de depósito deve ser positivo.\n");
        }
    } while (valorDeposito <= 0);

    conta->saldo += valorDeposito;
    printf("\nDepósito realizado com sucesso! Novo saldo: R$%.2f\n", conta->saldo);
}

void consultarSaldo(Conta *conta) {
    printf("\nSaldo Atual: R$%.2f.\n", conta->saldo);
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
    printf("\nSaque realizado com sucesso! Novo saldo: R$%.2f\n", conta->saldo); 
}

void realizarPix(Conta *contaOrigem) {
    char cpfDestino[12];
    float valor;

    printf("\nDigite o CPF do destinatário: ");
    scanf(" %[^\n]", cpfDestino);
    getchar();

    Conta *contaDestino = NULL;
    for (int i = 0; i < numContas; i++) {
        if (strcmp(Contas[i].cpf, cpfDestino) == 0) {
            contaDestino = &Contas[i];
            break;
        }
    }

    if (contaDestino == NULL) {
        printf("\nConta do destinatário não encontrada.\n");
        return;
    }

    do {
        printf("Digite o valor a ser transferido: ");
        scanf("%f", &valor);
        getchar();

        if (valor <= 0) {
            printf("\nValor de transferência deve ser positivo.\n");
        } else if (valor > contaOrigem->saldo) {
            printf("\nSaldo insuficiente para a transferência. Saldo Atual: R$%.2f.\n", contaOrigem->saldo);
        }
    } while (valor <= 0 || valor > contaOrigem->saldo);

    contaOrigem->saldo -= valor;
    contaDestino->saldo += valor;

    printf("\nTransferência realizada com sucesso! Novo saldo: R$%.2f\n", contaOrigem->saldo);
}

void gerarRelatorio() {
    printf("\n| RELATÓRIO DE CONTAS |\n\n");
    for (int i = 0; i < numContas; i++) {
        printf("Conta Nº: %ld\n", Contas[i].numero);
        printf("Nome: %s\n", Contas[i].nomeCliente);
        printf("CPF: %s\n", Contas[i].cpf);
        printf("Saldo: R$%.2f\n\n", Contas[i].saldo);
    }
}

int main() {
    setlocale(LC_ALL, "");
    criarContaGerente();
    criarContaDemo();

    int opcao;

    do {
        printf("\n| SISTEMA BANCO |\n\n");
        printf("1. Criar Conta\n");
        printf("2. Fazer Login\n");
        printf("3. Depósito Rápido\n"); 
        printf("4. Saque Rápido\n");
        printf("5. Consultar Saldo\n");
        printf("6. Realizar Transferência/Pix\n");
        printf("7. Encerrar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        while (getchar() != '\n'); 

        if (opcao < 1 || opcao > 7) {
            printf("\nOpção Inválida!\n");
            continue;
        }

        switch (opcao) {
            case 1:
                cadastroConta();  
                break;
            
            case 2: {
                printf("\nDigite seu CPF: ");
                char cpfLogin[12];
                scanf(" %[^\n]", cpfLogin);
                while (getchar() != '\n'); 

                Conta contaEncontrada;
                int indice = autenticarUsuario(cpfLogin, &contaEncontrada);
                if (indice != -1) {                            

                    int opcaoLogin;
                    if (contaEncontrada.isGerente) {
                        do {
                            printf("\n| SISTEMA BANCO - Logado(a) como Gerente: %s |\n", contaEncontrada.nomeCliente);
                            printf("1. Gerar Relatório\n");
                            printf("2. Sair da Conta\n");
                            printf("Escolha uma opção: ");
                            scanf("%d", &opcaoLogin);
                            getchar();
                            switch (opcaoLogin) {
                                case 1:
                                    gerarRelatorio();
                                    break;
                                case 2:
                                    printf("\nSaindo da Conta... Obrigado(a) por usar nossos serviços!\n");
                                    break;
                                default:
                                    printf("\nOpção Inválida!\n");
                                    break;
                            }
                        } while (opcaoLogin != 2);
                    } else {
                        do {
                            printf("\n| SISTEMA BANCO - Logado(a) como %s |\n", contaEncontrada.nomeCliente);
                            printf("Agência: 0287 | Número da Conta: %ld\n\n", contaEncontrada.numero);
                            printf("1. Consultar Saldo\n");
                            printf("2. Depositar\n");
                            printf("3. Sacar\n");
                            printf("4. Realizar Transferência/Pix\n");
                            printf("5. Sair da Conta\n");
                            printf("Escolha uma opção: ");
                            scanf("%d", &opcaoLogin);
                            getchar();
                            switch (opcaoLogin) {
                                case 1:
                                    consultarSaldo(&contaEncontrada);
                                    break;
                                case 2:
                                    depositar(&contaEncontrada);
                                    Contas[indice] = contaEncontrada;  // Atualizar a conta no array
                                    break;
                                case 3:
                                    sacar(&contaEncontrada);
                                    Contas[indice] = contaEncontrada;  // Atualizar a conta no array
                                    break;
                                case 4:
                                    realizarPix(&contaEncontrada);
                                    Contas[indice] = contaEncontrada;  // Atualizar a conta no array
                                    break;
                                case 5:
                                    printf("\nSaindo da Conta... Obrigado(a) por usar nossos serviços!\n");
                                    break;
                                default:
                                    printf("\nOpção Inválida!\n");
                                    break;
                            }
                        } while (opcaoLogin != 5);
                    }
                } else {
                    printf("\nCredenciais inválidas! CPF ou senha incorretos.\n");
                }
                break;
            }

            case 3: { 
                printf("\nDigite seu CPF: ");
                char cpfDep[12];
                scanf(" %[^\n]", cpfDep);
                while (getchar() != '\n');

                Conta contaDep;
                int indiceContaDep = autenticarUsuario(cpfDep, &contaDep);
                if (indiceContaDep != -1) {
                    depositar(&contaDep); 
                    Contas[indiceContaDep] = contaDep;  // Atualizar a conta no array
                } else {
                    printf("\nCredenciais inválidas! CPF ou senha incorretos.\n");
                }
                break;
            }

            case 4: {
                printf("\nDigite seu CPF: ");
                char cpfSaque[12];
                scanf(" %[^\n]", cpfSaque);
                while (getchar() != '\n');

                Conta contaSaque;
                int indiceContaSaque = autenticarUsuario(cpfSaque, &contaSaque);
                if (indiceContaSaque != -1) {
                    sacar(&contaSaque); 
                    Contas[indiceContaSaque] = contaSaque;  // Atualizar a conta no array
                }
                break;
            }

            case 5: {
                printf("\nDigite seu CPF: ");
                char cpfSaldo[12];
                scanf(" %[^\n]", cpfSaldo);
                while (getchar() != '\n');

                Conta contaSaldo;
                int indiceContaSaldo = autenticarUsuario(cpfSaldo, &contaSaldo);
                if (indiceContaSaldo != -1) {
                    consultarSaldo(&contaSaldo);
                }
                break;
            }

            case 6: {
                printf("\nDigite seu CPF: ");
                char cpf[12];
                scanf(" %[^\n]", cpf);
                getchar();

                Conta contaEncontrada;
                int indiceConta = autenticarUsuario(cpf, &contaEncontrada); 
                if (indiceConta != -1) {
                    realizarPix(&Contas[indiceConta]); 
                }
                break;
            }

            case 7:
                printf("\nEncerrando...\n");
                break;
        }
    } while (opcao != 7);

    return 0;
}
