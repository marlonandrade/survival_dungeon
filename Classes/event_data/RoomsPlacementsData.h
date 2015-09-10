//
//  RoomsPlacementsData.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 5/17/15.
//
//

#ifndef __SurvivalDungeon__RoomsPlacementsData__
#define __SurvivalDungeon__RoomsPlacementsData__

#include "GameObject.h"

#include "RoomPlacementData.h"

class RoomsPlacementsData : public GameObject {
  CC_SYNTHESIZE(cocos2d::Vector<RoomPlacementData*>, _placements, Placements);
  CREATE_FUNC(RoomsPlacementsData);
};

#endif /* defined(__SurvivalDungeon__RoomsPlacementsData__) */
