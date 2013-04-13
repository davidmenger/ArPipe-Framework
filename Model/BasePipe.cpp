//
//  BasePipe.cpp
//  AR
//
//  Created by Menger David on 17.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "BasePipe.h"

namespace ArPipe {
    
    BasePipe::BasePipe()
    {
        
    }
    
    BasePipe::BasePipe(BaseFrameSource *previousPipe)
    {
        BasePipe::BasePipe();
        previousPipe->addNextPipe(this);
    }
    
    void BasePipe::processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *src)
    {
        // override this method
    }

    void BasePipe::pushNewFrameContainer(BaseFrameContainer *frm, BaseFrameSource *src) {
        this->processFrameContainer(frm, src);
        this->pushFrameConainerToNextPipes(frm);
    }
    
}