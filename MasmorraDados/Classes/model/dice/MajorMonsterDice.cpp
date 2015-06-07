//
//  MajorMonsterDice.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 5/3/15.
//
//

#include "MajorMonsterDice.h"

#include "Images.h"

#include "DiceFace.h"

USING_NS_CC;

#pragma mark - Public Interface

bool MajorMonsterDice::init() {
  DiceFaces faces;
  
  faces.pushBack(DiceFace::create(IMG_DICE_MONSTER_MAJOR_OGRO));
  faces.pushBack(DiceFace::create(IMG_DICE_MONSTER_MAJOR_MORCEGO_GIGANTE));
  faces.pushBack(DiceFace::create(IMG_DICE_MONSTER_MAJOR_CUBO_GELATINOSO));
  faces.pushBack(DiceFace::create(IMG_DICE_MONSTER_MAJOR_APARICAO));
  faces.pushBack(DiceFace::create(IMG_DICE_MONSTER_MAJOR_OBSERVADOR_SOMBRIO));
  faces.pushBack(DiceFace::create(IMG_DICE_MONSTER_MAJOR_DRAGAO_JOVEM));
  
  if (!MonsterDice::initWithFaces(faces)) {
    return false;
  }
  
  this->setBlurImagePath(IMG_DICE_MONSTER_MAJOR_BLUR);
  
  return true;
}
