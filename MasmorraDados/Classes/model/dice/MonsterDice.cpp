//
//  MonsterDice.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 5/3/15.
//
//

#include "MonsterDice.h"

#include "Definitions.h"
#include "Images.h"
#include "NodeNames.h"

#include "MonsterDiceFace.h"

#include "Game.h"

#include "FileUtil.h"

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
      auto fileName = FileUtil::damageDealtFileName(damage);
      damageDealtSprite = Sprite::create(fileName);
      damageDealtSprite->setName(DAMAGE_DEALT_SPRITE_NAME);
      
      auto size = sprite->getContentSize() - Size(2, 2);
      damageDealtSprite->setPosition(Vec2(size));
      
      sprite->addChild(damageDealtSprite);
      
      if (damage >= maxHitPoints) {
        log("mórreu");
        auto removeAnimation = Spawn::create(ScaleTo::create(0.3, 0),
                                             RotateBy::create(0.3, 180),
                                             NULL);
        auto remove = RemoveSelf::create();
        
        sprite->runAction(Sequence::create(removeAnimation, remove, NULL));
        
        if (!this->getMeleeCombat()) {
          auto game = Game::getInstance();
          game->setDamageTaken(-face->getAttack());
        }
      }
    }
  }
}

#pragma mark - Public Interface

void MonsterDice::takeDamage(int damage, CombatMode combatMode) {
  log("hp: %d taken: %d damage", this->getHitPoints(), damage);
  this->setHitPoints(this->getHitPoints() - damage);
  
  if (combatMode == CombatModeMelee) {
    this->setMeleeCombat(true);
  }
}

void MonsterDice::resetLife() {
  auto face = (MonsterDiceFace*) this->getSelectedFace();
  this->setHitPoints(face->getDefense());
  this->setMeleeCombat(false);
}