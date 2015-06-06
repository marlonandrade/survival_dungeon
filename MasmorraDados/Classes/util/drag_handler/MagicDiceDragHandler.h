//
//  MagicDiceDragHandler.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#ifndef __MasmorraDados__MagicDiceDragHandler__
#define __MasmorraDados__MagicDiceDragHandler__

#include "CommonDiceDragHandler.h"

class MagicDiceDragHandler : public CommonDiceDragHandler {
public:
  CREATE_FUNC(MagicDiceDragHandler);
  
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

#endif /* defined(__MasmorraDados__MagicDiceDragHandler__) */
