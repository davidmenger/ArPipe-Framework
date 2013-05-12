//
//  PipeMerge.cpp
//  AR
//
//  Created by Menger David on 11.05.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "PipeMerge.h"

using namespace cv;
namespace ArPipe {
    
    bool PipeMerge::processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource)
    {
        if (frameSource == frameSourcePipe) {
            frame = frm;
        } else if (frameSource == shapesSourcePipe) {
            shapes = frm;
        }
        if (frame != NULL && shapes != NULL) {
            this->processFrameAndShapes();
            
            frame->getShapes()->setMarkers(shapes->getShapes()->getMarkers());
            containerToPush = frame;
            delete this->shapes;
            this->shapes = NULL;
            
            return true;
        } else {
            return false;
        }
        
    }
    
    void PipeMerge::processFrameAndShapes()
    {
        
    }
}