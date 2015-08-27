//
//  MagicHeaderBrick.h
//  CactusPacker
//
//  Created by Suu on 12/06/2015.
//  Copyright (c) 2015 suu. All rights reserved.
//

#ifndef __CactusPacker__MagicHeaderBrick__
#define __CactusPacker__MagicHeaderBrick__

#include <iostream>

#include "Brick.h"

class MachoHeaderBrick : public Brick
{
public: MachoHeaderBrick(Brick *pre, char *fileData, string Name, int order, int size);
    
private:
    uint32_t NumberLC;
    uint32_t SizeLC;
    uint32_t flags;
};
#endif /* defined(__CactusPacker__MagicHeaderBrick__) */
