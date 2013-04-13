//
//  BaseFrameContainer.cpp
//  AR
//
//  Created by Menger David on 17.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "BaseFrameContainer.h"

namespace ArPipe {
    
    BaseFrameContainer::BaseFrameContainer(cv::Mat mat) {
        frame = new Frame(mat);
        shapes = NULL;
    }
    
    BaseFrameContainer::BaseFrameContainer(Frame* frm)
    {
        frame = frm;
        shapes = NULL;
    }

    Frame* BaseFrameContainer::getFrame()
    {
        return frame;
    }
    
    BaseFrameContainer::~BaseFrameContainer()
    {
        delete frame;
        if (shapes!=NULL) {
            delete shapes;
        }
    }
    
    BaseFrameContainer* BaseFrameContainer::clone()
    {
        BaseFrameContainer* cloned = new BaseFrameContainer(frame->clone());
        return cloned;
    }
    
    Shapes* BaseFrameContainer::getShapes()
    {
        if (shapes == NULL) {
            shapes = new Shapes();
        }
        return shapes;
    }
    
}