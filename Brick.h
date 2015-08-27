//
//  Brick.h
//  CactusPacker
//
//  Created by Suu on 12/06/2015.
//  Copyright (c) 2015 suu. All rights reserved.
//

#ifndef __CactusPacker__Brick__
#define __CactusPacker__Brick__

#include <iostream>
#include <string>

#include <sys/stat.h>

#include <mach-o/arch.h>
#include <mach-o/loader.h>
#include <mach-o/fat.h>

#include "Defines.h"

using namespace std;

class Brick
{
public: Brick()
    {
        
    }
public:
    uint32_t brickType;
    int brickOrder;
    string brickName;
    char *rawData;
    
    uint32_t size;
    uint32_t dataOffset;
    
    Brick *previousBrick;
    Brick *nextBrick;
    
    uint32_t readWordByOffset(char *data, uint32_t offset);
    uint32_t wordToInt(char *data);
    
    uint32_t getOffset();
};



#endif /* defined(__CactusPacker__Brick__) */
