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
    
    //! Converts Black And White image to color or back
    /**
     * Converting image to black and white can speed up feature detection
     */
    class BlackAndWhite : public BasePipe
    {
    public:
        BlackAndWhite() : BasePipe() {
            color = false;
        }
        BlackAndWhite(BaseFrameSource *previousPipe) : BasePipe(previousPipe) {}
        
        /**
         * Factory to create new BlackAndWhite pipe
         * @return new instance
         */
        static BlackAndWhite* init() {
            return new BlackAndWhite();
        }
        bool processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        
        /**
         * Convert BlackAndWhite image to color
         * @return current pipe object. Supports fluent interface
         */
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
