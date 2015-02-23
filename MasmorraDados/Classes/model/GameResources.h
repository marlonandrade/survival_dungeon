//
//  GameResources.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 21/02/2015.
//
//

#ifndef __MasmorraDados__GameResources__
#define __MasmorraDados__GameResources__

#include "DungeonRoom.h"

#include "EffectType.h"
#include "EffectKind.h"

class Character;
class Dungeon;

typedef std::unordered_map<std::string, Character*> CharacterMap;

// description:            no players   rooms
typedef std::unordered_map<std::string, cocos2d::Vector<DungeonRoom*> > DungeonFloorMap;
// description:            floor number
typedef std::unordered_map<std::string, DungeonFloorMap> DungeonMap;

typedef std::unordered_map<std::string, EffectType> EffectTypeMap;
typedef std::unordered_map<std::string, EffectKind> EffectKindMap;

class GameResources {
  CC_SYNTHESIZE(CharacterMap, _characters, Characters);
  CC_SYNTHESIZE(DungeonMap, _dungeonMap, DungeonMap);
  CC_SYNTHESIZE(EffectTypeMap, _effectTypeMap, EffectTypeMap);
  CC_SYNTHESIZE(EffectKindMap, _effectKindMap, EffectKindMap);
  
public:
  static GameResources& getInstance() {
    static GameResources instance;
    return instance;
  }
  void loadResources();
  
  Dungeon* dungeonFor(int numberOfPlayers);
private:
  GameResources() {};
  
  GameResources(GameResources const&)  = delete;
  void operator=(GameResources const&) = delete;
  
  void initializeEnumMaps();
  void loadAudio();
  void loadCharacters();
  void loadDungeonRooms();
  void loadMonsters();
  
  cocos2d::Vector<DungeonRoom*> firstFloorRooms(int numberOfPlayers);
  cocos2d::Vector<DungeonRoom*> secondFloorRooms(int numberOfPlayers);
  cocos2d::Vector<DungeonRoom*> roomsFor(int numberOfPlayers, DungeonFloorMap floorMap);
};

#endif /* defined(__MasmorraDados__GameResources__) */
