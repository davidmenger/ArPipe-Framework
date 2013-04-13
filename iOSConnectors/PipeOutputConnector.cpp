//
//  PipeOutputConnector.cpp
//  AR
//
//  Created by Menger David on 24.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "PipeOutputConnector.h"

namespace ArPipe {
    
    void PipeOutputConnector::processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *src) {
        if (newFrameCallback) {
            newFrameCallback(frm);
        }
    }
    
    void PipeOutputConnector::setOnNewFrameContainerCallback(void (*callback)(BaseFrameContainer *frm))
    {
        newFrameCallback = callback;
        
    }
    
}