//
//  DiceFace.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 23/02/2015.
//
//

#ifndef __SurvivalDungeon__DiceFace__
#define __SurvivalDungeon__DiceFace__

#include "GameObject.h"

class Dice;

class DiceFace : public GameObject {
  CC_SYNTHESIZE(Dice*, _dice, Dice);
  CC_SYNTHESIZE(std::string, _imagePath, ImagePath);
public:
  static DiceFace* create(std::string imagePath);
  virtual bool init(std::string imagePath);
};

#endif /* defined(__SurvivalDungeon__DiceFace__) */
