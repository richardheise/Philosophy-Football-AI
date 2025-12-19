# Projeto Futebol dos Filósofos

Este repositório contém o código de um jogador automático (IA) para o jogo "Futebol dos Filósofos Unidimensional", desenvolvido para a disciplina de Inteligência Artificial. O projeto foi reorganizado para melhor clareza e manutenção.

## Estrutura do Repositório

A estrutura de diretórios foi organizada da seguinte forma:

```
.
├── bin/          # Contém os executáveis compilados do projeto.
├── include/      # Contém todos os arquivos de cabeçalho (.h).
├── src/          # Contém todos os arquivos de código fonte (.c).
├── examples/     # Contém programas de exemplo que interagem com o controlador.
├── makefile      # Arquivo de configuração para compilação do projeto.
├── README.md     # Este arquivo README.
└── redis.conf    # Arquivo de configuração para o servidor Redis.
```

### Detalhes das Pastas:

*   **`src/`**:
    *   `main.c`: Contém a lógica principal da IA que se conecta ao controlador e chama a função `solve` para determinar a próxima jogada.
    *   `marIA_lib.c`: Implementa a função `solve` que orquestra a decisão da melhor jogada, delegando a lógica para as heurísticas de esquerda e direita.
    *   `right.c`: Funções heurísticas e de teste relacionadas ao lado direito do campo.
    *   `left.c`: Funções heurísticas e de teste relacionadas ao lado esquerdo do campo.
    *   `utils.c`: Funções utilitárias e auxiliares para manipulação do estado do jogo e alocação de memória.
    *   `controller.c`: O programa controlador do campo de jogo (originalmente parte do setup do problema).

*   **`include/`**:
    *   `field.h`: Funções para comunicação com o controlador do campo via servidor Redis.
    *   `marIA_lib.h`: Declaração da função principal da IA (`solve`).
    *   `right.h`: Declarações das funções heurísticas e de teste para o lado direito.
    *   `left.h`: Declarações das funções heurísticas e de teste para o lado esquerdo.
    *   `utils.h`: Declarações das funções utilitárias.

*   **`examples/`**:
    *   `exemplo1.c`: Um programa de exemplo que demonstra como se conectar ao controlador, receber o estado do campo e enviar um movimento simples.
    *   `exemplo2.c`: Um jogador interativo de exemplo que mostra os dados recebidos do controlador e espera por uma nova jogada via entrada padrão.

## Como Compilar e Rodar

Para compilar e executar o projeto, siga os passos abaixo:

### Pré-requisitos

Certifique-se de ter as seguintes bibliotecas instaladas em seu sistema:

*   `libhiredis-dev`: Biblioteca C para interface com o Redis.
*   `libreadline-dev`: Biblioteca para edição de linha de comando (usada nos exemplos).

No Ubuntu/Debian, você pode instalá-las com:
```bash
sudo apt-get update
sudo apt-get install libhiredis-dev libreadline-dev
```

### Compilação

Para compilar o projeto, navegue até o diretório raiz do repositório e execute o `make`:

```bash
make
```

Isso criará o executável `marIA` dentro do diretório `bin/`.

### Execução

Para rodar o jogador automático, você precisará de um servidor Redis e do programa `controller` em execução.

1.  **Iniciar o Servidor Redis**:
    Em um terminal, inicie o servidor Redis usando o arquivo de configuração fornecido:
    ```bash
    redis-server redis.conf
    ```

2.  **Iniciar o Controlador do Campo**:
    Em outro terminal, execute o programa controlador. O controlador requer parâmetros como o lado que inicia, o tamanho do campo, o número máximo de jogadas e o limite de tempo.
    Exemplo:
    ```bash
    ./bin/controller e 13 50 0
    ```
    Este comando inicia o controlador indicando que o jogador que começa é o 'e' (esquerdo), a partida terá 50 movimentos e não há limite de tempo para as jogadas. Para mais detalhes sobre os parâmetros do controlador, execute `./bin/controller` sem argumentos.

3.  **Executar o Jogador Automático (IA)**:
    Em um terceiro terminal, execute a sua IA, especificando o lado em que ela jogará ('e' para esquerda ou 'd' para direita):
    ```bash
    ./bin/marIA e
    ```
    ou
    ```bash
    ./bin/marIA d
    ```

Você pode testar a sua IA jogando interativamente contra ela usando o `exemplo2`. Basta executar a sua IA em um terminal e o `examples/exemplo2` em outro.

## Autores

*   Richard Fernando Heise Ferreira GRR20101053
*   Carlos Iago Bueno GRR20190171

Este trabalho foi desenvolvido para a disciplina de Inteligência Artificial.

---

### Conteúdo do pacote:

- campo.c e campo.h: biblioteca de funções para comunicação como o
  controlador do campo via servidor redis

- controlador.c: programa que controla o campo

- exemplo1.c: programa exemplo comentado que usa as funções de
  comunicação, conecta com o controlador, recebe o campo e o movimento
  do adversário e envia para o controlador um novo movimento

- exemplo2.c: programa exemplo que implenta um jogador interativo que
  mostra na saída padrão os dados recebidos do controlador e espera na
  entrada padrão uma nova jogada

- leiame.txt: este texto

- makefile: compila os 3 programas anteriores

- redis.conf: arquivo de configuração para ser usado com o servidor
  redis

Para compilar os programas o sistema deve ter o pacote libhiredis-dev 
instalado, ele contém a biblioteca hiredis usada pelos programa para 
acessar o servidor redis.

Para preparar o seu jogador para se comunicar com o controlador do
campo você deve alterar o seu programa para utilizar as funções que
enviam e recebem dados do controlador. O exemplo1 pode ajudar nesta
alteração.

Para testar o seu jogador você deve iniciar o servidor redis e
executar o controlador.

Para iniciar o servidor redis nos sistemas do DInf execute em um
terminal:

   $ redis-server redis.conf

Para iniciar o controlador execute em outro terminal:

   $ ./controlador e 13 50 0

Este comando inicia o controlador indicando que o jogador que começa é
o 'e', a partida terá 50 movimentos e não há limite de tempo para as
jogadas. Para mais detalhes sobre os parâmetros do controlador
execute:

   $ ./controlador

Para conectar duas instâncias do exemplo2 ao controlador, uma de cada
lado do campo, execute em outros dois terminais os comandos:

   $ ./exemplo2 e

   $ ./exemplo2 d

Você pode testar o seu jogador jogando interativamente contra ele
usando o exemplo2. Basta executar o seu jogador em um terminal e o
exemplo2 em outro.
