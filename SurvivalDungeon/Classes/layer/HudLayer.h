//
//  HudLayer.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/24/15.
//
//

#ifndef __SurvivalDungeon__HudLayer__
#define __SurvivalDungeon__HudLayer__

#include "cocos2d.h"

class HudLayer : public cocos2d::Layer {
public:
  CREATE_FUNC(HudLayer);
  bool init();
  
  void adjustLevel(int level);
  void adjustXp(int xp);
  void adjustCoins(int coins);
private:
  void _setupChildren();
  
  cocos2d::Label* _getLevelLabel();
  cocos2d::Label* _getXpLabel();
  cocos2d::Label* _getCoinsLabel();
  
  std::string _append(std::string base, int number);
};

#endif /* defined(__SurvivalDungeon__HudLayer__) */
