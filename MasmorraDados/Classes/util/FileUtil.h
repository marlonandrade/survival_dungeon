//
//  FileUtil.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/18/15.
//
//

#ifndef __MasmorraDados__FileUtil__
#define __MasmorraDados__FileUtil__

#include "cocos2d.h"

class FileUtil {
public:
  static std::string characterFileName(int hitPoints);
  static std::string damageFileName(int damage);
  static std::string fileNameForBaseImage(std::string baseName, int amount);
};

#endif /* defined(__MasmorraDados__FileUtil__) */
