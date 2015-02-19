//
//  MonsterDiceFaceBuilder.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "MonsterDiceFaceBuilder.h"

#include "Monster.h"
#include "MonsterDiceFace.h"

USING_NS_CC;

DiceFace* MonsterDiceFaceBuilder::diceFace(ValueMap &map)
{
    auto face = MonsterDiceFace::create();
    face->setImageName(map.at("image").asString());
    face->setMonster(this->monsterFrom(map));
    return face;
}

#pragma mark - Private Interface

Monster* MonsterDiceFaceBuilder::monsterFrom(ValueMap &map)
{
    auto monster = Monster::create();
    monster->setName(map.at("name").asString());
    monster->setKind(map.at("kind").asString());
    monster->setAttack(map.at("attack").asInt());
    monster->setDefense(map.at("defense").asInt());
    monster->setXp(map.at("xp").asInt());
    monster->setSpecials(map.at("specials").asValueVector());
    
    return monster;
}