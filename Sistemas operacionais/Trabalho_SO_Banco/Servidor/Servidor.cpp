#include <iostream>
#include <windows.h>
#include <thread>
#include <semaphore>
#include <fstream>
#include <string>
#include <vector>
#include "banco.h"

using namespace std;

// Semáforo para controlar o acesso ao arquivo .txt
binary_semaphore semaforo_banco{ 1 };

// Função que cada THREAD vai executar
void processar_requisicao(Requisicao req) {
    // Tenta adquirir o semáforo
    semaforo_banco.acquire();

    cout << "[Thread " << this_thread::get_id() << "] Processando ID: " << req.dados.id << endl;

    // Lógica do Banco de Dados no arquivo .txt 
    switch (req.op){
        // O semáforo já deve ter sido adquirido (acquire) antes de entrar aqui
        case INSERT:{
            ifstream arquivoLeitura("banco.txt");
            string linha;
            bool idRepetido = false;

            // Verifica se o ID já existe no arquivo
            if (arquivoLeitura.is_open()) {
                while (getline(arquivoLeitura, linha)) {
                    size_t pos = linha.find(';'); // Pega apens o que vem antes do ';'
                    if (pos != string::npos) {
                        int idExistente = stoi(linha.substr(0, pos));
                        if (idExistente == req.dados.id) {
                            idRepetido = true;
                            break;
                        }
                    }
                }
                arquivoLeitura.close();
            }

            // Só insere se o ID for único
            if (!idRepetido) {
                ofstream arquivoEscrita("banco.txt", ios::app);
                if (arquivoEscrita.is_open()) {
                    arquivoEscrita << req.dados.id << ";" << req.dados.nome << endl;
                    arquivoEscrita.close();
                    cout << "[SUCESSO] ID " << req.dados.id << " inserido com exito." << endl;
                }
            }
            else {
                cout << "[ERRO] Tentativa de inserir ID " << req.dados.id << " ja existente." << endl;
            }
            break;
        }
        case SELECT: {
            ifstream arquivo("banco.txt");
            string linha;
            bool encontrado = false;

            cout << "[BUSCA] Procurando por ID: " << req.dados.id << "..." << endl;

            if (arquivo.is_open()) {
                while (getline(arquivo, linha)) {
                    size_t pos = linha.find(';');
                    if (pos != string::npos) {
                        int idExistente = stoi(linha.substr(0, pos));
                        string nomeExistente = linha.substr(pos + 1);

                        // Comparação por ID 
                        if (idExistente == req.dados.id) {
                            cout << "[ACHOU] ID: " << idExistente << " | Nome: " << nomeExistente << endl;
                            encontrado = true;
                            break;
                        }
                    }
                }
                arquivo.close();
            }

            if (!encontrado) {
                cout << "[AVISO] Registro com ID " << req.dados.id << " nao encontrado." << endl;
            }
            break;
        };
        case UPDATE: {
            // Le todo o conteúdo para a memória
            ifstream arquivoLeitura("banco.txt");
            vector<string> linhas;
            string linha;
            bool encontrado = false;

            if (arquivoLeitura.is_open()) {
                while (getline(arquivoLeitura, linha)) {
                    size_t pos = linha.find(';');
                    if (pos != string::npos) {
                        int idExistente = stoi(linha.substr(0, pos));

                        // Se for o ID que o cliente mandou, altera a linha
                        if (idExistente == req.dados.id) {
                            string novaLinha = to_string(req.dados.id) + ";" + req.dados.nome;
                            linhas.push_back(novaLinha);
                            encontrado = true;
                        }
                        else {
                            linhas.push_back(linha); // Mantém a linha original
                        }
                    }
                }
                arquivoLeitura.close();
            }

            // Se encontrar, sobrescreve o arquivo com o vetor atualizado
            if (encontrado) {
                ofstream arquivoEscrita("banco.txt", ios::trunc); // 'trunc' apaga o conteúdo anterior
                for (const string& l : linhas) {
                    arquivoEscrita << l << endl;
                }
                arquivoEscrita.close();
                cout << "[SUCESSO] Registro ID " << req.dados.id << " atualizado." << endl;
            }
            else {
                cout << "[ERRO] ID " << req.dados.id << " nao encontrado para update." << endl;
            }
            break;
        };
        case DELETE: {
            ifstream arquivoLeitura("banco.txt");
            vector<string> linhasParaManter;
            string linha;
            bool encontrado = false;

            if (arquivoLeitura.is_open()) {
                while (getline(arquivoLeitura, linha)) {
                    size_t pos = linha.find(';');
                    if (pos != string::npos) {
                        int idExistente = stoi(linha.substr(0, pos));

                        // Se o ID for diferente do solicitado, guarda a linha
                        if (idExistente != req.dados.id) {
                            linhasParaManter.push_back(linha);
                        }
                        else {
                            encontrado = true; // Encontrado o ID que deve ser deletado
                        }
                    }
                }
                arquivoLeitura.close();
            }

            // Se o registro foi encontrado, sobreve o arquivo sem ele
            if (encontrado) {
                ofstream arquivoEscrita("banco.txt", ios::trunc); // 'ios::trunc' limpa o arquivo
                for (const string& l : linhasParaManter) {
                    arquivoEscrita << l << endl;
                }
                arquivoEscrita.close();
                cout << "[SUCESSO] Registro ID " << req.dados.id << " removido com exito." << endl;
            }
            else {
                cout << "[ERRO] ID " << req.dados.id << " nao encontrado para remocao." << endl;
            }

            break;
        };
        case SAIR: {
            cout << "Encerrando programa...";
            break;
        };
        default:{
            cout << "Erro ao processar consulta. Tente novamente.";
        }
    }

    // Libera o semáforo
    semaforo_banco.release();
}

int main() {
    cout << "--- SERVIDOR DE BANCO DE DADOS INICIADO ---" << endl;

    // Cria o Pipe Nominal (IPC)
    HANDLE hPipe = CreateNamedPipe(
        PIPE_NAME,
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        sizeof(Requisicao),
        sizeof(Requisicao),
        0,
        NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        cout << "Erro ao criar Pipe!" << endl;
        return 1;
    }

    while (true) {
        cout << "Aguardando conexao do cliente..." << endl;

        // Espera o Cliente conectar
        if (ConnectNamedPipe(hPipe, NULL) || GetLastError() == ERROR_PIPE_CONNECTED) {
            cout << "[SISTEMA] Cliente conectado!" << endl;

            Requisicao req;
            DWORD bytesRead;

            // Enquanto houver dados vindo deste cliente, continue lendo
            // Isso impede que o servidor execute o Disconnect antes da hora
            while (ReadFile(hPipe, &req, sizeof(Requisicao), &bytesRead, NULL) && bytesRead > 0) {

                //Cria a THREAD para processar em paralelo [cite: 34, 44, 87]
                thread t(processar_requisicao, req);
                t.detach();

                cout << "[LOG] Requisicao recebida e enviada para Thread." << endl;
            }
        }

        // Só chega aqui quando o cliente fecha a janela ou escolhe SAIR
        cout << "[SISTEMA] Cliente desconectado. Limpando Pipe..." << endl;
        DisconnectNamedPipe(hPipe);
    }

    CloseHandle(hPipe);
    return 0;
}