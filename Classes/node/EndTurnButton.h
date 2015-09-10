//
//  EndTurnButton.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#ifndef __SurvivalDungeon__EndTurnButton__
#define __SurvivalDungeon__EndTurnButton__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class EndTurnButton : public cocos2d::ui::Button {
public:
  CREATE_FUNC(EndTurnButton);
  virtual bool init();
  
private:
  void _handleButtonTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
};

#endif /* defined(__SurvivalDungeon__EndTurnButton__) */
