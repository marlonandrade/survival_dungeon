//
//  Shake.cpp
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 4/16/15.
//
//

#include "Shake.h"

USING_NS_CC;

Shake* Shake::create(float duration, const Vec2 &strength) {
  auto *shake = new (std::nothrow) Shake();
  if (shake && shake->initWithDuration(duration, strength)) {
    shake->autorelease();
  } else {
    CC_SAFE_DELETE(shake);
  }
  
  return shake;
}

bool Shake::initWithDuration(float duration, const Vec2 &strength) {
  if (!ActionInterval::initWithDuration(duration)) {
    return false;
  }
  
  _strength = strength;
  
  return true;
}

Shake* Shake::clone() const {
  auto a = new (std::nothrow) Shake();
  a->initWithDuration(_duration, _strength);
  a->autorelease();
  return a;
}

void Shake::startWithTarget(Node* target) {
  ActionInterval::startWithTarget(target);
  
  _previousPosition = _startPosition = target->getPosition();
}

void Shake::stop(void) {
  _target->setPosition(_startPosition);
  ActionInterval::stop();
}

Shake* Shake::reverse() const {
  return Shake::create(_duration, -_strength);
}

void Shake::update(float time) {
  if (_target) {
#if CC_ENABLE_STACKABLE_ACTIONS
    auto currentPosition = _target->getPosition();
    auto diff = currentPosition - _previousPosition;
    _startPosition = _startPosition + diff;
    
    auto newPosition = this->_newPosition();
    _target->setPosition(newPosition);
    _previousPosition = newPosition;
#else
    auto newPosition = this->_newPosition();
    _target->setPosition(newPosition);
#endif
  }
}

Vec2 Shake::_newPosition() {
  float random = ((float)rand() / (float)RAND_MAX);
  float x = random * (2 * _strength.x) - _strength.x;
  float y = random * (2 * _strength.y) - _strength.y;
  return Vec2(x, y) + _startPosition;
}
