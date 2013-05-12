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
    
    //! Class for image rotate in 90 degrees multiples
    class PolarRotate : public BasePipe
    {
    protected:
        int deg;
        
    public:
        /**
         * Constructor which determines angle to rotate image
         * @param degrees degrees to clockwise image rotate
         */
        PolarRotate(int degrees) : BasePipe() {
            this->setDeg(degrees);
        }
        
        /**
         * Factory to create image rotating pipe
         * @param degrees degrees to clockwise image rotate
         * @return new instance
         */
        static PolarRotate* init(int degrees) {
            PolarRotate* obj = new PolarRotate(degrees);
            return obj;
        }
        
        /**
         * Setter for degrees value
         * @param degrees degrees to clockwise image rotate
         * @return current pipe object. Supports fluent interface
         */
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
