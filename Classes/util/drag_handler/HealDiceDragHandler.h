//
//  HealDiceDragHandler.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/18/15.
//
//

#ifndef __SurvivalDungeon__HealDiceDragHandler__
#define __SurvivalDungeon__HealDiceDragHandler__

#include "CommonDiceDragHandler.h"

class HealDiceDragHandler : public CommonDiceDragHandler {
public:
  CREATE_FUNC(HealDiceDragHandler);
  
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

#endif /* defined(__SurvivalDungeon__HealDiceDragHandler__) */
