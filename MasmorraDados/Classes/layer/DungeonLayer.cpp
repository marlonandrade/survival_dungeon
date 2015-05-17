//
//  DungeonLayer.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 5/17/15.
//
//

#include "DungeonLayer.h"

#include "Events.h"
#include "Images.h"
#include "NodeNames.h"

#include "CoordinateUtil.h"
#include "PositionUtil.h"

#include "CharacterDiceSprite.h"

#include "Game.h"
#include "PlayerTurn.h"

#include "MonsterMoveData.h"
#include "RoomsPlacementsData.h"

USING_NS_CC;

#pragma mark - Public Interface

bool DungeonLayer::init() {
  if (!Layer::init()) {
    return false;
  }
  
  this->setName(DUNGEON_LAYER_NAME);
  
  auto initialRoom = Game::getInstance()->getDungeon()->getInitialRoom();
  auto initialCoordinate = INITIAL_COORDINATE;
  
  auto initialSprite = Sprite::create(initialRoom->getImagePath());
  initialSprite->setName(CoordinateUtil::nameForCoordinate(initialCoordinate));
  initialSprite->setPosition(PositionUtil::positionForCoordinate(initialCoordinate));
  
  this->addChild(initialSprite, DUNGEON_ROOM_WITH_CHAR_Z_ORDER);
  
  auto characterSprite = CharacterDiceSprite::createWithDelegate(this);
  characterSprite->setName(CHARACTER_DICE_SPRITE_NAME);
  characterSprite->setPosition(PositionUtil::centerOfNode(initialSprite));
  
  initialSprite->addChild(characterSprite);
  
  this->_setupEventHandlers();
  
  return true;
}

#pragma mark - CharacterMoveDelegate Methods

bool DungeonLayer::canCharacterMove() {
  bool canMove = false;
  
  if (Game::getInstance()->isPlayerTurn()) {
    auto playerTurn = (PlayerTurn *) Game::getInstance()->getTurn();
  
    auto availableSkills = Game::getInstance()->getAvailableSkills();
    
    bool playerHasBoot = availableSkills[IMG_DICE_ACTION_BOOT].asInt() ||
        !Game::getInstance()->getFreeBootUsed();
    
    canMove = playerTurn->isActionDicesRolled() && playerHasBoot;
  }
  
  return canMove;
}

void DungeonLayer::characterWillMove(CharacterDiceSprite* sprite) {
  Vector<Node*> visibleNodes;
  visibleNodes.pushBack(this->_getRoomNodeForCharacterCoordinate());
  visibleNodes.pushBack(this->_getRoomsNodesForAdjacentCharacterCoordinate());
  this->_addOverlayWithVisibleNodes(visibleNodes);
}

void DungeonLayer::characterIsMovingToLocation(Vec2 location) {
  for (auto adjacentRoomNode : this->_getRoomsNodesForAdjacentCharacterCoordinate()) {
    Color3B color = Color3B::WHITE;
    
    if (adjacentRoomNode->getBoundingBox().containsPoint(location)) {
      color = Color3B(170, 255, 170);
    }
    
    adjacentRoomNode->setColor(color);
  }
}

bool DungeonLayer::canCharacterMoveToLocation(Vec2 location) {
  bool canMove = false;
  
  for (auto adjacentRoomNode : this->_getRoomsNodesForAdjacentCharacterCoordinate()) {
    if (adjacentRoomNode->getBoundingBox().containsPoint(location)) {
      canMove = true;
      break;
    }
  }
  
  return canMove;
}

void DungeonLayer::characterMovedToLocation(CharacterDiceSprite* sprite, Vec2 location) {
  this->_resetCharacterMoveState();
  
  auto newCoordinate = PositionUtil::coordinateForPosition(location);
  Game::getInstance()->characterMovedTo(newCoordinate);
  
  auto oldRoomSprite = sprite->getParent();
  auto newRoomSprite = this->_getRoomNodeForCharacterCoordinate();
  
  auto oldPosition = oldRoomSprite->convertToWorldSpace(sprite->getPosition());
  auto newPosition = newRoomSprite->convertToNodeSpace(oldPosition);
  
  sprite->retain();
  sprite->removeFromParent();
  newRoomSprite->addChild(sprite);
  sprite->release();
  
  newRoomSprite->setLocalZOrder(DUNGEON_ROOM_WITH_CHAR_Z_ORDER + OVERLAY_Z_ORDER);
  oldRoomSprite->setLocalZOrder(DUNGEON_ROOM_Z_ORDER + OVERLAY_Z_ORDER);
 
  sprite->setPosition(newPosition);
  
  this->_adjustSpritesForRoom(oldRoomSprite);
  this->_adjustSpritesForRoom(newRoomSprite);
}

