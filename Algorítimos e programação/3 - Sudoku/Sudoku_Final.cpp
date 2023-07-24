//M3 Algoritimos da programação - Sudoku
// Luan Murilo de Mello
//Nilton Tadeu Moreira Alves
//Henrique Severiano Pereira
//Lucas Mantovani
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

using namespace std;

int main(){
    setlocale(LC_ALL, "Portuguese"); //pt-BR

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
                switch(opMod){ //Embaralha a matriz principal e joga na matriz gabarito e jogo conforme o número sorteado na variável opMod

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


                count = 0; //variável somente para contar quantidade de posições zeradas
				do { //Zera 40 posições aleatórias na matriz de jogo
					l = rand() % 9;
					c = rand() % 9;

					if(matJogo[l][c] != 0){
                        matJogo[l][c] = 0;
                        count++;
                    }
				}while(count < 40);

				/*

                FINS DE TESTE

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

                system("pause");
                
                */
                
                acertos = 0; //quantidade de acertos do jogador, jogo termina quando o valor for 40
                tentativas = 0; //quantidade de tentativas do jogador, apresentada ao terminar o sudoku
                do{ //loop de jogo
                    system("cls");

                    cout << "     1  2  3  4  5  6  7  8  9" << endl << "     _  _  _  _  _  _  _  _  _" << endl;//exibe a matriz com posições zeradas com guias de linha e coluna
                    for(int linha = 0; linha < 9; linha++){
                        cout << linha + 1 << "  | ";
                        for(int coluna = 0; coluna < 9; coluna++){
                            if(matJogo[linha][coluna] == 0){
                                cout << "*  ";
                            } else {
                                cout << matJogo[linha][coluna] << "  ";
                            }
                        }
                    cout << endl;
                    }

                    do{ //loop de input de linha do jogador
                        cout << "\nInforme a linha: ";
                        cin >> jogadorLinha;
                        if(jogadorLinha < 1 || jogadorLinha > 9) cout << "\nLinha inválida, tente outro valor.";
                    } while (jogadorLinha < 1 || jogadorLinha > 9);
                    jogadorLinha = jogadorLinha - 1;
				    
                    do{ //loop de input de coluna do jogador
                        cout << "\nInforme a coluna: ";
                        cin >> jogadorColuna;
                        if(jogadorColuna < 1 || jogadorColuna > 9) cout << "\nColuna inválida, tente outro valor.";
                    } while (jogadorColuna < 1 || jogadorColuna > 9);
                    jogadorColuna = jogadorColuna - 1;
				    
				    if(matJogo[jogadorLinha][jogadorColuna] == 0) { //valida se a posição pode ser preenchida
                        do{ //loop de input de valor do jogador
                            cout << "\nInforme o número: ";
                            cin >> valor;
                            if(valor < 1 || valor > 9) cout << "\nNúmero inválido, tente novamente.";
                        } while (valor < 1 || valor > 9);

				        if(valor == matGabarito[jogadorLinha][jogadorColuna]) { //valida resposta correta com matriz gabarito e repassa para matriz jogo
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

                //final de jogo

                cout << "\n\nVocê ganhou!\n\n";
                cout << "Número de tentativas: " << tentativas << "\n";
                system("pause");

                break;

            case 2: //Sobre
                system("cls");
                cout << "O Sudoku é um jogo de lógica e raciocínio que se tornou muito popular em todo o mundo.\n"
                        "O objetivo do jogo é preencher uma grade 9x9 com números de 1 a 9, de forma que cada coluna, "
                        "cada linha e cada uma das nove subgrades 3x3 contenha todos os números de 1 a 9 sem repetição.\n\n"
                        "Autores: Luan Murilo de Mello - Nilton Tadeu Moreira Alves - Henrique Severiano Pereira - Lucas Mantovani\n"
                        "Professor: Rafael Ballottin\n06/23\n";
                system("pause");
                break;

            case 3: //Sair
                return 0;
                break;

            default: //Informa caso selecione uma opção invalida no menu
            cout << "Opção inválida, digite um valor apresentado.\n";
            system("pause");
            break;
        }
    } while(opMenu != 3);
    return 0;
}