#include "usuario.h"

int id_usuario_atual = 0;
int id_grupo_atual = 0;

void definir_usuario(int uid, int gid) {
    id_usuario_atual = uid;
    id_grupo_atual = gid;
}

int checar_permissao(int permissao_necessaria, unsigned short permissoes_arquivo, int dono_arquivo, int grupo_arquivo) {
    // Usuário root sempre tem permissão
    if (id_usuario_atual == 0) return 1;

    unsigned short permissoes_relevantes = 0;

    if (id_usuario_atual == dono_arquivo) {
        // Desloca as permissões do dono para a posição 0 para comparação
        permissoes_relevantes = (permissoes_arquivo & 0700) >> 6;
    } else if (id_grupo_atual == grupo_arquivo) {
        // Desloca as permissões do grupo para a posição 0 para comparação
        permissoes_relevantes = (permissoes_arquivo & 0070) >> 3;
    } else {
        permissoes_relevantes = (permissoes_arquivo & 0007);
    }

    // permissao_necessaria deve ser passada como, por exemplo, 4 para leitura (0b100), 2 para escrita (0b010), 1 para execução (0b001)
    // Aqui verificamos se o bit de permissão necessário está definido
    
    // Exemplo: permissao_necessaria é 4 (leitura). permissoes_relevantes é 6 (rw-).
    // (6 & 4) == 4, então permissão concedida.
    return (permissoes_relevantes & permissao_necessaria) == permissao_necessaria;
}