void DungeonLayer::characterDidNotMove(CharacterDiceSprite* sprite) {
  this->_resetCharacterMoveState();
  this->_adjustSpritesForRoom(sprite->getParent());
}

#pragma mark - Private Interface

void DungeonLayer::_setupEventHandlers() {
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  
  auto lastTileHasBeenPlacedCallback = CC_CALLBACK_1(DungeonLayer::_handleLastTileHasBeenPlaced, this);
  this->setLastTileHasBeenPlacedListener(
    dispatcher->addCustomEventListener(EVT_LAST_TILE_HAS_BEEN_PLACED, lastTileHasBeenPlacedCallback)
  );
  
  auto monsterDiceGeneratedCallback = CC_CALLBACK_1(DungeonLayer::_handleMonsterDiceGenerated, this);
  this->setMonsterDiceGeneratedListener(
    dispatcher->addCustomEventListener(EVT_MONSTER_DICE_GENERATED, monsterDiceGeneratedCallback)
  );
  
  auto monsterMovedCallback = CC_CALLBACK_1(DungeonLayer::_handleMonsterMoved, this);
  this->setMonsterMovedListener(
     dispatcher->addCustomEventListener(EVT_MONSTER_MOVED, monsterMovedCallback)
  );
  
  auto roomsPlacementsCallback = CC_CALLBACK_1(DungeonLayer::_handleRoomsPlacements, this);
  this->setRoomsPlacementsListener(
     dispatcher->addCustomEventListener(EVT_ROOMS_HAVE_BEEN_PLACED, roomsPlacementsCallback)
  );
}

void DungeonLayer::_adjustSpritesForRoom(Node *roomNode) {
  auto roomCenter = PositionUtil::centerOfNode(roomNode);
  
  auto sprites = roomNode->getChildren();
  switch (sprites.size()) {
    case 1: {
      auto sprite1 = sprites.at(0);
      auto moveSprite1 = MoveTo::create(MOVE_DICE_DURATION, roomCenter);
      sprite1->runAction(moveSprite1);
    } break;
    case 2: {
      auto sprite1 = sprites.at(0);
      
      auto w = sprite1->getContentSize().width / 2;
      
      auto sprite1NewPosition = roomCenter + Vec2(-(w + 1), 0);
      auto moveSprite1 = MoveTo::create(MOVE_DICE_DURATION, sprite1NewPosition);
      sprite1->runAction(moveSprite1);
      
      auto sprite2 = sprites.at(1);
      
      w = sprite2->getContentSize().width / 2;
      
      auto sprite2NewPosition = roomCenter + Vec2(w + 1, 0);
      auto moveSprite2 = MoveTo::create(MOVE_DICE_DURATION, sprite2NewPosition);
      sprite2->runAction(moveSprite2);
    } break;
    case 3: {
      auto sprite1 = sprites.at(0);
      
      auto w = sprite1->getContentSize().width / 2;
      auto h = sprite1->getContentSize().height / 2;
      
      auto sprite1NewPosition = roomCenter + Vec2(-(w + 1), h + 1);
      auto moveSprite1 = MoveTo::create(MOVE_DICE_DURATION, sprite1NewPosition);
      sprite1->runAction(moveSprite1);
      
      auto sprite2 = sprites.at(1);
      
      w = sprite2->getContentSize().width / 2;
      h = sprite2->getContentSize().height / 2;
      
      auto sprite2NewPosition = roomCenter + Vec2(w + 1, h + 1);
      auto moveSprite2 = MoveTo::create(MOVE_DICE_DURATION, sprite2NewPosition);
      sprite2->runAction(moveSprite2);
      
      auto sprite3 = sprites.at(2);
      
      h = sprite3->getContentSize().height / 2;
      
      auto sprite3NewPosition = roomCenter + Vec2(0, -(h + 1));
      auto moveSprite3 = MoveTo::create(MOVE_DICE_DURATION, sprite3NewPosition);
      sprite3->runAction(moveSprite3);
    } break;
    case 4: {
      auto sprite1 = sprites.at(0);
      
      auto w = sprite1->getContentSize().width / 2;
      auto h = sprite1->getContentSize().height / 2;
      
      auto sprite1NewPosition = roomCenter + Vec2(-(w + 1), h + 1);
      auto moveSprite1 = MoveTo::create(MOVE_DICE_DURATION, sprite1NewPosition);
      sprite1->runAction(moveSprite1);
      
      auto sprite2 = sprites.at(1);
      
      w = sprite2->getContentSize().width / 2;
      h = sprite2->getContentSize().height / 2;
      
      auto sprite2NewPosition = roomCenter + Vec2(w + 1, h + 1);
      auto moveSprite2 = MoveTo::create(MOVE_DICE_DURATION, sprite2NewPosition);
      sprite2->runAction(moveSprite2);
      
      auto sprite3 = sprites.at(2);
      
      w = sprite3->getContentSize().width / 2;
      h = sprite3->getContentSize().height / 2;
      
      auto sprite3NewPosition = roomCenter + Vec2(-(w + 1), -(h + 1));
      auto moveSprite3 = MoveTo::create(MOVE_DICE_DURATION, sprite3NewPosition);
      sprite3->runAction(moveSprite3);
      
      auto sprite4 = sprites.at(3);
      
      w = sprite4->getContentSize().width / 2;
      h = sprite4->getContentSize().height / 2;
      
      auto sprite4NewPosition = roomCenter + Vec2(w + 1, -(h + 1));
      auto moveSprite4 = MoveTo::create(MOVE_DICE_DURATION, sprite4NewPosition);
      sprite4->runAction(moveSprite4);
    } break;
  }
}


