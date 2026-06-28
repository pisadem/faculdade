#include "SistemaArquivos.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

SistemaArquivos criarSistemaArquivos() {
    SistemaArquivos fs;
    Usuario root = criarUsuario("root");
    fs.usuariosRegistrados.push_back(root);
    fs.usuarioAtual = root;
    fs.contadorInodes = 1;
    fs.disco = criarDisco();
    
    fs.raiz = criarNo("/", DIRETORIO, gerarInode(fs), "root", "root", 0755);
    fs.diretorioAtual = fs.raiz;
    
    return fs;
}

void destruirSistemaArquivos(SistemaArquivos& fs) {
    destruirNo(fs.raiz);
    fs.raiz = nullptr;
    fs.diretorioAtual = nullptr;
}

int gerarInode(SistemaArquivos& fs) {
    return fs.contadorInodes++;
}

No* resolverCaminho(const SistemaArquivos& fs, const string& caminho, string& nomeBase) {
    if (caminho.empty()) return nullptr;

    No* atual = (caminho[0] == '/') ? fs.raiz : fs.diretorioAtual;
    stringstream ss(caminho);
    string token;
    vector<string> partes;

    while (getline(ss, token, '/')) {
        if (!token.empty()) {
            partes.push_back(token);
        }
    }

    if (partes.empty()) {
        nomeBase = "/";
        return fs.raiz;
    }

    nomeBase = partes.back();
    for (size_t i = 0; i < partes.size() - 1; ++i) {
        if (partes[i] == ".") {
            continue;
        } else if (partes[i] == "..") {
            if (atual->pai) atual = atual->pai;
        } else {
            atual = buscarFilho(atual, partes[i]);
            if (!atual || atual->fcb.tipo != DIRETORIO) {
                return nullptr; // Caminho inválido
            }
            // Verifica permissão de execução (acesso) no diretório ao atravessar
            if (!verificarPermissao(fs.usuarioAtual, atual, ACESSO_EXECUCAO)) {
                cerr << "cd: Permissao negada para atravessar '" << partes[i] << "'\n";
                return nullptr;
            }
        }
    }

    return atual; // Retorna o diretório pai do último elemento
}

string getCaminhoAtual(const SistemaArquivos& fs) {
    string caminho = "";
    No* atual = fs.diretorioAtual;
    while (atual != nullptr && atual->fcb.nome != "/") {
        caminho = "/" + atual->fcb.nome + caminho;
        atual = atual->pai;
    }
    return caminho.empty() ? "/" : caminho;
}

void mkdirFS(SistemaArquivos& fs, const string& caminho) {
    string nomeBase;
    No* dirPai = resolverCaminho(fs, caminho, nomeBase);

    if (!dirPai) {
        cerr << "mkdir: Não foi possivel criar o diretório '" << caminho << "': Arquivo ou diretorio inexistente\n";
        return;
    }

    if (buscarFilho(dirPai, nomeBase)) {
        cerr << "mkdir: Não foi possivel criar o diretório '" << caminho << "': O arquivo já existe\n";
        return;
    }

    // Verifica permissão de escrita no diretório pai (2 = W)
    if (!verificarPermissao(fs.usuarioAtual, dirPai, ACESSO_ESCRITA)) {
        cerr << "mkdir: Permissão negada\n";
        return;
    }

    No* novoDir = criarNo(nomeBase, DIRETORIO, gerarInode(fs), fs.usuarioAtual.nome, fs.usuarioAtual.grupo, 0755);
    adicionarFilho(dirPai, novoDir);
}

void cdFS(SistemaArquivos& fs, const string& caminho) {
    if (caminho == "/") {
        fs.diretorioAtual = fs.raiz;
        return;
    } else if (caminho == "..") {
        if (fs.diretorioAtual->pai) {
             fs.diretorioAtual = fs.diretorioAtual->pai;
        }
        return;
    } else if (caminho == ".") {
        return;
    }

    string nomeBase;
    No* dirPai = resolverCaminho(fs, caminho, nomeBase);
    
    if (!dirPai) {
        cerr << "cd: " << caminho << ": Arquivo ou diretório inexistente\n";
        return;
    }

    No* alvo = (nomeBase == "/") ? fs.raiz : buscarFilho(dirPai, nomeBase);
    
    if (!alvo) {
        cerr << "cd: " << caminho << ": Arquivo ou diretório inexistente\n";
        return;
    }

    if (alvo->fcb.tipo != DIRETORIO) {
        cerr << "cd: " << caminho << ": Não é um diretório\n";
        return;
    }

    // Permissão de execução (1 = X) para entrar no diretório
    if (!verificarPermissao(fs.usuarioAtual, alvo, ACESSO_EXECUCAO)) {
        cerr << "cd: " << caminho << ": Permissão negada\n";
        return;
    }

    fs.diretorioAtual = alvo;
}

