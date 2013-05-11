//
//  PolarRotate.h
//  AR
//
//  Created by Menger David on 01.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__PolarRotate__
#define __AR__PolarRotate__

#include <iostream>
#include "BasePipe.h"
#include <math.h>

namespace ArPipe {
    
    class PolarRotate : public BasePipe
    {
    protected:
        int deg;
        
    public:
        PolarRotate(int degrees) : BasePipe() {
            this->setDeg(degrees);
        }
        
        static PolarRotate* init(int degrees) {
            PolarRotate* obj = new PolarRotate(degrees);
            return obj;
        }
        
        PolarRotate* setDeg(int degrees) {
            if (degrees%90!=0) {
                deg = round(degrees/90)*90;
            } else {
                deg = degrees;
            }
            return this;
        }
        
        bool processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
    };
    
}

#endif /* defined(__AR__PolarRotate__) */