Node* DungeonLayer::_getRoomNodeForCharacterCoordinate() {
  auto coordinate = Game::getInstance()->getCharacterCoordinate();
  return this->_getRoomNodeForCoordinate(coordinate);
}

Node* DungeonLayer::_getRoomNodeForCoordinate(Vec2 coordinate) {
  auto name = CoordinateUtil::nameForCoordinate(coordinate);
  return this->getChildByName(name);
}

Vector<Node*> DungeonLayer::_getRoomsNodesForAdjacentCharacterCoordinate() {
  Vector<Node*> roomNodes;
  
  auto coordinate = Game::getInstance()->getCharacterCoordinate();
  auto adjacentCoordinates = CoordinateUtil::adjacentCoordinatesTo(coordinate);
  for (auto adjacentCoordinate : adjacentCoordinates) {
    auto roomNode = this->_getRoomNodeForCoordinate(adjacentCoordinate);
    
    if (roomNode) {
      roomNodes.pushBack(roomNode);
    }
  }
  
  return roomNodes;
}

void DungeonLayer::_resetCharacterMoveState() {
  this->_removeOverlay();
  
  for (auto adjacentRoomNode : this->_getRoomsNodesForAdjacentCharacterCoordinate()) {
    adjacentRoomNode->setColor(Color3B::WHITE);
  }
}

void DungeonLayer::_addOverlayWithVisibleNodes(Vector<Node *> visibleNodes) {
  if (!this->getChildByName(OVERLAY_LAYER_NAME)) {
    auto overlayLayer = LayerColor::create(Color4B(0, 0, 0, 0));
    overlayLayer->setName(OVERLAY_LAYER_NAME);
    overlayLayer->setPosition(-this->getParent()->getPosition());
    
    this->addChild(overlayLayer, OVERLAY_Z_ORDER);
    
    auto fadeIn = FadeTo::create(OVERLAY_DURATION, OVERLAY_OPACITY);
    overlayLayer->runAction(fadeIn);
    
    for (auto visibleNode : visibleNodes) {
      auto newZOrder = visibleNode->getLocalZOrder() + OVERLAY_Z_ORDER;
      visibleNode->setLocalZOrder(newZOrder);
    }
    
    this->setInteractableNodes(visibleNodes);
  }
}

void DungeonLayer::_removeOverlay() {
  auto overlayLayer = this->getChildByName(OVERLAY_LAYER_NAME);
  
  if (overlayLayer) {
    auto fadeOut = FadeOut::create(OVERLAY_DURATION);
    auto changeLayer = CallFunc::create([=]() {
      for (auto node : this->getInteractableNodes()) {
        auto oldZOrder = node->getLocalZOrder() - OVERLAY_Z_ORDER;
        node->setLocalZOrder(oldZOrder);
      }
    });
    auto removeSelf = RemoveSelf::create();
    
    overlayLayer->runAction(Sequence::create(fadeOut, changeLayer, removeSelf, NULL));
  }
}

#pragma mark - Event Handlers

