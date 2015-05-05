//
//  MonsterDice.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 5/3/15.
//
//

#include "MonsterDice.h"

#include "Images.h"

#include "DiceFace.h"

USING_NS_CC;

#pragma mark - Public Interface

//MonsterDice* MonsterDice::createWithFaces(DiceFaces faces) {
//  auto dice = new (std::nothrow) MonsterDice;
//  if (dice && dice->initWithFaces(faces)) {
//    dice->autorelease();
//  } else {
//    CC_SAFE_DELETE(dice);
//  }
//  return dice;
//}

bool MonsterDice::init() {
  DiceFaces faces;
  
  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MINOR_GOBLIN));
  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MINOR_CULTISTA));
  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MINOR_ESQUELETO));
  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MINOR_ORC));
  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MINOR_ARANHA));
  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MINOR_CARNICAL));
  
  if (!Dice::initWithFaces(faces)) {
    return false;
  }
  
  this->setBlurImagePath(IMG_DICE_MONSTER_MINOR_BLUR);
  
  return true;
}

//MonsterDice* MonsterDice::createMinorMonsterDice() {
//  DiceFaces faces;
//  
//  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MINOR_GOBLIN));
//  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MINOR_CULTISTA));
//  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MINOR_ESQUELETO));
//  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MINOR_ORC));
//  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MINOR_ARANHA));
//  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MINOR_CARNICAL));
//  
//  auto dice =  MonsterDice::createWithFaces(faces);
//  if (dice) {
//    dice->setBlurImagePath(IMG_DICE_MONSTER_MINOR_BLUR);
//  }
//  
//  return dice;
//}
//
//MonsterDice* MonsterDice::createMajorMonsterDice() {
//  DiceFaces faces;
//  
//  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MAJOR_OGRO));
//  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MAJOR_MORCEGO_GIGANTE));
//  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MAJOR_CUBO_GELATINOSO));
//  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MAJOR_APARICAO));
//  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MAJOR_OBSERVADOR_SOMBRIO));
//  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MAJOR_DRAGAO_JOVEM));
//  
//  auto dice = MonsterDice::createWithFaces(faces);
//  if (dice) {
//    dice->setBlurImagePath(IMG_DICE_MONSTER_MAJOR_BLUR);
//  }
//  
//  return dice;
//}