//
//  ScrollableDungeonLayer.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 4/5/15.
//
//

#ifndef __SurvivalDungeon__ScrollableDungeonLayer__
#define __SurvivalDungeon__ScrollableDungeonLayer__

#include "cocos2d.h"

class DungeonLayer;

class ScrollableDungeonLayer : public cocos2d::Layer {
public:
  CREATE_FUNC(ScrollableDungeonLayer);
  virtual bool init();
  
  void resetDungeonLayer();
private:
  void _setupChildren();
  void _setupTouchListener();
  
  DungeonLayer* _getDungeonLayer();
  
  bool _onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
  void _onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif /* defined(__SurvivalDungeon__ScrollableDungeonLayer__) */
