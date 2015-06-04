//
//  MagicDiceDragHandler.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#ifndef __MasmorraDados__MagicDiceDragHandler__
#define __MasmorraDados__MagicDiceDragHandler__

#include "GameObject.h"

class ActionDiceDragData;
class Dice;

class MagicDiceDragHandler : public GameObject {
public:
  CREATE_FUNC(MagicDiceDragHandler);
  
  void dragStarted(ActionDiceDragData* data, cocos2d::Layer* layer);
  void dragMoved(ActionDiceDragData* data, cocos2d::Layer* layer);
  void dragEnded(ActionDiceDragData* data, cocos2d::Layer* layer);
  
private:
  void _triggerEffectOnTarget(Dice* dice, cocos2d::Layer* layer);
};

#endif /* defined(__MasmorraDados__MagicDiceDragHandler__) */
