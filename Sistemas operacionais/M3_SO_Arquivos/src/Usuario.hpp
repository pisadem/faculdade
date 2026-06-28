#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>
#include "No.hpp"

using namespace std;

// Permissões utilizando representação binária explícita
// 0b100 = Ler, 0b010 = Escrever, 0b001 = Executar
const int ACESSO_LEITURA = 0b100;
const int ACESSO_ESCRITA = 0b010;
const int ACESSO_EXECUCAO = 0b001;

// Estrutura para representar o usuário atual no sistema
struct Usuario {
    string nome;
    string grupo;
};

// Cria um usuário padrão
Usuario criarUsuario(const string& nome);

// Simplifica a verificação de permissões do sistema comparando os bits do arquivo com os do usuário
bool verificarPermissao(const Usuario& usuario, No* no, int tipoAcessoBinario);

#endif // USUARIO_HPP