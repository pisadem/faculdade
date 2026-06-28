#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fs.h"
#include "disco.h"
#include "usuario.h"

No* raiz;
No* diretorio_atual;
int proximo_inode = 1;

No* criar_no(const char* nome, int eh_diretorio) {
    No* no = (No*)malloc(sizeof(No));
    if (!no) return NULL;
    strncpy(no->nome, nome, MAX_NOME);
    no->eh_diretorio = eh_diretorio;
    no->pai = NULL;
    no->primeiro_filho = NULL;
    no->proximo_irmao = NULL;

    if (!eh_diretorio) {
        no->fcb = (FCB*)malloc(sizeof(FCB));
        strncpy(no->fcb->nome, nome, MAX_NOME);
        no->fcb->tamanho = 0;
        no->fcb->tipo = TIPO_ARQUIVO_TXT;
        time(&no->fcb->criado_em);
        no->fcb->modificado_em = no->fcb->criado_em;
        no->fcb->acessado_em = no->fcb->criado_em;
        no->fcb->id = proximo_inode++;
        no->fcb->permissoes = 0644; // Padrão rw-r--r--
        no->fcb->id_dono = id_usuario_atual;
        no->fcb->id_grupo = id_grupo_atual;
        no->fcb->bloco_inicial = -1;
    } else {
        no->fcb = NULL;
    }
    return no;
}

void fs_iniciar() {
    raiz = criar_no("/", 1);
    diretorio_atual = raiz;
}

No* encontrar_filho(No* pai, const char* nome) {
    if (!pai || !pai->eh_diretorio) return NULL;
    No* atual = pai->primeiro_filho;
    while (atual) {
        if (strcmp(atual->nome, nome) == 0) return atual;
        atual = atual->proximo_irmao;
    }
    return NULL;
}

void adicionar_filho(No* pai, No* filho) {
    if (!pai || !filho) return;
    filho->pai = pai;
    if (!pai->primeiro_filho) {
        pai->primeiro_filho = filho;
    } else {
        No* atual = pai->primeiro_filho;
        while (atual->proximo_irmao) {
            atual = atual->proximo_irmao;
        }
        atual->proximo_irmao = filho;
    }
}

void remover_filho(No* pai, No* filho) {
    if (!pai || !filho) return;
    if (pai->primeiro_filho == filho) {
        pai->primeiro_filho = filho->proximo_irmao;
    } else {
        No* atual = pai->primeiro_filho;
        while (atual && atual->proximo_irmao != filho) {
            atual = atual->proximo_irmao;
        }
        if (atual) {
            atual->proximo_irmao = filho->proximo_irmao;
        }
    }
}

void fs_mkdir(const char* nome) {
    if (encontrar_filho(diretorio_atual, nome)) {
        printf("mkdir: não foi possível criar o diretório '%s': Arquivo existe\n", nome);
        return;
    }
    No* novo_dir = criar_no(nome, 1);
    adicionar_filho(diretorio_atual, novo_dir);
}

void fs_cd(const char* caminho) {
    if (strcmp(caminho, "..") == 0) {
        if (diretorio_atual->pai) {
            diretorio_atual = diretorio_atual->pai;
        }
    } else if (strcmp(caminho, "/") == 0) {
        diretorio_atual = raiz;
    } else {
        No* proximo_dir = encontrar_filho(diretorio_atual, caminho);
        if (proximo_dir && proximo_dir->eh_diretorio) {
            diretorio_atual = proximo_dir;
        } else {
            printf("cd: %s: Arquivo ou diretório inexistente\n", caminho);
        }
    }
}

void fs_ls() {
    No* atual = diretorio_atual->primeiro_filho;
    while (atual) {
        if (atual->eh_diretorio) {
            printf("\033[1;34m%s\033[0m\n", atual->nome); // Azul para diretório
        } else {
            printf("%s\n", atual->nome);
        }
        atual = atual->proximo_irmao;
    }
}

void fs_touch(const char* nome) {
    if (encontrar_filho(diretorio_atual, nome)) {
        // Arquivo existe, apenas atualizaria timestamp em um FS real, aqui apenas retornamos
        return;
    }
    No* novo_arquivo = criar_no(nome, 0);
    adicionar_filho(diretorio_atual, novo_arquivo);
}

void fs_rm(const char* nome) {
    No* no = encontrar_filho(diretorio_atual, nome);
    if (!no) {
        printf("rm: não foi possível remover '%s': Arquivo ou diretório inexistente\n", nome);
        return;
    }
    if (no->eh_diretorio) {
        printf("rm: não foi possível remover '%s': É um diretório\n", nome);
        return;
    }

    if (!checar_permissao(2, no->fcb->permissoes, no->fcb->id_dono, no->fcb->id_grupo)) {
        printf("rm: permissão negada\n");
        return;
    }

    remover_filho(diretorio_atual, no);
    if (no->fcb->bloco_inicial != -1) {
        int num_blocos = (no->fcb->tamanho + TAMANHO_BLOCO - 1) / TAMANHO_BLOCO;
        disco_liberar_blocos(no->fcb->bloco_inicial, num_blocos);
    }
    free(no->fcb);
    free(no);
}

void fs_mv(const char* origem, const char* destino) {
    No* no = encontrar_filho(diretorio_atual, origem);
    if (!no) {
        printf("mv: não foi possível obter estado de '%s': Arquivo ou diretório inexistente\n", origem);
        return;
    }
    
    // Simplificação: renomear apenas no diretório atual
    if (encontrar_filho(diretorio_atual, destino)) {
         printf("mv: o destino '%s' já existe\n", destino);
         return;
    }
    
    strncpy(no->nome, destino, MAX_NOME);
    if (!no->eh_diretorio && no->fcb) {
        strncpy(no->fcb->nome, destino, MAX_NOME);
    }
}

