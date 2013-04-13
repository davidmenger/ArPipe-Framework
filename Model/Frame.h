//
//  Frame.h
//  AR
//
//  Created by Menger David on 17.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__Frame__
#define __AR__Frame__

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
namespace ArPipe {
    
    class Frame { 
        
    public:
        Mat frame;

        Frame();
        Frame(Mat frm);
        ~Frame();
        
        Frame* clone();
        
        Mat &getMat();
        void rotate(int degrees);
        bool isGrey();
        
        int getChannelCount();
        double getDepth();
    };
        
}

#endif /* defined(__AR__Frame__) */
