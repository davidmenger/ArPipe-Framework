//
//  BasePipe.cpp
//  AR
//
//  Created by Menger David on 17.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "BasePipe.h"

namespace ArPipe {
    
    BasePipe::BasePipe(BaseFrameSource *previousPipe)
    {
        previousPipe->addNextPipe(this);
    }
    
    void BasePipe::pushNewFrameContainer(BaseFrameContainer *frm, BaseFrameSource *src)
    {
        containerToPush = frm;
        if (this->processFrameContainer(frm, src)) {
            this->pushFrameConainerToNextPipes(containerToPush);
        } else if (this->canDestroyUnprocessedContainer(frm, src)) {
            delete frm;
        }
        containerToPush = NULL;
    }
    
    bool BasePipe::canDestroyUnprocessedContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource)
    {
        return false;
    }
    
    template< class T>
        T BasePipe::init()
    {
        return new T();
    }
    
}