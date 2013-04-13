//
//  FindContours.cpp
//  AR
//
//  Created by Menger David on 07.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "FindContours.h"


namespace ArPipe {
    
    void FindContours::processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource)
    {
        cv::Mat input = frm->getFrame()->getMat().clone();
        Shapes* shapes = frm->getShapes();
        
        
        cv::findContours( input, shapes->getContours(), shapes->getHierarchy(), mode, method );
        
        input.release();
    }
    
}