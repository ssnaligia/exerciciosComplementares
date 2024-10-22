#include <stdio.h>
#include <string.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");
    criarContaGerente();
    criarContaDemo();

    int opcao;

    do {
        printf("\n| SISTEMA BANCO |\n\n");
        printf("1. Criar Conta\n");
        printf("2. Fazer Login\n");
        printf("3. Saque Rápido\n");
        printf("4. Consultar Saldo\n");
        printf("5. Realizar Transferência/Pix\n");
        printf("6. Encerrar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        while (getchar() != '\n'); 

        if (opcao < 1 || opcao > 6) {
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
                if (autenticarUsuario(cpfLogin, &contaEncontrada)) {                            
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
                                    printf("\nSaindo da Conta do Gerente...\n");
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
                                    printf("\nSaldo Atual: R$%.2f.\n", contaEncontrada.saldo);
                                    break;
                                case 2:
                                    depositar(&contaEncontrada);
                                    break;
                                case 3:
                                    sacar(&contaEncontrada);
                                    break;
                                case 4:
                                    realizarPix(&contaEncontrada);
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
                    printf("\nSenha incorreta! Tente novamente.\n");
                }
                break;
            }

            case 3: {
                printf("\nDigite seu CPF: ");
                char cpf[12];
                scanf(" %[^\n]", cpf);
                printf("Digite sua senha: ");
                char senha[15];
                scanf(" %[^\n]", senha);

                Conta contaEncontrada;
                if (autenticarUsuario(cpf, &contaEncontrada)) {
                    sacar(&contaEncontrada);
                } else {
                    printf("\nCredenciais inválidas! CPF ou senha incorretos.\n");
                }
                break;
            }

           case 4: {
                printf("\nDigite seu CPF: ");
                char cpf[12];
                scanf(" %[^\n]", cpf);
                while (getchar() != '\n'); 

                printf("Digite sua senha: ");
                char senha[15];
                scanf(" %[^\n]", senha);
                while (getchar() != '\n'); 

                Conta contaEncontrada;
                if (autenticarUsuario(cpf, &contaEncontrada)) {
                    printf("\nSaldo Atual: R$%.2f.\n", contaEncontrada.saldo);
                } else {
                    printf("\nCredenciais inválidas! CPF ou senha incorretos.\n");
                }
                break;
            }


            case 5: {
                printf("\nDigite seu CPF: ");
                char cpf[12];
                scanf(" %[^\n]", cpf);
                printf("Digite sua senha: ");
                char senha[15];
                scanf(" %[^\n]", senha);

                Conta contaEncontrada;
                if (autenticarUsuario(cpf, &contaEncontrada)) {
                    realizarPix(&contaEncontrada);
                } else {
                    printf("\nCredenciais inválidas! CPF ou senha incorretos.\n");
                }
                break;
            }

            case 6:
                printf("\nEncerrando...\n");
                break;
        }
    } while (opcao != 6);

    return 0;
}

