//
//  PipeLine.h
//  AR
//
//  Created by Menger David on 07.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__PipeLine__
#define __AR__PipeLine__

#include <iostream>
#include <vector>
#include "BasePipe.h"

namespace ArPipe {
    
    class PipeLine : public BasePipe
    {
    public:
        PipeLine(BaseFrameSource *previousPipe) : BasePipe(previousPipe) {}
        ~PipeLine();
        
        bool processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        PipeLine* addPipe(BasePipe* pipe);
        int getCount();
        BasePipe* operator[](int i) const { return subPipes[i]; };
        BasePipe* &operator[](int i) { return subPipes[i]; };
        
        BasePipe* front()
        {
            return subPipes.front();
        }
        
        BasePipe* back()
        {
            return subPipes.back();
        }
        
    protected:
        std::vector<BasePipe*> subPipes;
    };
    
}

#endif /* defined(__AR__PipeLine__) */
