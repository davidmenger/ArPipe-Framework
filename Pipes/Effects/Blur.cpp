//
//  Blur.cpp
//  AR
//
//  Created by Menger David on 07.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "Blur.h"
#include <opencv2/opencv.hpp>

namespace ArPipe {
    
    void Blur::processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource)
    {
        cv::Mat src = frm->getFrame()->getMat().clone();
        cv::Mat &dst = frm->getFrame()->getMat();
        
        if (type == ARP_BLUR_STANDARD) {
            /// Applying Homogeneous blur
            for ( int i = 1; i < kernelLength; i++ )
            {
                cv::blur( src, dst, cv::Size( i*2+1, i*2+1 ), cv::Point(-1,-1) );
            }
        } else if (type == ARP_BLUR_GAUSSIAN) {
            /// Applying Gaussian blur
            for ( int i = 1; i < kernelLength; i++ )
            {
                cv::GaussianBlur( src, dst, cv::Size( i*2+1, i*2+1), 0, 0 );
            }
        } else if (type == ARP_BLUR_MEDIAN) {
            /// Applying Median blur
            for ( int i = 1; i < kernelLength; i = i + 2 )
            {
                cv::medianBlur ( src, dst, i );
            }
        } else if (type == ARP_BLUR_BILATERAL) {
            /// Applying Bilateral Filter
            for ( int i = 1; i < kernelLength; i = i + 2 )
            {
                cv::bilateralFilter ( src, dst, i, i*2, i/2 );
            }
        }
        src.release();
    }
    
}