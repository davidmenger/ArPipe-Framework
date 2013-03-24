//
//  BaseFrameSource.cpp
//  AR
//
//  Created by Menger David on 17.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "BaseFrameSource.h"
#include "BasePipe.h"

namespace ArPipe {
    
    
    void BaseFrameSource::setNextPipe(BasePipe *pipe)
    {
        nextPipe = pipe;
    }
    
    BasePipe* BaseFrameSource::getNextPipe()
    {
        return nextPipe;
    }
    
    BaseFrameSource::~BaseFrameSource()
    {
        delete nextPipe;
    }
    
    
}