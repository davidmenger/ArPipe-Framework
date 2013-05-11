//
//  BaseFrameSource.h
//  AR
//
//  Created by Menger David on 17.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__BaseFrameSource__
#define __AR__BaseFrameSource__

#include <iostream>
#include <vector>
#include "BaseFrameContainer.h"

namespace ArPipe {
    
    class BasePipe;

    class BaseFrameSource {
    
    public:
        ~BaseFrameSource();
        BasePipe* addNextPipe(BasePipe *pipe);
        void pushFrameConainerToNextPipes(BaseFrameContainer *container, bool dontDeleteFrame = false);
        
    protected:
        std::vector<BasePipe*> nextPipes;
        
        
        
    };
    
}

#endif /* defined(__AR__BaseFrameSource__) */
