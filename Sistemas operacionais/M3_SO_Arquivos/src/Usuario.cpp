#include "Usuario.hpp"

Usuario criarUsuario(const string& nome) {
    Usuario u;
    u.nome = nome;
    u.grupo = nome; // Para simplificar, o grupo tem o mesmo nome do usuário
    return u;
}

bool verificarPermissao(const Usuario& usuario, No* no, int tipoAcessoBinario) {
    if (usuario.nome == "root") {
        return true;
    }

    int permissoesArquivo = no->fcb.permissoes;
    int mascaraBits = 0;

    if (usuario.nome == no->fcb.dono) {
        // Desloca os bits do dono para a posição base (unidades)
        mascaraBits = (permissoesArquivo >> 6);
    } else if (usuario.grupo == no->fcb.grupo) {
        // Desloca os bits do grupo para a posição base (unidades)
        mascaraBits = (permissoesArquivo >> 3);
    } else {
        // Os bits dos outros usuários já estão na posição base
        mascaraBits = permissoesArquivo;
    }

    // Isola apenas os 3 bits menos significativos (0b111)
    mascaraBits = mascaraBits & 0b111; 
    
    // Aplica o operador bit a bit AND para checar se o acesso solicitado existe nos bits extraídos
    return (mascaraBits & tipoAcessoBinario) != 0;
}