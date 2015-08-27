//
//  MagicBrick.cpp
//  CactusPacker
//
//  Created by Suu on 28/07/2015.
//  Copyright (c) 2015 suu. All rights reserved.
//

#include "MagicBrick.h"

MagicBrick::MagicBrick(char *fileData)
{
    //Initiate Brick Information
    this->previousBrick = NULL;
    this->rawData = fileData;
    this->brickName = "Magic";
    this->brickType = MAGIC;
    this->brickOrder = 0;
    this->size = 0x4;
    this->dataOffset = 0;
    
    #ifdef DEBUG
    DEBUG_COUT << endl << "=Building Brick: " << this->brickName << endl;
    DEBUG_COUT << "Type: 0x" << hex << this->brickType << endl;
    DEBUG_COUT << "Order: 0x" << this->brickOrder << endl;
    #endif
    
    //Get Magic
    this->magic = readWordByOffset(fileData, 0);
    #ifdef DEBUG
    DEBUG_COUT << "Magic: 0x" << hex << this->magic << endl;
    #endif
    
    //Estimate Fat or not
    if (magic != FAT_MAGIC)
    {
        isFat = false;
        
        //Estimate if it is an Executable file and Get header size
        if (magic == MH_MAGIC_64)
        {
            #ifdef DEBUG
            DEBUG_COUT << "64-bit file"<< endl;
            #endif
            
            #ifdef DEBUG
            DEBUG_COUT << "=Build ended" << endl << endl;
            #endif
            
            //Create Header Brick(next)
            MachoHeaderBrick *header = new MachoHeaderBrick(this, &fileData[4], "Header64", 1, 28);
            this->nextBrick = header;
        }
        else if (magic == MH_MAGIC)
        {
            #ifdef DEBUG
            DEBUG_COUT << "32-bit file(NOT SUPPORTED)"<< endl;
            #endif
            
            #ifdef DEBUG
            DEBUG_COUT << "=Build ended" << endl << endl;
            #endif
            //Create Header Brick(next)
            //MachoHeaderBrick *header = new MachoHeaderBrick(this, &fileData[4], "Header32", 1, 0x1b-4);
            //this->nextBrick = header;
        }
        else
        {
            cout << "Magic: 0x" << hex << magic << " not supported" << endl;
            return;
        }
    }
    else
    {
        isFat = true;
        cout << "Fat file not supported" << endl;
        return;
    }
}