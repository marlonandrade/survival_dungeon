//
//  ScrollableDungeonLayer.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/5/15.
//
//

#ifndef __MasmorraDados__ScrollableDungeonLayer__
#define __MasmorraDados__ScrollableDungeonLayer__

#include "cocos2d.h"

class ScrollableDungeonLayer : public cocos2d::Layer {
public:
  CREATE_FUNC(ScrollableDungeonLayer);
  virtual bool init();
  
private:
  void _setupChildren();
  void _setupTouchListener();
  
  bool _onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
  void _onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif /* defined(__MasmorraDados__ScrollableDungeonLayer__) */
