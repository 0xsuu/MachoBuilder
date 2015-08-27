//
//  Brick.cpp
//  CactusPacker
//
//  Created by Suu on 12/06/2015.
//  Copyright (c) 2015 suu. All rights reserved.
//

#include "Brick.h"

uint32_t Brick::readWordByOffset(char *data, uint32_t offset)
{
    //Little Endian
    uint32_t returnValue;
    
    returnValue = ((data[offset+3]&0xff)<<24)|
    ((data[offset+2]&0xff)<<16)|
    ((data[offset+1]&0xff)<<8)|
    ((data[offset]&0xff));
    
    return returnValue;
}

uint32_t Brick::wordToInt(char *data)
{
    return (data[0]&0xff)+(data[1]&0xff)+(data[2]&0xff)+(data[3]&0xff);
}

uint32_t Brick::getOffset()
{
    if (this->brickType == DATABRICK)
    {
        return this->dataOffset;
    }
    else
    {
        Brick *tmp = this->previousBrick;
        this->dataOffset = 0;
        while (tmp!=NULL)
        {
            this->dataOffset += tmp->size;
            tmp = tmp->previousBrick;
        }
        return  this->dataOffset;
    }
}