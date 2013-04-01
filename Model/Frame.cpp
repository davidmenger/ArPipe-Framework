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
    
    
}