//
//  ActionDiceDragData.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/27/15.
//
//

#ifndef __MasmorraDados__ActionDiceDragData__
#define __MasmorraDados__ActionDiceDragData__

#include "GameObject.h"

#include "ActionDiceSprite.h"

class ActionDiceDragData : public GameObject {
  CC_SYNTHESIZE_RETAIN(ActionDiceSprite*, _sprite, Sprite);
  CC_SYNTHESIZE_RETAIN(cocos2d::Touch*, _touch, Touch);
public:
  CREATE_FUNC(ActionDiceDragData);
  
};

#endif /* defined(__MasmorraDados__ActionDiceDragData__) */
