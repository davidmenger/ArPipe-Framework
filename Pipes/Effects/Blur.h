//
//  Blur.h
//  AR
//
//  Created by Menger David on 07.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__Blur__
#define __AR__Blur__

#include <iostream>
#include "BasePipe.h"

namespace ArPipe {
    
    class Blur : public BasePipe
    {
    public:
        Blur(BaseFrameSource *previousPipe) : BasePipe(previousPipe) {
            Blur();
        }
        Blur() : BasePipe() {
            kernelLength = 10;
            type = ARP_BLUR_STANDARD;
        }
        static Blur* init() {
            return new Blur();
        }
        
        static Blur* init(int depth) {
            return Blur::init()->setDepth(depth);
        }
        
        bool processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        
        Blur* setType(int type)
        {
            type = type;
            return this;
        }
        
        Blur* setDepth(int depth)
        {
            kernelLength = depth;
            return this;
        }
        
        Blur* setTypeGaussian()
        {
            type = ARP_BLUR_GAUSSIAN;
            return this;
        }
        
        Blur* setTypeMedian()
        {
            type = ARP_BLUR_MEDIAN;
            return this;
        }
        
        Blur* setTypeBilateral()
        {
            type = ARP_BLUR_BILATERAL;
            return this;
        }
    
    protected:
        int kernelLength;
        enum {ARP_BLUR_STANDARD, ARP_BLUR_GAUSSIAN, ARP_BLUR_MEDIAN, ARP_BLUR_BILATERAL} type;
        
    };
    
}


#endif /* defined(__AR__Blur__) */
