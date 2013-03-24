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

namespace ArPipe {
    
    class BasePipe;

    class BaseFrameSource {
    
    public:
        ~BaseFrameSource();
        void setNextPipe(BasePipe *pipe);
        BasePipe* getNextPipe();
        
    protected:
        BasePipe *nextPipe;
        
    };
    
}

#endif /* defined(__AR__BaseFrameSource__) */
