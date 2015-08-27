//
//  MachoFile.h
//  CactusPacker
//
//  Created by Suu on 12/06/2015.
//  Copyright (c) 2015 suu. All rights reserved.
//

#ifndef __CactusPacker__MachoFile__
#define __CactusPacker__MachoFile__

#include <iostream>
#include <fstream>
#include <string.h>

#include "Defines.h"

#include "Brick.h"
#include "MagicBrick.h"
#include "LCBrick.h"
#include "SubLCBrick.h"
#include "DataBrick.h"

using namespace std;

class MachoFile
{
public: MachoFile(string path);
public: ~MachoFile();
    
private:
    ifstream fpRead;
    ofstream fpWrite;
    
    bool fileExists(string &name);
    
public:
    string filePath;
    uint64_t fileLength;
    
    char *rawData;
    
    Brick *rootBrick;
    
    //Modify
    int replaceBrickDataWithBrickAndDataAndLength(Brick *thisBrick, char *data, int length);
    int clearBrickData(Brick *thisBrick);
    
    void reverseBit(char *dst, uint32_t ori, int size);
    
    //Information
    Brick *getBrickWithName(string name);
    Brick *getBrickWithType(uint32_t type);
    void displayBrickInformation(Brick *someBrick);
    
    //Save
    void saveAs(string path);
    
};

#endif /* defined(__CactusPacker__MachoFile__) */
