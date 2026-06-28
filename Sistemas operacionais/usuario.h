#ifndef USUARIO_H
#define USUARIO_H

#define DONO_R 0400
#define DONO_W 0200
#define DONO_X 0100
#define GRUPO_R 0040
#define GRUPO_W 0020
#define GRUPO_X 0010
#define OUTROS_R 0004
#define OUTROS_W 0002
#define OUTROS_X 0001

extern int id_usuario_atual;
extern int id_grupo_atual;

void definir_usuario(int uid, int gid);
int checar_permissao(int permissao_necessaria, unsigned short permissoes_arquivo, int dono_arquivo, int grupo_arquivo);

#endif
