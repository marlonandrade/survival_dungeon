//
//  FileUtil.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/18/15.
//
//

#ifndef __SurvivalDungeon__FileUtil__
#define __SurvivalDungeon__FileUtil__

#include "GameObject.h"

typedef cocos2d::Map<std::string, cocos2d::Sprite*> SpriteMap;

class FileUtil : public GameObject {
  CC_SYNTHESIZE(SpriteMap, _damageDealtSprites, DamageDealtSprites);
  CC_SYNTHESIZE(SpriteMap, _damageTakenSprites, DamageTakenSprites);
  CC_SYNTHESIZE(SpriteMap, _monsterDiceSprites, MonsterDiceSprites);
  
public:
  static FileUtil* getInstance();
  
  std::string characterFileName(int hitPoints);
  std::string damageTakenFileName(int damage);
  std::string damageDealtFileName(int damage);
  std::string fileNameForBaseImage(std::string baseName, int amount);
  
  cocos2d::Sprite* damageTakenSprite(int damage);
  cocos2d::Sprite* damageDealtSprite(int damage);
};

#endif /* defined(__SurvivalDungeon__FileUtil__) */