void touchFS(SistemaArquivos& fs, const string& caminho) {
    string nomeBase;
    No* dirPai = resolverCaminho(fs, caminho, nomeBase);

    if (!dirPai) {
        cerr << "touch: não foi possivel criar '" << caminho << "': Arquivo ou diretorio inexistente\n";
        return;
    }

    No* existente = buscarFilho(dirPai, nomeBase);
    if (existente) {
        atualizarDataModificacao(existente);
        atualizarDataAcesso(existente);
        return;
    }

    // Permissão de escrita (2 = W) no pai para criar arquivo
    if (!verificarPermissao(fs.usuarioAtual, dirPai, ACESSO_ESCRITA)) {
        cerr << "touch: Permissão negada\n";
        return;
    }

    No* novoArquivo = criarNo(nomeBase, ARQUIVO, gerarInode(fs), fs.usuarioAtual.nome, fs.usuarioAtual.grupo, 0644);
    adicionarFilho(dirPai, novoArquivo);
}

void echoFS(SistemaArquivos& fs, const string& conteudo, const string& caminho) {
    string nomeBase;
    No* dirPai = resolverCaminho(fs, caminho, nomeBase);

    if (!dirPai) {
        cerr << "bash: " << caminho << ": Arquivo ou diretorio inexistente\n";
        return;
    }

    No* alvo = buscarFilho(dirPai, nomeBase);
    if (!alvo) {
        // Arquivo não existe, cria (como echo "texto" > arquivo)
        if (!verificarPermissao(fs.usuarioAtual, dirPai, ACESSO_ESCRITA)) {
            cerr << "bash: " << caminho << ": Permissão negada\n";
            return;
        }
        alvo = criarNo(nomeBase, ARQUIVO, gerarInode(fs), fs.usuarioAtual.nome, fs.usuarioAtual.grupo, 0644);
        adicionarFilho(dirPai, alvo);
    } else {
        if (alvo->fcb.tipo != ARQUIVO) {
            cerr << "bash: " << caminho << ": É um diretório\n";
            return;
        }
    }

    // Permissão de escrita no arquivo (2 = W)
    if (!verificarPermissao(fs.usuarioAtual, alvo, ACESSO_ESCRITA)) {
        cerr << "bash: " << caminho << ": Permissão negada\n";
        return;
    }

    // Libera blocos antigos
    liberarBlocos(fs.disco, alvo->blocos);
    limparBlocos(alvo);

    // Aloca novos blocos
    vector<int> blocosAlocados = alocarBlocos(fs.disco, conteudo);
    if (blocosAlocados.empty() && !conteudo.empty()) {
        cerr << "bash: " << caminho << ": Sem espaço no disco simulado\n";
        return;
    }

    for (int bloco : blocosAlocados) {
        adicionarBloco(alvo, bloco);
    }
    
    alvo->fcb.tamanho = conteudo.length();
}

void catFS(const SistemaArquivos& fs, const string& caminho) {
    string nomeBase;
    No* dirPai = resolverCaminho(fs, caminho, nomeBase);

    if (!dirPai) {
        cerr << "cat: " << caminho << ": Arquivo ou diretorio inexistente\n";
        return;
    }

    No* alvo = buscarFilho(dirPai, nomeBase);
    if (!alvo) {
        cerr << "cat: " << caminho << ": Arquivo ou diretorio inexistente\n";
        return;
    }

    if (alvo->fcb.tipo != ARQUIVO) {
        cerr << "cat: " << caminho << ": É um diretório\n";
        return;
    }

    // Permissão de leitura (4 = R) no arquivo
    if (!verificarPermissao(fs.usuarioAtual, alvo, ACESSO_LEITURA)) {
        cerr << "cat: " << caminho << ": Permissão negada\n";
        return;
    }

    atualizarDataAcesso(alvo);
    string conteudo = lerDeBlocos(fs.disco, alvo->blocos);
    
    // Como simulamos echo > arquivo, o conteúdo pode não ter \n no final,
    // mas vamos exibir diretamente.
    cout << conteudo;
    if (!conteudo.empty() && conteudo.back() != '\n') {
        cout << '\n';
    }
}

