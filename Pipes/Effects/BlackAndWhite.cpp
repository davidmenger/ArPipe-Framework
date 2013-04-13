//
//  BlackAndWhite.cpp
//  AR
//
//  Created by Menger David on 06.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "BlackAndWhite.h"
#include <opencv2/opencv.hpp>

namespace ArPipe {
    
    void BlackAndWhite::processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource)
    {
        if (frm->getFrame()->getChannelCount() > 1 && !color) {
            cv::Mat &mat = frm->getFrame()->getMat();
            cv::cvtColor(mat, mat, color ? CV_GRAY2BGR : CV_BGR2GRAY);
        } else if (frm->getFrame()->getChannelCount() < 3 && color) {
            // create 32bit image from 8bit
            //cv::Mat &grey = frm->getFrame()->getMat();
            
            //cv::Mat img_gray_32f;
            //grey.convertTo(img_gray_32f, CV_32F, 1./255.);
            
            // create 3 channel image from grayscale image
            //cv::Mat img_rgb;
            cv::cvtColor(frm->getFrame()->getMat(), frm->getFrame()->getMat(), CV_GRAY2RGB);
            
            //frm->getFrame()->getMat() = img_rgb;
            
            //grey.release();
        }
    }
    
}