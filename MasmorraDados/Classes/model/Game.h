//
//  Game.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 15/02/2015.
//
//

#ifndef __MasmorraDados__Game__
#define __MasmorraDados__Game__

class GameOptions;

class Game
{
private:
    GameOptions *_options;
public:
    Game();
    GameOptions& getOptions();
};

#endif /* defined(__MasmorraDados__Game__) */
