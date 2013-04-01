//
//  PipeOutputConnector.cpp
//  AR
//
//  Created by Menger David on 24.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "PipeOutputConnector.h"

namespace ArPipe {
    
    void PipeOutputConnector::pushNewFrameContainer(BaseFrameContainer *frm, BaseFrameSource *src) {
        if (newFrameCallback) {
            newFrameCallback(frm);
        }
        delete frm;
    }
    
    void PipeOutputConnector::setOnNewFrameContainerCallback(void (*callback)(BaseFrameContainer *frm))
    {
        newFrameCallback = callback;
        
    }
    
}