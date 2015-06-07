//
//  DamageTakenData.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/7/15.
//
//

#ifndef __MasmorraDados__DamageTakenData__
#define __MasmorraDados__DamageTakenData__

#include "GameObject.h"

class DamageTakenData : public GameObject {
  CC_SYNTHESIZE(int, _damage, Damage);
  CREATE_FUNC(DamageTakenData);
};

#endif /* defined(__MasmorraDados__DamageTakenData__) */
