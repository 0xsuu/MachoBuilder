//
//  HeaderBrick.cpp
//  CactusPacker
//
//  Created by Suu on 12/06/2015.
//  Copyright (c) 2015 suu. All rights reserved.
//

#include "LCBrick.h"

LCBrick::LCBrick(Brick *pre, char *fileData, int order, int number, int counter)
{
    //Unique Initiation
    this->numberOfBricks = number;
    counter --;
    
    //Base Initiation
    this->previousBrick = pre;
    this->rawData = fileData;
    this->brickType = readWordByOffset(this->rawData, 0x0);
    if (this->brickType == LC_SEGMENT_64)
    {
        this->brickName = readLCName();
    }
    else
    {
        this->brickName = "OtherLC";
    }
    
    this->brickOrder = order;
    this->size = readWordByOffset(this->rawData, 0x4);
    this->getOffset();
    this->rootSubLCBrick = NULL;
    
    #ifdef DEBUG
    DEBUG_COUT << "=Building Brick: " << this->brickName << endl;
    DEBUG_COUT << "Type: 0x" << hex << this->brickType << endl;
    DEBUG_COUT << "Order: 0x" << this->brickOrder << endl;
    #endif
    
    //Collect Information
    this->command = readWordByOffset(this->rawData, 0x0);
    this->commandSize = readWordByOffset(this->rawData, 0x4);
    if (this->brickType == LC_SEGMENT_64)
    {//Block Contains Data Block
        this->VMAddress = readWordByOffset(this->rawData, 0x18);
        this->VMSize = readWordByOffset(this->rawData, 0x20);
        this->fileOffset = readWordByOffset(this->rawData, 0x28);
        this->fileSize = readWordByOffset(this->rawData, 0x30);
        this->maxVMProtection = readWordByOffset(this->rawData, 0x38);
        this->initialVMProtection = readWordByOffset(this->rawData, 0x3c);
        this->numberOfSections = readWordByOffset(this->rawData, 0x40);
        if (this->numberOfSections != 0 && this->fileSize != 0)
        {//Build SubLCBricks
            this->rootSubLCBrick = new SubLCBrick(this, &this->rawData[0x48], this->numberOfSections);
        }
    }
    else if (this->brickType == LC_MAIN)
    {
        this->entryPoint = readWordByOffset(this->rawData, 0x8);
    }
    else if (this->brickType == LC_UNIXTHREAD)
    {
        this->entryPoint = readWordByOffset(this->rawData, 0x90);
    }
    
    
    #ifdef DEBUG
    DEBUG_COUT << "=Build ended" << endl << endl;
    #endif
    
    //Build Next
    if (counter > 0)
    {
        LCBrick *next = new LCBrick(this, &this->rawData[this->size], order+1, number, counter);
        this->nextBrick = next;
    }
    else
    {
        this->nextBrick = NULL;
    }
}

string LCBrick::readLCName()
{
    string retStr;
    for (int i = 8; i < 24; i++)
    {
        retStr += this->rawData[i];
    }
    return retStr;
}

void LCBrick::applyVMProtection()
{
    char *max = new char[4];
    char *init = new char[4];
    for (int i=0; i<4; i++)
    {
        max[i] = (this->maxVMProtection & (0xff << (i*8))) >> (i*8);
        init[i] = (this->initialVMProtection & (0xff << (i*8))) >> (i*8);
    }
    memcpy(&this->rawData[0x38], max, 4*sizeof(char));
    memcpy(&this->rawData[0x3c], init, 4*sizeof(char));
    delete(max);
    delete(init);
}

//Public Method
void LCBrick::addVMProtectionFlag(int addedFlag)
{
    this->maxVMProtection = this->maxVMProtection | addedFlag;
    this->initialVMProtection = this->initialVMProtection | addedFlag;
    applyVMProtection();
}
void LCBrick::removeVMProtectionFlag(int removedFlag)
{
    this->maxVMProtection = this->maxVMProtection & (removedFlag ^ 0xffffffff);
    this->initialVMProtection = this->initialVMProtection & (removedFlag ^ 0xffffffff);
    applyVMProtection();
}
void LCBrick::makeReadable()
{
    this->addVMProtectionFlag(VM_PROT_READ);
}
void LCBrick::makeWritable()
{
    this->addVMProtectionFlag(VM_PROT_WRITE);
}
void LCBrick::makeExecutable()
{
    this->addVMProtectionFlag(VM_PROT_EXECUTE);
}

void LCBrick::setEntryPoint(uint64_t ent)
{
    if (this->brickType == LC_MAIN)
    {
        char *ent_c = new char[8];
        for (int i=0; i<8; i++)
        {
            ent_c[i] = ent & 0xff;
            ent = ent >> 8;
        }
        
        memcpy(&this->rawData[0x8], ent_c, 8*sizeof(char));
        this->entryPoint = readWordByOffset(this->rawData, 0x8);
    }
    else if (this->brickType == LC_UNIXTHREAD)
    {
        char *ent_c = new char[8];
        ent += 0x0000000100000000;
        for (int i=0; i<8; i++)
        {
            ent_c[i] = ent & 0xff;
            ent = ent >> 8;
        }
        
        memcpy(&this->rawData[0x90], ent_c, 8*sizeof(char));
        this->entryPoint = readWordByOffset(this->rawData, 0x90);
    }
}
