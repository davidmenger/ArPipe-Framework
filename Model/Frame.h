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
        /**
         * Contains OpenCV matrix with image data
         */
        Mat frame;

        /**
         * Empty constructor
         */
        Frame();
        
        /**
         * Creates new instance of Frame with OpenCV matrix data
         * @param frm
         */
        Frame(Mat frm);
        
        /**
         * Destructor of image data 
         */
        ~Frame();
        
        /**
         * Method for create copy of Frame object
         * @return new instance which will contain new copy of image data
         */
        Frame* clone();
        
        /**
         * Returns OpenCV image data reference for modification inside 
         * Pipe objects
         * @return reference to cv::Mat
         */
        Mat &getMat();
        
        /**
         * 
         * @return true if image data is in only one channel
         */
        bool isGrey();
        
        /**
         * 
         * @return count of image data channels
         */
        int getChannelCount();
        
        /**
         * 
         * @return Color depth of channels
         */
        double getDepth();
    };
        
}

#endif /* defined(__AR__Frame__) */
