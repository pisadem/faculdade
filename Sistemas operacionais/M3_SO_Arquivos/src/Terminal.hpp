#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include "SistemaArquivos.hpp"
#include <string>
#include <vector>

using namespace std;

// Funções utilitárias para o Terminal
vector<string> quebrarComando(const string& entrada);
void executarComando(const vector<string>& argumentos, SistemaArquivos& fs, bool& rodando);
void iniciarTerminal();

#endif // TERMINAL_HPP