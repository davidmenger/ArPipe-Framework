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
    
    
    BaseFrameSource::~BaseFrameSource()
    {
    
    }
    
    void BaseFrameSource::addNextPipe(BasePipe *pipe)
    {
        nextPipes.push_back(pipe);
    }
    
    void BaseFrameSource::pushFrameConainerToNextPipes(BaseFrameContainer *container)
    {
        if (nextPipes.size() == 0) {
            delete container;
        } else {
            BaseFrameContainer *tmp = container;
            for(std::vector<BasePipe*>::iterator iterator = nextPipes.begin(); iterator != nextPipes.end(); ++iterator) {
                (*iterator)->pushNewFrameContainer(tmp, this);
                if ((iterator+1) != nextPipes.end()) {
                    tmp = tmp->clone();
                }
            }
        }
    }
    
    
}