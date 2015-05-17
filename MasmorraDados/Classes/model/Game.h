//
//  Game.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 15/02/2015.
//
//

#ifndef __MasmorraDados__Game__
#define __MasmorraDados__Game__

#include "cocos2d.h"

#include "ActionDice.h"
#include "Dungeon.h"
#include "DungeonRoom.h"
#include "GameObject.h"

class Turn;

class Game : public GameObject {
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _freeBootSpentListener,
                       FreeBootSpentListener);
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _diceSpentListener,
                       DiceSpentListener);
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _endPlayerTurnListener,
                       EndPlayerTurnListener);
  
  CC_SYNTHESIZE_RETAIN(Dungeon*, _dungeon, Dungeon);
  CC_SYNTHESIZE(cocos2d::Vector<ActionDice*>, _actionDices, ActionDices);
  CC_SYNTHESIZE(bool, _freeBootUsed, FreeBootUsed);
  CC_PROPERTY(int, _level, Level);
protected:
  cocos2d::Vector<DungeonRoom*> _availableRooms;
  Turn* _turn;
  cocos2d::Vec2 _characterCoordinate;
  
public:
  static Game* getInstance();
  
  virtual bool init();
  
  virtual Turn* getTurn(void) const { return _turn; }
  virtual void setTurn(Turn* turn);
  
  virtual cocos2d::Vec2 getCharacterCoordinate(void) const { return _characterCoordinate; }
private:
  virtual void setCharacterCoordinate(cocos2d::Vec2 coordinate);
public:
  void setupCharacterInitialCoordinate();
  void characterMovedTo(cocos2d::Vec2 coordinate);
  
  virtual cocos2d::Vector<ActionDice*> getDockedDices();
  virtual cocos2d::ValueMap getAvailableSkills();
  
  virtual bool isInitialTurn();
  virtual bool isPlayerTurn();
  virtual void executeCurrentTurn();
  virtual void finishCurrentTurn();
  virtual void restoreFreeBoot();
  
private:
  void _setupDungeon();
  void _setupAvaiableRooms();
  void _setupActionDices();
  void _setupEventHandlers();
  
  DungeonRoom* _pickRandomRoom();
  
  void _dispatchDiceSpent();
  
#pragma mark - Event Handlers
  void _handleActionFreeBootSpent(cocos2d::EventCustom* event);
  void _handleActionDiceSpent(cocos2d::EventCustom* event);
  void _handleEndPlayerTurn(cocos2d::EventCustom* event);
};

#endif /* defined(__MasmorraDados__Game__) */
