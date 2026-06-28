#ifndef DISCO_HPP
#define DISCO_HPP

#include <vector>
#include <string>

using namespace std;

const int TAMANHO_BLOCO = 64; // Tamanho de cada bloco em bytes
const int NUM_BLOCOS = 1024;  // Numero total de blocos (total = 64KB)

// Estrutura que simula o disco
struct Disco {
    vector<char> dados;             // Memoria contigua simulando o disco
    vector<bool> blocosLivres;      // Mapa de bits para gerenciar blocos livres
};

// Protótipos das funções do disco
Disco criarDisco();
vector<int> alocarBlocos(Disco& disco, const string& conteudo);
void liberarBlocos(Disco& disco, const vector<int>& blocos);
void escreverEmBlocos(Disco& disco, const vector<int>& blocos, const string& conteudo);
string lerDeBlocos(const Disco& disco, const vector<int>& blocos);
int espacoLivre(const Disco& disco);

#endif // DISCO_HPP
