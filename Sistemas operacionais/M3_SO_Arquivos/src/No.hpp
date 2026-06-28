#ifndef NO_HPP
#define NO_HPP

#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

enum TipoNo {
    ARQUIVO,
    DIRETORIO
};

// Bloco de Controle de Arquivo (File Control Block)
struct FCB {
    string nome;
    int tamanho;
    TipoNo tipo;
    time_t dataCriacao;
    time_t dataModificacao;
    time_t dataAcesso;
    int inode;
    int permissoes; // ex: 0777 em octal
    string dono;
    string grupo;
};

// Estrutura Nó que atua como diretório ou arquivo
struct No {
    FCB fcb;
    No* pai;
    vector<No*> filhos; // Para diretórios
    vector<int> blocos; // Para arquivos (índices de blocos no disco)
};

// Protótipos de funções globais para manipulação de Nós
No* criarNo(string nome, TipoNo tipo, int inode, string dono, string grupo, int permissoes);
void destruirNo(No* no); // To handle deletion of tree recursively
void atualizarDataModificacao(No* no);
void atualizarDataAcesso(No* no);
void adicionarFilho(No* pai, No* filho);
void removerFilho(No* pai, const string& nomeFilho);
No* buscarFilho(No* pai, const string& nomeFilho);
void adicionarBloco(No* no, int indiceBloco);
void limparBlocos(No* no);
string getPermissoesString(No* no);

#endif // NO_HPP