void DungeonLayer::_handleLastTileHasBeenPlaced(EventCustom* event) {
  for (auto data : _monsterRoomDatas) {
    auto dice = data->getMonsterDice();
    auto room = data->getRoom();
    
    dice->roll();
    
    auto coordinate = Game::getInstance()->getDungeon()->getCoordinateForRoom(room);
    auto roomNode = this->_getRoomNodeForCoordinate(coordinate);
    
    auto diceSprite = dice->getSprite();
    diceSprite->setPosition(PositionUtil::centerOfNode(roomNode));
    roomNode->addChild(diceSprite);
    
    this->_adjustSpritesForRoom(roomNode);
  }
  
  _monsterRoomDatas.clear();
}

void DungeonLayer::_handleMonsterDiceGenerated(EventCustom* event) {
  auto data = (MonsterRoomData*) event->getUserData();
  _monsterRoomDatas.pushBack(data);
}

void DungeonLayer::_handleMonsterMoved(EventCustom* event) {
  auto data = (MonsterMoveData*) event->getUserData();
  
  auto origin = data->getOrigin();
  auto destination = data->getDestination();
  
  auto deltaCoordinate = origin->getCoordinate() - destination->getCoordinate();
  auto deltaPosition = Vec2(deltaCoordinate.x * TILE_DIMENSION,
                            deltaCoordinate.y * TILE_DIMENSION);
  
  auto destinationNode = this->_getRoomNodeForCoordinate(destination->getCoordinate());
  
  for (auto monster : data->getMonsterDices()) {
    auto monsterSprite = monster->getSprite();
    
    monsterSprite->retain();
    monsterSprite->removeFromParent();
    destinationNode->addChild(monsterSprite);
    monsterSprite->release();
    
    monsterSprite->setPosition(monsterSprite->getPosition() + deltaPosition);
  }
  
  this->_adjustSpritesForRoom(destinationNode);
}

void DungeonLayer::_handleRoomsPlacements(EventCustom* event) {
  auto placementsData = (RoomsPlacementsData*) event->getUserData();
  auto placements = placementsData->getPlacements();
  
  int zOrder = placements.size();
  
  if (placements.size() > 0) {
    float delayTime = 0;
    auto lastPlacement = placements.at(placements.size() - 1);
    
    for (auto placement : placements) {
      auto room = placement->getRoom();
      auto coordinate = placement->getCoordinate();
      
      auto roomSprite = Sprite::create(room->getImagePath());
      auto name = CoordinateUtil::nameForCoordinate(coordinate);
      roomSprite->setName(name);
      
      auto size = Director::getInstance()->getVisibleSize();
      auto origin = Director::getInstance()->getVisibleOrigin() - this->getParent()->getPosition();
      
      auto initialSize = TILE_DIMENSION * TILE_PLACEMENT_SCALE;
      
      auto deckPosition = Vec2(origin.x + size.width - initialSize / 2 - 10,
                               origin.y + size.height - initialSize / 2 - 10);
      roomSprite->setScale(TILE_PLACEMENT_SCALE, TILE_PLACEMENT_SCALE);
      roomSprite->setPosition(deckPosition);
      
      this->addChild(roomSprite, zOrder + 1);
      
      auto position = PositionUtil::positionForCoordinate(coordinate);
      
      auto delay = DelayTime::create(delayTime);
      auto animationStarted = CallFunc::create([=]() {
        roomSprite->setLocalZOrder(DUNGEON_ROOM_Z_ORDER + 10);
      });
      auto moveAndScale = Spawn::create(MoveTo::create(PLACE_ROOM_DURATION, position),
                                        ScaleTo::create(PLACE_ROOM_DURATION, 1),
                                        NULL);
      auto easeMove = EaseBackIn::create(moveAndScale);
      auto animationEnded = CallFunc::create([=]() {
        roomSprite->setLocalZOrder(DUNGEON_ROOM_Z_ORDER);
        
        if (placement == lastPlacement) {
          auto dispatcher = Director::getInstance()->getEventDispatcher();
          dispatcher->dispatchCustomEvent(EVT_LAST_TILE_HAS_BEEN_PLACED, placement);
          
          if (Game::getInstance()->isInitialTurn()) {
            Game::getInstance()->finishCurrentTurn();
          }
        }
      });
      
      roomSprite->runAction(Sequence::create(delay, animationStarted, easeMove,
                                             animationEnded, NULL));
      
      delayTime += PLACE_ROOM_DURATION;
      zOrder--;
    }
  }
}
