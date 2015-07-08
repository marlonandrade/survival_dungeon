//
//  CommonDiceDragHandler.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#ifndef __SurvivalDungeon__CommonDiceDragHandler__
#define __SurvivalDungeon__CommonDiceDragHandler__

class ActionDiceDragData;
class Dice;
class DockableContainer;
class GameplayLayer;

#include "GameObject.h"

class CommonDiceDragHandler : public GameObject {
public:
  CREATE_FUNC(CommonDiceDragHandler);
  
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

#endif /* defined(__SurvivalDungeon__CommonDiceDragHandler__) */
