#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(){

	//Declaração das matrizes
    int matPrincipal[9][9] = {  4, 9, 5, 2, 8, 7, 3, 6, 1, 
                                7, 2, 8, 6, 1, 3, 4, 9, 5,
                                3, 6, 1, 9, 5, 4, 7, 2, 8,
                                6, 5, 3, 8, 4, 9, 2, 1, 7,
                                9, 8, 4, 1, 7, 2, 6, 5, 3,
                                2, 1, 7, 5, 3, 6, 9, 8, 4,
                                1, 3, 2, 4, 6, 5, 8, 7, 9,
                                5, 4, 6, 7, 9, 8, 1, 3, 2,
                                8, 7, 9, 3, 2, 1, 5, 4, 6},
         matGabarito[9][9], matJogo[9][9];
     //Declaração das variaveis
	int opMenu, opMod, count, l, c, acertos, tentativas, jogadorLinha, jogadorColuna, valor;

    do{
        system("cls");
        cout << "1 - Jogar\n2 - Sobre\n3 - Sair\n\n";
        cin >> opMenu;

        switch(opMenu){

            case 1: //Jogar
                system("cls");
                srand(time(NULL));
                opMod = rand() % 4 + 1;

                switch(opMod){ //Embaralha a matriz principal e joga na matriz gabarito e jogo conforme o numero sorteado na variavel opMod

                    case 1: //Somente copia a matriz
                        for(int linha = 0; linha < 9; linha++){
                            for(int col = 0; col < 9; col++){
                                matGabarito[linha][col] = matPrincipal[linha][col];
                                matJogo[linha][col] = matPrincipal[linha][col];
                            }
                        }

                    case 2: //Transpoe a matriz
                        for(int x = 0; x < 9; x++){
                            for(int y = 0; y < 9; y++){
                                matGabarito[x][y] = matPrincipal[y][x];
                                matJogo[x][y] = matGabarito[x][y];
                            }
                        }
                        break;

                    case 3: //Inverte por linha
                        for(int origem = 0, destino = 8; origem < 9; origem++, destino--){
                            for(int col = 0; col < 9; col++){
                                matGabarito[destino][col] = matPrincipal[origem][col];
                                matJogo[destino][col] = matGabarito[destino][col];
                            }
                        }
                        break;

                    case 4:  //Inverte por coluna
                        for(int origem = 0, destino = 8; origem < 9; origem++, destino--){
                            for(int linha = 0; linha < 9; linha++){
                                matGabarito[linha][destino] = matPrincipal[linha][origem];
                                matJogo[linha][destino] = matGabarito[linha][destino];
                            }
                        }
                        break;
                }


                count = 0;
				do { //Cria a matriz do jogo para o usuário, zerando algumas posicoes
					l = rand() % 9;
					c = rand() % 9;

					if(matJogo[l][c] != 0){
                        matJogo[l][c] = 0;
                        count++;
                    }
				}while(count < 40);
				/*

                for(int x = 0; x < 9; x++){
                    for(int y = 0; y < 9; y++){
                        cout << matGabarito[x][y] << "\t";
                    }
                    cout << endl;
                }

                cout << endl;

                for(int x = 0; x < 9; x++){
                    for(int y =0; y < 9; y++){
                        if(matJogo[x][y] == 0){
                            cout << "X\t";
                        } else{
                            cout << matJogo[x][y] << "\t";
                        }
                    }
                    cout << endl;
                }

                system("pause");*/
                
                acertos = 0;
                tentativas = 0;
                do{ // game loop
                    system("cls");

                    for(int linha = 0; linha < 9; linha++){
                        for(int coluna = 0; coluna < 9; coluna++){
                            if(matJogo[linha][coluna] == 0){
                                cout << "X\t";
                            } else {
                                cout << matJogo[linha][coluna] << "\t";
                            }
                        }
                    cout << endl;
                    }

				    cout << "\nInforme a linha: ";
				    cin >> jogadorLinha;
                    jogadorLinha = jogadorLinha - 1;
				    
				    cout << "\nInforme a coluna: ";
				    cin >> jogadorColuna;
                    jogadorColuna = jogadorColuna - 1;
				    
				    if(matJogo[jogadorLinha][jogadorColuna] == 0) {
    				    cout << "\nInforme o número: ";
    				    cin >> valor;
                        //! adicionar if para verificação do valor entre 1 e 9
				        if(valor == matGabarito[jogadorLinha][jogadorColuna]) {
    				        cout << "\nVocê acertou\n";
    				        matJogo[jogadorLinha][jogadorColuna] = matGabarito[jogadorLinha][jogadorColuna];
    				        acertos++;
                            tentativas++;
                            system("pause");
    				    } else {
    				        cout << "\nValor errado!\n\n";
                            tentativas++;
                            system("pause");
    				    }
				    } else {
    				    cout << "\nPosição já preenchida!\n";
                        system("pause");
    				}
				}while(acertos < 40);

                cout << "\n\nVocê ganhou!\n\n";
                cout << "Número de tentativas: " << tentativas << "\t";
                system("pause");

                break;

            case 2: //! mudar
                system("cls");
                cout << "SOBRE\n\n";
                system("pause");
                break;

            case 3: //Sair
                return 0;
                break;

            default: //Informa caso selecione uma opção invalida
            cout << "Opção inválida, digite um valor apresentado.\n";
            system("pause");
            break;
        }
    } while(opMenu != 3);
    return 0;
}