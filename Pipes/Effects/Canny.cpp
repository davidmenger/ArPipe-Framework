//
//  Canny.cpp
//  AR
//
//  Created by Menger David on 07.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "Canny.h"
#include <opencv2/opencv.hpp>

namespace ArPipe {
    
    
    bool Canny::processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource) {
        
        cv::Canny(frm->getFrame()->getMat(), frm->getFrame()->getMat(), this->getLowerThreshold(frm->getFrame()), this->getUpperThreshold(frm->getFrame()));
        return true;
    }
    
    double Canny::getLowerThreshold(Frame* frm)
    {
        if (autoThresholds) {
            return frm->getDepth() * 0.06;
        } else {
            return lowerThreshold;
        }
    }
    
    double Canny::getUpperThreshold(Frame* frm)
    {
        if (autoThresholds) {
            return frm->getDepth() * 0.80;
        } else {
            return lowerThreshold;
        }
    }
    
}