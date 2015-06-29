//
//  MonsterDice.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 5/3/15.
//
//

#include "MonsterDice.h"

#include "Definitions.h"

#include "MonsterDiceFace.h"

#include "Game.h"

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
    int damageTaken = maxHitPoints - hitPoints;
    if (damageTaken > 0) {
      if (damageTaken < maxHitPoints) {
        log("colocar sprite de dano");
      } else {
        log("mórreu");
        
        if (!this->getMeleeCombat()) {
          log("remover o dano tomado por esse monstro");
          auto game = Game::getInstance();
          game->setDamageTaken(-face->getAttack());
        }
      }
    } else {
      log("remove sprite de dano");
    }
  }
}

#pragma mark - Public Interface

void MonsterDice::takeDamage(int damage, CombatMode combatMode) {
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