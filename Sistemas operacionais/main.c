#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fs.h"
#include "disco.h"
#include "usuario.h"

int main() {
    char comando[512];
    
    disco_iniciar();
    fs_iniciar();
    definir_usuario(1000, 1000); // Usuário padrão (ex: estudante)

    printf("Simulador de Sistema de Arquivos (M3 SO)\n");
    printf("Comandos suportados: mkdir, cd, ls, touch, rm, mv, cp, chmod, echo, cat, exit\n");

    while (1) {
        printf("> ");
        if (fgets(comando, sizeof(comando), stdin) == NULL) break;
        
        comando[strcspn(comando, "\n")] = 0; // Remove a nova linha
        
        if (strlen(comando) == 0) continue;
        
        // Trata o echo separadamente porque pode ter aspas e redirecionamento
        if (strncmp(comando, "echo ", 5) == 0) {
            char* inicio_conteudo = strchr(comando, '"');
            if (inicio_conteudo) {
                inicio_conteudo++; // Pula aspas de abertura
                char* fim_conteudo = strchr(inicio_conteudo, '"');
                if (fim_conteudo) {
                    *fim_conteudo = '\0';
                    char* redirecionamento = strstr(fim_conteudo + 1, ">");
                    if (redirecionamento) {
                        char* nome_arquivo = redirecionamento + 1;
                        while (*nome_arquivo == ' ') nome_arquivo++; // Remove espaços iniciais
                        if (strlen(nome_arquivo) > 0) {
                            fs_echo(nome_arquivo, inicio_conteudo);
                        } else {
                            printf("Uso: echo \"conteudo\" > <arquivo>\n");
                        }
                    } else {
                        printf("%s\n", inicio_conteudo); // Apenas imprime no terminal
                    }
                    continue;
                }
            }
            // Alternativa simples baseada em espaços
            char* resto = comando + 5;
            char* redirecionamento = strstr(resto, ">");
            if (redirecionamento) {
                *redirecionamento = '\0';
                char* nome_arquivo = redirecionamento + 1;
                while (*nome_arquivo == ' ') nome_arquivo++; // Remove espaços iniciais
                if (strlen(nome_arquivo) > 0) {
                     // Remove espaços finais do conteúdo
                     int len = strlen(resto);
                     while(len > 0 && resto[len-1] == ' ') {
                         resto[len-1] = '\0';
                         len--;
                     }
                    fs_echo(nome_arquivo, resto);
                } else {
                    printf("Uso: echo conteudo > <arquivo>\n");
                }
            } else {
                printf("%s\n", resto);
            }
            continue;
        }

        // Tokeniza os comandos padrões
        char* token = strtok(comando, " ");
        if (token == NULL) continue;
        
        if (strcmp(token, "exit") == 0) {
            break;
        } else if (strcmp(token, "mkdir") == 0) {
            token = strtok(NULL, " ");
            if (token) fs_mkdir(token);
            else printf("Uso: mkdir <nome>\n");
        } else if (strcmp(token, "cd") == 0) {
            token = strtok(NULL, " ");
            if (token) fs_cd(token);
            else printf("Uso: cd <diretorio>\n");
        } else if (strcmp(token, "ls") == 0) {
            fs_ls();
        } else if (strcmp(token, "touch") == 0) {
            token = strtok(NULL, " ");
            if (token) fs_touch(token);
            else printf("Uso: touch <nome>\n");
        } else if (strcmp(token, "rm") == 0) {
            token = strtok(NULL, " ");
            if (token) fs_rm(token);
            else printf("Uso: rm <nome>\n");
        } else if (strcmp(token, "mv") == 0) {
            char* origem = strtok(NULL, " ");
            char* destino = strtok(NULL, " ");
            if (origem && destino) fs_mv(origem, destino);
            else printf("Uso: mv <origem> <destino>\n");
        } else if (strcmp(token, "cp") == 0) {
            char* origem = strtok(NULL, " ");
            char* destino = strtok(NULL, " ");
            if (origem && destino) fs_cp(origem, destino);
            else printf("Uso: cp <origem> <destino>\n");
        } else if (strcmp(token, "chmod") == 0) {
            char* modo_str = strtok(NULL, " ");
            char* nome = strtok(NULL, " ");
            if (modo_str && nome) {
                int modo;
                if (sscanf(modo_str, "%o", &modo) == 1) {
                    fs_chmod(nome, modo);
                } else {
                    printf("Modo octal invalido.\n");
                }
            } else {
                printf("Uso: chmod <modo octal> <nome>\n");
            }
        } else if (strcmp(token, "cat") == 0) {
            token = strtok(NULL, " ");
            if (token) fs_cat(token);
            else printf("Uso: cat <nome>\n");
        } else {
            printf("Comando desconhecido: %s\n", token);
        }
    }

    return 0;
}
