//
//  CommonDiceDragHandler.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#ifndef __MasmorraDados__CommonDiceDragHandler__
#define __MasmorraDados__CommonDiceDragHandler__

class ActionDiceDragData;
class Dice;

#include "GameObject.h"

class CommonDiceDragHandler : public GameObject {
public:
  CREATE_FUNC(CommonDiceDragHandler);
  
  void dragStarted(ActionDiceDragData* data, cocos2d::Layer* layer,
                   cocos2d::Node* dockableContainer,
                   cocos2d::Vector<cocos2d::Node*> dockableNodes);
  
  void dragMoved(ActionDiceDragData* data, cocos2d::Layer* layer,
                 cocos2d::Node* dockableContainer,
                 cocos2d::Vector<cocos2d::Node*> dockableNodes);
  
  bool dragEnded(ActionDiceDragData* data, cocos2d::Layer* layer,
                 cocos2d::Node* dockableContainer,
                 cocos2d::Vector<cocos2d::Node*> dockableNodes);
};

#endif /* defined(__MasmorraDados__CommonDiceDragHandler__) */
