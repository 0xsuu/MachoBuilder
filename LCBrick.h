//
//  HeaderBrick.h
//  CactusPacker
//
//  Created by Suu on 12/06/2015.
//  Copyright (c) 2015 suu. All rights reserved.
//

#ifndef __CactusPacker__HeaderBrick__
#define __CactusPacker__HeaderBrick__

#include <iostream>

#include "Brick.h"
#include "SubLCBrick.h"

class LCBrick: public Brick
{
public:LCBrick(Brick *pre, char *fileData, int order ,int number, int counter);
    
public:
    SubLCBrick *rootSubLCBrick;
    //LC_MAIN
    uint64_t entryPoint;
    
    //LC_Segment_64
    void addVMProtectionFlag(int addedFlag);
    void removeVMProtectionFlag(int removedFlag);
    void makeReadable();
    void makeWritable();
    void makeExecutable();
    
    //LC_MAIN
    void setEntryPoint(uint64_t ent);
    
private:
    uint32_t command;
    uint32_t commandSize;
    
    //LC_Segment_64
    uint32_t VMAddress;
    uint32_t VMSize;
    uint32_t fileOffset;
    uint32_t fileSize;
    uint32_t maxVMProtection;
    uint32_t initialVMProtection;
    uint32_t numberOfSections;
    
    int numberOfBricks;
    
    string readLCName();
    
    //LC_Segment_64
    void applyVMProtection();
};

#endif /* defined(__CactusPacker__HeaderBrick__) */
