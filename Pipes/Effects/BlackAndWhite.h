//
//  BlackAndWhite.h
//  AR
//
//  Created by Menger David on 06.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__BlackAndWhite__
#define __AR__BlackAndWhite__

#include <iostream>
#include "BasePipe.h"

namespace ArPipe {
    class BlackAndWhite : public BasePipe
    {
    public:
        BlackAndWhite() : BasePipe() {
            color = false;
        }
        BlackAndWhite(BaseFrameSource *previousPipe) : BasePipe(previousPipe) {}
        static BlackAndWhite* init() {
            return new BlackAndWhite();
        }
        void processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        
        BlackAndWhite* toColor()
        {
            color = true;
            return this;
        }
        
    protected:
        bool color;
        
    };
}

#endif /* defined(__AR__BlackAndWhite__) */
