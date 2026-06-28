#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disco.h"

char blocos_disco[NUM_BLOCOS][TAMANHO_BLOCO];
int tabela_alocacao_blocos[NUM_BLOCOS]; // 0 = livre, 1 = alocado

void disco_iniciar() {
    memset(blocos_disco, 0, sizeof(blocos_disco));
    memset(tabela_alocacao_blocos, 0, sizeof(tabela_alocacao_blocos));
}

int disco_alocar_blocos(int num_blocos, int* bloco_inicial) {
    if (num_blocos <= 0) return 1;

    // Alocação contígua simples
    int contagem = 0;
    int primeiro = -1;

    for (int i = 0; i < NUM_BLOCOS; i++) {
        if (tabela_alocacao_blocos[i] == 0) {
            if (contagem == 0) {
                primeiro = i;
            }
            contagem++;
            if (contagem == num_blocos) {
                *bloco_inicial = primeiro;
                // Marca como alocado
                for (int j = primeiro; j < primeiro + num_blocos; j++) {
                    tabela_alocacao_blocos[j] = 1;
                }
                return 1; // Sucesso
            }
        } else {
            contagem = 0; // Reinicia
        }
    }

    return 0; // Falha, sem blocos contíguos disponíveis
}

void disco_liberar_blocos(int bloco_inicial, int num_blocos) {
    if (bloco_inicial < 0 || bloco_inicial + num_blocos > NUM_BLOCOS) return;

    for (int i = bloco_inicial; i < bloco_inicial + num_blocos; i++) {
        tabela_alocacao_blocos[i] = 0;
        memset(blocos_disco[i], 0, TAMANHO_BLOCO);
    }
}

void disco_escrever(int indice_bloco, const char* dados, int tamanho) {
    if (indice_bloco < 0 || indice_bloco >= NUM_BLOCOS) return;
    int tamanho_escrita = tamanho > TAMANHO_BLOCO ? TAMANHO_BLOCO : tamanho;
    memcpy(blocos_disco[indice_bloco], dados, tamanho_escrita);
}

void disco_ler(int indice_bloco, char* buffer, int tamanho) {
    if (indice_bloco < 0 || indice_bloco >= NUM_BLOCOS) return;
    int tamanho_leitura = tamanho > TAMANHO_BLOCO ? TAMANHO_BLOCO : tamanho;
    memcpy(buffer, blocos_disco[indice_bloco], tamanho_leitura);
}
