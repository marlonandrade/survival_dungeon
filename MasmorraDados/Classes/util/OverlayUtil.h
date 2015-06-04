//
//  OverlayUtil.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#ifndef __MasmorraDados__OverlayUtil__
#define __MasmorraDados__OverlayUtil__

#include "cocos2d.h"

class OverlayUtil {
public:
  static void addOverlay(cocos2d::Vector<cocos2d::Node*> nodes, cocos2d::Node* node);
  static void addOverlay(cocos2d::Vector<cocos2d::Node*> nodes, cocos2d::Node* node, cocos2d::Vec2 position);
  static void removeOverlay(cocos2d::Node* node);
};

#endif /* defined(__MasmorraDados__OverlayUtil__) */
