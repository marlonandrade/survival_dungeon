//
//  GameplayScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "GameplayScene.h"

#include "Events.h"
#include "Images.h"
#include "NodeNames.h"

#include "ActionDiceLayer.h"
#include "ActionDiceSprite.h"
#include "BackgroundLayer.h"
#include "CharacterDiceSprite.h"
#include "MonsterMoveData.h"
#include "MonsterRoomData.h"
#include "PlayerSkillsLayer.h"
#include "RoomPlacementData.h"
#include "ScrollableLayer.h"

#include "DungeonTurn.h"
#include "InitialTurn.h"
#include "PlayerTurn.h"

USING_NS_CC;

#pragma mark - Public Interface

bool GameplayScene::init() {
  if (!Scene::init()) {
    return false;
  }
  
  this->_enableInteractions();
  
  auto game = Game::createWithRoomPlacedDelegate(CC_CALLBACK_1(GameplayScene::_roomsHasBeenPlaced, this));
  
  this->setGame(game);
  
  this->_setupEventHandlers();
  this->_adjustInitialLayers();
  
  return true;
}

#pragma mark - Private Interface

void GameplayScene::_adjustInitialLayers() {
  auto center = this->_centerOfScene();
  
  auto scrollableLayer = ScrollableLayer::createWithDungeon(this->getGame()->getDungeon());
  
  scrollableLayer->addChild(BackgroundLayer::create(), -10);
  scrollableLayer->addChild(this->_createObjectsLayer(), 0);
  
  this->addChild(scrollableLayer, 0);
  this->addChild(this->_createControlsLayer(), 1);
  
  this->getGame()->setCharacterCoordinate(INITIAL_COORDINATE);
}

void GameplayScene::_setupEventHandlers() {
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  
  auto turnHasStartedCallback = CC_CALLBACK_1(GameplayScene::_handleTurnHasStarted, this);
  this->setTurnHasStartedListener(
    dispatcher->addCustomEventListener(EVT_TURN_HAS_STARTED, turnHasStartedCallback)
  );
  
  auto turnHasEndedCallback = CC_CALLBACK_1(GameplayScene::_handleTurnHasEnded, this);
  this->setTurnHasEndedListener(
    dispatcher->addCustomEventListener(EVT_TURN_HAS_ENDED, turnHasEndedCallback)
  );
  
  auto actionDicesRolledCallback = CC_CALLBACK_1(GameplayScene::_handleActionDicesRolled, this);
  this->setActionDicesRolledListener(
    dispatcher->addCustomEventListener(EVT_ACTION_DICES_ROLLED, actionDicesRolledCallback)
  );
  
  auto monsterDiceGeneratedCallback = CC_CALLBACK_1(GameplayScene::_handleMonsterDiceGenerated, this);
  this->setMonsterDiceGeneratedListener(
    dispatcher->addCustomEventListener(EVT_MONSTER_DICE_GENERATED, monsterDiceGeneratedCallback)
  );
  
  auto monsterMovedCallback = CC_CALLBACK_1(GameplayScene::_handleMonsterMoved, this);
  this->setMonsterMovedListener(
     dispatcher->addCustomEventListener(EVT_MONSTER_MOVED, monsterMovedCallback)
  );
  
  auto lastTileHasBeenPlacedCallback = CC_CALLBACK_1(GameplayScene::_handleLastTileHasBeenPlaced, this);
  this->setLastTileHasBeenPlacedListener(
    dispatcher->addCustomEventListener(EVT_LAST_TILE_HAS_BEEN_PLACED, lastTileHasBeenPlacedCallback)
  );
}

