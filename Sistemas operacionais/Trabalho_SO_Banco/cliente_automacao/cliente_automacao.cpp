#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include "../Servidor/banco.h"

using namespace std;

// Função auxiliar para enviar a requisição e evitar repetição de código
void enviar(HANDLE hPipe, Requisicao& req, string descricao) {
    DWORD bytesWritten;
    if (WriteFile(hPipe, &req, sizeof(Requisicao), &bytesWritten, NULL)) {
        cout << "[TESTE] " << descricao << " (ID: " << req.dados.id << ") enviado." << endl;
    }
    // Pequena pausa opcional para você conseguir ver as threads no Servidor
    Sleep(200);
}

int main() {
    HANDLE hPipe = CreateFile(PIPE_NAME, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        cout << "Erro: Ligue o Servidor antes!" << endl;
        return 1;
    }

    Requisicao req;

    cout << "=== INICIANDO BATERIA DE TESTES CRUD AUTOMATIZADA ===" << endl;

    // 1. TESTE DE INSERT (C - Create)
    for (int i = 1; i <= 5; i++) {
        req.op = INSERT;
        req.dados.id = i;
        string n = "Usuario_Original_" + to_string(i);
        strcpy_s(req.dados.nome, n.c_str());
        enviar(hPipe, req, "INSERT");
    }

    // 2. TESTE DE SELECT (R - Read)
    // Vamos buscar o ID 3 que acabamos de criar
    req.op = SELECT;
    req.dados.id = 3;
    enviar(hPipe, req, "SELECT");

    // 3. TESTE DE UPDATE (U - Update)
    // Vamos mudar o nome do ID 2
    req.op = UPDATE;
    req.dados.id = 2;
    strcpy_s(req.dados.nome, "NOME_ATUALIZADO_VIA_TESTE");
    enviar(hPipe, req, "UPDATE");

    // 4. TESTE DE DELETE (D - Delete)
    // Vamos apagar o ID 1
    req.op = DELETE;
    req.dados.id = 1;
    enviar(hPipe, req, "DELETE");

    // 5. TESTE DE ERRO (ID Repetido)
    // Tentar inserir o ID 3 de novo (deve dar erro no console do servidor)
    req.op = INSERT;
    req.dados.id = 3;
    strcpy_s(req.dados.nome, "TENTATIVA_DUPLICADA");
    enviar(hPipe, req, "INSERT (DUPLICADO)");

    cout << "\n=== TESTES FINALIZADOS! VERIFIQUE O CONSOLE DO SERVIDOR E O BANCO.TXT ===" << endl;

    CloseHandle(hPipe);
    system("pause");
    return 0;
}