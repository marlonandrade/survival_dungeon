//
//  DockableContainer.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#ifndef __SurvivalDungeon__DockableContainer__
#define __SurvivalDungeon__DockableContainer__

#include "cocos2d.h"

class DockableContainer : public cocos2d::Node {
public:
  CREATE_FUNC(DockableContainer);
  virtual bool init();
  
  void resetDockableNodes();
  
  cocos2d::Vector<Node*> getDockableNodes();
  
private:
  void _setupChildren();
};

#endif /* defined(__SurvivalDungeon__DockableContainer__) */
