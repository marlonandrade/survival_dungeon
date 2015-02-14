# Cocos2d-x

Game engine open-source iniciada em 2010 para produção de jogos multiplataformas.  
API em C++ moderna.
Uma game engine é um software que provê funcionalidades comuns a todos jogos, basicamente o mesmo conceito que um framework.  
Todos os jogos possuem vários aspectos em comum, como um renderizador, gráficos 2d ou 3d, detecção de colisão, física, audio, suporte a input (controles), animações entre outros.  
Engines normalmente são multiplataformas permitindo desenvolver o jogo somente uma vez e distribuir para várias plataformas com pouco trabalho, a engine abstrai o hardware e APIs de cada uma das plataformas.  

## Conceitos

### Diretor (Director)

Responsável pela transição de cenas (Scenes).  
Controla qual cena está sendo exibida.  
Analogia com um diretor de um filme.

### Cena (Scene)

Responsável por separar partes do jogo.  
É um container para `Sprites`, `Labels`, `Nodes` e outros objetos que o jogo precisa.  
Responsável por executar a lógica do jogo e renderizar o conteúdo em cada frame.  
É preciso pelo menos uma Cena para iniciar o jogo.  
Exemplos: cena de menu inicial, cena de jogo, cena de fim de jogo, cena de placar.

### Grafo de cenas (Scene Graph)

Estrutura de dados que organiza a cena.  
Contém vários Nós em uma estrutura de árvore.  
Estrutura percorrida pelo Renderizador utilizando algorito InOrdem (referenciar algoritmo - primeiro percorre o nó filho a esquerda, depois o nó raiz e em seguida o nó filho a direita) para renderizar cada um dos nós da árvore.  
Pensar que nós à direita serão desenhados por último, portanto sendo exibidos acima dos nós à esquerda (z-order).  

### Sprite (Sprite)

Imagem 2d que pode ser animada ou transformada modificando suas propriedades.  
Pode ser criado a partir de um arquivo de imagem.  
Personagens, por exemplo, provavelmente são Sprites.  
Qualquer objeto que se 'mova' é um Sprite.

### Planilha de Sprites (Sprite Sheet)

Forma de combinar vários sprites em somente um arquivo.  
Utilizado para reduzir consumo de memória, tamanho de arquivos e tempo de carregamento.  
Além disto há um ganho de performance pois diminui a quantidade de chamadas de desenho.  
Uma panilha de sprites basicamente é um arquivo de imagem com todos os sprites e um outro arquivo que define os tamanhos e posições de cada um deles.  
Juntar todas imagens em uma panilha de sprites manualmente é um processo entediante, portanto, existem algumas ferramentas que auxiliam nesse processo (Cocos Studio, Texture Packer, Zwoptex).

### Nó (Node)

Objetos que não se movem.  
Como título do jogo na cena de início, obstáculos imóveis em uma fase, etc.  
Além disto, todos os outros objetos se comportam também como Nós, porém possuem mais comportamento (herança).  

### Ponto de âncora (Anchor Point)

Todo nó possui um valor para o ponto de âncora.  
Um ponto que especifica qual parte do nó/sprite será usado como referência para posicionamento.  
Interfere somente em propriedades que podem ser transformadas, isso inclui: position (posição), scale (escala), rotation (rotação) e skew (torção) e exclui: color (cor) e opacity (opacidade).  
Sistema de coordenada usado é esquerda/baixo.  Pontos entre 0 e 1. Sendo 0 esquerda ou baixo e 1 direita ou cima.  
Valor default é (0.5, 0.5).

  (0, 0)     -> esquerda / baixo
  (0, 1)     -> esquerda / cima
  (0.5, 0.5) -> centro   / centro
  (1, 0)     -> direita  / baixo
  (1, 1)     -> direita  / cima

Por padrão é representado por um vetor de 2 posições com valores (0, 0) representando o canto esquerdo inferior. O valor máximo é (1, 1) que representa o canto direito superior.

Propriedades afetadas pelo Ponto de âncora:

* Position
* Rotation
* Scale
* Skew

#### Posição (Position)

Ponto de âncora é usado como referência para o ponto inicial de posicionamento.  
Referenciado por um Vetor de 2 posições (Vec2), normalmente utilizando referências (x, y) em um eixo cartesiano.  
Valor padrão é (0, 0).

#### Rotação (Rotation)

Modifica a rotação de um sprite uma quantidade de ângulos positiva ou negativa.  
Valores positivos rotacional o sprite em sentido horário, valores negativos modificam em sentido anti-horário.  
Valor padrão é 0.

#### Escala (Scale)

Modifica a escala de um sprite, seja de forma uniforme em x e y ou separadamente.  
Valor padrão é 1.0 tanto para x quanto y.

#### Torção (Skew)

Modifica a torção de um sprite, seja de forma uniforme em x e y ou separadamente.  
Valor padrão é 0.0 tanto para x quanto y.

Propriedades não afetadas pelo ponto de âncora:

* Color
* Opacity

#### Cor (Color)

Modifica a cor de um sprite. É configurado utilizando um objeto `Color3B` que representa valores RGB.  
Os valores RGB de cor são representandos por 3 bites com valores entre 0 e 255.  
RGB é o acrônimo de Red (Vermelho), Green (Verde) e Blue (Azul).

#### Opacidade (Opacity)

Modifica a opacidade de um sprite. Um objeto opaco possui nenhuma transparência.  
Expera um valor entre 0 e 255, onde 255 significa totalmente opaco e 0 totalmente transparente.  
"0 significa transparente".
Valor padrão é 2555 (totalmente opaco).

### Renderizador (Renderer)

Responsável por renderizar uma Scene Graph na tela.

### Ação (Action)

Responsável por permitir transformações de nós das cenas em um dado intervalo de tempo.  
Pode ser utilizado para mover um sprite de um ponto a outro, rotacionar um sprite, modificar o tamanho, etc.  
Estrutura fundamental para dar dinâmica a todos os jogos.  

Existem dois tipos para cada `Action`, um `By` e um `To`.  
Uma action `By` é relativa ao estado atual do nó, já uma action `To` é absoluta, ou seja, não considera o estado atual do nó.

### Sequencias (Sequence)

Permite realizar múltiplas ações em uma ordem específica.  

### Spawn

Permite realizar múltiplas ações ao mesmo tempo.

### Relação entre nós

Um nó possui relação de pai (parent) e filho (child).  
Todas propriedades modificadas em um nó pai se propaga também para os nós filhos (lembrar da estrutura da árvore).  


