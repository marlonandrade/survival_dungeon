//
//  GameResources.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 21/02/2015.
//
//

#include "GameResources.h"

#include "Character.h"
#include "Dungeon.h"
#include "DungeonFloor.h"

USING_NS_CC;

#pragma mark - Public Interface

void GameResources::loadResources() {
  this->initializeEnumMaps();
  this->loadAudio();
  this->loadCharacters();
  this->loadDungeonRooms();
  this->loadMonsters();
}

Dungeon* GameResources::dungeonFor(int numberOfPlayers) {
  auto dungeon = Dungeon::create();
  
  auto firstFloor = DungeonFloor::create();
  firstFloor->setRooms(this->firstFloorRooms(numberOfPlayers));
  dungeon->setFirstFloor(firstFloor);
  
  auto secondFloor = DungeonFloor::create();
  secondFloor->setRooms(this->secondFloorRooms(numberOfPlayers));
  dungeon->setSecondFloor(secondFloor);
  
  return dungeon;
}

#pragma mark - Private Interface

void GameResources::initializeEnumMaps() {
  EffectTypeMap effectTypeMap;
  
  effectTypeMap["damage_adjacent"] =   EffectType::DAMAGE_ADJACENT;
  effectTypeMap["teleport"] =          EffectType::TELEPORT;
  effectTypeMap["monster_lvl1"] =      EffectType::MONSTER_LVL1;
  effectTypeMap["monster_lvl2"] =      EffectType::MONSTER_LVL2;
  effectTypeMap["monster_lvl1_lvl2"] = EffectType::MONSTER_LVL1_LVL2;
  effectTypeMap["treasure_1_coin"] =   EffectType::TREASURE_1_COIN;
  effectTypeMap["treasure_2_coin"] =   EffectType::TREASURE_2_COIN;
  effectTypeMap["down_floor"] =        EffectType::DOWN_FLOOR;
  effectTypeMap["up_floor"] =          EffectType::UP_FLOOR;
  effectTypeMap["spider_web"] =        EffectType::SPIDER_WEB;
  effectTypeMap["take_1_damage"] =     EffectType::TAKE_1_DAMAGE;
  effectTypeMap["discard_1_card"] =    EffectType::DICARD_1_CARD;
  effectTypeMap["heal_2"] =            EffectType::HEAL_2;
  effectTypeMap["custom_pit"] =        EffectType::CUSTOM_PIT;
  
  this->setEffectTypeMap(effectTypeMap);
  
  EffectKindMap effectKindMap;
  effectKindMap["pre_action"] = EffectKind::PRE_ACTION;
  effectKindMap["optional"] =   EffectKind::OPTIONAL;
  effectKindMap["pos_action"] = EffectKind::POS_ACTION;
  
  this->setEffectKindMap(effectKindMap);
}

void GameResources::loadAudio() {
  // todo: carregar audio
}

void GameResources::loadCharacters() {
  CharacterMap characters;
  
  auto gameModes = FileUtils::getInstance()->getValueMapFromFile("res/characters.plist");
  for (auto gameMode : gameModes) {
    auto gameModeType = std::get<0>(gameMode);
    auto charactersMap = std::get<1>(gameMode).asValueMap();
    
    for (auto characterMap : charactersMap) {
      auto characterKey = std::get<0>(characterMap);
      auto properties = std::get<1>(characterMap).asValueMap();
      
      auto character = Character::createWithValueMap(properties);
      character->retain();
      
      characters[characterKey] = character;
    }
  }
  
  this->setCharacters(characters);
}

void GameResources::loadDungeonRooms() {
  auto dungeonInfo = FileUtils::getInstance()->getValueMapFromFile("res/dungeon.plist");
  
  DungeonMap dungeonMap;
  
  for (auto floorInfo : dungeonInfo) {
    auto floorKey = std::get<0>(floorInfo);
    auto noPlayersRooms = std::get<1>(floorInfo).asValueMap();
    
    DungeonFloorMap floorMap;
    
    for (auto noPlayersInfo : noPlayersRooms) {
      auto noPlayerKey = std::get<0>(noPlayersInfo);
      auto roomsData = std::get<1>(noPlayersInfo).asValueVector();
      
      Vector<DungeonRoom*> rooms;
      
      for (auto roomData : roomsData) {
        auto room = DungeonRoom::create();
        
        // criar room
      }
      
      floorMap[noPlayerKey] = rooms;
    }
    
    dungeonMap[floorKey] = floorMap;
  }
  
  this->setDungeonMap(dungeonMap);
}

void GameResources::loadMonsters() {
}

Vector<DungeonRoom*> GameResources::firstFloorRooms(int numberOfPlayers) {
  auto firstFloorMap = this->getDungeonMap().at("floor_1");
  return this->roomsFor(numberOfPlayers, firstFloorMap);
}

Vector<DungeonRoom*> GameResources::secondFloorRooms(int numberOfPlayers) {
  auto firstFloorMap = this->getDungeonMap().at("floor_2");
  return this->roomsFor(numberOfPlayers, firstFloorMap);
}

Vector<DungeonRoom*> GameResources::roomsFor(int numberOfPlayers, DungeonFloorMap floorMap) {
  Vector<DungeonRoom*> rooms;
  
  switch (numberOfPlayers) {
    case 5:
      rooms.pushBack(floorMap.at("5 players"));
    case 1:
    case 4:
      rooms.pushBack(floorMap.at("4 players"));
    case 3:
      rooms.pushBack(floorMap.at("3 players"));
    case 2:
      rooms.pushBack(floorMap.at("2 players"));
      break;
  }
  
  return rooms;
}