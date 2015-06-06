//
//  ShieldDiceDragHandler.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/6/15.
//
//

#ifndef __MasmorraDados__ShieldDiceDragHandler__
#define __MasmorraDados__ShieldDiceDragHandler__

#include "CommonDiceDragHandler.h"

class ShieldDiceDragHandler : public CommonDiceDragHandler {
public:
  CREATE_FUNC(ShieldDiceDragHandler);
  
  virtual void dragStarted(ActionDiceDragData* data,
                           GameplayLayer* layer,
                           DockableContainer* dockableContainer);
  
  virtual void dragMoved(ActionDiceDragData* data,
                         GameplayLayer* layer,
                         DockableContainer* dockableContainer);
  
  virtual bool dragEnded(ActionDiceDragData* data,
                         GameplayLayer* layer,
                         DockableContainer* dockableContainer);
};

#endif /* defined(__MasmorraDados__ShieldDiceDragHandler__) */
