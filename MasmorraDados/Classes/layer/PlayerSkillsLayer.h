//
//  PlayerSkillsLayer.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/27/15.
//
//

#ifndef __MasmorraDados__PlayerSkillsLayer__
#define __MasmorraDados__PlayerSkillsLayer__

#include "cocos2d.h"

class PlayerSkillsLayer : public cocos2d::Layer {
public:
  CREATE_FUNC(PlayerSkillsLayer);
  virtual bool init();
  
  cocos2d::Vector<Node*> getDockableNodes();
private:
  void _setupFreeBootSymbol();
  void _setupDockableDice();
  
  cocos2d::Node* _getDockContainer();
};

#endif /* defined(__MasmorraDados__PlayerSkillsLayer__) */
