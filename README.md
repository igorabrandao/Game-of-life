# README #

**Visão Geral**

O ‘Hell in the Sky’ é um jogo em duas dimensões que tem como objetivo invadir a base inimiga, para isso terá que sobreviver e destruir os aviões e helicópteros inimigos. No fim do estágio, o herói enfrentará o chefão da tela que possuirá um hp (vida) maior do que a dos inimigos comuns. Uma vez que derrotar o chefão, o herói poderá libertar aviões aliados que estavam sendo mantidos como reféns pelos inimigos. A cada estágio o herói receberá um upgrade em seu hp e armamento, assim como a dificuldade do jogo também aumentará, através do número de naves inimigas e velocidade de ataque destas. Ao finalizar todas as fases, o herói vencerá o jogo ao resgatar todos os aliados que estão sendo feitos de reféns. O diferencial deste jogo está na dinâmica na qual o player resgatará os aviões aliados e o sistema de recompensa pelo desempenho. Além disso, durante o jogo elementos aleatórios como itens de força ou inimigos diferenciados surgirão para desequilibrar positivamente ou não a partida.

**Membros da equipe**

Igor A. Brandão
Leandro Antonio F. da Silva

**Como compilar**

Use o makefile digitando o comando 'make' pelo terminal, após ter navegado para a pasta do projeto.

**Informações adicionais**

Inicialmente buscamos utilizar uma estrutura mais rebuscada para o jogo como um todo, realizando o gerenciamento da plataforma em classes responsáveis por gerenciar elementos distintos do jogo, separadas da seguinte maneira:
Animation.h => Gerencia os efeitos de transição entre tela (fade, scroll, zoom)
FadeAnimation.h => Classe responsável pelo efeito fade
FileManager.h => Gerencia a manipulação de arquivos (leitura das configurações)
GameScreen.h => Lida com instâncias genéricas e reutilizáveis do projeto
InputManager.h => Gerencia eventos de entrada de teclado e outros periféricos
LevelScreen.h => Classe responsável por gerar as telas do jogo de acordo com os parâmetros de configuração (não terminada)
MenuManager.h => Gera o menu do jogo de acordo com o arquivo de configuração (devido ao segfault está estática)
ScreenManager.h => Principal classe do jogo que gerencia a criação de todas as telas através do método AddScreen com GetInstance
SoundManager.h => Gerenciamento dos áudios a serem reproduzidos, seja em buffer ou diretamente em arquivo
SplashScreen.h => Cria a apresentação inicial do jogo
TitleScreen.h => Tela base que através do MenuManager faz a geração do menu inicial
sllist.h => Classe responsável pela lista encadeada

**Considerações finais**

O jogo apesar de não estar pronto de acordo com o esperado, proporcionou uma grande escalada de conhecimento em termos da programação em si, além de estruturação de projetos com maior complexidade e também do SFML em si.