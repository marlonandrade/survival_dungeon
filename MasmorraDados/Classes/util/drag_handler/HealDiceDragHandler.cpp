//
//  HealDiceDragHandler.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/18/15.
//
//

#include "HealDiceDragHandler.h"

#include "Game.h"

USING_NS_CC;

#pragma mark - Public Interface

void HealDiceDragHandler::dragStarted(ActionDiceDragData* data,
                                      GameplayLayer* layer,
                                      DockableContainer* dockableContainer) {
  Vector<Node*> targetNodes;
  
  auto character = Game::getInstance()->getPlayer()->getCharacter();
//  if (!character->isLifeFull()) {
    log("PODE ARRASTAR");
//  }
}

void HealDiceDragHandler::dragMoved(ActionDiceDragData* data,
                                    GameplayLayer* layer,
                                    DockableContainer* dockableContainer) {
}

bool HealDiceDragHandler::dragEnded(ActionDiceDragData* data,
                                    GameplayLayer* layer,
                                    DockableContainer* dockableContainer) {
  return true;
}