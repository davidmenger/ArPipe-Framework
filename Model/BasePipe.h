//
//  BasePipe.h
//  AR
//
//  Created by Menger David on 17.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__BasePipe__
#define __AR__BasePipe__

#include <iostream>

#include "BaseFrameSource.h"
#include "BaseFrameContainer.h"

namespace ArPipe {
    
    
    class BasePipe : public BaseFrameSource {
  
    public:
        void pushNewFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        
        
    
    
    };
    
}

#endif /* defined(__AR__BasePipe__) */

