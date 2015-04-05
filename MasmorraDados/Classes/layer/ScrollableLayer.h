//
//  ScrollableLayer.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/5/15.
//
//

#ifndef __MasmorraDados__ScrollableLayer__
#define __MasmorraDados__ScrollableLayer__

#include "cocos2d.h"

#include "Dungeon.h"

class ScrollableLayer : public cocos2d::Layer {
  CC_SYNTHESIZE_RETAIN(Dungeon*, _dungeon, Dungeon);
  
public:
  static ScrollableLayer* createWithDungeon(Dungeon* dungeon);
  virtual bool initWithDungeon(Dungeon* dungeon);
private:
  void _setupTouchListener();
  
  bool _onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
  void _onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif /* defined(__MasmorraDados__ScrollableLayer__) */
