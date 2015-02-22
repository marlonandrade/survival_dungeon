//
//  GameResources.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 21/02/2015.
//
//

#ifndef __MasmorraDados__GameResources__
#define __MasmorraDados__GameResources__

class Character;

typedef std::unordered_map<std::string, Character*> CharacterMap;

class GameResources {
public:
  static GameResources& getInstance() {
    static GameResources instance;
    return instance;
  }
  void loadResources();
private:
  GameResources() {};
  
  GameResources(GameResources const&)  = delete;
  void operator=(GameResources const&) = delete;
  
  void loadAudio();
  void loadCharacters();
  void loadDungeonRooms();
  void loadMonsters();
  
  CC_SYNTHESIZE(CharacterMap, characters, Characters);
};

#endif /* defined(__MasmorraDados__GameResources__) */
