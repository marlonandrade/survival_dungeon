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
#include "DungeonRoomSprite.h"

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
  
  auto initialSprite = DungeonRoomSprite::createWithRoom(initialRoom);
  initialSprite->setCoordinate(initialCoordinate);
  
  this->addChild(initialSprite, DUNGEON_ROOM_WITH_CHAR_Z_ORDER);
  
  auto characterSprite = CharacterDiceSprite::createWithDelegate(this);
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
  visibleNodes.pushBack(this->_getRoomSpriteForCharacterCoordinate());
  visibleNodes.pushBack(this->_getRoomSpritesForAdjacentCharacterCoordinate());
  this->_addOverlayWithVisibleNodes(visibleNodes);
}

void DungeonLayer::characterIsMovingToLocation(Vec2 location) {
  for (auto adjacentRoomSprite : this->_getRoomSpritesForAdjacentCharacterCoordinate()) {
    Color3B color = Color3B::WHITE;
    
    if (adjacentRoomSprite->getBoundingBox().containsPoint(location)) {
      color = OK_COLOR;
    }
    
    adjacentRoomSprite->setColor(color);
  }
}

bool DungeonLayer::canCharacterMoveToLocation(Vec2 location) {
  bool canMove = false;
  
  for (auto node : this->_getRoomSpritesForAdjacentCharacterCoordinate()) {
    auto adjacentRoomSprite = (DungeonRoomSprite*) node;
    if (adjacentRoomSprite->canCharacterMoveToLocation(location)) {
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
  
  auto oldRoomSprite = (DungeonRoomSprite*) sprite->getParent();
  auto newRoomSprite = (DungeonRoomSprite*) this->_getRoomSpriteForCharacterCoordinate();
  
  auto oldPosition = oldRoomSprite->convertToWorldSpace(sprite->getPosition());
  auto newPosition = newRoomSprite->convertToNodeSpace(oldPosition);
  
  sprite->retain();
  sprite->removeFromParent();
  newRoomSprite->addChild(sprite);
  sprite->release();
  
  newRoomSprite->setLocalZOrder(DUNGEON_ROOM_WITH_CHAR_Z_ORDER + OVERLAY_Z_ORDER);
  oldRoomSprite->setLocalZOrder(DUNGEON_ROOM_Z_ORDER + OVERLAY_Z_ORDER);
 
  sprite->setPosition(newPosition);
  
  oldRoomSprite->adjustChildren();
  newRoomSprite->adjustChildren();
  
  auto delay = DelayTime::create(MOVE_DICE_DURATION);
  auto restoreZOrder = CallFunc::create([=]{
    newRoomSprite->setLocalZOrder(DUNGEON_ROOM_WITH_CHAR_Z_ORDER);
    oldRoomSprite->setLocalZOrder(DUNGEON_ROOM_Z_ORDER);
  });
  
  this->runAction(Sequence::create(delay, restoreZOrder, NULL));
}

void DungeonLayer::characterDidNotMove(CharacterDiceSprite* sprite) {
  this->_resetCharacterMoveState();
  auto roomSprite = (DungeonRoomSprite*) sprite->getParent();
  roomSprite->adjustChildren();
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
  
  auto roomsPlacementsCallback = CC_CALLBACK_1(DungeonLayer::_handleRoomsPlacements, this);
  this->setRoomsPlacementsListener(
     dispatcher->addCustomEventListener(EVT_ROOMS_HAVE_BEEN_PLACED, roomsPlacementsCallback)
  );
  
  auto monsterMovedCallback = CC_CALLBACK_1(DungeonLayer::_handleMonsterMoved, this);
  this->setMonsterMovedListener(
     dispatcher->addCustomEventListener(EVT_MONSTER_MOVED, monsterMovedCallback)
  );
  
  auto monstersFinishedMovingCallback = CC_CALLBACK_1(DungeonLayer::_handleMonstersFinishedMoving, this);
  this->setMonstersFinishedMovingListener(
     dispatcher->addCustomEventListener(EVT_MONSTERS_FINISHED_MOVING, monstersFinishedMovingCallback)
  );
  
  auto monstersFinishedRisingCallback = CC_CALLBACK_1(DungeonLayer::_handleMonstersFinishedRising, this);
  this->setMonstersFinishedRisingListener(
     dispatcher->addCustomEventListener(EVT_MONSTERS_FINISHED_RISING, monstersFinishedRisingCallback)
  );
}

void DungeonLayer::_consumeMonsterRoomDatas() {
  for (auto data : _monsterRoomDatas) {
    auto dice = data->getMonsterDice();
    auto room = data->getRoom();
    
    dice->roll();
    
    auto coordinate = Game::getInstance()->getDungeon()->getCoordinateForRoom(room);
    auto roomSprite = this->_getRoomSpriteForCoordinate(coordinate);
    roomSprite->addDice(dice);
  }
  
  _monsterRoomDatas.clear();
}

void DungeonLayer::_moveMonsterSpriteToDestinationRoom(Node* monsterSprite,
                                                       DungeonRoomSprite* destinationRoom) {
  auto originNode = monsterSprite->getParent();
  
  auto deltaPosition = originNode->getPosition() - destinationRoom->getPosition();
  
  monsterSprite->retain();
  monsterSprite->removeFromParent();
  destinationRoom->addChild(monsterSprite);
  monsterSprite->release();
  
  monsterSprite->setPosition(monsterSprite->getPosition() + deltaPosition);
}

DungeonRoomSprite* DungeonLayer::_getRoomSpriteForCharacterCoordinate() {
  auto coordinate = Game::getInstance()->getCharacterCoordinate();
  return this->_getRoomSpriteForCoordinate(coordinate);
}

DungeonRoomSprite* DungeonLayer::_getRoomSpriteForCoordinate(Vec2 coordinate) {
  auto name = CoordinateUtil::nameForCoordinate(coordinate);
  return (DungeonRoomSprite*) this->getChildByName(name);
}

Vector<Node*> DungeonLayer::_getRoomSpritesForAdjacentCharacterCoordinate() {
  Vector<Node*> roomSprites;
  
  auto coordinate = Game::getInstance()->getCharacterCoordinate();
  auto adjacentCoordinates = CoordinateUtil::adjacentCoordinatesTo(coordinate);
  for (auto adjacentCoordinate : adjacentCoordinates) {
    auto roomSprite = this->_getRoomSpriteForCoordinate(adjacentCoordinate);
    
    if (roomSprite) {
      roomSprites.pushBack(roomSprite);
    }
  }
  
  return roomSprites;
}

void DungeonLayer::_resetCharacterMoveState() {
  this->_removeOverlay();
  
  for (auto adjacentRoomSprite : this->_getRoomSpritesForAdjacentCharacterCoordinate()) {
    adjacentRoomSprite->setColor(Color3B::WHITE);
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
  this->_consumeMonsterRoomDatas();
}

void DungeonLayer::_handleMonsterDiceGenerated(EventCustom* event) {
  auto data = (MonsterRoomData*) event->getUserData();
  _monsterRoomDatas.pushBack(data);
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
      
      auto roomSprite = DungeonRoomSprite::createWithRoom(room);
      roomSprite->setCoordinate(coordinate);
      
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

void DungeonLayer::_handleMonsterMoved(EventCustom* event) {
  auto data = (MonsterMoveData*) event->getUserData();
  
  auto origin = data->getOrigin();
  auto destination = data->getDestination();
  auto monsterDice = data->getMonsterDice();
  
  this->_moveMonsterSpriteToDestinationRoom(
    monsterDice->getSprite(),
    this->_getRoomSpriteForCoordinate(destination->getCoordinate())
  );
  
  if (origin->getMonsters().size() > 0 && !_modifiedRooms.contains(origin)) {
    _modifiedRooms.pushBack(origin);
  }
  
  if (!_modifiedRooms.contains(destination)) {
    _modifiedRooms.pushBack(destination);
  }
}

void DungeonLayer::_handleMonstersFinishedMoving(EventCustom* event) {
  if (_modifiedRooms.size() > 0) {
    auto delay = 0.f;
    auto lastModifiedRoom = _modifiedRooms.at(_modifiedRooms.size() - 1);
    
    for (auto room : _modifiedRooms) {
      auto coordinate = room->getCoordinate();
      auto roomSprite = this->_getRoomSpriteForCoordinate(coordinate);
      
      auto delayTime = DelayTime::create(delay);
      auto callFunc = CallFunc::create([=]{
        auto center = PositionUtil::visibleCenter();
        auto cameraPosition = center - roomSprite->getPosition();
        
        auto cameraMove = MoveTo::create(ADJUST_CAMERA_DURATION, cameraPosition);
        auto adjustCamera = EaseOut::create(cameraMove, 2.f);
        auto delayToMove = DelayTime::create(ADJUST_CAMERA_DURATION - 0.2);
        auto showMonsterAnimation = CallFunc::create([=]{
          roomSprite->adjustChildren();
          
          if (room == lastModifiedRoom) {
            auto delayAfterAdjust = DelayTime::create(MOVE_DICE_DURATION);
            auto notififyLastRoomAdjusted = CallFunc::create([=]{
              this->_consumeMonsterRoomDatas();
              Game::getInstance()->finishCurrentTurn();
            });
            
            this->runAction(Sequence::create(delayAfterAdjust, notififyLastRoomAdjusted, NULL));
          }
        });
        
        auto waitAndMoveMonster = Sequence::create(delayToMove, showMonsterAnimation, NULL);
        
        this->getParent()->runAction(Spawn::create(adjustCamera, waitAndMoveMonster, NULL));
      });
      
      this->runAction(Sequence::create(delayTime, callFunc, NULL));
      
      delay += MOVE_DICE_DURATION + ADJUST_CAMERA_DURATION;
    }
    
    _modifiedRooms.clear();
    
    for (auto child : this->getChildren()) {
      child->setLocalZOrder(DUNGEON_ROOM_Z_ORDER);
    }
    
    auto characterRoomSprite = this->_getRoomSpriteForCharacterCoordinate();
    characterRoomSprite->setLocalZOrder(DUNGEON_ROOM_WITH_CHAR_Z_ORDER);
  }
}

void DungeonLayer::_handleMonstersFinishedRising(EventCustom* event) {
  // TODO: tem que esperar acabar a animação de
  //this->_consumeMonsterRoomDatas();
}
