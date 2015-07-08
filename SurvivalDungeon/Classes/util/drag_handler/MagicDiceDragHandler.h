//
//  MagicDiceDragHandler.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#ifndef __SurvivalDungeon__MagicDiceDragHandler__
#define __SurvivalDungeon__MagicDiceDragHandler__

#include "CommonDiceDragHandler.h"

class MagicDiceDragHandler : public CommonDiceDragHandler {
public:
  CREATE_FUNC(MagicDiceDragHandler);
  
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

#endif /* defined(__SurvivalDungeon__MagicDiceDragHandler__) */
