#ifndef BANCO_H
#define BANCO_H

#include <windows.h> // Necessário para as funções de Pipe no Windows

// Configurações do Pipe e limites
#define MAX_NOME 50
#define PIPE_NAME L"\\\\.\\pipe\\BancoDadosPipe" 

#undef DELETE

// 1. Operações suportadas
enum Operacao {
    INSERT = 1,
    DELETE,
    SELECT,
    UPDATE,
    SAIR
};

// 2. Estrutura do Registro
typedef struct {
    int id;
    char nome[MAX_NOME];
} Registro;

// 3. Estrutura da Requisicao para enviar pelo IPC
typedef struct {
    Operacao op;
    Registro dados;
} Requisicao;

#endif