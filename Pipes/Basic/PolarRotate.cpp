//
//  PolarRotate.cpp
//  AR
//
//  Created by Menger David on 01.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "PolarRotate.h"

namespace ArPipe {
    
    
    bool PolarRotate::processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource)
    {
        cv::Mat &mat = frm->getFrame()->getMat();
        int angle = deg%360;
        if (angle<0) {
            angle = 360 + angle;
        }
        
        if (angle == 90) {
            cv::transpose(mat, mat);
            cv::flip(mat, mat, 1);
        } else if (angle == 180) {
            cv::flip(mat, mat, -1);
        } else if (angle == 270) {
            cv::transpose(mat, mat);
            cv::flip(mat, mat, 0);
        } else {
            // implement other agles rotate
        }
        return true;
    }
    
}