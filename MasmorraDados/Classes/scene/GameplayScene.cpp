//
//  GameplayScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "GameplayScene.h"

#include "ActionDiceDragData.h"
#include "ActionDiceLayer.h"
#include "BackgroundLayer.h"
#include "CharacterDiceSprite.h"
#include "PlayerSkillsLayer.h"
#include "RoomPlacement.h"
#include "ScrollableLayer.h"

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
  
  this->_adjustInitialLayers();
  this->_setupEventHandlers();
  
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
  
  this->getGame()->setCharacterPosition(INITIAL_POSITION);
  this->_adjustCharacterDiceSpritePosition();
}

void GameplayScene::_setupEventHandlers() {
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->addCustomEventListener(EVT_TURN_HAS_ENDED,
                                     CC_CALLBACK_1(GameplayScene::_handleTurnHasEnded, this));
  dispatcher->addCustomEventListener(EVT_TURN_HAS_STARTED,
                                     CC_CALLBACK_1(GameplayScene::_handleTurnHasStarted, this));
  dispatcher->addCustomEventListener(EVT_ACTION_DICE_DRAG_STARTED,
                                     CC_CALLBACK_1(GameplayScene::_handleActionDiceDragStarted, this));
  dispatcher->addCustomEventListener(EVT_ACTION_DICE_DRAG_MOVED,
                                     CC_CALLBACK_1(GameplayScene::_handleActionDiceDragMoved, this));
  dispatcher->addCustomEventListener(EVT_ACTION_DICE_DRAG_ENDED,
                                     CC_CALLBACK_1(GameplayScene::_handleActionDiceDragEnded, this));
  dispatcher->addCustomEventListener(EVT_ACTION_DICES_ROLLED,
                                     CC_CALLBACK_1(GameplayScene::_handleActionDicesRolled, this));
}

