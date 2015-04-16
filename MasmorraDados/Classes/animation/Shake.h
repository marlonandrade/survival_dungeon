//
//  Shake.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/16/15.
//
//

#ifndef __MasmorraDados__Shake__
#define __MasmorraDados__Shake__

#include "cocos2d.h"

class Shake : public cocos2d::ActionInterval {
public:
  static Shake* create(float duration, const cocos2d::Vec2& strength);
  
  virtual Shake* clone() const override;
  virtual Shake* reverse(void) const override;
  virtual void startWithTarget(cocos2d::Node *target) override;
  virtual void stop(void) override;
  virtual void update(float time) override;
  
CC_CONSTRUCTOR_ACCESS:
  Shake() {}
  virtual ~Shake() {}
  
  bool initWithDuration(float duration, const cocos2d::Vec2& strength);
  
protected:
  cocos2d::Vec2 _startPosition;
  cocos2d::Vec2 _previousPosition;
  cocos2d::Vec2 _strength;
  
private:
  CC_DISALLOW_COPY_AND_ASSIGN(Shake);
  cocos2d::Vec2 _newPosition();
};

#endif /* defined(__MasmorraDados__Shake__) */
