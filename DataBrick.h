//
//  DataBrick.h
//  CactusPacker
//
//  Created by Suu on 12/06/2015.
//  Copyright (c) 2015 suu. All rights reserved.
//

#ifndef __CactusPacker__DataBrick__
#define __CactusPacker__DataBrick__

#include <iostream>

#include "Brick.h"

class DataBrick : public Brick
{
public: DataBrick(Brick *pre, uint32_t dataSize, uint32_t dataOffset);
    
public:

    void getEntireFileData();
};

#endif /* defined(__CactusPacker__DataBrick__) */
