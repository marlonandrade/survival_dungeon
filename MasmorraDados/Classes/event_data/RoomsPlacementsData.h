//
//  RoomsPlacementsData.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 5/17/15.
//
//

#ifndef __MasmorraDados__RoomsPlacementsData__
#define __MasmorraDados__RoomsPlacementsData__

#include "GameObject.h"

#include "RoomPlacementData.h"

class RoomsPlacementsData : public GameObject {
  CC_SYNTHESIZE(cocos2d::Vector<RoomPlacementData*>, _placements, Placements);
  CREATE_FUNC(RoomsPlacementsData);
};

#endif /* defined(__MasmorraDados__RoomsPlacementsData__) */