void rmFS(SistemaArquivos& fs, const string& caminho) {
    string nomeBase;
    No* dirPai = resolverCaminho(fs, caminho, nomeBase);

    if (!dirPai) {
        cerr << "rm: não foi possível remover '" << caminho << "': Arquivo ou diretorio inexistente\n";
        return;
    }

    No* alvo = buscarFilho(dirPai, nomeBase);
    if (!alvo) {
        cerr << "rm: não foi possível remover '" << caminho << "': Arquivo ou diretorio inexistente\n";
        return;
    }

    // Permissão de escrita (2 = W) no DIRETÓRIO PAI para remover um arquivo/dir
    if (!verificarPermissao(fs.usuarioAtual, dirPai, ACESSO_ESCRITA)) {
        cerr << "rm: não foi possível remover '" << caminho << "': Permissão negada\n";
        return;
    }

    if (alvo->fcb.tipo == DIRETORIO && !alvo->filhos.empty()) {
        cerr << "rm: não foi possível remover '" << caminho << "': É um diretório não vazio\n";
        return;
    }

    if (alvo->fcb.tipo == ARQUIVO) {
        liberarBlocos(fs.disco, alvo->blocos);
    }

    removerFilho(dirPai, nomeBase);
    destruirNo(alvo);
}

void cpFS(SistemaArquivos& fs, const string& origem, const string& destino) {
    string nomeBaseOrigem, nomeBaseDestino;
    No* dirPaiOrigem = resolverCaminho(fs, origem, nomeBaseOrigem);
    No* dirPaiDestino = resolverCaminho(fs, destino, nomeBaseDestino);

    if (!dirPaiOrigem || !dirPaiDestino) {
        cerr << "cp: Arquivo ou diretorio inexistente\n";
        return;
    }

    No* alvoOrigem = buscarFilho(dirPaiOrigem, nomeBaseOrigem);
    if (!alvoOrigem) {
        cerr << "cp: não foi possível obter estado de '" << origem << "': Arquivo ou diretorio inexistente\n";
        return;
    }

    // Permissão de leitura (4 = R) na origem
    if (!verificarPermissao(fs.usuarioAtual, alvoOrigem, ACESSO_LEITURA)) {
        cerr << "cp: não foi possível abrir '" << origem << "' para leitura: Permissão negada\n";
        return;
    }

    // Permissão de escrita (2 = W) no diretório destino
    if (!verificarPermissao(fs.usuarioAtual, dirPaiDestino, ACESSO_ESCRITA)) {
        cerr << "cp: Permissão negada\n";
        return;
    }

    if (alvoOrigem->fcb.tipo == DIRETORIO) {
        cerr << "cp: omitindo diretório '" << origem << "' (nao suportado recursivo neste simulador)\n";
        return;
    }

    string conteudo = lerDeBlocos(fs.disco, alvoOrigem->blocos);
    
    // Se o destino apontar para um diretório, copia para dentro dele com o mesmo nome
    No* alvoDest = buscarFilho(dirPaiDestino, nomeBaseDestino);
    if (alvoDest && alvoDest->fcb.tipo == DIRETORIO) {
        dirPaiDestino = alvoDest;
        nomeBaseDestino = nomeBaseOrigem;
        alvoDest = buscarFilho(dirPaiDestino, nomeBaseDestino);
    }

    if (alvoDest) {
        // Se já existe e é arquivo, sobrescreve
        if (alvoDest->fcb.tipo == DIRETORIO) {
            cerr << "cp: destino é um diretório\n";
            return;
        }
        if (!verificarPermissao(fs.usuarioAtual, alvoDest, ACESSO_ESCRITA)) {
            cerr << "cp: Permissão negada no destino\n";
            return;
        }
        liberarBlocos(fs.disco, alvoDest->blocos);
        limparBlocos(alvoDest);
    } else {
        // Cria novo arquivo
        alvoDest = criarNo(nomeBaseDestino, ARQUIVO, gerarInode(fs), fs.usuarioAtual.nome, fs.usuarioAtual.grupo, alvoOrigem->fcb.permissoes);
        adicionarFilho(dirPaiDestino, alvoDest);
    }

    vector<int> blocosAlocados = alocarBlocos(fs.disco, conteudo);
    for (int bloco : blocosAlocados) {
        adicionarBloco(alvoDest, bloco);
    }
    alvoDest->fcb.tamanho = conteudo.length();
}

