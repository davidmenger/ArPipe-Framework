//
//  Shapes.h
//  AR
//
//  Created by Menger David on 07.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__Shapes__
#define __AR__Shapes__

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "Marker.h"

namespace ArPipe {
    
    class Shapes
    {
    public:
        Shapes() : contours(), hierarchy(), markers() {
            
        }
        
        std::vector<std::vector<cv::Point> > &getContours() {
            return contours;
        }
        
        std::vector<cv::Vec4i> &getHierarchy() {
            return hierarchy;
        }
        
        std::vector<Marker> &getMarkers() {
            return markers;
        }
        
        void setMarkers(std::vector<Marker> newMarkers) {
            markers = newMarkers;
        }
        
    protected:
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
        std::vector<Marker> markers;
        
    };
    
}

#endif /* defined(__AR__Shapes__) */