void fs_cp(const char* origem, const char* destino) {
    No* no = encontrar_filho(diretorio_atual, origem);
    if (!no) {
        printf("cp: não foi possível obter estado de '%s': Arquivo ou diretório inexistente\n", origem);
        return;
    }
    if (no->eh_diretorio) {
        printf("cp: -r não especificado; omitindo o diretório '%s'\n", origem);
        return;
    }

    if (!checar_permissao(4, no->fcb->permissoes, no->fcb->id_dono, no->fcb->id_grupo)) {
        printf("cp: permissão negada para a origem\n");
        return;
    }

    if (encontrar_filho(diretorio_atual, destino)) {
        printf("cp: o destino '%s' já existe\n", destino);
        return;
    }

    No* novo_arquivo = criar_no(destino, 0);
    novo_arquivo->fcb->tamanho = no->fcb->tamanho;
    
    if (no->fcb->tamanho > 0 && no->fcb->bloco_inicial != -1) {
        int num_blocos = (no->fcb->tamanho + TAMANHO_BLOCO - 1) / TAMANHO_BLOCO;
        int novo_inicio = -1;
        if (disco_alocar_blocos(num_blocos, &novo_inicio)) {
            novo_arquivo->fcb->bloco_inicial = novo_inicio;
            for(int i=0; i<num_blocos; i++) {
                char buf[TAMANHO_BLOCO];
                disco_ler(no->fcb->bloco_inicial + i, buf, TAMANHO_BLOCO);
                disco_escrever(novo_arquivo->fcb->bloco_inicial + i, buf, TAMANHO_BLOCO);
            }
        }
    }
    adicionar_filho(diretorio_atual, novo_arquivo);
}

void fs_chmod(const char* nome, int modo) {
    No* no = encontrar_filho(diretorio_atual, nome);
    if (!no || no->eh_diretorio) {
        printf("chmod: não foi possível acessar '%s': Arquivo inexistente\n", nome);
        return;
    }
    if (id_usuario_atual != 0 && id_usuario_atual != no->fcb->id_dono) {
         printf("chmod: alterando as permissões de '%s': Operação não permitida\n", nome);
         return;
    }
    no->fcb->permissoes = modo;
}

void fs_echo(const char* nome, const char* conteudo) {
    No* no = encontrar_filho(diretorio_atual, nome);
    if (!no) {
        fs_touch(nome);
        no = encontrar_filho(diretorio_atual, nome);
    } else if (no->eh_diretorio) {
        printf("echo: %s é um diretório\n", nome);
        return;
    }

    if (!checar_permissao(2, no->fcb->permissoes, no->fcb->id_dono, no->fcb->id_grupo)) {
        printf("echo: permissão negada\n");
        return;
    }

    // Libera blocos antigos se existirem
    if (no->fcb->bloco_inicial != -1) {
        int num_blocos = (no->fcb->tamanho + TAMANHO_BLOCO - 1) / TAMANHO_BLOCO;
        disco_liberar_blocos(no->fcb->bloco_inicial, num_blocos);
        no->fcb->bloco_inicial = -1;
        no->fcb->tamanho = 0;
    }

    int tamanho_conteudo = strlen(conteudo);
    int num_blocos_necessarios = (tamanho_conteudo + TAMANHO_BLOCO - 1) / TAMANHO_BLOCO;
    if (num_blocos_necessarios == 0) return;

    int bloco_inicial;
    if (disco_alocar_blocos(num_blocos_necessarios, &bloco_inicial)) {
        no->fcb->bloco_inicial = bloco_inicial;
        no->fcb->tamanho = tamanho_conteudo;
        
        int bytes_escritos = 0;
        for (int i = 0; i < num_blocos_necessarios; i++) {
            int para_escrever = tamanho_conteudo - bytes_escritos;
            if (para_escrever > TAMANHO_BLOCO) para_escrever = TAMANHO_BLOCO;
            disco_escrever(bloco_inicial + i, conteudo + bytes_escritos, para_escrever);
            bytes_escritos += para_escrever;
        }
        time(&no->fcb->modificado_em);
    } else {
        printf("echo: não há espaço disponível no dispositivo\n");
    }
}

void fs_cat(const char* nome) {
    No* no = encontrar_filho(diretorio_atual, nome);
    if (!no) {
        printf("cat: %s: Arquivo ou diretório inexistente\n", nome);
        return;
    }
    if (no->eh_diretorio) {
        printf("cat: %s: É um diretório\n", nome);
        return;
    }
    
    if (!checar_permissao(4, no->fcb->permissoes, no->fcb->id_dono, no->fcb->id_grupo)) {
        printf("cat: permissão negada\n");
        return;
    }

    if (no->fcb->tamanho == 0 || no->fcb->bloco_inicial == -1) {
        return; // Arquivo vazio
    }

    int num_blocos = (no->fcb->tamanho + TAMANHO_BLOCO - 1) / TAMANHO_BLOCO;
    int bytes_lidos = 0;
    char buffer[TAMANHO_BLOCO + 1];

    for (int i = 0; i < num_blocos; i++) {
        int para_ler = no->fcb->tamanho - bytes_lidos;
        if (para_ler > TAMANHO_BLOCO) para_ler = TAMANHO_BLOCO;
        
        memset(buffer, 0, sizeof(buffer));
        disco_ler(no->fcb->bloco_inicial + i, buffer, para_ler);
        printf("%s", buffer);
        bytes_lidos += para_ler;
    }
    printf("\n");
    time(&no->fcb->acessado_em);
}
