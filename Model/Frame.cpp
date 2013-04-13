//
//  Frame.cpp
//  AR
//
//  Created by Menger David on 17.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "Frame.h"

using namespace cv;
namespace ArPipe {
    
    Frame::Frame()
    {
        
    }
    
    Frame::Frame(Mat frm)
    {
        frame = frm;
    }
    
    Frame::~Frame()
    {
        frame.release();
    }
    
    Mat &Frame::getMat()
    {
        return frame;
    }
    
    void Frame::rotate(int degrees) {
        cv::transpose(frame, frame);
        cv::flip(frame, frame, 1);
    }
    
    bool Frame::isGrey()
    {
        return frame.type() == CV_8UC3;
    }
    
    Frame* Frame::clone()
    {
        return new Frame(frame.clone());
    }
    
    int Frame::getChannelCount()
    {
        return frame.channels();
    }
    
    double Frame::getDepth()
    {
        /**
         
         CV_8U - 8-bit unsigned integers ( 0..255 )
         CV_8S - 8-bit signed integers ( -128..127 )
         CV_16U - 16-bit unsigned integers ( 0..65535 )
         CV_16S - 16-bit signed integers ( -32768..32767 )
         CV_32S - 32-bit signed integers ( -2147483648..2147483647 )
         CV_32F - 32-bit floating-point numbers ( -FLT_MAX..FLT_MAX, INF, NAN )
         CV_64F - 64-bit floating-point numbers ( -DBL_MAX..DBL_MAX, INF, NAN )
         
         */
        int depth = frame.depth();
        if (depth == CV_8U || depth == CV_8S) {
            return 255;
        } else if (depth == CV_16U || depth == CV_16S) {
            return 65535;
        } else  {
            return 2147483647;
        }
    }
    
}