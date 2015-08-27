//
//  DataBrick.cpp
//  CactusPacker
//
//  Created by Suu on 12/06/2015.
//  Copyright (c) 2015 suu. All rights reserved.
//

#include "DataBrick.h"

DataBrick::DataBrick(Brick *pre, uint32_t dataSize, uint32_t dataOffset)
{
    //Base initiation
    this->previousBrick = pre;
    this->nextBrick = NULL;
    this->brickName = "Data Brick";
    this->brickType = DATABRICK;
    this->brickOrder = NOT_ORDERED;
    
    this->size = dataSize;
    this->dataOffset = dataOffset;
    
    #ifdef DEBUG
    DEBUG_COUT << "    =Building Data Brick, offset: 0x" << hex << this->dataOffset << endl;
    #endif
    
    getEntireFileData();
    #ifdef DEBUG
    DEBUG_COUT << "    =Building ended" << endl;
    #endif
}

void DataBrick::getEntireFileData()
{
    Brick *tmp = this;
    while (tmp->previousBrick != NULL)
    {
        tmp = tmp->previousBrick;
    }
    this->rawData = &tmp->rawData[this->dataOffset];
    #ifdef DEBUG
    DEBUG_COUT << "    Raw Data first character: " << this->rawData[0] << endl;
    #endif
}