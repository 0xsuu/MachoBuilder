//
//  SubLCBrick.cpp
//  CactusPacker
//
//  Created by Suu on 12/06/2015.
//  Copyright (c) 2015 suu. All rights reserved.
//

#include "SubLCBrick.h"

SubLCBrick::SubLCBrick(Brick *pre, char *fileData, int count)
{
    //Base initiation
    this->previousBrick = pre;
    this->rawData = fileData;
    this->size = 0x50;
    this->getOffset();
    this->brickName = this->readName();
    this->brickOrder = NOT_ORDERED;
    this->brickType = SUBLCBRICK;
    
    count --;
    
    #ifdef DEBUG
    DEBUG_COUT << "  =Building Sub Brick: " << this->brickName << endl;
    #endif
    
    //Unique Initiation
    this->dataSize = readWordByOffset(this->rawData, 0x28);
    this->dataOffset = readWordByOffset(this->rawData, 0x30);
    
    //Build data brick under this brick
    this->myData = new DataBrick(this, this->dataSize, this->dataOffset);
    
    #ifdef DEBUG
    DEBUG_COUT << "  =Sub Brick Building ended" << endl;
    #endif
    
    //Build next brick
    if (count != 0)
    {
        SubLCBrick *next = new SubLCBrick(this, &fileData[this->size], count);
        this->nextBrick = next;
    }
    else
    {
        this->nextBrick = NULL;
    }
}

string SubLCBrick::readName()
{
    string retStr;
    for (int i = 0; i < 0x10; i++)
    {
        retStr += this->rawData[i];
    }
    return retStr;
}
