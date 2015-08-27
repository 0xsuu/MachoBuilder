//
//  MachoFile.cpp
//  CactusPacker
//
//  Created by Suu on 12/06/2015.
//  Copyright (c) 2015 suu. All rights reserved.
//

#include "MachoFile.h"

MachoFile::MachoFile(string path)
{
    #ifdef DEBUG
        DEBUG_COUT << "MachoFile Constructor" << endl;
    #endif
    //Set file path
    this->filePath = path;
    
    //Is this file exists?
    if (this->fileExists(this->filePath))
    {
        //
        //Yes: Process file
        //
        #ifdef DEBUG
            DEBUG_COUT << "File exists" << endl;
        #endif
        //Read file
        this->fpRead.open(this->filePath.c_str(), ios::in | ios::binary);
        if (!this->fpRead.is_open())
        {
            cout << "Failed to open binary" << endl;
            return;
        }
        
        //Get file length
        this->fpRead.seekg(0, this->fpRead.end);
        this->fileLength = this->fpRead.tellg();
        this->fpRead.seekg(0, this->fpRead.beg);
        
        #ifdef DEBUG
            DEBUG_COUT << "File size: " << this->fileLength << " bytes" << endl;
        #endif
        
        
        //Read all data into buffer
        this->rawData = new char[this->fileLength];
        this->fpRead.read(this->rawData, fileLength * sizeof(char));
        
        //Construct root brick(macho magic brick)
        MagicBrick *magic = new MagicBrick(this->rawData);
        this->rootBrick = magic;
        
        //Close the file
        this->fpRead.close();
    }
    else
    {
        //
        //No: Create new file
        //
        #ifdef DEBUG
            DEBUG_COUT << "File does not exists, creating file" << endl;
        #endif
    }
}

MachoFile::~MachoFile()
{
    delete(this->rawData);
}

bool MachoFile::fileExists(string &name)
{
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

void MachoFile::reverseBit(char *dst, uint32_t ori, int size)
{
    //Check size befor call this function!!!!!
    for (int i=0; i<size; i++)
    {
        dst[i] = ori & 0xff;
        ori = ori >> 8;
    }    
}

//Documented Methods

//Modify
int MachoFile::replaceBrickDataWithBrickAndDataAndLength(Brick *thisBrick, char *data, int length)
{
    //Check Brick exsistence
    if (!thisBrick)
    {
        return -1;
    }
    
    //Check Length
    if (thisBrick->size != length)
    {
        return -2;
    }
    
    //Modify
    memcpy(thisBrick->rawData, data, length*sizeof(char));
    
    return 0;
}

int MachoFile::clearBrickData(Brick *thisBrick)
{
    //Check Brick exsistence
    if (!thisBrick)
    {
        return -1;
    }
    
    char *emptyData = new char[thisBrick->size];
    for (int i = 0; i < thisBrick->size; i++)
    {
        emptyData[i] = 0;
    }
    
    //Modify
    memcpy(thisBrick->rawData, emptyData, thisBrick->size*sizeof(char));
    
    return 0;
}

//Information
Brick * MachoFile::getBrickWithName(string name)
{
    Brick *tmp = this->rootBrick;
    SubLCBrick *tmpSubLC = nullptr;
    
    while (tmp != NULL && (tmp->brickName.compare(name)<0 || tmp->brickName.compare(name)>1) && !tmpSubLC)
    {
        if (tmp->brickType == LC_SEGMENT_64)
        {
            LCBrick *tmpLC = (LCBrick *)tmp;
            tmpSubLC = tmpLC->rootSubLCBrick;
            while (tmpSubLC != NULL && (tmpSubLC->brickName.compare(name)<0 || tmpSubLC->brickName.compare(name)>1))
            {
                tmpSubLC = (SubLCBrick *)tmpSubLC->nextBrick;
            }
        }
        tmp = tmp->nextBrick;
    }
    return !tmpSubLC?(!tmp?NULL:tmp):tmpSubLC;
}

Brick * MachoFile::getBrickWithType(uint32_t type)
{
    Brick *tmp = this->rootBrick;
    SubLCBrick *tmpSubLC = nullptr;
    
    while (tmp != NULL && tmp->brickType != type && !tmpSubLC)
    {
        if (tmp->brickType == LC_SEGMENT_64)
        {
            LCBrick *tmpLC = (LCBrick *)tmp;
            tmpSubLC = tmpLC->rootSubLCBrick;
            while (tmpSubLC != NULL && tmpSubLC->brickType != type)
            {
                tmpSubLC = (SubLCBrick *)tmpSubLC->nextBrick;
            }
        }
        tmp = tmp->nextBrick;
    }
    return !tmpSubLC?(!tmp?NULL:tmp):tmpSubLC;
}

void MachoFile::displayBrickInformation(Brick *someBrick)
{
    if (someBrick == NULL)
    {
        cout << "NULL Brick" << endl;
        return;
    }
    else
    {
        cout << "Brick Name: " << someBrick->brickName << endl;
        cout << "Type: 0x" << hex << someBrick->brickType << endl;
        cout << "Size: 0x" << someBrick->size << endl;
    }
}

//Save
void MachoFile::saveAs(string path)
{
    this->fpWrite.open(path.c_str(), ios::out | ios::binary);
    this->fpWrite.write(this->rawData, this->fileLength);
    this->fpWrite.close();
}
