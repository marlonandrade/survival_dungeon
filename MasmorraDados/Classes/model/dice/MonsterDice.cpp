//
//  MonsterDice.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 5/3/15.
//
//

#include "MonsterDice.h"

#include "MonsterDiceFace.h"

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
    if (hitPoints < 1) {
      log("mórreu");
    } else {
      log("colocar sprite da dano no bichim");
    }
  }
}

#pragma mark - Public Interface

void MonsterDice::takeDamage(int damage, CombatMode combatMode) {
  this->setHitPoints(this->getHitPoints() - damage);
}

void MonsterDice::resetLife() {
  auto face = (MonsterDiceFace*) this->getSelectedFace();
  this->setHitPoints(face->getDefense());
  this->setMeleeCombat(CombatModeMelee);
}