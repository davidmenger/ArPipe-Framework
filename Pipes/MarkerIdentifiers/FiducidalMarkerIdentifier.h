//
//  FiducidalMarkerIdentifier.h
//  AR
//
//  Created by Menger David on 11.05.13.
//  Using Aruco framework source code
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__FiducidalMarkerIdentifier__
#define __AR__FiducidalMarkerIdentifier__

#include <iostream>
#include "SquareMarkerDetector.h"
#include <opencv2/opencv.hpp>

namespace ArPipe {
    
    class FiducidalMarkerIdentifier : public SquareMarkerDetector
    {
    public:
        FiducidalMarkerIdentifier(BaseFrameSource *previousPipe) : SquareMarkerDetector() {
            FiducidalMarkerIdentifier();
        }
        FiducidalMarkerIdentifier() : SquareMarkerDetector() {
            
        }
        
        static FiducidalMarkerIdentifier* init() {
            return new FiducidalMarkerIdentifier();
        }
        
        
        /*FiducidalMarkerIdentifier* set()
         {
         
         return this;
         }*/
        
        
        /**
         * \brief Creates an ar marker with the id specified using a modified version of the hamming code.
         * There are two type of markers: a) These of 10 bits b) these of 3 bits. The latter are employed for applications
         * that need few marker but they must be small.  The two type of markers are distinguished by their ids. While the first type
         * of markers have ids in the interval [0-1023], the second type ids in the interval [2000-2006].
         *
         *
         * 10 bits markers
         * -----------------------
         * There are a total of 5 rows of 5 cols. Each row encodes a total of 2 bits, so there are 2^10 bits:(0-1023).
         *
         * The least significative bytes are first (from left-up to to right-bottom)
         *
         * Example: the id = 110 (decimal) is be represented in binary as : 00 01 10 11 10.
         *
         * Then, it will generate the following marker:
         *
         * -# 1st row encodes 00: 1 0 0 0 0 : hex 0x10
         * -# 2nd row encodes 01: 1 0 1 1 1 : hex 0x17
         * -# 3nd row encodes 10: 0 1 0 0 1 : hex 0x09
         * -# 4th row encodes 11: 0 1 1 1 0 : hex 0x0e
         * -# 5th row encodes 10: 0 1 0 0 1 : hex 0x09
         *
         * Note that : The first bit, is the inverse of the hamming parity. This avoids the 0 0 0 0 0 to be valid
         * These marker are detected by the function  getFiduciadlMarker_Aruco_Type1
         */
        static cv::Mat createMarkerImage(int id,int size) throw (cv::Exception);
        
        /** Detection of fiducidal aruco markers (10 bits)
         * @param in input image with the patch that contains the possible marker
         * @param nRotations number of 90deg rotations in clockwise direction needed to set the marker in correct position
         * @return -1 if the image passed is a not a valid marker, and its id in case it really is a marker
         */
        static int detect(const cv::Mat &in,int &nRotations);
        
        /**Similar to createMarkerImage. Instead of returning a visible image, returns a 8UC1 matrix of 0s and 1s with the marker info
         */
        static cv::Mat getMarkerMat(int id) throw (cv::Exception);
        
        int detectMarker(const cv::Mat &in,int &nRotations);
        
        
        
    private:
        static  cv::Mat rotate(cv::Mat  in);
        static  int hammDistMarker(cv::Mat  bits);
        static  int analyzeMarkerImage(cv::Mat &grey,int &nRotations);
        static  bool correctHammMarker(cv::Mat &bits);
        
        
        
    };
    
}


#endif /* defined(__AR__FiducidalMarkerIdentifier__) */