Layer* GameplayScene::_createObjectsLayer() {
  auto objectsLayer = Layer::create();
  objectsLayer->setName(OBJECTS_LAYER_NAME);
  
  auto initialRoom = this->getGame()->getDungeon()->getInitialRoom();
  auto initialCoordinate = INITIAL_COORDINATE;
  
  auto initialSprite = Sprite::create(initialRoom->getImagePath());
  auto name = this->getGame()->getDungeon()->nameForCoordinate(initialCoordinate);
  initialSprite->setName(name);
  initialSprite->setPosition(this->_positionForCoordinate(initialCoordinate));
  objectsLayer->addChild(initialSprite, DUNGEON_ROOM_WITH_CHAR_Z_ORDER);
  
  auto characterSprite = this->_createCharacterDiceSprite();
  characterSprite->setName(CHARACTER_DICE_SPRITE_NAME);
  characterSprite->setPosition(Vec2(initialSprite->getContentSize().width / 2,
                                    initialSprite->getContentSize().height / 2));
  initialSprite->addChild(characterSprite);
    
  return objectsLayer;
}

Layer* GameplayScene::_createControlsLayer() {
  auto controlsLayer = Layer::create();
  controlsLayer->setVisible(false);
  controlsLayer->setName(CONTROLS_LAYER_NAME);
  
  auto actionDiceLayer = ActionDiceLayer::createWithDices(this->getGame()->getActionDices());
  actionDiceLayer->setName(ACTION_DICE_LAYER_NAME);
  controlsLayer->addChild(actionDiceLayer);
  
  auto playerSkillsLayer = PlayerSkillsLayer::create();
  playerSkillsLayer->setName(PLAYER_SKILL_LAYER_NAME);
  playerSkillsLayer->setVisible(false);
  controlsLayer->addChild(playerSkillsLayer);
    
  return controlsLayer;
}

Node* GameplayScene::_createCharacterDiceSprite() {
  return CharacterDiceSprite::createWithDelegate(this);
}

Layer* GameplayScene::_getScrollableLayer() {
  return (Layer*) this->getChildByName(SCROLLABLE_LAYER_NAME);
}

Layer* GameplayScene::_getObjectsLayer() {
  auto scrollableLayer = this->_getScrollableLayer();
  return (Layer*) scrollableLayer->getChildByName(OBJECTS_LAYER_NAME);
}

Layer* GameplayScene::_getControlsLayer() {
  return (Layer*) this->getChildByName(CONTROLS_LAYER_NAME);
}

