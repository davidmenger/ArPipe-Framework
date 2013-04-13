//
//  PipeLine.cpp
//  AR
//
//  Created by Menger David on 07.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "PipeLine.h"

namespace ArPipe {
    
    PipeLine::~PipeLine()
    {
        for (std::vector<BasePipe*>::iterator i = subPipes.begin(); i!=subPipes.end();) {
            if ((*i) != NULL) {
                delete *i;
                i = subPipes.erase(i);
            }  else {
                ++i;
            }
        }
        
    }
    
    void PipeLine::processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource)
    {
        BasePipe* src = this;
        for (std::vector<BasePipe*>::iterator i = subPipes.begin(); i != subPipes.end(); ++i) {
            (*i)->processFrameContainer(frm, src);
            src = (*i);
        }
    }
    
    PipeLine* PipeLine::addPipe(BasePipe* pipe)
    {
        subPipes.push_back(pipe);
        return this;
    }
    
    int PipeLine::getCount()
    {
        return subPipes.size();
    }
    
}