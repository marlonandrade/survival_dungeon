//
//  DiceUtil.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#ifndef __MasmorraDados__DiceUtil__
#define __MasmorraDados__DiceUtil__

#include "cocos2d.h"

class Dice;

class DiceUtil {
public:
  static bool isBootDice(Dice* dice);
  static bool isMagicDice(Dice* dice);
  static bool isSwordDice(Dice* dice);
  static bool isShieldDice(Dice* dice);
  static bool isBowDice(Dice* dice);
  static bool isHealDice(Dice* dice);
  static bool isSwordAndShieldDice(Dice* dice);
  
private:
  static bool _isWhatDice(Dice* dice, std::string imagePath);
};

#endif /* defined(__MasmorraDados__DiceUtil__) */
