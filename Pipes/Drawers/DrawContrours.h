//
//  DrawContrours.h
//  AR
//
//  Created by Menger David on 07.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//  Using Aruco framework algorithms: http://www.uco.es/investiga/grupos/ava/node/26
//

#ifndef __AR__DrawContrours__
#define __AR__DrawContrours__

#include <iostream>
#include <opencv2/opencv.hpp>
#include "BasePipe.h"

namespace ArPipe {
    
    //! Simple pipe to Draw detected contours and markers to Frame
    class DrawContours : public BasePipe
    {
    public:
        
        DrawContours(BaseFrameSource *previousPipe) : BasePipe() {
            DrawContours();
        }
        
        DrawContours() : BasePipe() {
            thickness = 1;
            lineType = 4; //4, 8
            maxLevel = 1;
            color = cv::Scalar(255, 0, 0, 255);
            
        }
        
        /**
         * Factory to create new CameraApply pipe
         * @return new instance
         */
        static DrawContours* init() {
            return new DrawContours();
        }
        
        /*DrawContours* set()
         {
         
         return this;
         }*/
        
        
        bool processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        
    protected:
        int thickness;
        int lineType;
        int maxLevel;
        cv::Scalar color;
        
        
    };
    
}

#endif /* defined(__AR__DrawContrours__) */
