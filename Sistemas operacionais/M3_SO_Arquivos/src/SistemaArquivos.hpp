#ifndef SISTEMA_ARQUIVOS_HPP
#define SISTEMA_ARQUIVOS_HPP

#include "No.hpp"
#include "Disco.hpp"
#include "Usuario.hpp"
#include <string>
#include <vector>

using namespace std;

// Estrutura do Sistema de Arquivos
struct SistemaArquivos {
    No* raiz;
    No* diretorioAtual;
    Disco disco;
    
    Usuario usuarioAtual;
    vector<Usuario> usuariosRegistrados;
    int contadorInodes;
};

// Protótipos das funções do Sistema de Arquivos
SistemaArquivos criarSistemaArquivos();
void destruirSistemaArquivos(SistemaArquivos& fs);

// Métodos auxiliares
No* resolverCaminho(const SistemaArquivos& fs, const string& caminho, string& nomeBase);
int gerarInode(SistemaArquivos& fs);
string formatarTempo(time_t tempo);

// Operações do Sistema de Arquivos
void mkdirFS(SistemaArquivos& fs, const string& caminho);
void cdFS(SistemaArquivos& fs, const string& caminho);
void touchFS(SistemaArquivos& fs, const string& caminho);
void echoFS(SistemaArquivos& fs, const string& conteudo, const string& caminho);
void catFS(const SistemaArquivos& fs, const string& caminho);
void cpFS(SistemaArquivos& fs, const string& origem, const string& destino);
void mvFS(SistemaArquivos& fs, const string& origem, const string& destino);
void rmFS(SistemaArquivos& fs, const string& caminho);
void chmodFS(SistemaArquivos& fs, const string& permissoesOctais, const string& caminho);
void lsFS(const SistemaArquivos& fs);
void statFS(const SistemaArquivos& fs, const string& caminho);

// Gerenciamento de Usuário e ambiente
void suFS(SistemaArquivos& fs, const string& usuario);
void useraddFS(SistemaArquivos& fs, const string& usuario);
void userdelFS(SistemaArquivos& fs, const string& usuario);
string getCaminhoAtual(const SistemaArquivos& fs);

#endif // SISTEMA_ARQUIVOS_HPP