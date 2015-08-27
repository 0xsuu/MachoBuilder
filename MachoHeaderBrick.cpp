//
//  MagicHeaderBrick.cpp
//  CactusPacker
//
//  Created by Suu on 12/06/2015.
//  Copyright (c) 2015 suu. All rights reserved.
//

#include "MachoHeaderBrick.h"
#include "LCBrick.h"

MachoHeaderBrick::MachoHeaderBrick(Brick *pre, char *fileData, string Name, int order, int size)
{
    //Initiate Brick Information
    this->previousBrick = pre;
    this->rawData = fileData;
    this->brickName = Name;
    this->brickType = HEADER;
    this->brickOrder = order;
    this->size = size;
    this->getOffset();
    
    #ifdef DEBUG
    DEBUG_COUT << "=Building Brick: " << this->brickName << endl;
    DEBUG_COUT << "Type: 0x" << hex << this->brickType << endl;
    DEBUG_COUT << "Order: 0x" << this->brickOrder << endl;
    #endif
    
    //Collect Information
    this->NumberLC = readWordByOffset(this->rawData, 0x10-4);
    this->SizeLC = readWordByOffset(this->rawData, 0x14-4);
    this->flags = readWordByOffset(this->rawData, 0x18-4);
    #ifdef DEBUG
    DEBUG_COUT << "Number of Load Commands: 0x" << this->NumberLC << endl;
    DEBUG_COUT << "Size of Load Commands: 0x" << this->SizeLC << endl;
    DEBUG_COUT << "Flags: 0x" << this->flags << endl;
    #endif
    
    #ifdef DEBUG
    DEBUG_COUT << "=Build ended" << endl << endl;
    #endif
    
    //Generate Next Brick
    LCBrick *next = new LCBrick(this, &fileData[this->size], this->brickOrder+1, this->NumberLC, this->NumberLC);
    this->nextBrick = next;
}

