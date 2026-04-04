#include <iostream>
#include <windows.h>
#include <string>
#include "../Servidor/banco.h" // ATENÇÃO PARA ESSE CAMINHO

using namespace std;

int main() {
    // Tenta abrir o Pipe criado pelo Servidor
    // A conexão é aberta uma única vez fora do loop para permitir múltiplas operações
    HANDLE hPipe = CreateFile(
        PIPE_NAME,           // Nome definido no banco.h
        GENERIC_WRITE,       // Cliente envia requisições (escrita)
        0,
        NULL,
        OPEN_EXISTING,       // Só abre se o servidor já tiver criado o pipe
        0,
        NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        cout << "Erro: Nao foi possivel conectar ao servidor." << endl;
        cout << "Certifique-se de que o projeto SERVIDOR ja esta em execucao!" << endl;
        system("pause");
        return 1;
    }

    Requisicao req;
    int opcao;

    while (true) {
        cout << "\n--- GERENCIADOR DE BANCO DE DADOS ---" << endl;
        cout << "1 - INSERT" << endl;
        cout << "2 - DELETE" << endl;
        cout << "3 - SELECT" << endl;
        cout << "4 - UPDATE" << endl;
        cout << "5 - SAIR" << endl;
        cout << "Escolha uma opcao: ";

        if (!(cin >> opcao)) { // Validação simples de entrada numérica
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        req.op = (Operacao)opcao; // Converte para o enum

        // Verifica se o usuário quer encerrar
        if (req.op == SAIR || opcao == 5) {
            cout << "Encerrando cliente..." << endl;
            break;
        }

        // Captura o ID (necessário para todas as operações CRUD)
        cout << "Digite o ID do registro: ";
        cin >> req.dados.id;

        // Se for INSERT ou UPDATE, precisamos do nome
        if (req.op == INSERT || req.op == UPDATE) {
            cout << "Digite o Nome: ";
            cin.ignore(); // Limpa o buffer do 'cin >> id' para o 'getline' funcionar
            cin.getline(req.dados.nome, MAX_NOME);
        }
        else {
            // Limpa o campo nome para DELETE e SELECT
            memset(req.dados.nome, 0, MAX_NOME);
        }

        // Envia a struct preenchida via IPC (Pipe) 
        DWORD bytesWritten;
        bool result = WriteFile(
            hPipe,
            &req,
            sizeof(Requisicao),
            &bytesWritten,
            NULL);

        if (result) {
            cout << ">> Sucesso: Requisicao enviada ao servidor." << endl;
            cout << ">> Verifique o console do servidor para o resultado." << endl;
        }
        else {
            cout << ">> Erro fatal: A conexao com o servidor foi perdida." << endl;
            break;
        }
    }

    // Fecha a conexão antes de sair [cite: 86]
    CloseHandle(hPipe);
    return 0;
}