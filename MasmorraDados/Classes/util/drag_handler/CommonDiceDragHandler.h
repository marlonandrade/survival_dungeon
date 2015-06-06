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
class DockableContainer;

#include "GameObject.h"

class CommonDiceDragHandler : public GameObject {
public:
  CREATE_FUNC(CommonDiceDragHandler);
  
  virtual void dragStarted(ActionDiceDragData* data,
                           cocos2d::Layer* layer,
                           DockableContainer* dockableContainer);
  
  virtual void dragMoved(ActionDiceDragData* data,
                         cocos2d::Layer* layer,
                         DockableContainer* dockableContainer);
  
  virtual bool dragEnded(ActionDiceDragData* data,
                         cocos2d::Layer* layer,
                         DockableContainer* dockableContainer);
};

#endif /* defined(__MasmorraDados__CommonDiceDragHandler__) */
