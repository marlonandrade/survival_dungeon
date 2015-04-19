//
//  Dice.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__Dice__
#define __MasmorraDados__Dice__

#include "GameObject.h"

#include "DiceFace.h"
#include "DiceState.h"

typedef cocos2d::Vector<DiceFace*> DiceFaces;

class Dice : public GameObject {
  CC_PROPERTY(DiceFace*, _selectedFace, SelectedFace);
  CC_PROPERTY(DiceFaces, _faces, Faces);
  CC_SYNTHESIZE(cocos2d::Sprite*, _sprite, Sprite);
  CC_SYNTHESIZE(std::string, _blurImagePath, BlurImagePath);
  CC_SYNTHESIZE_RETAIN(DiceState*, _state, State);
public:
  static Dice* createWithFaces(DiceFaces faces);
  virtual bool initWithFaces(DiceFaces faces);
  
  virtual void roll();
  virtual void changeState();
  
  virtual bool isSelected();
};

#endif /* defined(__MasmorraDados__Dice__) */
