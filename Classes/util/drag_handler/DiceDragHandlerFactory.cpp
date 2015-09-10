//
//  DiceDragHandlerFactory.cpp
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/18/15.
//
//

#include "Dice.h"

#include "AttackDiceDragHandler.h"
#include "CommonDiceDragHandler.h"
#include "HealDiceDragHandler.h"
#include "MagicDiceDragHandler.h"
#include "ShieldDiceDragHandler.h"

#include "DiceUtil.h"

#include "DiceDragHandlerFactory.h"

CommonDiceDragHandler* DiceDragHandlerFactory::getHandler(Dice* dice) {
  CommonDiceDragHandler* dragHandler;
  
  if (DiceUtil::isMagicDice(dice)) {
    dragHandler = MagicDiceDragHandler::create();
  } else if (DiceUtil::isShieldDice(dice)) {
    dragHandler = ShieldDiceDragHandler::create();
  } else if (DiceUtil::isHealDice(dice)) {
    dragHandler = HealDiceDragHandler::create();
  } else if (DiceUtil::isSwordDice(dice) ||
             DiceUtil::isBowDice(dice) ||
             DiceUtil::isSwordAndShieldDice(dice)) {
    dragHandler = AttackDiceDragHandler::create();
  } else {
    dragHandler = CommonDiceDragHandler::create();
  }
  
  return dragHandler;
}