void mvFS(SistemaArquivos& fs, const string& origem, const string& destino) {
    string nomeBaseOrigem, nomeBaseDestino;
    No* dirPaiOrigem = resolverCaminho(fs, origem, nomeBaseOrigem);
    No* dirPaiDestino = resolverCaminho(fs, destino, nomeBaseDestino);

    if (!dirPaiOrigem || !dirPaiDestino) {
        cerr << "mv: Arquivo ou diretorio inexistente\n";
        return;
    }

    No* alvoOrigem = buscarFilho(dirPaiOrigem, nomeBaseOrigem);
    if (!alvoOrigem) {
        cerr << "mv: não foi possível obter estado de '" << origem << "': Arquivo ou diretorio inexistente\n";
        return;
    }

    // Permissão escrita no pai origem para remover, e pai destino para adicionar
    if (!verificarPermissao(fs.usuarioAtual, dirPaiOrigem, ACESSO_ESCRITA) || 
        !verificarPermissao(fs.usuarioAtual, dirPaiDestino, ACESSO_ESCRITA)) {
        cerr << "mv: Permissão negada\n";
        return;
    }

    No* alvoDest = buscarFilho(dirPaiDestino, nomeBaseDestino);
    if (alvoOrigem == alvoDest) return; // Evita edge-case UAF
    if (alvoDest && alvoDest->fcb.tipo == DIRETORIO) {
        // Move para dentro do diretório destino
        dirPaiDestino = alvoDest;
        nomeBaseDestino = nomeBaseOrigem;
        alvoDest = buscarFilho(dirPaiDestino, nomeBaseDestino);
    }
    
    if (alvoDest) {
        // Se destino existe, temos que apagar antes (se for arquivo)
        if (alvoDest->fcb.tipo == DIRETORIO) {
             cerr << "mv: destino é um diretório não vazio\n";
             return;
        }
        liberarBlocos(fs.disco, alvoDest->blocos);
        removerFilho(dirPaiDestino, nomeBaseDestino);
        destruirNo(alvoDest);
    }

    // Move (apenas muda referências)
    removerFilho(dirPaiOrigem, nomeBaseOrigem);
    alvoOrigem->fcb.nome = nomeBaseDestino;
    adicionarFilho(dirPaiDestino, alvoOrigem);
}

void chmodFS(SistemaArquivos& fs, const string& permissoesOctais, const string& caminho) {
    string nomeBase;
    No* dirPai = resolverCaminho(fs, caminho, nomeBase);

    if (!dirPai) {
        cerr << "chmod: não foi possível acessar '" << caminho << "': Arquivo ou diretorio inexistente\n";
        return;
    }

    No* alvo = (nomeBase == "/") ? fs.raiz : buscarFilho(dirPai, nomeBase);
    if (!alvo) {
        cerr << "chmod: não foi possível acessar '" << caminho << "': Arquivo ou diretorio inexistente\n";
        return;
    }

    // Apenas dono ou root pode mudar permissões
    if (fs.usuarioAtual.nome != "root" && fs.usuarioAtual.nome != alvo->fcb.dono) {
        cerr << "chmod: mudando permissões de '" << caminho << "': Operação não permitida\n";
        return;
    }

    int perm;
    try {
        perm = stoi(permissoesOctais, nullptr, 8);
    } catch (...) {
        cerr << "chmod: modo inválido: '" << permissoesOctais << "'\n";
        return;
    }
    
    alvo->fcb.permissoes = perm;
}

