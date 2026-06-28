#include "No.hpp"

No* criarNo(string nome, TipoNo tipo, int inode, string dono, string grupo, int permissoes) {
    No* novo = new No();
    novo->fcb.nome = nome;
    novo->fcb.tamanho = 0;
    novo->fcb.tipo = tipo;
    novo->fcb.inode = inode;
    novo->fcb.dono = dono;
    novo->fcb.grupo = grupo;
    novo->fcb.permissoes = permissoes;
    novo->pai = nullptr;
    
    time_t agora = time(nullptr);
    novo->fcb.dataCriacao = agora;
    novo->fcb.dataModificacao = agora;
    novo->fcb.dataAcesso = agora;
    
    return novo;
}

void destruirNo(No* no) {
    if (no == nullptr) return;
    for (No* filho : no->filhos) {
        destruirNo(filho);
    }
    delete no;
}

void atualizarDataModificacao(No* no) { 
    no->fcb.dataModificacao = time(nullptr); 
}

void atualizarDataAcesso(No* no) { 
    no->fcb.dataAcesso = time(nullptr); 
}

void adicionarFilho(No* pai, No* filho) {
    if (pai->fcb.tipo == DIRETORIO) {
        pai->filhos.push_back(filho);
        filho->pai = pai;
        atualizarDataModificacao(pai);
    }
}

void removerFilho(No* pai, const string& nomeFilho) {
    if (pai->fcb.tipo == DIRETORIO) {
        auto it = pai->filhos.begin();
        while (it != pai->filhos.end()) {
            if ((*it)->fcb.nome == nomeFilho) {
                pai->filhos.erase(it);
                atualizarDataModificacao(pai);
                break;
            }
            ++it;
        }
    }
}

No* buscarFilho(No* pai, const string& nomeFilho) {
    if (pai->fcb.tipo == DIRETORIO) {
        for (No* filho : pai->filhos) {
            if (filho->fcb.nome == nomeFilho) {
                return filho;
            }
        }
    }
    return nullptr;
}

void adicionarBloco(No* no, int indiceBloco) {
    if (no->fcb.tipo == ARQUIVO) {
        no->blocos.push_back(indiceBloco);
        atualizarDataModificacao(no);
    }
}

void limparBlocos(No* no) {
    if (no->fcb.tipo == ARQUIVO) {
        no->blocos.clear();
        no->fcb.tamanho = 0;
        atualizarDataModificacao(no);
    }
}

string getPermissoesString(No* no) {
    string str = (no->fcb.tipo == DIRETORIO) ? "d" : "-";
    
    // Dono
    str += ((no->fcb.permissoes >> 6) & 4) ? "r" : "-";
    str += ((no->fcb.permissoes >> 6) & 2) ? "w" : "-";
    str += ((no->fcb.permissoes >> 6) & 1) ? "x" : "-";
    
    // Grupo
    str += ((no->fcb.permissoes >> 3) & 4) ? "r" : "-";
    str += ((no->fcb.permissoes >> 3) & 2) ? "w" : "-";
    str += ((no->fcb.permissoes >> 3) & 1) ? "x" : "-";
    
    // Outros
    str += (no->fcb.permissoes & 4) ? "r" : "-";
    str += (no->fcb.permissoes & 2) ? "w" : "-";
    str += (no->fcb.permissoes & 1) ? "x" : "-";
    
    return str;
}
