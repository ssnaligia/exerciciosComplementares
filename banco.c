#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include "funcoes.c"

int main() {
    setlocale(LC_ALL, "");

    int opcao;

    do {
        printf("\n| SISTEMA BANCO |\n\n");
        printf("1. Criar Conta\n");
        printf("2. Fazer Login\n");
        printf("3. Encerrar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        while (getchar() != '\n'); 


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
                while (getchar() != '\n'); 


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
                    getchar();  

                    if (strcmp(contaEncontrada.senha, senhaLogin) == 0) {
                        int opcaoLogin;

                        do {
                            printf("\n| SISTEMA BANCO - Logado(a) como %s |\n\n", contaEncontrada.nomeCliente);
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
                                    printf("\nSaldo Atual: R$%.2f.\n", contaEncontrada.saldo);
                                    break;
                                case 2:
                                    depositar(&contaEncontrada);
                                    break;
                                case 3:
                                    //sacar(&contaEncontrada);
                                    break;
                                case 4:
                                    //realizarPix(&contaEncontrada);
                                    break;
                                case 5:
                                    printf("\nSaindo da Conta... Até mais!\n");
                                    break;
                                default:
                                    printf("\nOpção Inválida!\n");
                                    break;
                            }
                        } while (opcaoLogin != 5);
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