void lsFS(const SistemaArquivos& fs) {
    // Verifica leitura (4 = R) no diretório atual
    if (!verificarPermissao(fs.usuarioAtual, fs.diretorioAtual, ACESSO_LEITURA)) {
        cerr << "ls: não foi possível abrir o diretório '.': Permissão negada\n";
        return;
    }

    for (const auto& filho : fs.diretorioAtual->filhos) {
        cout << getPermissoesString(filho) << " " 
                  << setw(4) << filho->fcb.dono << " " 
                  << setw(4) << filho->fcb.grupo << " " 
                  << setw(6) << filho->fcb.tamanho << " " 
                  << filho->fcb.nome << "\n";
    }
}

string formatarTempo(time_t tempo) {
    char buffer[26];
    #ifdef _WIN32
    ctime_s(buffer, sizeof(buffer), &tempo);
    #else
    ctime_r(&tempo, buffer);
    #endif
    string str(buffer);
    if (!str.empty() && str.back() == '\n') {
        str.pop_back();
    }
    return str;
}

void statFS(const SistemaArquivos& fs, const string& caminho) {
    string nomeBase;
    No* dirPai = resolverCaminho(fs, caminho, nomeBase);

    if (!dirPai) {
        cerr << "stat: não foi possível obter estado de '" << caminho << "': Arquivo ou diretorio inexistente\n";
        return;
    }

    No* alvo = (nomeBase == "/") ? fs.raiz : buscarFilho(dirPai, nomeBase);
    if (!alvo) {
        cerr << "stat: não foi possível obter estado de '" << caminho << "': Arquivo ou diretorio inexistente\n";
        return;
    }

    cout << "  Arquivo: " << alvo->fcb.nome << "\n";
    cout << "  Tamanho: " << alvo->fcb.tamanho << "\tBlocos: " << alvo->blocos.size() << "\n";
    cout << "  Inode: " << alvo->fcb.inode << "\n";
    cout << "  Acesso: (" << oct << alvo->fcb.permissoes << dec << "/" << getPermissoesString(alvo) << ")  ";
    cout << "Uid: ( " << alvo->fcb.dono << ")   Gid: ( " << alvo->fcb.grupo << ")\n";
    cout << "  Acesso: " << formatarTempo(alvo->fcb.dataAcesso) << "\n";
    cout << "  Modificação: " << formatarTempo(alvo->fcb.dataModificacao) << "\n";
    cout << "  Criação: " << formatarTempo(alvo->fcb.dataCriacao) << "\n";
}

void suFS(SistemaArquivos& fs, const string& usuario) {
    for (const Usuario& u : fs.usuariosRegistrados) {
        if (u.nome == usuario) {
            fs.usuarioAtual = u;
            return;
        }
    }
    cerr << "su: usuário '" << usuario << "' não existe\n";
}

void useraddFS(SistemaArquivos& fs, const string& usuario) {
    if (fs.usuarioAtual.nome != "root") {
        cerr << "useradd: permissão negada (apenas root)\n";
        return;
    }
    
    for (const Usuario& u : fs.usuariosRegistrados) {
        if (u.nome == usuario) {
            cerr << "useradd: usuário '" << usuario << "' já existe\n";
            return;
        }
    }
    
    fs.usuariosRegistrados.push_back(criarUsuario(usuario));
}

void userdelFS(SistemaArquivos& fs, const string& usuario) {
    if (fs.usuarioAtual.nome != "root") {
        cerr << "userdel: permissão negada (apenas root)\n";
        return;
    }
    if (usuario == "root") {
        cerr << "userdel: não é possível remover o usuário root\n";
        return;
    }
    
    auto it = fs.usuariosRegistrados.begin();
    while (it != fs.usuariosRegistrados.end()) {
        if (it->nome == usuario) {
            fs.usuariosRegistrados.erase(it);
            
            // Se deletou o usuário atual do sistema, retorna para o root como precaução
            if (fs.usuarioAtual.nome == usuario) {
                suFS(fs, "root");
            }
            return;
        }
        ++it;
    }
    
    cerr << "userdel: usuário '" << usuario << "' não encontrado\n";
}