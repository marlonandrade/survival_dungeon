//
//  Player.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __SurvivalDungeon__Player__
#define __SurvivalDungeon__Player__

#include "GameObject.h"

#include "Character.h"

class Player : public GameObject {
  CC_SYNTHESIZE_RETAIN(Character*, _character, Character);
  CREATE_FUNC(Player);
  virtual bool init();
};

#endif /* defined(__SurvivalDungeon__Player__) */
