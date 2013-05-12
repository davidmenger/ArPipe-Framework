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
        
        /**
         * Empty constructor
         */
        Shapes() : contours(), hierarchy(), markers() {
            
        }
        
        /**
         * Returns reference to vector for capturing contours
         * @return 
         */
        std::vector<std::vector<cv::Point> > &getContours() {
            return contours;
        }
        
        /**
         * Returns reference to vector for capturing contours hierarchy
         * @return 
         */
        std::vector<cv::Vec4i> &getHierarchy() {
            return hierarchy;
        }
        
        /**
         * Returns reference to vector containing detected Marker objects
         * @return 
         */
        std::vector<Marker> &getMarkers() {
            return markers;
        }
        
        void setMarkers(std::vector<Marker> newMarkers) {
            markers = newMarkers;
        }
        
        void setHierarchy(std::vector<cv::Vec4i> newHierarchy) {
            hierarchy = newHierarchy;
        }
        
        void setContours(std::vector<std::vector<cv::Point> > newContours) {
            contours = newContours;
        }
        
        /**
         * Returns copy of Shapes object
         * @return 
         */
        Shapes* clone();
        
    protected:
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
        std::vector<Marker> markers;
        
    };
    
}

#endif /* defined(__AR__Shapes__) */
