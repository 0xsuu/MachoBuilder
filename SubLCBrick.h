//
//  SubLCBrick.h
//  CactusPacker
//
//  Created by Suu on 12/06/2015.
//  Copyright (c) 2015 suu. All rights reserved.
//

#ifndef __CactusPacker__SubLCBrick__
#define __CactusPacker__SubLCBrick__

#include <iostream>

#include "Brick.h"
#include "DataBrick.h"

class SubLCBrick : public Brick
{
public: SubLCBrick(Brick *pre, char *fileData, int count);

public:
    DataBrick *myData;
    
private:
    uint32_t dataSize;
    uint32_t dataOffset;
    
    string readName();
};

#endif /* defined(__CactusPacker__SubLCBrick__) */
