# Mini-Sistema de Arquivos em Memória

O objetivo é simular as estruturas e operações internas de um sistema de arquivos, implementando conceitos fundamentais como diretórios, arquivos, metadados (FCB/inode) e controle de acesso (RWX) baseados num ambiente tipo Linux. No nosso simulador, um arquivo não interage com o disco real da máquina (HD/SSD); sua informação e o seu conteúdo em bytes residem na memória primária (RAM).

## Funcionalidades e Comandos

O simulador fornece um terminal interativo suportando os seguintes comandos:

- `mkdir <caminho>`: Cria um novo diretório.
- `cd <caminho>`: Navega pelos diretórios (suporta `.`, `..` e caminhos absolutos ou relativos).
- `touch <caminho>`: Cria um arquivo vazio ou atualiza as datas de acesso/modificação.
- `echo "<texto>" > <caminho>`: Simula a escrita de texto em um arquivo, alocando blocos no disco. (Aspas são necessárias).
- `cat <caminho>`: Lê o conteúdo do arquivo e mostra na tela.
- `cp <origem> <destino>`: Copia o conteúdo de um arquivo para outro local/nome.
- `mv <origem> <destino>`: Move ou renomeia um arquivo ou diretório.
- `rm <caminho>`: Exclui um arquivo ou diretório (se vazio) e libera o espaço.
- `chmod <permissoes_octais> <caminho>`: Altera as permissões de acesso (ex: `chmod 755 arquivo.txt`).
- `ls`: Lista o conteúdo do diretório atual, mostrando permissões, dono, grupo, tamanho e nome.
- `stat <caminho>`: Exibe informações detalhadas de metadados do arquivo (FCB).
- `su <usuario>`: Alterna o usuário atual para simular controle de acesso (por padrão, inicia como "root").
- `useradd <usuario>`: Adiciona um novo usuário ao sistema (requer permissão de root).
- `userdel <usuario>`: Remove um usuário do sistema (requer permissão de root).
- `exit`: Sai do simulador.

## Instruções de Compilação e Execução

O projeto foi desenvolvido em C++ com a utilização da bibliotecas padrão.

**Pré-requisitos:** Compilador `g++` e `make`, ou executar em ambiente virtual, como o online GDB.

1. **Compilação:**
   No diretório raiz do projeto, execute o comando:
   ```bash
   make
   ```
   Isso compilará os arquivos da pasta `src/` e colocará o executável na pasta raiz.

2. **Execução:**
   Após compilar, inicie o simulador com:
   ```bash
   ./minifs
   ```

3. **Limpeza:**
   Para limpar os arquivos objetos e o executável gerado:
   ```bash
   make clean
   ```

### A representação do File Control Block (FCB) e "inode"
A struct `FCB` em `No.hpp` implementa diretamente este conceito, guardando metadados de cada arquivo ou diretório, como:
- `nome`, `tamanho`, `tipo`
- Datas de criação, acesso e modificação (`time_t`)
- ID único (simulando um inode)
- Dono, Grupo e Permissões

### A estrutura de diretórios em árvore
O sistema organiza diretórios em árvore. A estrutura `No` armazena um vetor de ponteiros para os seus "filhos", no caso de diretórios. Cada Nó sabe quem é o seu pai armazenando um ponteiro de volta à origem, facilitando a navegação via `cd ..`.

### Mecanismo de proteção de acesso (RWX)
As permissões são controladas na estrutura através de um inteiro e simuladas usando o sistema clássico tipo UNIX. As verificações são feitas em nível de bits (ex: `0b100` para ler, `0b010` para escrever, `0b001` para executar). A função `verificarPermissao()` isola os conjuntos de três bits do arquivo utilizando deslocamento (`>>`) dependendo se o ator é dono, grupo ou outros. O resultado é checado dinamicamente comparando os bits de acesso desejado contra essa máscara isolada, usando o operador E (`&`) a fim de conceder ou barrar o acesso aos comandos.

### Simulação da alocação de blocos
Em vez de ter um espaço infinito, o sistema usa um 'Disco' de tamanho fixo para guardar as informações.
Quando salvamos um arquivo, ele não precisa ficar inteiro em um único espaço no disco. Na verdade, o sistema divide o arquivo em pequenas fatias e as espalha pelos espaços que estiverem vazios no momento. Para não perder nada, o arquivo guarda apenas uma lista com os 'endereços' de onde cada uma de suas fatias foi parar.

Assim, na hora de abrir e ler esse arquivo, o sistema consulta essa lista de endereços, busca os pedaços espalhados e os cola na ordem certa para te mostrar o conteúdo completo."

## Estrutura do Código (Arquitetura)
- `No` (`src/No.cpp` e `src/No.hpp`): Estruturas puras de Arquivo ou Diretório e suas funções de gerenciamento de hierarquia.
- `Usuario` (`src/Usuario.cpp` e `src/Usuario.hpp`): Representa um perfil no sistema com funções utilitárias que cruzam máscaras de bits.
- `Disco` (`src/Disco.cpp` e `src/Disco.hpp`): Contém o vetor global limitador e matrizes boleanas de verificação. Funções puras lidam com suas modificações.
- `SistemaArquivos` (`src/SistemaArquivos.cpp` e `src/SistemaArquivos.hpp`): Centraliza as funções simuladoras de comandos POSIX para navegar nas estruturas interligadas.
- `Terminal` (`src/Terminal.cpp` e `src/Terminal.hpp`): Rotina de leitura contínua (REPL) que capta *inputs* e delega responsabilidades as funções acima.
