//
//  DungeonLayer.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 5/17/15.
//
//

#ifndef __MasmorraDados__DungeonLayer__
#define __MasmorraDados__DungeonLayer__

#include "cocos2d.h"

#include "CharacterMoveDelegate.h"
#include "MonsterRoomData.h"

class DungeonRoomSprite;

class DungeonLayer : public cocos2d::Layer, CharacterMoveDelegate {
  CC_SYNTHESIZE(cocos2d::Vector<cocos2d::Node*>, _interactableNodes, InteractableNodes);
  
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _lastTileHasBeenPlacedListener,
                       LastTileHasBeenPlacedListener);
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _monsterDiceGeneratedListener,
                       MonsterDiceGeneratedListener);
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _roomsPlacementsListener,
                       RoomsPlacementsListener);
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _monsterMovedListener,
                       MonsterMovedListener);
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _monstersFinishedMovingListener,
                       MonstersFinishedMovingListener);
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _monstersFinishedRisingListener,
                       MonstersFinishedRisingListener);
  
public:
  CREATE_FUNC(DungeonLayer);
  virtual bool init();
  
#pragma mark - CharacterMoveDelegate Methods
  virtual bool canCharacterMove();
  virtual void characterWillMove(CharacterDiceSprite* sprite);
  virtual void characterIsMovingToLocation(cocos2d::Vec2 location);
  virtual bool canCharacterMoveToLocation(cocos2d::Vec2 location);
  virtual void characterMovedToLocation(CharacterDiceSprite* sprite, cocos2d::Vec2 location);
  virtual void characterDidNotMove(CharacterDiceSprite* sprite);
  
private:
  cocos2d::Vector<MonsterRoomData*> _monsterRoomDatas;
  cocos2d::Vector<DungeonRoom*> _modifiedRooms;
  
  void _setupEventHandlers();
  
  void _consumeMonsterRoomDatas();
  void _moveMonsterSpriteToDestinationRoom(Node* monsterSprite, DungeonRoomSprite* destinationRoom);
  
  DungeonRoomSprite* _getRoomSpriteForCharacterCoordinate();
  DungeonRoomSprite* _getRoomSpriteForCoordinate(cocos2d::Vec2 coordinate);
  cocos2d::Vector<cocos2d::Node*> _getRoomSpritesForAdjacentCharacterCoordinate();
  
  void _resetCharacterMoveState();
  
#pragma mark - Event Handlers
  void _handleLastTileHasBeenPlaced(cocos2d::EventCustom* event);
  void _handleMonsterDiceGenerated(cocos2d::EventCustom* event);
  void _handleRoomsPlacements(cocos2d::EventCustom* event);
  void _handleMonsterMoved(cocos2d::EventCustom* event);
  void _handleMonstersFinishedMoving(cocos2d::EventCustom* event);
  void _handleMonstersFinishedRising(cocos2d::EventCustom* event);
  
};

#endif /* defined(__MasmorraDados__DungeonLayer__) */
