#include <iostream>
#include <locale.h>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Portuguese"); //pt-BR

    int escolhaOut, escolha, escolhaIn, arma, countVida, buff, moedas, temCristal;
    countVida = 3;

    cout << "Jás a lenda sobre um gigantesco e místico labirinto. Em seu final, se encontra uma estrela caída, o único artefato com o poder de conceder um pedido a quem segurá-la.\nMagos, elfos, anões e homens, ao saber da queda do ser celeste foram ao seu encontro. Séculos de guerra caíram entre os povos.";
    cout << "\nAssim, quando os líderes desses povos viram o caos que a ganância deles gerou, eles acabaram com os conflitos de imediato e fizeram uma aliança para selar esse poder onde ninguém impuro possa chegar.";
    cout << "\nIniciou-se assim a construção de uma grande fortificação que se tornou o labirinto, dentro dele criaturas e armadilhas prontos para impedir mãos impuras de tocarem a estrela.\nSe você se acha digno deixe seus pertences na entrada e prossiga.\nTodos os caminhos levam ao centro.";

    cout << "\n\nVocê passa pela entrada e se depara com dois pedestais. O labirinto oferece seus próprios meios de se defender.";
    cout << "\n\n1 - Arco";
    cout << "\n2 - Espada e Escudo";

    cout << "\n\nEscolha a sua arma:\n";
    cin >> arma;

    if (arma == 1) {
        cout << "\nVocê escolheu o arco.\n";
        cout << "Você é mais cauteloso, gosta de se manter seguro na batalhas, sábia escolha.\n";
    }

    else if (arma == 2) {
        cout << "\nVocê escolheu a espada e o escudo.\n";
        cout << "Ótima escolha, sua arma é excelente para te proteger de ataques de longa distância, dessa forma é possível se aproximar do alvo e dar um golpe fatal...\n";
    }

    //CENTAURO

	cout << "\nApós andar alguns metros, uma parede se fechou atrás de você, assim impedindo-o de voltar. Logo afrente, o corredor se abre em uma sala.\nEm seu centro, uma criatura mística: um centauro, metade homem, metade cavalo. Sua cabeça virada para baixo, parece estar meditando."; 
	cout << "\nAo dar alguns passos a frente ele levanta sua cabeça, e também seu arco, atirando uma flecha certeira em sua direção. Seu treinamento toma conta, e você se esquiva no último momento, escondendo-se atrás de um pilar da sala. Você precisa lutar.";

	if (arma == 1) {
		cout << "\n1 - Tentar cegá-lo com suas flechas";
        cout << "\n2 - Mirar em sua perna, tentando imobilizá-lo";   
	}

	else {
		cout << "\n1 - Aproximar-se com seu escudo e golpeá-lo no peito";
		cout << "\n2 - Aproximar-se com seu escudo e tentar derrubá-lo com um impacto de seu escudo";

	}

	cout << "\n3 - Tentar dialogar com a fera\n";
    cout << "O que você vai fazer?\n";
	cin >> escolha;

	if (escolha == 1) {//certa
		if (arma == 1) { //arco e flecha
		cout << "\n\nVocê toma mira e acerta, sua flecha cravando-se no olho da fera. Ela grita de dor, soltando seu arco ao levar suas mãos a face.\nVocê aproveita o momento de vulnerabilidade e corre para a saída, os gemidos de dor da besta cada vez mais suaves em suas costas.";
	    }

	    else {//espada
		cout << "\n\nVocê levanta seu escudo, protejendo-se da rajada de flechas do centauro enquando lentamente se aproxima. Finalmente, em um momento de descuido a fera dá uma abertura, e você golpeia sua espada em seu abdômen. A besta se debate por alguns momentos, mas não resiste.";
        cout << "\nVocê se move em direção a saída sem olhar para trás.";
	    }
	}

	else if (escolha == 2) {//errada
		if (arma == 1) { //arco e flecha
		cout << "\n\nVocê toma mira e acerta a perna da besta. O centauro perde o equilíbrio por um segundo, mas não deixa de atirar suas próprias flechas.";
        cout << "\nCom o centauro imobilizado, você corre em direção a saída. A fera tenta lhe seguir, mas sua perna não o permite. Com uma última flecha calmamente mirada ele acerta o seu ombro, uma lembrança de sua batalha.";
        cout << "\n-1 vida";
        countVida = countVida - 1;
        cout << "\nVidas: " << countVida;
	    }

	    else {//espada
        cout << "\n\nVocê levanta seu escudo, protejendo-se da rajada de flechas do centauro enquando lentamente se aproxima. Ao chegar na distância correta da besta, você avança com seu escudo, botando todo seu peso na investida.";
        cout << "\nA besta se desquilibra por um momento, mas sua metade de cavalo se faz útil, suas quatro patas rapidamente se firmando no chão. Em um momento de desespero você golpeia uma pata, abrindo um ferimento profundo, e foge em direção a saída.";
        cout << "\nA fera, agora ímovel por sua ferida, solta sua rajada de flechas em sua direção, duas flechas acertando-o. Apesar dos ferimentos, você alcança a saída, e sem olhar para trás, percorre o longo corredor à frente.";
        cout << "\n-1 vida";
        countVida = countVida - 1;
        cout << "\nVidas: " << countVida;
	    }
	}

	else if (escolha == 3) {//dialogar
        cout << "\n\nVocê tenta dialogar com a besta, mas ela não abre mão de sua rajada de flechas. Apesar de sua metade homem, o centauro é completamenta fera.";
        cout << "\nA fera, enfurecida por seus gritos, avança para o pilar em que você se escondia, usando todo o seu peso no impacto. O pilar cede e cai em sua direção, o impacto com o chão jogando destroços para todos os lados. Um pedaço do pilar voa em direção a sua cabeça, o impacto ferindo sua têmpora.";
        cout << "\n-1 vida";
        countVida = countVida - 1;
        cout << "\nVidas: " << countVida;
        cout << "\n\nCom a fera atordoada da investida, você aproveita a abertura e corre em direção a saída. \nApós alguns momentos percorrendo o corredor você ouve um rugido, a fera mostrando sua frustação de sua presa ter escapado.";		
	}

    //AUTOMATONS - JARDIM COM FRUTAS
	cout << "\n\nDados alguns minutos de caminhada, o corredor se abre em duas direções: \n"; 
	cout << "1 - Esquerda\n2 - Direita\n\n";
	cin >> escolhaOut;

    //AUTOMATONS
	if (escolhaOut == 1) { 
		cout << "\n\nVocê segue pela esquerda. Lentamente pelo caminho, pequenas engrenagens e peças metálicas aparecem pelo chão. Após mais alguns momentos de caminhada você chega numa sala aberta, em seu centro uma criatura mecânica, imóvel a não ser por suas engrenagens.";
        cout << "\nAo se aproximar, a criatura mecânica ativa, seus quatro braços metálicos revelando lâminas em suas pontas. Em seu peito, uma luminosa esfera de cristal azul.";
		cout << "\n1 - Tentar despedaçar os membros da criatura\n";

		if (arma == 1) {
			cout << "2 - Acertar o cristal com uma flecha\n";
		}
		else if (arma == 2) {
			cout << "2 - Golpear o cristal com sua espada\n";
		}
		cout << "Escolha o que fazer:\n";
		cin >> escolha;

		if (escolha == 1) {//errado
			cout << "\n\nA criatura prepara seu ataque com um de seus braços. Você se esquiva do ataque previsível, e contra-ataca com um golpe na junta da criatura. A conexão mecânica se desfaz, a lâmina caindo ao chão com um baque metálico.";
            cout << "\nPorém, após um segundo de pausa, a lâmina começa a vibrar. Em um momento, ela voa em direção a criatura, se conectando magnéticamente.";
            cout << "\nA criatura ataca novamente, girando seu torso em um ângulo desumano. Ela solta uma série de ataques, você não consegue se esquivar de todos.";
            
            cout << "\n-1 vida";
            countVida = countVida - 1;
            cout << "\nVidas: " << countVida;
            if (countVida <= 0) {
			cout << "VOCÊ MORREU\n";
			return 0;
		    }

            cout << "\nEm meio aos bloqueios e esquivos incessantes você tenta encaixar um ataque ou outro. Em um desses ataques você acerta o cristal no peito da criatura, derrubando-o de seu encaixe. Ela imediatamente congela, seus braços rigidamente suspensos no ar.";
		}

		else if (escolha == 2) {//certo
            cout << "\n\nA criatura prepara seu ataque com um de seus braços. Você se esquiva do ataque previsível, e contra-ataca, seu alvo o cristal em seu peito.";
            cout << "\nSeu ataque faz contato, derrubando-o de seu encaixe. Ela imediatamente congela, seus braços rigidamente suspensos no ar.";
        }

		cout << "\nVocê observa o cristal no chão.";
		cout << "\n1 - Levar o cristal\n2 - Deixar o cristal\n";
        cout << "Faça sua escolha:\n";
		cin >> escolha;

		if (escolha == 1){
			temCristal = 1;
            cout << "\nVocê pega o cristal.";
		}
		
        //AUTOMATONS > PAREDES QUE FECHAM - LAGO
		cout << "\n\nAo seguir o caminho da saída logo duas escolhas se mostram:\n"; 
		cout << "1 - Esquerda\n2 - Direita\n";
		cout << "Qual caminho você vai seguir?\n";
		cin >> escolhaIn;

        // AUTOMATONS > PAREDES QUE FECHAM
		if (escolhaIn == 1) {
			cout << "\n\nVocê segue pela esquerda. Logo, encontra-se em uma sala quase vazia, salvo pelo pedestal em seu centro. A entrava se fecha atrás de você. A sala treme, e as paredes começam a se fechar.";
			cout << "\nVocê rapidamente inspeciona o pedestal: ele é simples, possui somente um encaixe para algo esférico.";
            cout << "\n1 - Procurar algo pela sala";

			if (arma == 1){
				cout << "\n2 - Fincar uma flecha no vão das paredes.";
			}
			else if (arma == 2){
				cout << "\n2 - Fincar sua espada no vão das paredes.";
			}

			if (temCristal == 1){ //só aparece se tiver pego o cristal do automaton
				cout << "\n3 - Encaixar o cristal da criatura mecânica no pedestal.";
			}

			cout << "\nO que você vai fazer?";
			cin >> escolha;

			if (escolha == 1) {
				cout << "\n\nVocê desesperadamente procura pela sala, mas não encontra nada além de poeira, ela é desértica. As paredes se fecham cada vez mais, até que finalmente te esmagam por completo.";
                cout << "\n\nVOCÊ MORREU";
				return 0;
			}

			else if (escolha == 2) {
                if (arma == 1){//arco
                    cout << "\n\nVocê finca sua flecha no vão, com todas as sua forças você a segura lá. Com imenso esforço, a parede para de se mover. Seus braços estão extremamente doloridos, é possível que você tenha rompido alguns músculos.";
                }
                
                else if (arma == 2) {//espada
                    cout << "\n\nVocê finca sua lâmina no vão, com todas as sua forças você a segura lá. Com imenso esforço, a parede para de se mover. Seus braços estão extremamente doloridos, é possível que você tenha rompido alguns músculos.";
                }
                cout << "\n-1 vida";
                countVida = countVida - 1;
                cout << "\nVidas: " << countVida;
                if (countVida <= 0) {
                cout << "\n\nVOCÊ MORREU\n";
                return 0;
			    }
            }

			else if (escolha == 3) {
				cout << "\n\nVocê rapidamente encaixa o cristal azul no pedestal. Com outro tremor, as paredes ficam imóveis. Uma saída se abre no outro lado da sala.";
			}
		}

        //AUTOMATONS > LAGO
		else if (escolhaIn == 2) {
            cout << "\nVocê decide seguir sua intuição novamente e segue pela direita.";
            cout << "\nChegando na próxima sala percebe que está completamente vazia, apenas uma sala circular com uma poça de água no meio e pilares em sua volta.";
            cout << "\nA porta de entrada então se fecha e você segue para o centro da sala.";
            cout << "\nA água parece limpa, então, tomado pela sede, você bebe um pouco.\nUma única gota cai sobre a poça, revelando no reflexo da água sua falecida esposa.";
            cout << "\nRevelando o motivo da sua jornada: chegar à estrela caída para desejar tê-la de volta.\nLogo, o reflexo começa a sumir. Desesperado para vê-la por mais um momento você bebe mais da água, porém sem sucesso, ela se esvai entre suas mãos, como se não estivesse lá.";
            cout << "\nEntão, após alguns segundo de silêncio, a saída se revela.";
		}
	}

    //JARDIM EXOTICO
	else if (escolhaOut == 2){ 
        cout << "\nGuiado pelos seus instintos você escolheu o caminho da direita.\nApós andar mais pelos corredores escuros você escuta ao fundo o cantar de pássaros e vê uma luz surgindo ao fundo do caminho.";
        cout << "\nAo final do caminho você chega em uma sala que mantinha um belo jardim, com árvores lindas e frutas saborosas.";
        cout << "\nVocê continua a andar. Ao centro do jardim vê um senhor sentado em uma cadeira velha segurando uma cesta com frutas.";
        cout << "\n'Fique a vontade e pegue uma'\nNa cesta contém 3 frutas diferentes, uma maçã cristalina, um cacho de uvas peroladas e uma misteriosa fruta dourada";
        cout << "\nO senhor então insiste: 'Não seja timido, pegue uma'";
        cout << "\n\n1 - Maça Vermelha\n2 - Um cacho de uvas\n3 - Uma fruta Dourada\n\n";
        cout << "Escolha uma fruta: ";
        cin >> escolha;
        
        //Maça Vermelha
        if (escolha == 1) {
            cout << "\nA maçã do Éden, ótima escolha você foi presenteado com um sopro de vida extra.\nVida +1";
            countVida = countVida + 1;
            cout << "\nVida: " << countVida;
        }
        
        //Cacho de Uvas
        else if (escolha == 2) {
            cout << "\nAs uvas de Dionísio, uma fruta que lhe fornece precognição.\n";
            cout << "\nUma voz sussura ao seu ouvido: 'A sua frente uma escolha deve fazer, uma planta colher ou o passado reviver.\nA sua esquerda melancolia, a direita conflito...\n";
        }
        
        //Fruta Dourada
        else if (escolha == 3) {
            cout << "\nFruto de fogo de Merlin, Merlin antes de morrer lançou algumas dessas frutas pelo mundo com encantamentos, essa é de fogo e servirá para encantar sua arma.\n";
            if (arma == 1) {
                cout << "\nAgora seu arco dispara flechas de fogo.\n";
                buff = 1;
            }
            else {
                cout << "\nAgora sua lâmina entra em chamas sempre que empunhada.\n\n";
                buff = 2;
            }
        }
        
        //JARDIM EXOTICO > POÇA - PLANTA CARNIVORA
        cout << "\nAo sair do jardim a porta se fecha às suas costas.\nAndando mais alguns metros encontra-se outra escolha:";
        cout << "\nÀ direita você vê um brilho azulado.\nÀ esquerda sente uma leve brisa.";
        cout << "\n1 - Seguir o brilho\n2 - Seguir a brisa\n";
        cout << "\nEscolha um caminho: ";
        cin >> escolhaIn; 
        
        //JARDIM EXOTICO > POÇA
        if (escolhaIn == 1) {
            cout << "\nVocê decide seguir sua intuição novamente e segue o brilho.";
            cout << "\nChegando na próxima sala percebe que está completamente vazia, apenas uma sala circular com uma poça de água no meio e pilares em sua volta.";
            cout << "\nA porta de entrada então se fecha e você segue para o centro da sala.";
            cout << "\nA água parece limpa então, tomado pela sede, você bebe um pouco.\nUma única gota cai sobre a poça, revelando no reflexo da água sua falecida esposa.";
            cout << "\nO motivo da sua jornada: chegar à estrela caída para desejar tê-la de volta.\nLogo, o reflexo começa a sumir. Desesperado para vê-la por mais um momento você bebe mais da água, porém sem sucesso, ela se esvai entre suas mãos, como se não estivesse lá.";
            cout << "\nEntão, após alguns segundo de silêncio, a saída se revela.";
        }
        
        //JARDIM EXOTICO > PLANTA CARNIVORA
        else if (escolhaIn == 2) { 
            cout << "\nVocê decide seguir pela brisa.\n\n";
            cout << "\nLogo entra em outra sala, e se encontra em um pântano.\nA mata é densa o que causa dificuldades ao atravessar o gramado inundado.";
            cout << "\nConforme anda pela água, você se depara com cadáveres, o que o deixa em alerta. O cheiro de podridão do pântano queimando suas narinas.";
            cout << "\nEm meio às árvores caídas e podres você avista a saída e parte em sua direção.\nEntão, algo prende sua perna sob a raza água. Bruscamente você é puxado para trás, perdendo o equilíbrio.\nEnquanto está sendo arrastado pelo chão, você consegue segurar em uma cipó, fazendo força o suficiente para contrariar a força que te puxava.";
            cout << "\nOlhando para trás você entende o motivo de tantos cadáveres, uma planta gigantesca emerge da água.\nSuas raizes se entrelaçando aos seus lados, talvez elas se extendam por todo o pântano...";
            
            //Luta Com Buff
            if (buff == 1 || buff == 2) {
                cout << "\n\nGraças aos deuses você escolheu certo no jardim, a fruta de Merlin lhe deu as codições perfeitas para enfrentar essa criatura, com sua arma flamejante, pode quiemá-la rapidamente.\nOu caso prefira pode tentar a fuga enquanto ela ainda sai do chão.";
                cout << "\n1 - Atacá-la\n2 - Aproveitar para fugir\n";
                cout << "\nFaça sua escolha: ";
                cin >> escolha;
                
                if (escolha == 1) {
                    cout << "\nVocê então a ataca, ela tenta se defender com seus tentáculos, porém sem sucesso, com cada ataque você a queima mais.\nAté o momento em que ela abre sua últimas defesas e você a finaliza.\n";
                    cout << "\nEnquanto ela queima, o restante do pântano vai morrendo junto, as árvores caem, a grama perde sua cor e o caminho da saída se abre.";
                }
                
                else {
                    cout << "\nMesmo enterrada a planta ainda tem tentáculos, e sim, ela é o pântano.\nApós alguns passos ela te puxa novamente mas dessa vez não te solta, seus equipamentos acabam caindo no chão.";
                    cout << "\nEla te puxa diretamente para sua boca e te engole por inteiro.O ácido em seu interior faz o resto do serviço. A planta volta a se submergir, contente com sua refeição.";
                    cout << "\nFim da sua jornada...";
                    return 0;
                }
            }
            
            //Luta sem Buff
            else {
                cout << "Sua arma é inútil contra essa criatura, é preciso outra forma de enfrentá-la.\nAo olhar em volta, você vê um buraco em um terreno mais elevado e corre em direção a ele.\nA criatura acerta um golpe e te derruba no buraco, para sua sorte.";
                cout << "No buraco, alguns cadáveres mais frescos, talvez outros que tiveram a mesma idéia que a sua.\nAlgumas raízes se esgueiram na entrada do buraco.";
                cout << "\n1 - Usar um dos cadáveres de ísca\n2 - Tentar golpear as raízes\n";
                cout << "\nFaça sua escolha: ";
                cin >> escolha;
                
                //Escolha 1 Sem Buff
                if (escolha == 1) {
                    cout << "\nVocê levanta um dos cadáveres. Ao fazer contato com o corpo a raiz o puxa. Após alguns momentos de silêncio você sai do buraco.\nJá fora do buraco, você se esconde atrás de uma árvore para esperar uma abertura e fugir.";
                    cout << "\nVocê vê a planta engolir o corpo, e, aos poucos, recuar abaixo d'água.\nVocê toma sua deixa e parte para a saída.";
                }
                
                //Escolha 2 Sem Buff
                else {
                    cout << "\nAo tentar golpear sua arma se finca na raiz, prendendo-a. A planta manda mais raízes, dessa vez segurando cada membro seu.";
                    cout << "\nImóvel e sem poder se defender o final é um: aos poucos ela te arrasta para sua boca e o engole por inteiro. O ácido em seu interior faz o resto do serviço. A planta volta a se submergir, contente com sua refeição.";
                    cout << "\nFim da sua jornada...";
                    return 0;
                }
            }
        }
    }

    //CONVERGENCIA

    cout << "\n\nVocê continua pelo corredor, e, novamente, o caminho se divide.";
    cout << "\n1 - Esquerda\n2 - Direita";
    cout << "\nEscolha um caminho: ";
    cin >> escolhaOut;
    
    //INFERIOR ESQUERDA / ESFINGE
    if (escolhaOut == 1) { 
        
        cout << "\n\nAo seguir este caminho, você se depara com uma esfinge bloqueando o caminho.";
        cout << "\n'Responda minha charada corretamente e passará sem prejuízo. Erre, e sofrerá as consequências.'";
        cout << "\n'Eu sou alta quando jovem e baixa quando velha. Quem sou eu?'";
        cout << "\n1 - Vela\n2 - Árvore\n3 - Paciência";
        cout << "\n'Qual é a sua resposta?'";
        cin >> escolha;

        if (escolha == 1) {
            cout << "\n\n'Resposta correta'\nA esfinge abre sua boca e revela o caminho adiante.";            
        }

        else if (escolha == 2 || escolha == 3){
            cout << "\n\n'Resposta incorreta'\n De repente, a esfinge pula em sua direção, lhe dando uma abocanhada certeira. Ela então, abre sua boca e revela o caminho adiante.";
            cout << "\n-1 vida";
            countVida = countVida - 1;
            cout << "\nVidas: " << countVida;
            if (countVida <= 0) {
            cout << "\nVOCÊ MORREU\n";
            return 0;
            }
        }

         //ESFINGE > PADROES - ESQUELETOS
        cout << "\n\nNovamente, você se encontra em uma bifurcação.";
        cout << "\n1 - Esquerda\n2 - Direita";
        cout << "\nEscolha seu caminho:";
        cin >> escolhaIn; 

         //ESFINGE > PADROES
        if (escolhaIn == 1) {
            cout << "\nAo final do corredor você se encontra em uma sala antiga, em sua parede, três imagens: \nUma gota\nUma chama\nUm furacão";
            cout << "\nNo chão da sala, dois quadrados estão destacados, cada um com uma imagem no centro.";
            cout << "\n1 - Uma pedra\n2 - Um raio";
            cout << "Escolha sua resposta:\n";
            cin >> escolha;

            if (escolha == 1) {//certo
                cout << "\n\nVocê pisa no quadrado da pedra. Ele levemente entra para o chão, e a saída se revela.";
                cout << "\nSeguindo pela saída, lentamente o chão é repleto de pedras escuras. Ao final do corredor, você se encontra em uma praia de pedras negras.";
            }

            else if (escolha == 2) {//errado
                cout << "\n\nVocê pisa no quadrado do raio. A imagem no chão se parte, revelando um alçapão sob seus pés, em seu fundo um só destino: espinhos afiados.";
                cout << "VOCÊ MORREU";
                return 0;

            }
        }
        
        //ESFINGE > ESQUELETOS
        else if (escolhaIn == 2) {
            cout << "\n\nSeguindo pelo caminho, você se depara com uma sala repleta de ossos. Montanhas de crânios se espalham pelo chão.";
            cout << "\nAo fundo da câmara, um único esqueleto em pé, protegendo uma tumba ornamentada. Ao te perceber, o esqueleto entra em posição de ataque, levantando sua espada.";
            cout << "\n1 - Atacar o esqueleto, focando em desmembrar-lo\n2 - Se defender do esqueleto, focando em chegar perto da tumba\n";
            cout << "\nEscolha sua estratégia:\n";
            cin >> escolha;

            if (escolha == 1) {
                cout << "\n\nVocê ataca o esqueleto. Apesar de desmembrá-lo, ele simplesmente pega seus ossos extraviados e os reconecta em seu corpo.";
                cout << "Após uma longa batalha de diversos ossos derrubados e reconectados, sua exaustão é seu fim. Cansado demais para continuar a luta, o esqueleto lhe dá um ataque certeiro.";
                cout << "Seu corpo permanece no chão da câmara. Em alguns dias seus ossos serão somente mais munição para o esqueleto.";
                return 0;

            }
            else if (escolha == 2) {
                cout << "\n\nVocê se aproxima da tumba enquanto defende-se do esqueleto. Dentro da tumba, uma múmia segura um cristal com uma gravura de caveira. Porém, essa múmia não está morta.\nAinda.";
                cout << "\nVocê dá um ataque forte no esqueleto, o que o desequilibra, te dando tempo para dar um golpe fatal na múmia. Imediatamente após seu ataque o esqueleto se desfaz em ossos, somente o silêncio da câmara restando.";
                cout << "\nVocê ruma em direção a saída. No corredor em que percorreu, pequenas pedras escuras ficaram mais frequentes no chão. Ao final do caminho, você se encontra em uma praia de pedras negras.";
            }
        }
        

    }
    
    //INFERIOR DIREITA / MOEDAS
    else if (escolhaOut == 2) { 
        cout << "\nVocê chegou a um belo jardim com arbustos e árvores cheias de frutas, pássaros cantam ao fundo. Parece ser um lugar calmo.\n";
        cout << "\nNo centro do jardim, um chafariz, nele várias moedas cintilam ao fundo.";
        cout << "\n1 - Pegar uma moeda\n2 - Não pegar as moedas\n";
        cout << "\nEscolha: ";
        cin >> moedas;
        
        //MOEDAS > NEVOA - BARQUEIRO
        cout << "\nVocê segue em frente e se depara com outra bifurcação, um caminho pela esquerda e outro seguindo em frente.\n"; 
        cout << "\n1 - Seguir pela esquerda\n2 - Seguir em frente\n";
        cout << "\nEscolha um caminho: ";
        cin >> escolhaIn;
    
        //MOEDAS > NEVOA
        if (escolhaIn == 1) { 
            cout << "\n\nAo seguir pela equerda, quanto mais andava pelo corredor mais um estranha névoa encobria sua visão.";
            cout << "\nVocê chegou na próxima sala e não é possivel ver nada. Você tropeça em algo: uma tocha apagada.";
            cout << "\nPara facilitar seu caminho, você pega a tocha.\nEntão você nota algumas escritas no punho da tocha:";
            cout << "\n'Eu sou sempre vista, mas nunca tocada. Eu sou frequentemente subestimada, mas minha ausência é impensável. O que sou eu?'";
            
            cout << "\nUma charada para fazer a tocha funcionar.";
            cout << "\n1 - O fogo\n2 - A sombra";
            cout << "\nQual será sua resposta?";
            cin >> escolha;
            
            if (escolha == 2) {
                cout << "\n\nA tocha súbitamente acende. Alguns pedregulhos no chão começam a cintilar, revelando um caminho.\n";
                cout << "\nSeguindo as pedras cintilantes, você encontra a saída.\nSeguindo pelo corredor, o chão se completa de pedras escuras. Ao final do corredor, você se encontra em uma praia de pedras negras.";
            }

            else {
                cout << "\n\nA tocha súbitamente fica quente ao toque, e você instintivamente a solta. Já no chão, a tocha entra em chamas por completo, até sobrarem apenas cinzas.";
                cout << "\nAgora sem a tocha, você tenta seguir seu caminho. Após dar alguns passos, as pedras em que pisou se desfizeram sob seus pés, revelando um profundo abismo.\nCom a surpresa da ocorrência, você perde o equilíbrio, e acaba caindo no abismo, sua jornada incompleta.";
                cout << "\nVocê morreu...";
                return 0;
            }
        }
        
       //MOEDAS > BARQUEIRO
        else if (escolhaIn == 2) {  
            cout << "\nVocê decide então ir em frente. Após seguir parte do caminho se depara em uma caverna, em seu interior um gigantesco rio.";
            cout << "\nOlhando em sua volta avista um deck na borda da água. Um barco com uma figura encapuzada.";
            cout << "\nAo se aproximar do barco percebe que o rio está repleto de centenas de vultos flutuantes.";
            cout << "\nSão almas.\nO barqueiro, então, solta um grunhido, sua face encapuzada virada em sua direção.\nEle estende a mão.";
            
            //Tem moedas
            if (moedas == 1) {
                cout << "\n\nVocê alcança em seu bolso e produz a moeda que pegou no chafariz.\nO barqueiro a aceita em silêncio, abrindo o caminho para você entrar em seu barco.";
                cout << "\nDurante a travessia você olha para fora do barco. Diversas mãos fantasmagóricas arranham e tentam alcançar a borda, mas nenhuma com força o suficiente para subir.";
                cout << "\nFinalmente, sua travessia acaba. O barqueiro atraca seu barco em uma praia de pedras negras.";
            }
            
            //Não tem moedas
            else {
                cout << "\nDe repente uma imagem vem à sua cabeça: o chafariz com seu fundo de moedas. 'Eu não tenho como pagar', você fala.\nO barqueiro abaixa sua mão, solta um suspiro e lhe dá as costas.";
                cout << "\nO unico jeito de atravessar é nadando.";
                countVida = countVida - 1;
                
                if (countVida <= 0) {
                    cout << "\n\nComo sua única opção, você pula no rio. Braçada atrás de braçada, você segue nadando, as almas ao seu redor agarrando e puxando-o para baixo.";
                    cout << "\nFinalmente, apenas na metade do caminho, suas feridas tomam seu peso. Você está exausto e lesionado.\nSua força lentamente se exausta, perdendo a batalha que travava com as almas.\nVocê se afoga. Mais uma alma para o rio.";
                    return 0;
                }
                
                else {
                    cout << "\n\nComo sua única opção, você pula no rio. Braçada atrás de braçada, você segue nadando, as almas ao seu redor agarrando e puxando-o para baixo.";
                    cout << "\nApós agonizantes momentos e muito esforço, você chega em uma praia de pedras negras. Porém, seu caminho não foi sem consequências: seu corpo está coberto de arranhões, alguns abriram em feridas.";
                   cout << "\n-1 vida";
                    cout << "\nVidas: " << countVida;
                }
            }
        }
    }
    
    //BOSS
    
    cout << "\n\nVocê encontra, então, ao entrar mais profundamente na praia, a estrela. Porém, protegida por 3 criaturas primordiais, criadas antes mesmo do próprio homem: elementais...";
    cout << "\nCada um feito de um elemento ou força da natureza, conceitos imutáveis e primordiais.";
    cout << "\nUm é feito de plantas e madeira, representando a vida em si, a natureza.\nO segundo, feito de um gelo escuro, encoberto de uma névoa sombria, representa a morte.\nO terceiro é o fogo, o padrão incalculável de suas chamas, seu imenso potencial de destruição: o caos.";
    cout << "\n\nLogo, notam sua presença e te cercam preparando-se para atacar, procurando de todos os ângulos uma oportunidade.\n\nNessa luta será preciso conhecimento e lógica, sua estratégia é usar os ataques dos próprios elementais contra sí.";
    cout << "\nPoderosos como são, suas armas não tem nenhum efeito.";
    cout << "\n1 - Usar o ataque do caos para atacar a vida\n2 - Usar o ataque da morte para atacar a vida";
    cout << "\nDecida como organizar seus ataques:\n";
    cin >> escolha;

    if (escolha == 1){ //certo
        cout << "\n\nPerfeito, você escolheu fazer o elemental de fogo atacar primeiro em direção as plantas, usando-se de ísca, fazendo-o queimar.";
        cout << "\nSobram dois...";
        cout << "\n1 - Usar o ataque da morte para atacar o caos \n2 - Usar o ataque do caos para atacar a morte";
        cout << "\nDecida como organizar seus ataques:\n";
        cin >> escolha;

        if (escolha == 1){ //gelo atacando fogo - errado
            cout << "\nPéssima escolha, quando o Gelo ataca o Fogo não causa dano algum a ele, com isso o de Fogo contra-ataca, o queimando vivo.;";
            cout << "\n\nVOCÊ MORREU";
            return 0;
        }
        
        else {//fogo derretendo gelo - certo
            cout << "\n\nEsperto, usando a mesma lógica inicial, utilizando de suas fraquezas elementais. Agora restam apenas você e o caos.";

            cout << "\n1 - Fazer o Caos cair no rio das almas\n2 - Atacar";
            cin >> escolha;

            if (escolha == 1){//certo
                cout << "\n\nVocê então deixa o caos te atacar e desvia enquanto se aproxima da beira do rio.";
                cout << "\nEle te segue enfurecido, suas chamas cada vez mais quentes. Cego com raiva, ele se impulsiona em sua direção.\nNo último momento você se esquiva, o caos não consegue mudar sua trajetória e é apagado no rio de almas.";
                cout << "\n\nApós recuperar o seu fôlego, você vira em direção à estrela.";
            }
            
            else {//errado
                cout << "\nAo tentar atacá-lo diretamente, novamente não causa dano, apenas o deixa mais enfurecido que desfere um ataque enorme que te cobre completamente, queimando-o vivo.";
                cout << "\nVocê chegou tão perto...";
                cout << "\n\nVOCÊ MORREU";
                return 0;
            }
        }
    }
    
    else {
        cout << "\n\nVocê escolheu usar o ataque da morte (gelo) para atacar a vida (planta). O ataque faz contato, porém, após um momento de hesitação, todos os elementais se viram em sua direção.\nEles sabem seu plano.";
        cout << "\nPor mais que desviasse, os elementais agora cordenaram seus ataques, sua força e coordenação se mostrando o seu fim.";
        cout << "\n\nVOCÊ MORREU";
        return 0;
    }
    
    
    cout << "\n\nApós todo os desafios do labirinto você finalmente chega à estrela, pronto para enfim realizar seu pedido de ter sua amada de volta.\nQuando toca na estrela escuta uma voz em seu ouvido.";
    cout << "\nEssa voz diz que nada é de graça e que deve fazer uma ultima escolha: uma vida por uma vida...";
    cout << "\nPara alcançar o que deseja, precisa abrir mão de sua própria vida.";
    cout << "\n\n1 - Aceitar a troca\n2 - Seguir em frente";
    cout << "\nEscolha o fim da sua história: ";
    cin >> escolha;
    
    if (escolha == 1) {
        cout << "\n\nVocê aceita a troca.\nAos poucos suas pernas sedem força e você cai em frente a estrela. Ao fundo, uma forte luz enquanto sua visão escurece.";
        cout << "\nJá sem conseguir abrir os olhos, você sente alguém colocando sua cabeça no colo.\nUma lágrima cai na sua testa, em seguida, a doce voz da sua amada fala:\n'Obrigado...'";
        cout << "\nAqui então acaba sua jornada, não da forma como planejava, mas em paz por ter trazido quem mais amava de volta à vida.";
        cout << "\n\nFim";
    }

    else {
        cout << "\n\nSabendo que não poderia vê-la de novo, decide abrir mão do pedido, o substituindo porém, por algo tão nobre:\n'Eu desejo nunca esquecer o toque da minha amada, ou nossos momentos juntos. Quero tê-la para sempre em minha memória.'";
        cout << "\n\nFIM";
    }
    
    return 0;
}