void GameplayScene::_roomsHasBeenPlaced(Vector<RoomPlacementData*> placements) {
  auto objectsLayer = this->_getObjectsLayer();
  int zOrder = placements.size();
  
  if (placements.size() > 0) {
    this->_disableInteractions();
    
    float delayTime = 0;
    auto lastPlacement = placements.at(placements.size() - 1);
    
    for (auto placement : placements) {
      auto room = placement->getRoom();
      auto coordinate = placement->getCoordinate();
      
      auto roomSprite = Sprite::create(room->getImagePath());
      auto name = this->getGame()->getDungeon()->nameForCoordinate(coordinate);
      roomSprite->setName(name);
      
      auto size = Director::getInstance()->getVisibleSize();
      auto origin = Director::getInstance()->getVisibleOrigin() - objectsLayer->getParent()->getPosition();
      
      auto initialSize = TILE_DIMENSION * TILE_PLACEMENT_SCALE;
      
      auto deckPosition = Vec2(origin.x + size.width - initialSize / 2 - 10,
                               origin.y + size.height - initialSize / 2 - 10);
      roomSprite->setScale(TILE_PLACEMENT_SCALE, TILE_PLACEMENT_SCALE);
      roomSprite->setPosition(deckPosition);
      
      objectsLayer->addChild(roomSprite, zOrder + 1);
      
      auto position = this->_positionForCoordinate(coordinate);
      
      auto delay = DelayTime::create(delayTime);
      auto animationStarted = CallFunc::create([=]() {
        this->_disableInteractions();
        roomSprite->setLocalZOrder(DUNGEON_ROOM_Z_ORDER + 10);
      });
      auto moveAndScale = Spawn::create(MoveTo::create(PLACE_ROOM_DURATION, position),
                                        ScaleTo::create(PLACE_ROOM_DURATION, 1),
                                        NULL);
      auto easeMove = EaseBackIn::create(moveAndScale);
      auto animationEnded = CallFunc::create([=]() {
        this->_enableInteractions();
        roomSprite->setLocalZOrder(DUNGEON_ROOM_Z_ORDER);
        
        if (placement == lastPlacement) {
          auto dispatcher = Director::getInstance()->getEventDispatcher();
          dispatcher->dispatchCustomEvent(EVT_LAST_TILE_HAS_BEEN_PLACED, placement);
          
          if (this->getGame()->isInitialTurn()) {
            this->getGame()->finishCurrentTurn();
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


Vec2 GameplayScene::_positionForCoordinate(Vec2 coordinate) {
  auto centerCoordinate = INITIAL_COORDINATE;
  auto centerOfScene = this->_centerOfScene();
  
  auto offsetX = coordinate.x - centerCoordinate.x;
  auto offsetY = coordinate.y - centerCoordinate.y;
  
  return Vec2(centerOfScene.x + offsetX * TILE_DIMENSION,
              centerOfScene.y + offsetY * TILE_DIMENSION);
}

Vec2 GameplayScene::_coordinateForPosition(Vec2 scenePosition) {
  auto centerCoordinate = INITIAL_COORDINATE;
  auto centerOfScene = this->_centerOfScene();
  
  auto offsetX = scenePosition.x - centerOfScene.x;
  auto offsetY = scenePosition.y - centerOfScene.y;
  
  auto halfTileDimension = TILE_DIMENSION / 2;
  
  offsetX > halfTileDimension ? offsetX += halfTileDimension : offsetX -= halfTileDimension;
  offsetY > halfTileDimension ? offsetY += halfTileDimension : offsetY -= halfTileDimension;
  
  return Vec2(centerCoordinate.x + int(offsetX / TILE_DIMENSION),
              centerCoordinate.y + int(offsetY / TILE_DIMENSION));
}

CharacterDiceSprite* GameplayScene::_getCharacterDiceSprite() {
  auto room = this->_getNodeForCharacterCoordinate();
  return (CharacterDiceSprite*) room->getChildByName(CHARACTER_DICE_SPRITE_NAME);
}

void GameplayScene::_adjustDiceSpritesForRoom(CharacterDiceSprite* charSprite, DungeonRoom* room) {
  Vector<Sprite*> sprites;
  
  auto monsterDices = room->getMonsters();
  
  if (room->getDistanceToPlayer() == 0) {
    sprites.pushBack(charSprite);
  }
  
  for (auto monsterDice : monsterDices) {
    sprites.pushBack(monsterDice->getSprite());
  }
  
  auto coordinate = this->getGame()->getDungeon()->getCoordinateForRoom(room);
  auto roomSprite = this->_getNodeForCoordinate(coordinate);
  auto roomCenter = Vec2(roomSprite->getContentSize().width / 2,
                         roomSprite->getContentSize().height / 2);
  
  switch (sprites.size()) {
    case 1: {
      auto sprite1 = sprites.at(0);
      auto moveSprite1 = MoveTo::create(MOVE_DICE_DURATION, roomCenter);
      sprite1->runAction(moveSprite1);
      break;
    }
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
      break;
    }
    case 3: {
      auto sprite1 = sprites.at(0);
      
      auto w = sprite1->getContentSize().width / 2;
      auto h = sprite1->getContentSize().height / 2;
      
      auto sprite1NewPosition = roomCenter + Vec2(-(w + 1), h + 1);
      auto moveSprite1 = MoveTo::create(MOVE_DICE_DURATION, sprite1NewPosition);
      sprite1->runAction(moveSprite1);
      
      auto sprite2 = sprites.at(1);
      
      w = sprite2->getContentSize().height / 2;
      h = sprite2->getContentSize().height / 2;
      
      auto sprite2NewPosition = roomCenter + Vec2(w + 1, h + 1);
      auto moveSprite2 = MoveTo::create(MOVE_DICE_DURATION, sprite2NewPosition);
      sprite2->runAction(moveSprite2);
      
      auto sprite3 = sprites.at(2);
      
      h = sprite3->getContentSize().height / 2;
      
      auto sprite3NewPosition = roomCenter + Vec2(0, -(h + 1));
      auto moveSprite3 = MoveTo::create(MOVE_DICE_DURATION, sprite3NewPosition);
      sprite3->runAction(moveSprite3);
      break;
    }
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
      break;
    }
  }
}

void GameplayScene::_addOverlayWithVisibleNodes(Vector<Node *> visibleNodes) {
  auto objectsLayer = this->_getObjectsLayer();
  auto scrollableLayer = this->_getScrollableLayer();
  
  if (!objectsLayer->getChildByName(OVERLAY_LAYER_NAME)) {
    auto overlayLayer = LayerColor::create(Color4B(0, 0, 0, 0));
    overlayLayer->setName(OVERLAY_LAYER_NAME);
    overlayLayer->setPosition(Vec2(-scrollableLayer->getPosition().x,
                                   -scrollableLayer->getPosition().y));
    
    objectsLayer->addChild(overlayLayer, OVERLAY_Z_ORDER);
    
    auto fadeIn = FadeTo::create(OVERLAY_DURATION, OVERLAY_OPACITY);
    overlayLayer->runAction(fadeIn);
    
    for (auto visibleNode : visibleNodes) {
      auto newZOrder = visibleNode->getLocalZOrder() + OVERLAY_Z_ORDER;
      visibleNode->setLocalZOrder(newZOrder);
    }
    
    this->setInteractableNodes(visibleNodes);
  }
}

void GameplayScene::_removeOverlay() {
  auto overlayLayer = this->_getObjectsLayer()->getChildByName(OVERLAY_LAYER_NAME);
  
  if (overlayLayer) {
    this->_disableInteractions();
    
    auto fadeOut = FadeOut::create(OVERLAY_DURATION);
    auto changeLayer = CallFunc::create([=]() {
      for (auto node : this->getInteractableNodes()) {
        auto oldZOrder = node->getLocalZOrder() - OVERLAY_Z_ORDER;
        node->setLocalZOrder(oldZOrder);
      }
    });
    auto removeSelf = RemoveSelf::create();
    auto animationEnded = CallFunc::create([=]() {
      this->_enableInteractions();
    });
    
    overlayLayer->runAction(Sequence::create(fadeOut, changeLayer, removeSelf, animationEnded, NULL));
  }
}

Vec2 GameplayScene::_centerOfScene() {
  Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
  Size visibleSize = Director::getInstance()->getVisibleSize();
  
  return Vec2(visibleSize.width / 2 + visibleOrigin.x,
              visibleSize.height / 2 + visibleOrigin.y);
}

Node* GameplayScene::_getNodeForCharacterCoordinate() {
  auto coordinate = this->getGame()->getCharacterCoordinate();
  return this->_getNodeForCoordinate(coordinate);
}

Node* GameplayScene::_getNodeForCoordinate(Vec2 coordinate) {
  auto name = this->getGame()->getDungeon()->nameForCoordinate(coordinate);
  return this->_getObjectsLayer()->getChildByName(name);
}

Vector<Node*> GameplayScene::_getNodesForAdjacentCharacterCoordinate() {
  Node* activeLayer = this->_getObjectsLayer();
  auto overlayLayer = this->getChildByName(OVERLAY_LAYER_NAME);
  if (overlayLayer) {
    activeLayer = overlayLayer;
  }
  
  Vector<Node*> nodes;
  
  auto coordinate = this->getGame()->getCharacterCoordinate();
  auto adjacentCoordinates = this->getGame()->getDungeon()->adjacentCoordinatesTo(coordinate);
  for (auto adjacentCoordinate : adjacentCoordinates) {
    auto name = this->getGame()->getDungeon()->nameForCoordinate(adjacentCoordinate);
    nodes.pushBack(activeLayer->getChildByName(name));
  }
  
  return nodes;
}

bool GameplayScene::_isInteractionEnabled() {
  return _userInteractionEnabled;
}

void GameplayScene::_disableInteractions() {
  _userInteractionEnabled = false;
}

void GameplayScene::_enableInteractions() {
  _userInteractionEnabled = true;
}

void GameplayScene::_resetCharacterMoveState() {
  this->_removeOverlay();
  
  for (auto adjacentNode : this->_getNodesForAdjacentCharacterCoordinate()) {
    adjacentNode->setColor(Color3B::WHITE);
  }
}

void GameplayScene::_showPlayerTurnInfo() {
  this->_showTurnInfo(Sprite::create(IMG_TURN_PLAYER));
}

void GameplayScene::_showDungeonTurnInfo() {
  this->_showTurnInfo(Sprite::create(IMG_TURN_DUNGEON));
}

void GameplayScene::_showTurnInfo(cocos2d::Sprite *infoSprite) {
  auto layer = LayerColor::create(Color4B(0, 0, 0, 130));
  layer->setName(TURN_OVERLAY_LAYER_NAME);
  this->addChild(layer);
  
  infoSprite->setPosition(this->_centerOfScene());
  infoSprite->setScale(0.5, 0.5);
  infoSprite->setOpacity(0);
  layer->addChild(infoSprite);
  
  auto overlayFadeDuration = 0.2;
  auto overlayDelayDuration = TURN_INFO_DURATION - overlayFadeDuration;
  
  auto waitAndRemoveOverlay = Sequence::create(DelayTime::create(overlayDelayDuration),
                                               FadeTo::create(overlayFadeDuration, 0),
                                               CallFunc::create([&] {
    this->removeChildByName(TURN_OVERLAY_LAYER_NAME);
  }), NULL);
  
  
  auto infoFadeInDuration = 0.2;
  auto infoFadeOutDuration = 0.2;
  auto infoDelayDuration = TURN_INFO_DURATION - infoFadeInDuration - infoFadeOutDuration;
  
  auto fadeInTurnInfo = Spawn::create(FadeIn::create(infoFadeInDuration),
                                      EaseBackOut::create(ScaleTo::create(infoFadeInDuration, 1)), NULL);
  auto fadeOutTurnInfo = Spawn::create(FadeOut::create(infoFadeOutDuration),
                                       EaseBackIn::create(ScaleTo::create(infoFadeOutDuration + 0.2, 0)), NULL);
  
  layer->runAction(waitAndRemoveOverlay);
  infoSprite->runAction(Sequence::create(fadeInTurnInfo,
                                         DelayTime::create(infoDelayDuration),
                                         fadeOutTurnInfo, NULL));
}

#pragma mark - Event Handlers

void GameplayScene::_handleTurnHasStarted(EventCustom* event) {
  log("turn has started");
  
  auto turn = (Turn*) event->getUserData();
  
  if (IS(turn, PlayerTurn)) {
    auto show = Show::create();
    auto roll = CallFunc::create([&] {
      for (auto dice : this->getGame()->getActionDices()) {
        dice->roll();
      }
    });
    auto showAndRoll = Sequence::create(show, roll, NULL);
    
    this->_getControlsLayer()->runAction(showAndRoll);
    
    this->_showPlayerTurnInfo();
  } else if (IS(turn, DungeonTurn)) {
    this->_showDungeonTurnInfo();
    
    auto delay = DelayTime::create(TURN_INFO_DURATION);
    auto executeTurn = CallFunc::create([&] {
      this->getGame()->executeCurrentTurn();
    });
    this->runAction(Sequence::create(delay, executeTurn, NULL));
  }
}

void GameplayScene::_handleTurnHasEnded(EventCustom* event) {
  log("turn has ended");
  
  auto turn = (Turn*) event->getUserData();
  
  if (IS(turn, PlayerTurn)) {
    this->_getControlsLayer()->runAction(Hide::create());
  }
}

void GameplayScene::_handleActionDicesRolled(EventCustom* event) {
  auto actionDicesLayer = (ActionDiceLayer*) event->getUserData();
  auto playerSkillLayer = (PlayerSkillsLayer*)this->_getControlsLayer()->getChildByName(PLAYER_SKILL_LAYER_NAME);
  
  for (auto dice : actionDicesLayer->getDices()) {
    auto sprite = (ActionDiceSprite*) dice->getSprite();
    CC_SAFE_RETAIN(sprite);
    auto position = sprite->getParent()->getPosition();
    sprite->removeFromParent();
    
    auto newPosition = sprite->getPosition() + position;
    sprite->setPosition(newPosition);
    sprite->setOriginalPosition(newPosition);
    
    playerSkillLayer->addChild(sprite);
    CC_SAFE_RELEASE(sprite);
  }
  
  actionDicesLayer->setVisible(false);
  playerSkillLayer->runAction(Show::create());
}

void GameplayScene::_handleMonsterDiceGenerated(EventCustom* event) {
  auto data = (MonsterRoomData*) event->getUserData();
  _monsterRoomDatas.pushBack(data);
}

void GameplayScene::_handleMonsterMoved(EventCustom* event) {
  auto data = (MonsterMoveData*) event->getUserData();
  
  auto origin = data->getOrigin();
  auto destination = data->getDestination();
  
  auto deltaCoordinate = origin->getCoordinate() - destination->getCoordinate();
  auto deltaPosition = Vec2(deltaCoordinate.x * TILE_DIMENSION,
                            deltaCoordinate.y * TILE_DIMENSION);
  
  auto destinationNode = this->_getNodeForCoordinate(destination->getCoordinate());
  
  for (auto monster : data->getMonsterDices()) {
    auto monsterSprite = monster->getSprite();
    
    monsterSprite->retain();
    monsterSprite->removeFromParent();
    destinationNode->addChild(monsterSprite);
    monsterSprite->release();
    
    monsterSprite->setPosition(monsterSprite->getPosition() + deltaPosition);
  }
  
  log("monster moved");
  
  auto charSprite = this->_getCharacterDiceSprite();
  this->_adjustDiceSpritesForRoom(charSprite, destination);
}

void GameplayScene::_handleLastTileHasBeenPlaced(EventCustom* event) {
  auto charSprite = this->_getCharacterDiceSprite();
  Vector<DungeonRoom*> rooms;
  
  for (auto data : _monsterRoomDatas) {
    auto dice = data->getMonsterDice();
    auto room = data->getRoom();
    
    if (!rooms.contains(room)) {
      rooms.pushBack(room);
    }
    
    auto coordinate = this->getGame()->getDungeon()->getCoordinateForRoom(room);
    
    auto node = this->_getNodeForCoordinate(coordinate);
    auto diceSprite = dice->getSprite();
    
    diceSprite->setPosition(Vec2(node->getContentSize().width / 2, node->getContentSize().height / 2));
    dice->roll();
    node->addChild(dice->getSprite());
  }
  
  for (auto room : rooms) {
    this->_adjustDiceSpritesForRoom(charSprite, room);
  }
  
  _monsterRoomDatas.clear();
}

#pragma mark - CharacterMoveDelegate Methods

bool GameplayScene::canCharacterMove() {
  auto availableSkills = this->getGame()->getAvailableSkills();
  
  bool playerHasBoot = availableSkills[IMG_DICE_ACTION_BOOT].asInt() ||
      !this->getGame()->getFreeBootUsed();
  
  return true;
//  return this->_isInteractionEnabled() && playerHasBoot;
}

void GameplayScene::characterWillMove(CharacterDiceSprite* sprite) {
  Vector<Node*> visibleNodes;
  visibleNodes.pushBack(this->_getNodeForCharacterCoordinate());
  visibleNodes.pushBack(this->_getNodesForAdjacentCharacterCoordinate());
  this->_addOverlayWithVisibleNodes(visibleNodes);
}

void GameplayScene::characterIsMovingToLocation(Vec2 location) {
  for (auto adjacentNode : this->_getNodesForAdjacentCharacterCoordinate()) {
    Color3B color = Color3B::WHITE;
    
    if (adjacentNode->getBoundingBox().containsPoint(location)) {
      color = Color3B(170, 255, 170);
    }
    
    adjacentNode->setColor(color);
  }
}

bool GameplayScene::canCharacterMoveToLocation(Vec2 location) {
  bool canMove = false;
  
  for (auto adjacentNode : this->_getNodesForAdjacentCharacterCoordinate()) {
    if (adjacentNode->getBoundingBox().containsPoint(location)) {
      canMove = true;
      break;
    }
  }
  
  return canMove;
}

void GameplayScene::characterMovedToLocation(CharacterDiceSprite* sprite, Vec2 location) {
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  
//  if (!this->getGame()->getFreeBootUsed()) {
//    dispatcher->dispatchCustomEvent(EVT_ACTION_FREE_BOOT_SPENT);
//  } else {
//    auto dockedDices = this->getGame()->getDockedDices();
//    ActionDice* usedDice;
//    for (auto dice : dockedDices) {
//      if (dice->getSelectedFace()->getImagePath() == IMG_DICE_ACTION_BOOT && !dice->isSpent()) {
//        usedDice = dice;
//        break;
//      }
//    }
//    
//    dispatcher->dispatchCustomEvent(EVT_ACTION_DICE_SPENT, usedDice);
//  }
  
  this->_resetCharacterMoveState();
  
  auto newCoordinate = this->_coordinateForPosition(location);
  auto oldCoordinate = this->getGame()->getCharacterCoordinate();
  
  this->getGame()->setCharacterCoordinate(newCoordinate);
  
  auto newRoom = this->getGame()->getDungeon()->getRoomForCoordinate(newCoordinate);
  auto oldRoom = this->getGame()->getDungeon()->getRoomForCoordinate(oldCoordinate);
  
  auto oldRoomSprite = sprite->getParent();
  auto newRoomSprite = this->_getNodeForCharacterCoordinate();
  
  auto oldPosition = oldRoomSprite->convertToWorldSpace(sprite->getPosition());
  auto newPosition = newRoomSprite->convertToNodeSpace(oldPosition);
  
  sprite->retain();
  sprite->removeFromParent();
  newRoomSprite->addChild(sprite);
  sprite->release();
  
  newRoomSprite->setLocalZOrder(DUNGEON_ROOM_WITH_CHAR_Z_ORDER + OVERLAY_Z_ORDER);
  oldRoomSprite->setLocalZOrder(DUNGEON_ROOM_Z_ORDER + OVERLAY_Z_ORDER);
 
  sprite->setPosition(newPosition);
  
  this->_adjustDiceSpritesForRoom(sprite, oldRoom);
  this->_adjustDiceSpritesForRoom(sprite, newRoom);
}

void GameplayScene::characterDidNotMove(CharacterDiceSprite* sprite) {
  this->_resetCharacterMoveState();
  
  auto characterCoordinate = this->getGame()->getCharacterCoordinate();
  auto room = this->getGame()->getDungeon()->getRoomForCoordinate(characterCoordinate);
  this->_adjustDiceSpritesForRoom(sprite, room);
}
