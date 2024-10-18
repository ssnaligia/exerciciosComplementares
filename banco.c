#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "funcoes.c"

int main() {
    setlocale(LC_ALL, "");
    int opcao;

    do {
        printf("\n| SISTEMA BANCO |\n");
        printf("1. Criar Conta\n");
        printf("2. Fazer Login\n");
        printf("3. Encerrar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao < 1 || opcao > 3) {
            printf("\nOpção Inválida!\n");
            continue; 
        }

        switch (opcao) {
            case 1:
                cadastroConta();
                break;
            case 2:
                printf("\nDigite seu CPF: ");
                char cpfLogin[12];
                scanf(" %[^\n]", cpfLogin);

                Conta contaEncontrada;
                int contaValida = 0;

                for (int i = 0; i < numContas; i++) {
                    if (strcmp(Contas[i].cpf, cpfLogin) == 0) {
                        contaEncontrada = Contas[i];
                        contaValida = 1;
                        break;
                    }
                }

                if (contaValida) {
                    char senhaLogin[15];
                    printf("Digite sua senha: ");
                    scanf(" %[^\n]", senhaLogin);

                    if (strcmp(contaEncontrada.senha, senhaLogin) == 0) {
                        printf("\n| SISTEMA BANCO - Logado(a) como %s |", contaEncontrada.nomeCliente);
                        do {
                            printf("1. Consultar Saldo\n");
                            printf("2. Depositar\n");
                            printf("3. Sacar\n");
                            printf("4. Realizar Transferência/Pix\n");
                            printf("5. Sair da Conta\n");
                            printf("Escolha uma opção: ");
                            scanf("%d", &opcao);

                            switch (opcao) {
                                case 1:
                                    //consultarSaldo();
                                    break;
                                case 2:
                                    //depositar();
                                    break;
                                case 3:
                                    //sacar();
                                    break;
                                case 4:
                                    //realizarPix();
                                    break;
                                case 5:
                                    printf("\nSaindo da Conta... Até mais!\n");
                                    break;
                                default:
                                    printf("\nOpção Inválida!\n");
                                    break;
                            }
                        } while (opcao != 5);
                    } else {
                        printf("\nSenha incorreta!\n");
                    }
                } else {
                    printf("\nConta não encontrada para o CPF: %s.\n", cpfLogin);
                }
                break;
            case 3:
                printf("\nEncerrando...\n");
                break;
        }
    } while (opcao != 3);

    return 0;
}
