//
//  Canny.h
//  AR
//
//  Created by Menger David on 07.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__Canny__
#define __AR__Canny__

#include <iostream>
#include "BasePipe.h"

namespace ArPipe {
    
    //! Encapsulated OpenCV Threshold function
    /**
     * Canny function is useful for feature detection in image
     */
    class Canny : public BasePipe
    {
    public:
        Canny(BaseFrameSource *previousPipe) : BasePipe(previousPipe) {
            Canny();
        }
        Canny() : BasePipe() {
            autoThresholds = true;
        }
        
         /**
         * Factory to create new Canny pipe
         * @return new instance
         */
        static Canny* init() {
            return new Canny();
        }
        bool processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        
        /**
         * Sets static upper and lower threshold values
         * @param lower
         * @param upper
         * @return current pipe object. Supports fluent interface
         */
        Canny* setThresholds(double lower, double upper)
        {
            lowerThreshold = lower;
            upperThreshold = upper;
            autoThresholds = false;
            return this;
        }
        
        /**
        * Use Automatic threshold values
        * @return current pipe object. Supports fluent interface
        */
        Canny* setAutoThreshold()
        {
            autoThresholds = true;
            return this;
        }
        
    protected:
        double lowerThreshold;
        double upperThreshold;
        bool autoThresholds;
        
        double getLowerThreshold(Frame* frm);
        double getUpperThreshold(Frame* frm);
    
    };
}

#endif /* defined(__AR__Canny__) */
