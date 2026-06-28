#include "Terminal.hpp"
#include <iostream>
#include <sstream>

using namespace std;

vector<string> quebrarComando(const string& entrada) {
    vector<string> args;
    string atual;
    bool dentroAspas = false;

    for (char c : entrada) {
        if (c == '"') {
            dentroAspas = !dentroAspas;
        } else if (c == ' ' && !dentroAspas) {
            if (!atual.empty()) {
                args.push_back(atual);
                atual.clear();
            }
        } else {
            atual += c;
        }
    }
    
    if (!atual.empty()) {
        args.push_back(atual);
    }
    
    return args;
}

void executarComando(const vector<string>& argumentos, SistemaArquivos& fs, bool& rodando) {
    if (argumentos.empty()) return;

    string cmd = argumentos[0];

    if (cmd == "exit") {
        rodando = false;
    } else if (cmd == "mkdir" && argumentos.size() == 2) {
        mkdirFS(fs, argumentos[1]);
    } else if (cmd == "cd" && argumentos.size() == 2) {
        cdFS(fs, argumentos[1]);
    } else if (cmd == "touch" && argumentos.size() == 2) {
        touchFS(fs, argumentos[1]);
    } else if (cmd == "echo" && argumentos.size() >= 4 && argumentos[2] == ">") {
        echoFS(fs, argumentos[1], argumentos[3]);
    } else if (cmd == "cat" && argumentos.size() == 2) {
        catFS(fs, argumentos[1]);
    } else if (cmd == "cp" && argumentos.size() == 3) {
        cpFS(fs, argumentos[1], argumentos[2]);
    } else if (cmd == "mv" && argumentos.size() == 3) {
        mvFS(fs, argumentos[1], argumentos[2]);
    } else if (cmd == "rm" && argumentos.size() == 2) {
        rmFS(fs, argumentos[1]);
    } else if (cmd == "chmod" && argumentos.size() == 3) {
        chmodFS(fs, argumentos[1], argumentos[2]);
    } else if (cmd == "ls") {
        lsFS(fs);
    } else if (cmd == "stat" && argumentos.size() == 2) {
        statFS(fs, argumentos[1]);
    } else if (cmd == "su" && argumentos.size() == 2) {
        suFS(fs, argumentos[1]);
    } else if (cmd == "useradd" && argumentos.size() == 2) {
        useraddFS(fs, argumentos[1]);
    } else if (cmd == "userdel" && argumentos.size() == 2) {
        userdelFS(fs, argumentos[1]);
    } else {
        cerr << "Comando não encontrado ou sintaxe inválida.\n";
    }
}

void iniciarTerminal() {
    SistemaArquivos fs = criarSistemaArquivos();
    bool rodando = true;
    string entrada;
    
    cout << "Mini-Sistema de Arquivos em Memória iniciado.\n";
    cout << "Digite 'exit' para sair.\n\n";

    while (rodando) {
        cout << fs.usuarioAtual.nome << "@ambiente:" << getCaminhoAtual(fs) << "$ ";
        if (!getline(cin, entrada)) {
            break; // EOF
        }
        
        vector<string> args = quebrarComando(entrada);
        executarComando(args, fs, rodando);
    }
    
    destruirSistemaArquivos(fs);
}