//
//  DiceDragHandlerFactory.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/18/15.
//
//

#ifndef __MasmorraDados__DiceDragHandlerFactory__
#define __MasmorraDados__DiceDragHandlerFactory__

#include "cocos2d.h"

class CommonDiceDragHandler;
class Dice;

class DiceDragHandlerFactory : public cocos2d::Ref {
public:
  static CommonDiceDragHandler* getHandler(Dice* dice);
};

#endif /* defined(__MasmorraDados__DiceDragHandlerFactory__) */
