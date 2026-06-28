#ifndef DISCO_H
#define DISCO_H

#define TAMANHO_BLOCO 64
#define NUM_BLOCOS 1024

void disco_iniciar();
int disco_alocar_blocos(int num_blocos, int* bloco_inicial);
void disco_liberar_blocos(int bloco_inicial, int num_blocos);
void disco_escrever(int indice_bloco, const char* dados, int tamanho);
void disco_ler(int indice_bloco, char* buffer, int tamanho);

#endif
