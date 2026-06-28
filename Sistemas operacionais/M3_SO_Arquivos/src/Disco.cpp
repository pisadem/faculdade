#include "Disco.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

Disco criarDisco() {
    Disco d;
    d.dados.resize(TAMANHO_BLOCO * NUM_BLOCOS, 0);
    d.blocosLivres.resize(NUM_BLOCOS, true); // Todos os blocos iniciam livres
    return d;
}

vector<int> alocarBlocos(Disco& disco, const string& conteudo) {
    int blocosNecessarios = ceil(static_cast<double>(conteudo.length()) / TAMANHO_BLOCO);
    
    // Contar blocos livres
    int contLivres = 0;
    for (bool livre : disco.blocosLivres) {
        if (livre) contLivres++;
    }
    
    // Se não ha espaco suficiente
    if (contLivres < blocosNecessarios) {
        return {};
    }
    
    vector<int> blocosAlocados;
    int alocados = 0;
    for (int i = 0; i < NUM_BLOCOS && alocados < blocosNecessarios; ++i) {
        if (disco.blocosLivres[i]) {
            disco.blocosLivres[i] = false;
            blocosAlocados.push_back(i);
            alocados++;
        }
    }
    
    escreverEmBlocos(disco, blocosAlocados, conteudo);
    return blocosAlocados;
}

void liberarBlocos(Disco& disco, const vector<int>& blocos) {
    for (int bloco : blocos) {
        if (bloco >= 0 && bloco < NUM_BLOCOS) {
            disco.blocosLivres[bloco] = true;
            // Opcional: limpar os dados para 0
            fill(disco.dados.begin() + bloco * TAMANHO_BLOCO, 
                 disco.dados.begin() + (bloco + 1) * TAMANHO_BLOCO, 0);
        }
    }
}

void escreverEmBlocos(Disco& disco, const vector<int>& blocos, const string& conteudo) {
    size_t tamanhoConteudo = conteudo.length();
    size_t bytesEscritos = 0;
    
    for (size_t i = 0; i < blocos.size() && bytesEscritos < tamanhoConteudo; ++i) {
        int indiceBloco = blocos[i];
        size_t bytesParaEscrever = min(static_cast<size_t>(TAMANHO_BLOCO), tamanhoConteudo - bytesEscritos);
        
        copy(conteudo.begin() + bytesEscritos, 
             conteudo.begin() + bytesEscritos + bytesParaEscrever, 
             disco.dados.begin() + (indiceBloco * TAMANHO_BLOCO));
                  
        bytesEscritos += bytesParaEscrever;
    }
}

string lerDeBlocos(const Disco& disco, const vector<int>& blocos) {
    string resultado;
    
    for (int indiceBloco : blocos) {
        // Encontra o fim da string dentro do bloco (pode conter zeros no final)
        const char* inicioBloco = disco.dados.data() + (indiceBloco * TAMANHO_BLOCO);
        const char* fimBloco = inicioBloco + TAMANHO_BLOCO;
        
        // Vamos ler tudo que é diferente de 0.
        for (const char* p = inicioBloco; p < fimBloco && *p != '\0'; ++p) {
            resultado += *p;
        }
    }
    
    return resultado;
}

int espacoLivre(const Disco& disco) {
    int contLivres = 0;
    for (bool livre : disco.blocosLivres) {
        if (livre) contLivres++;
    }
    return contLivres * TAMANHO_BLOCO;
}
