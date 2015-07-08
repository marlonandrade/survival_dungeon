//
//  AttackDiceDragHandler.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/27/15.
//
//

#ifndef __SurvivalDungeon__AttackDiceDragHandler__
#define __SurvivalDungeon__AttackDiceDragHandler__

#include "CommonDiceDragHandler.h"

class AttackDiceDragHandler : public CommonDiceDragHandler {
public:
  CREATE_FUNC(AttackDiceDragHandler);
  
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

#endif /* defined(__SurvivalDungeon__AttackDiceDragHandler__) */
