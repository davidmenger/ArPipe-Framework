//
//  PipeOutputConnector.h
//  AR
//
//  Created by Menger David on 24.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__PipeOutputConnector__
#define __AR__PipeOutputConnector__

#include <iostream>
#include "BasePipeOutput.h"

namespace ArPipe {
    
    class PipeOutputConnector : public BasePipeOutput
    {
    public:
        void setOnNewFrameContainerCallback(void (*callback)(BaseFrameContainer *frm));
        void processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        
    protected:
        void (*newFrameCallback)(BaseFrameContainer *frm);
    };
    
}

#endif /* defined(__AR__PipeOutputConnector__) */
