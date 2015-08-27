//
//  MagicBrick.h
//  CactusPacker
//
//  Created by Suu on 28/07/2015.
//  Copyright (c) 2015 suu. All rights reserved.
//

#ifndef __CactusPacker__MagicBrick__
#define __CactusPacker__MagicBrick__

#include <iostream>

#include "Brick.h"
#include "MachoHeaderBrick.h"

class MagicBrick : public Brick
{
public:MagicBrick(char *fileData);
    
private:
    uint32_t magic;
    
public:
    bool isFat;
};
#endif /* defined(__CactusPacker__MagicBrick__) */