Layer* GameplayScene::_createObjectsLayer() {
  auto objectsLayer = Layer::create();
  objectsLayer->setName(OBJECTS_LAYER_NAME);
  
  auto initialRoom = this->getGame()->getDungeon()->getInitialRoom();
  auto initialPosition = INITIAL_POSITION;
  
  auto initialSprite = Sprite::create(initialRoom->getImagePath());
  auto name = this->getGame()->getDungeon()->nameForPosition(initialPosition);
  initialSprite->setName(name);
  initialSprite->setPosition(this->_positionInScene(INITIAL_POSITION));
  objectsLayer->addChild(initialSprite, DUNGEON_ROOM_Z_ORDER);
  
  objectsLayer->addChild(this->_createCharacterDiceSprite(), GAME_OBJECTS_Z_ORDER);
    
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

void GameplayScene::_roomsHasBeenPlaced(Vector<RoomPlacement*> placements) {
  auto objectsLayer = this->_getObjectsLayer();
  int zOrder = placements.size();
  
  if (placements.size() > 0) {
    this->_disableInteractions();
  }
  
  float delayTime = 0;
  auto lastPlacement = placements.at(placements.size() - 1);
  
  for (auto placement : placements) {
    auto room = placement->getRoom();
    auto position = placement->getPosition();
    
    auto roomSprite = Sprite::create(room->getImagePath());
    auto name = this->getGame()->getDungeon()->nameForPosition(position);
    roomSprite->setName(name);
    
    auto size = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin() - objectsLayer->getParent()->getPosition();
    
    auto initialSize = TILE_DIMENSION * TILE_PLACEMENT_SCALE;
    
    auto deckPosition = Vec2(origin.x + size.width - initialSize / 2 - 10,
                             origin.y + size.height - initialSize / 2 - 10);
    roomSprite->setScale(TILE_PLACEMENT_SCALE, TILE_PLACEMENT_SCALE);
    roomSprite->setPosition(deckPosition);
    
    objectsLayer->addChild(roomSprite, zOrder + 1);
    
    auto spritePosition = this->_positionInScene(position);
    
    auto delay = DelayTime::create(delayTime);
    auto animationStarted = CallFunc::create([=]() {
      this->_disableInteractions();
      roomSprite->setLocalZOrder(DUNGEON_ROOM_Z_ORDER + 10);
    });
    auto moveAndScale = Spawn::create(MoveTo::create(PLACE_ROOM_DURATION, spritePosition),
                                      ScaleTo::create(PLACE_ROOM_DURATION, 1),
                                      NULL);
    auto easeMove = EaseBackIn::create(moveAndScale);
    auto animationEnded = CallFunc::create([=]() {
      this->_enableInteractions();
      roomSprite->setLocalZOrder(DUNGEON_ROOM_Z_ORDER);
      
      if (placement == lastPlacement && this->getGame()->isInitialTurn()) {
        this->getGame()->executeCurrentTurn();
      }
    });
    
    roomSprite->runAction(Sequence::create(delay, animationStarted, easeMove,
                                           animationEnded, NULL));
    
    delayTime += PLACE_ROOM_DURATION;
    zOrder--;
  }
}


Vec2 GameplayScene::_positionInScene(Vec2 gameCoordinate) {
  auto centerPosition = INITIAL_POSITION;
  auto centerOfScene = this->_centerOfScene();
  
  auto offsetX = gameCoordinate.x - centerPosition.x;
  auto offsetY = gameCoordinate.y - centerPosition.y;
  
  return Vec2(centerOfScene.x + offsetX * TILE_DIMENSION,
              centerOfScene.y + offsetY * TILE_DIMENSION);
}

Vec2 GameplayScene::_positionInGameCoordinate(Vec2 scenePosition) {
  auto centerPosition = INITIAL_POSITION;
  auto centerOfScene = this->_centerOfScene();
  
  auto offsetX = scenePosition.x - centerOfScene.x;
  auto offsetY = scenePosition.y - centerOfScene.y;
  
  auto halfTileDimension = TILE_DIMENSION / 2;
  
  offsetX > halfTileDimension ? offsetX += halfTileDimension : offsetX -= halfTileDimension;
  offsetY > halfTileDimension ? offsetY += halfTileDimension : offsetY -= halfTileDimension;
  
  return Vec2(centerPosition.x + int(offsetX / TILE_DIMENSION),
              centerPosition.y + int(offsetY / TILE_DIMENSION));
}

void GameplayScene::_adjustCharacterDiceSpritePosition() {
  auto sprite = this->_getObjectsLayer()->getChildByName(CHARACTER_DICE_SPRITE_NAME);
  auto characterPosition = this->getGame()->getCharacterPosition();
  sprite->setPosition(this->_positionInScene(characterPosition));
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

Node* GameplayScene::_getNodeForCharacterPosition() {
  auto position = this->getGame()->getCharacterPosition();
  auto name = this->getGame()->getDungeon()->nameForPosition(position);
  return this->_getObjectsLayer()->getChildByName(name);
}

Vector<Node*> GameplayScene::_getNodesForAdjacentCharacterPosition() {
  Node* activeLayer = this->_getObjectsLayer();
  auto overlayLayer = this->getChildByName(OVERLAY_LAYER_NAME);
  if (overlayLayer) {
    activeLayer = overlayLayer;
  }
  
  Vector<Node*> nodes;
  
  auto position = this->getGame()->getCharacterPosition();
  auto adjacentPositions = this->getGame()->getDungeon()->adjacentPositionsTo(position);
  for (auto adjacentPosition : adjacentPositions) {
    auto name = this->getGame()->getDungeon()->nameForPosition(adjacentPosition);
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
  
  for (auto adjacentNode : this->_getNodesForAdjacentCharacterPosition()) {
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
  }
}

void GameplayScene::_handleTurnHasEnded(EventCustom* event) {
  log("turn has ended");
  
  auto turn = (Turn*) event->getUserData();
  
  if (IS(turn, PlayerTurn)) {
    this->_getControlsLayer()->runAction(Hide::create());
  }
}

void GameplayScene::_handleActionDiceDragStarted(EventCustom* event) {
  log("drag started");
  
  auto layer = (PlayerSkillsLayer*) this->_getControlsLayer()->getChildByName(PLAYER_SKILL_LAYER_NAME);
  auto dockableNodes = layer->getDockableNodes();
  this->_addOverlayWithVisibleNodes(dockableNodes);
  
  auto data = (ActionDiceDragData*) event->getUserData();
  auto sprite = data->getSprite();
  sprite->runAction(ScaleTo::create(0.2, 0.6));
}

void GameplayScene::_handleActionDiceDragMoved(EventCustom* event) {
  auto layer = (PlayerSkillsLayer*) this->_getControlsLayer()->getChildByName(PLAYER_SKILL_LAYER_NAME);
  auto data = (ActionDiceDragData*) event->getUserData();
  
  auto touchLocation = layer->convertTouchToNodeSpace(data->getTouch());
  data->getSprite()->setPosition(touchLocation);
  
  auto dockableContainer = this->getInteractableNodes().at(0)->getParent();
  auto dockableLocation = dockableContainer->convertTouchToNodeSpaceAR(data->getTouch());
  
  for (auto node : this->getInteractableNodes()) {
    Color3B color = Color3B::WHITE;
    
    if (node->getBoundingBox().containsPoint(dockableLocation)) {
      color = Color3B(170, 255, 170);
    }
    
    node->setColor(color);
  }
}

void GameplayScene::_handleActionDiceDragEnded(EventCustom* event) {
  auto layer = (PlayerSkillsLayer*) this->_getControlsLayer()->getChildByName(PLAYER_SKILL_LAYER_NAME);
  auto data = (ActionDiceDragData*) event->getUserData();
  auto sprite = data->getSprite();
  auto touchLocation = layer->convertTouchToNodeSpace(data->getTouch());
  
  auto dockableContainer = this->getInteractableNodes().at(0)->getParent();
  auto dockableLocation = dockableContainer->convertTouchToNodeSpaceAR(data->getTouch());
  
  bool moved = false;
  for (auto node : this->getInteractableNodes()) {
    if (node->getBoundingBox().containsPoint(dockableLocation)) {
      moved = true;
      break;
    }
  }
  
  log("drag ended");
  if (moved) {
    log("animate move");
  } else {
    auto move = MoveTo::create(0.2, sprite->getOriginalPosition());
    auto scale = ScaleTo::create(0.2, 1);
    
    sprite->runAction(Spawn::create(move, scale, NULL));
    log("animate back");
  }
  
  this->_removeOverlay();
}

void GameplayScene::_handleActionDicesRolled(EventCustom* event) {
  auto actionDicesLayer = (ActionDiceLayer*) event->getUserData();
  
  for (auto dice : actionDicesLayer->getDices()) {
    auto sprite = (ActionDiceSprite*) dice->getSprite();
    CC_SAFE_RETAIN(sprite);
    auto position = sprite->getParent()->getPosition();
    sprite->removeFromParent();
    
    auto newPosition = sprite->getPosition() + position;
    sprite->setPosition(newPosition);
    sprite->setOriginalPosition(newPosition);
    
    this->_getControlsLayer()->addChild(sprite);
    CC_SAFE_RELEASE(sprite);
  }
  
  actionDicesLayer->removeFromParent();
}

#pragma mark - CharacterMoveDelegate Methods

bool GameplayScene::canCharacterMove() {
  bool playerHasBoot = true;
  return this->_isInteractionEnabled() && playerHasBoot;
}

void GameplayScene::characterWillMove(CharacterDiceSprite* sprite) {
  Vector<Node*> visibleNodes;
  visibleNodes.pushBack(this->_getObjectsLayer()->getChildByName(CHARACTER_DICE_SPRITE_NAME));
  visibleNodes.pushBack(this->_getNodeForCharacterPosition());
  visibleNodes.pushBack(this->_getNodesForAdjacentCharacterPosition());
  this->_addOverlayWithVisibleNodes(visibleNodes);
}

void GameplayScene::characterIsMovingToLocation(Vec2 location) {
  for (auto adjacentNode : this->_getNodesForAdjacentCharacterPosition()) {
    Color3B color = Color3B::WHITE;
    
    if (adjacentNode->getBoundingBox().containsPoint(location)) {
      color = Color3B(170, 255, 170);
    }
    
    adjacentNode->setColor(color);
  }
}

bool GameplayScene::canCharacterMoveToLocation(Vec2 location) {
  bool canMove = false;
  
  for (auto adjacentNode : this->_getNodesForAdjacentCharacterPosition()) {
    if (adjacentNode->getBoundingBox().containsPoint(location)) {
      canMove = true;
      break;
    }
  }
  
  return canMove;
}

void GameplayScene::characterMovedToLocation(CharacterDiceSprite* sprite, Vec2 location) {
  this->_resetCharacterMoveState();
  
  auto newCoordinate = this->_positionInGameCoordinate(location);
  auto newPosition = this->_positionInScene(newCoordinate);
  
  auto moveNewPosition = MoveTo::create(RETURN_CHARACTER_DURATION, newPosition);
  auto actionEnded = CallFunc::create([=]() {
    this->getGame()->setCharacterPosition(newCoordinate);
  });
  sprite->runAction(Sequence::create(moveNewPosition, actionEnded, NULL));
}

void GameplayScene::characterDidNotMove(CharacterDiceSprite* sprite) {
  this->_resetCharacterMoveState();
  
  auto coordinate = this->getGame()->getCharacterPosition();
  auto scenePosition = this->_positionInScene(coordinate);
  
  auto moveBack = MoveTo::create(RETURN_CHARACTER_DURATION, scenePosition);
  sprite->runAction(moveBack);
}
