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
#include "Shapes.h"


namespace ArPipe {
    
    
    
    class BaseFrameContainer {
      
    public:
        BaseFrameContainer(cv::Mat frameMat);
        BaseFrameContainer(Frame* frm);
        
        ~BaseFrameContainer();
        
        Frame* getFrame();
        Shapes* getShapes();
        
        BaseFrameContainer* clone();
        
        
        
    protected:
        Frame* frame;
        Shapes* shapes;
        
    };
    
}

#endif /* defined(__AR__BaseFrameContainer__) */
