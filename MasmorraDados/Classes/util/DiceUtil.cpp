//
//  DiceUtil.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#include "DiceUtil.h"

#include "Images.h"

#include "Dice.h"

USING_NS_CC;

#pragma mark - Public Interface

bool DiceUtil::isBootDice(Dice *dice) {
  return _isWhatDice(dice, IMG_DICE_ACTION_BOOT);
}

bool DiceUtil::isMagicDice(Dice *dice) {
  return _isWhatDice(dice, IMG_DICE_ACTION_MAGIC);
}

bool DiceUtil::isSwordDice(Dice *dice) {
  return _isWhatDice(dice, IMG_DICE_ACTION_SWORD);
}

bool DiceUtil::isShieldDice(Dice *dice) {
  return _isWhatDice(dice, IMG_DICE_ACTION_SHIELD);
}

bool DiceUtil::isBowDice(Dice *dice) {
  return _isWhatDice(dice, IMG_DICE_ACTION_BOW);
}

bool DiceUtil::isHealDice(Dice *dice) {
  return _isWhatDice(dice, IMG_DICE_ACTION_HEAL);
}

bool DiceUtil::isSwordAndShieldDice(Dice* dice) {
  return _isWhatDice(dice, IMG_DICE_ACTION_SWORD_AND_SHIELD);
}

#pragma mark - Private Interface

bool DiceUtil::_isWhatDice(Dice *dice, std::string imagePath) {
  return dice->getSelectedFace()->getImagePath() == imagePath;
}