#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct pagina{
  int numero_frame;
  char validade;
};

int main()
{
    const int NUM_FRAMES = 10;
    const int NUM_PAGINAS = 20;
    const int NUM_ACESSOS = 10;

    int frames[NUM_FRAMES];
    vector<pagina> tabela_paginas(NUM_PAGINAS);
        int acessos[NUM_ACESSOS]; 

    srand(time(NULL));
    
    for(int i = 0; i < NUM_FRAMES; i++){ //deixa todos frames livres
        frames[i] = -1;
    }
    
    for(int i = 0; i < NUM_PAGINAS; i++){ //todas as paginas zeradas e invalidas
        tabela_paginas[i].numero_frame = -1;
        tabela_paginas[i].validade = 'i';
    }
    
    for (int i = 0; i < NUM_ACESSOS; i++) {//preenche com acessos aleatorios
        acessos[i] = rand() % NUM_PAGINAS; 
    }

    int frames_para_preencher = NUM_FRAMES / 2;
    int frames_preenchidos = 0;

    while(frames_preenchidos < frames_para_preencher){
        int frame_aleatorio = rand() % NUM_FRAMES;
        int pagina_aleatoria = rand() % NUM_PAGINAS;

        if(frames[frame_aleatorio] == -1 && tabela_paginas[pagina_aleatoria].validade == 'i'){
            
            frames[frame_aleatorio] = pagina_aleatoria;
            
            tabela_paginas[pagina_aleatoria].numero_frame = frame_aleatorio; //guarda o frame
            tabela_paginas[pagina_aleatoria].validade = 'v'; //muda a validade
            
            frames_preenchidos++;
        }
    }
    

    //vizualizacao
    
    cout << "--- STATUS DOS FRAMES (RAM) ---" << endl;
    for(int i = 0; i < NUM_FRAMES; i++){
        if(frames[i] != -1) {
            cout << "Frame " << i << ": Contem a Pagina " << frames[i] << endl;
        } else {
            cout << "Frame " << i << ": Livre (-1)" << endl;
        }
    }

    cout << "\n--- STATUS DA TABELA DE PAGINAS ---" << endl;
    for(int i = 0; i < NUM_PAGINAS; i++){
        cout << "Pagina " << i << "\t-> Frame: " << tabela_paginas[i].numero_frame 
             << "\t| Validade: " << tabela_paginas[i].validade << endl;
    }

    
    cout << endl << "--- SEQUENCIA DE ACESSOS GERADA ---" << endl;
    for (int i = 0; i < NUM_ACESSOS; i++) {
        cout << "Acesso " << i + 1 << ": Requisitando Pagina " << acessos[i] << endl;
    }
    
    cout << endl << endl;
    
    //----------------acessos---------------
    for(int i = 0; i < NUM_ACESSOS; i++){
        if(tabela_paginas[acessos[i]].validade == 'v'){
            cout << "Acesso rápido e direto na RAM, no frame: " << tabela_paginas[acessos[i]].numero_frame << endl;
        }
        
        if(tabela_paginas[acessos[i]].validade == 'i'){
            cout << "PAGE FAULT: Pagina " << tabela_paginas[acessos[i]].numero_frame << " Não está na RAM" << endl;
            
            int indice_espaco_livre = -1;
            
            for(int i = 0; i < NUM_FRAMES; i++){ //procura espaco livre e coloca o indice em indice_espaco_livre
                if(frames[i] == -1){
                    indice_espaco_livre = i;
                }
                if(indice_espaco_livre != -1){
                    break;
                }
            }
            
            if(indice_espaco_livre != -1){ //se achou
                tabela_paginas[acessos[i]].numero_frame = indice_espaco_livre; //guarda o frame
                tabela_paginas[acessos[i]].validade = 'v'; //muda a validade
                
                frames[indice_espaco_livre] = acessos[i];
                
                cout << "Resolvido: Página " << acessos[i] << " carregada do disco para o frame " << indice_espaco_livre << endl;
            }
            
            if(indice_espaco_livre == -1){ //se nao achou espaco livre
                cout << "OUT OF MEMORY: Necessário algorítimo de substituição." << endl;
            }
        }
    }
    
    cout << endl << "--- STATUS DOS FRAMES (RAM) ---" << endl;
    for(int i = 0; i < NUM_FRAMES; i++){
        if(frames[i] != -1) {
            cout << "Frame " << i << ": Contem a Pagina " << frames[i] << endl;
        } else {
            cout << "Frame " << i << ": Livre (-1)" << endl;
        }
    }

    cout << "\n--- STATUS DA TABELA DE PAGINAS ---" << endl;
    for(int i = 0; i < NUM_PAGINAS; i++){
        cout << "Pagina " << i << "\t-> Frame: " << tabela_paginas[i].numero_frame 
             << "\t| Validade: " << tabela_paginas[i].validade << endl;
    }

    
    return 0;
}
