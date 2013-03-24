//
//  BaseFrameContainer.h
//  AR
//
//  Created by Menger David on 17.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__BaseFrameContainer__
#define __AR__BaseFrameContainer__

#include <iostream>
#include <opencv2/opencv.hpp>

#include "Frame.h"

namespace ArPipe {
    
    class BaseFrameContainer {
      
    public:
        BaseFrameContainer(Frame *frm);
        BaseFrameContainer(cv::Mat frameMat);
        
        ~BaseFrameContainer();
        
        Frame* getFrame();
        
    protected:
        Frame *frame;
        
    };
    
}

#endif /* defined(__AR__BaseFrameContainer__) */
