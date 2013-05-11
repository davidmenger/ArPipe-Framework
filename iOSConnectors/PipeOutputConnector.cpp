//
//  PipeOutputConnector.cpp
//  AR
//
//  Created by Menger David on 24.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "PipeOutputConnector.h"

namespace ArPipe {
    
    bool PipeOutputConnector::processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *src) {
        if (newFrameCallback) {
            newFrameCallback(frm);
        }
        return true;
    }
    
    void PipeOutputConnector::setOnNewFrameContainerCallback(void (*callback)(BaseFrameContainer *frm))
    {
        newFrameCallback = callback;
        
    }
    
}