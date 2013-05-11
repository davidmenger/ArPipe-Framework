//
//  Threshold.cpp
//  AR
//
//  Created by Menger David on 01.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "Threshold.h"


namespace ArPipe {
    
    Threshold::Threshold() : BasePipe()
    {
        type = cv::THRESH_BINARY_INV;
        adaptiveMethod = cv::ADAPTIVE_THRESH_MEAN_C;
        autoMax = true;
        blockSize = 9;
        adaptive = true;
    }
    
    Threshold::Threshold(BaseFrameSource *previousPipe): BasePipe(previousPipe)
    {
        Threshold();
    }
    
    bool Threshold::processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource)
    {
        cv::Mat mat = frm->getFrame()->getMat().clone();
        if (adaptive) {
            double maxx = this->getCalcedMaxValue(frm->getFrame());
            cv::adaptiveThreshold(mat, frm->getFrame()->getMat(), maxx, adaptiveMethod, type, blockSize, blockSize);
        } else {
            cv::threshold(mat, frm->getFrame()->getMat(), thresh, this->getCalcedMaxValue(frm->getFrame()), type);
        }
        mat.release();
        return true;
    }
    
    double Threshold::getCalcedMaxValue(Frame* const mat)
    {
        if (autoMax) {
            return mat->getDepth();
        } else {
            return maxval;
        }
    }
    
}

