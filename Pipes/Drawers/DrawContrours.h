//
//  DrawContrours.h
//  AR
//
//  Created by Menger David on 07.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__DrawContrours__
#define __AR__DrawContrours__

#include <iostream>
#include <opencv2/opencv.hpp>
#include "BasePipe.h"

namespace ArPipe {
    
    class DrawContours : public BasePipe
    {
    public:
        
        DrawContours(BaseFrameSource *previousPipe) : BasePipe() {
            DrawContours();
        }
        
        DrawContours() : BasePipe() {
            thickness = 2;
            lineType = 8;
            maxLevel = INT_MAX;
            color = CV_RGB(255, 255, 0);
        }
        
        static DrawContours* init() {
            return new DrawContours();
        }
        
        /*DrawContours* set()
         {
         
         return this;
         }*/
        
        
        void processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        
    protected:
        int thickness;
        int lineType;
        int maxLevel;
        cv::Scalar color;
        
        
    };
    
}

#endif /* defined(__AR__DrawContrours__) */
