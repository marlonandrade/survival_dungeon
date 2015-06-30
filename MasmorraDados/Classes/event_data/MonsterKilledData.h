//
//  MonsterKilledData.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/30/15.
//
//

#ifndef __MasmorraDados__MonsterKilledData__
#define __MasmorraDados__MonsterKilledData__

#include "GameObject.h"

#include "MonsterDice.h"

class MonsterKilledData : public GameObject {
  CC_SYNTHESIZE_RETAIN(MonsterDice*, _monsterDice, MonsterDice);
  
  CREATE_FUNC(MonsterKilledData);
};

#endif /* defined(__MasmorraDados__MonsterKilledData__) */
