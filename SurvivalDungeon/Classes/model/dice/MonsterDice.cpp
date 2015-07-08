//
//  MonsterDice.cpp
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 5/3/15.
//
//

#include "MonsterDice.h"

#include "Definitions.h"
#include "Events.h"
#include "Images.h"
#include "NodeNames.h"

#include "MonsterDiceFace.h"

#include "MonsterKilledData.h"

#include "Game.h"
#include "PlayerTurn.h"

#include "DungeonRoomSprite.h"

#include "FileUtil.h"
#include "PositionUtil.h"

USING_NS_CC;

#pragma mark - Getter

int MonsterDice::getHitPoints() {
  return _hitPoints;
}

#pragma mark - Setter

void MonsterDice::setHitPoints(int hitPoints) {
  auto face = (MonsterDiceFace*) this->getSelectedFace();
  auto maxHitPoints = face->getDefense();
  if (hitPoints > maxHitPoints) hitPoints = maxHitPoints;
  
  _hitPoints = hitPoints;
  
  auto sprite = this->getSprite();
  if (sprite) {
    auto damageDealtSprite = sprite->getChildByName(DAMAGE_DEALT_SPRITE_NAME);
    if (damageDealtSprite) {
      damageDealtSprite->removeFromParent();
    }
    
    int damage = maxHitPoints - hitPoints;
    if (damage > 0) {
      damageDealtSprite = FileUtil::getInstance()->damageDealtSprite(damage);
      damageDealtSprite->setName(DAMAGE_DEALT_SPRITE_NAME);
      
      auto size = sprite->getContentSize() - Size(2, 2);
      damageDealtSprite->setPosition(Vec2(size));
      
      sprite->addChild(damageDealtSprite);
      
      if (damage >= maxHitPoints) {
        auto data = MonsterKilledData::create();
        data->setMonsterDice(this);
        
        auto dispatcher = Director::getInstance()->getEventDispatcher();
        dispatcher->dispatchCustomEvent(EVT_MONSTER_KILLED, data);
        
        auto game = Game::getInstance();
        auto dungeon = game->getDungeon();
        
        auto dungeonRoomSprite = (DungeonRoomSprite*) sprite->getParent();
        auto coordinate = PositionUtil::coordinateForPosition(dungeonRoomSprite->getPosition());
        auto dungeonRoom = dungeon->getRoomForCoordinate(coordinate);
        
        auto removeAnimation = Spawn::create(ScaleTo::create(0.3, 0),
                                             RotateBy::create(0.3, 180),
                                             NULL);
        auto cleanup = CallFunc::create([=]{
          sprite->removeFromParent();
          dungeonRoom->removeMonsterDice(this);
          dungeonRoomSprite->adjustChildren();
          
          if (this->getRangedCombat()) {
            auto damageTaken = game->getDamageTaken() - face->getAttack();
            game->setDamageTaken(damageTaken);
          }
          
          if (dungeonRoom->getMonsters().size() == 0) {
            game->resolveCombat();
          }
        });
        
        auto sequence = Sequence::create(removeAnimation,
                                         cleanup, NULL);
        
        sprite->runAction(sequence);
      }
    }
  }
}

#pragma mark - Public Interface

void MonsterDice::takeDamage(int damage, CombatMode combatMode) {
  this->setHitPoints(this->getHitPoints() - damage);
  
  auto rangedCombat = this->getRangedCombat() && combatMode == CombatModeRanged;
  this->setRangedCombat(rangedCombat);
}

void MonsterDice::resetLife() {
  auto face = (MonsterDiceFace*) this->getSelectedFace();
  this->setHitPoints(face->getDefense());
  this->setRangedCombat(true);
}

void MonsterDice::roll() {
  Dice::roll();
  this->resetLife();
}
