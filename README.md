# README #

**Visão Geral**

O ‘Game of Life’ é um autómato celular desenvolvido pelo matemático britânico John Horton Conway em 1970 É o exemplo mais bem conhecido de autômato celular.

O jogo foi criado de modo a reproduzir, através de regras simples, as alterações e mudanças em grupos de seres vivos, tendo aplicações em diversas áreas da ciência.

As regras definidas são aplicadas a cada nova "geração"; assim, a partir de uma imagem em um tabuleiro bi-dimensional definida pelo jogador, percebem-se mudanças muitas vezes inesperadas e belas a cada nova geração, variando de padrões fixos a caóticos.

Este projeto tem como objetivo implementar o ‘Game of Life’ na linguagem de programação C++ de forma a aplicar os conceitos que envolvem orientação a objetos, estruturação de projetos e uso da plataforma SFML aprendidos em sala de aula.

Definição retirada da wikpedia.


**Membros da equipe**

Igor A. Brandão e Leandro Antonio F. da Silva


**Como compilar**

Use o makefile digitando o comando 'make' pelo terminal, após ter navegado para a pasta do projeto.


**Informações adicionais**

Buscamos utilizar uma estrutura mais rebuscada para o jogo como um todo, realizando o gerenciamento da plataforma em classes responsáveis por gerenciar elementos distintos do jogo, separadas da seguinte maneira:

Animation.h => Gerencia os efeitos de transição entre tela (fade, scroll, zoom).
ConfigScreen.h => Trata os elementos visuais do jogo, assim como a atualização destes.
FadeAnimation.h => Classe responsável pelo efeito fade.
FileManager.h => Gerencia a manipulação de arquivos (leitura das configurações).
GameScreen.h => Lida com instâncias genéricas e reutilizáveis do projeto.
InputManager.h => Gerencia eventos de entrada de teclado e outros periféricos.
LifeScreen.h (Principal) => Trata os elementos que envolvem a mecânica da simulação.
MenuManager.h => Gera o menu do jogo de acordo com o arquivo de configuração.
ScreenManager.h => Principal classe do jogo que gerencia a criação de todas as telas através do método AddScreen com GetInstance.
SplashScreen.h => Cria a apresentação inicial do jogo.
TitleScreen.h => Tela base que através do MenuManager faz a geração do menu inicial.