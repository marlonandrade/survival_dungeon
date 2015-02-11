# Cocos2d-x

Game engine open-source iniciada em 2010 para produção de jogos multiplataformas.  
API em C++ moderna.
Uma game engine é um software que provê funcionalidades comuns a todos jogos, basicamente o mesmo conceito que um framework.  
Todos os jogos possuem vários aspectos em comum, como um renderizador, gráficos 2d ou 3d, detecção de colisão, física, audio, suporte a input (controles), animações entre outros.  
Engines normalmente são multiplataformas permitindo desenvolver o jogo somente uma vez e distribuir para várias plataformas com pouco trabalho, a engine abstrai o hardware e APIs de cada uma das plataformas.  

## Conceitos

* Director
* Scene
* Node

### Diretor (Director)

Responsável pela transição de cenas (Scenes).  
Controla qual cena está sendo exibida.  
Analogia com um diretor de um filme.

### Cena (Scene)

Responsável por separar partes do jogo.  
Exemplos: cena de menu inicial, cena de jogo, cena de fim de jogo, cena de placar.

### Grafo de cenas (Scene Graph)

Estrutura de dados que organiza a cena.  
Contém vários Nós em uma estrutura de árvore.  
Estrutura percorrida pelo Renderizador utilizando algorito InOrdem (referenciar algoritmo - primeiro percorre o nó filho a esquerda, depois o nó raiz e em seguida o nó filho a direita) para renderizar cada um dos nós da árvore.  
Pensar que nós à direita serão desenhados por último, portanto sendo exibidos acima dos nós à esquerda (z-order).  

### Sprite (Sprite)

Objetos que se movem na tela. Podem ser manipulados.  
Personagens, por exemplo, provavelmente são Sprites.  
Qualquer objeto que se 'mova' é um Sprite.

### Nó (Node)

Objetos que não se movem.  
Como título do jogo na cena de início, obstáculos imóveis em uma fase, etc.  
Além disto, todos os outros objetos se comportam também como Nós, porém possuem mais comportamento (herança).  

### Ponto de âncora (Anchor Point)

Todo nó possui um valor para o ponto de âncora.  
Um ponto que especifica qual parte do nó/sprite será usado como referência para posicionamento.  
Por padrão é representado por um vetor de 2 posições com valores (0, 0) representando o canto esquerdo inferior. O valor máximo é (1, 1) que representa o canto direito superior.

### Renderizador (Renderer)

Responsável por renderizar uma Scene Graph na tela.

### Ação (Action)

Responsável por permitir transformações de nós das cenas em um dado intervalo de tempo.  
Pode ser utilizado para mover um sprite de um ponto a outro, rotacionar um sprite, modificar o tamanho, etc.  
Estrutura fundamental para dar dinâmica a todos os jogos.  

### Sequencias (Sequence)

Permite realizar múltiplas ações em uma ordem específica.  

### Spawn

Permite realizar múltiplas ações ao mesmo tempo.

### Relação entre nós

Um nó possui relação de pai (parent) e filho (child).  
Todas propriedades modificadas em um nó pai se propaga também para os nós filhos (lembrar da estrutura da árvore).  



