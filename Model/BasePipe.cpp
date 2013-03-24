//
//  BasePipe.cpp
//  AR
//
//  Created by Menger David on 17.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "BasePipe.h"

namespace ArPipe {
    
    void BasePipe::pushNewFrameContainer(BaseFrameContainer *frm, BaseFrameSource *src) {
        if (nextPipe) {
            nextPipe->pushNewFrameContainer(frm, this);
        }
    }
    
}