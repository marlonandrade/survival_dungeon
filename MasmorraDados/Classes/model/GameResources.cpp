//
//  GameResources.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 21/02/2015.
//
//

#include "GameResources.h"

#include "Character.h"

USING_NS_CC;

#pragma mark - Public Interface

void GameResources::loadResources() {
  this->loadAudio();
  this->loadCharacters();
  this->loadDices();
  this->loadDungeonRooms();
  this->loadMonsters();
}

#pragma mark - Private Interface

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
      
      characters[characterKey] = Character::createWithValueMap(properties);
    }
  }
  
  this->setCharacters(characters);
}

void GameResources::loadDices() {
}

void GameResources::loadDungeonRooms() {
}

void GameResources::loadMonsters() {
}