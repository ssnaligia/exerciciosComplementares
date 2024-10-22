#ifndef FUNCOES_H
#define FUNCOES_H

void cadastroConta();
void depositar(Conta *conta);
void sacar(Conta *conta);
void realizarPix(Conta *conta);
void gerarRelatorio();
void criarContaGerente();
void criarContaDemo();
int autenticarUsuario(char *cpf, Conta *contaEncontrada);

#endif 
