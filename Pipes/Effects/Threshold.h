//
//  Threshold.h
//  AR
//
//  Created by Menger David on 01.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__Threshold__
#define __AR__Threshold__

#include <iostream>
#include "BasePipe.h"
#include <opencv2/opencv.hpp>

/* 0: Binary
 1: Binary Inverted
 2: Threshold Truncated
 3: Threshold to Zero
 4: Threshold to Zero Inverted
 */


namespace ArPipe {
   
    //! Encapsulated OpenCV Threshold functions
    /**
     * Using adaptive threshold and classic threshold
     */
   class Threshold : public BasePipe
   {
   public:
       Threshold(BaseFrameSource *previousPipe);
       Threshold();
       
       /**
         * Factory to create new Threshold pipe
         * @return new instance
         */
       static Threshold* init() {
           return new Threshold();
       }
       
       bool processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
       
       
       void setType(int typeConst) {
           type = typeConst;
       }
       int getType() {
           return type;
       }
       
       /**
        * Sets threshold value for simple threshold
        * @param treshVal
        * @return current pipe object. Supports fluent interface
        */
       Threshold* setThresh(double treshVal) {
           thresh = treshVal;
           return this;
       }
       
       /**
        * 
        * @return threshold value
        */
       double getThresh() {
           return thresh;
       }
       
       /**
        * Sets static maximal value for threshold
        * @param max
        * @return 
        */
       Threshold* setMaxVal(double max) {
           autoMax = false;
           maxval = max;
           return this;
       }
       
       /**
        * 
        * @return maximal threshold value
        */
       double getMaxVal() {
           return maxval;
       }
       
       /**
        * Enables automatic maximum value depending on color depth
        * @return current pipe object. Supports fluent interface
        */
       Threshold* setAutoMax() {
           autoMax = true;
           return this;
       }
       
       /**
        * Use Adaptive threshold method
        * @param inverted
        * @return current pipe object. Supports fluent interface
        */
       Threshold* setAdaptive(bool inverted) {
           type = inverted ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY;
           adaptive = true;
           return this;
       }
       
       /**
        * Use simple binary threshold with automatic maximal value
        * @param inverted sets inverted colors
        * @return current pipe object. Supports fluent interface
        */
       Threshold* setTypeBinary(bool inverted) {
           type = inverted ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY;
           autoMax = true;
           return this;
       }
       
       /**
        * Use simple binary threshold
        * @param inverted sets inverted colors
        * @param max sets static maximal value
        * @return current pipe object. Supports fluent interface
        */
       Threshold* setTypeBinary(bool inverted, double max) {
           type = inverted ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY;
           maxval = max;
           autoMax = false;
           return this;
       }
       
       /**
        * Use simple to zero threshold
        * @param inverted sets inverted colors
        * @return current pipe object. Supports fluent interface
        */
       Threshold* setTypeToZero(bool inverted) {
           type = inverted ? cv::THRESH_TOZERO_INV : cv::THRESH_TOZERO;
           adaptive = false;
           return this;
       }
       
       /**
         * Use simple truncated threshold
         * @return current pipe object. Supports fluent interface
         */
       Threshold* setTypeTruncated() {
           type = cv::THRESH_TRUNC;
           adaptive = false;
           return this;
       }
       /**
        * Sets radius for adaptive threshold
        * @param size
        * @return current pipe object. Supports fluent interface
        */
       Threshold* setAdaptiveBlockRadius(int size) {
           blockSize = size > 0 ? size*2-1 : 1;
           return this;
       }
       
       /**
         * Use Adaptive Mean method
         * @return current pipe object. Supports fluent interface
         */
       Threshold* setAdaptiveMethodMean() {
           adaptiveMethod = cv::ADAPTIVE_THRESH_MEAN_C;
           return this;
       }
       
       /**
         * Use Adaptive Gaussian threshold
         * @return current pipe object. Supports fluent interface
         */
       Threshold* setAdaptiveMethodGaussian() {
           adaptiveMethod = cv::ADAPTIVE_THRESH_GAUSSIAN_C;
           return this;
       }
       
       
   protected:
       bool adaptive;
       bool autoMax;
       double thresh;
       double maxval;
       int type;
       int blockSize;
       int adaptiveMethod;
       
       double getCalcedMaxValue(Frame* const mat);
   };
   
}

#endif /* defined(__AR__Threshold__) */
