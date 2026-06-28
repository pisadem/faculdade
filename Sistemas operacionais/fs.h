#ifndef FS_H
#define FS_H

#include <time.h>

#define MAX_NOME 256

typedef enum {
    TIPO_ARQUIVO_TXT,
    TIPO_ARQUIVO_BIN
} TipoArquivo;

typedef struct {
    char nome[MAX_NOME];
    int tamanho;
    TipoArquivo tipo;
    time_t criado_em;
    time_t modificado_em;
    time_t acessado_em;
    int id; // inode
    unsigned short permissoes; // rwx rwx rwx (dono, grupo, outros)
    int id_dono;
    int id_grupo;
    int bloco_inicial; // Bloco inicial para os dados
} FCB;

typedef struct No {
    char nome[MAX_NOME];
    int eh_diretorio;
    FCB* fcb; // Apenas para arquivos
    struct No* pai;
    struct No* primeiro_filho;
    struct No* proximo_irmao;
} No;

void fs_iniciar();
void fs_mkdir(const char* nome);
void fs_cd(const char* caminho);
void fs_ls();
void fs_touch(const char* nome);
void fs_rm(const char* nome);
void fs_mv(const char* origem, const char* destino);
void fs_cp(const char* origem, const char* destino);
void fs_chmod(const char* nome, int modo);
void fs_echo(const char* nome, const char* conteudo);
void fs_cat(const char* nome);

#endif
