// Luan Murilo de Mello
// Nilton Tadeu Moreira Alves
// Henrique Severiano Pereira
// Lucas Mantovani
#include <iostream>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "Portuguese"); //pt-BR

    // Declaração das variaveis principais
    int op_menu, num1, num2, num3, num4;
    //Declaração das variaveis do loop de jogo
    int tentativas, digito_1, digito_2, digito_3, digito_4, posiErrada, posiCerta;



    do { // Menu e seleção das opções
        system("cls");

        // Interação do usuário com o menu
        cout << "Menu:\n1 - Jogar\n2 - Como Jogar\n3 - Info\n4 - Sair";
        cout << "\nEscolha uma opção: ";
        cin >> op_menu;

        // Opções do menu 1 - Jogar(entra no game), 2 - Explicação de como o jogo funciona, 3 - Informações do autores e 4 - Para finalizar a aplicação
        switch(op_menu) {
            
            case 1: //Opção de jogar

                tentativas = 10;

                srand(time(NULL));
                do{ // Gera 4 números aleatórios entre 1 e 6 até que não se repitam
                    num1 = rand() % 6 + 1;
                    num2 = rand() % 6 + 1;
                    num3 = rand() % 6 + 1;
                    num4 = rand() % 6 + 1;
                } while (num1 == num2 || num1 == num3 || num1 == num4 || num2 == num3 || num2 == num4 || num3 == num4);

                do { // Inicio do loop do jogo

                    posiCerta = 0;
                    posiErrada = 0;

                    system("cls");

                    /* Impressão para fins de teste e validação dos números aleatórios 
                    cout << "\nNum aleatório 1: " << num1;
                    cout << "\nNum aleatório 2: " << num2;
                    cout << "\nNum aleatório 3: " << num3;
                    cout << "\nNum aleatório 4: " << num4;
                    */

                    do{// Solicitação dos 4 digitos, nesse modelo de coleta dos dados encadeados em um cin o usuário pracisa digitar com "espaço" entre os digitos ou "enter"
                        system("cls");
                        cout << "Digite uma sequência de 4 números entre 1 e 6 com um espaço entre eles: ";
                        cin >> digito_1 >> digito_2 >> digito_3 >> digito_4;

                        // Verifica se todos os digitos estão dentro do range de 1 a 6, caso um ou mais esteja fora do range solicita que digite novamente
                        if (digito_1 < 1 || digito_1 > 6 || digito_2 < 1 || digito_2 > 6 ||
                            digito_3 < 1 || digito_3 > 6 || digito_4 < 1 || digito_4 > 6){

                            cout << "\nValores fora do limite, tente novamente.\n";
                            system("pause");

                        }
                    } while (digito_1 < 1 || digito_1 > 6 || digito_2 < 1 || digito_2 > 6 ||
                             digito_3 < 1 || digito_3 > 6 || digito_4 < 1 || digito_4 > 6);

                    // Verifica se código contém dígito 1 na posição errada 
                    if ((digito_1 == num2 || digito_1 == num3 || digito_1 == num4) && (digito_1 != digito_2 && digito_1 != digito_3 && digito_1 != digito_4)) {
                        posiErrada ++;
                    } // verifica se código contém dígito 1 na posição certa
                    else if (digito_1 == num1) {
                        posiCerta ++;
                    }

                    // Verifica se código contém dígito 2 na posição errada 
                    if ((digito_2 == num1 || digito_2 == num3 || digito_2 == num4) && (digito_2 != digito_1 && digito_2 != digito_3 && digito_2 != digito_4)) {
                        posiErrada ++;
                    } // verifica se código contém dígito 2 na posição certa
                    else if (digito_2 == num2) {
                        posiCerta ++;
                    }

                    // Verifica se código contém dígito 3 na posição errada 
                    if ((digito_3 == num1 || digito_3 == num2 || digito_3 == num4) && (digito_3 != digito_1 && digito_3 != digito_2 && digito_3 != digito_4)) {
                        posiErrada ++;
                    } // verifica se código contém dígito 3 na posição certa
                    else if (digito_3 == num3) {
                        posiCerta ++;
                    }

                    // Verifica se código contém dígito 4 na posição errada 
                    if ((digito_4 == num1 || digito_4 == num2 || digito_4 == num3) && (digito_4 != digito_1 && digito_4 != digito_2 && digito_4 != digito_3)) {
                        posiErrada ++;
                    } // verifica se código contém dígito 4 na posição certa
                    else if (digito_4 == num4) {
                        posiCerta ++;
                    }

                    tentativas--;

                    // Infomações de tentativas e acertos
                    cout << "\nNúmeros certos na posição errada: " << posiErrada;
                    cout << "\nNúmeros certos na posição certa: " << posiCerta;
                    cout << "\nNúmero de tentativas restantes: " << tentativas;

                    // Validação se os 4 digitos estão corretos em relação aos numeros aleatórios e suas respectivas posições
                    if (posiCerta == 4) {
                        cout << "\nVocê acertou todos!\n";
                    }
                    cout << "\n";
                    system("pause");

                } while(posiCerta != 4 && tentativas > 0);

                // Caso o contador de tentativas seja igual a 0 apresenta mensagem de Game Over e pause a palicação até o usuário aperte uma tecla
                if (tentativas == 0){
                    system("cls");
                    cout << "GAME OVER\n\n";
                    system("pause");
                }
                break;

            case 2: //Como jogar
                system("cls");
                cout << "O objetivo do Mastermind é descobrir uma combinação de números determinada aleatoriamente pelo computador. Em cada jogada, o jogador apresenta uma combinação de números a que o computador responde, apontando por cada número na posição correta e cada número presente na combinação, mas noutra posição.\n";
                system("pause");
                break;

            case 3: //Informações
                system("cls");
                cout << "Jogo Desenvolvido Por:\nNilton Tadeu Moreira Alves\nLuan Murilo De Mello\nLucas Mantovani\nHenrique Severiano Pereira\n\n04/2023 - Disciplina de Algorítmos e Programação\nProfessor: Rafael Ballottin\n";
                system("pause");
                break;


            case 4: //Saída do jogo
                return 0;
                break;

            default: // Caso não seja escolhida uma opção entre 1 e 4 solicita que digite novamente
                system("cls");
                cout << "\n\nOpção inválida, digite um valor apresentado.\n";
                break;
        }
    } while(op_menu != 4);
}