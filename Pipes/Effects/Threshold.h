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
   
   class Threshold : public BasePipe
   {
   public:
       Threshold(BaseFrameSource *previousPipe);
       Threshold();
       static Threshold* init() {
           return new Threshold();
       }
       
       void processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
       
       void setType(int typeConst) {
           type = typeConst;
       }
       int getType() {
           return type;
       }
       
       Threshold* setThresh(double treshVal) {
           thresh = treshVal;
           return this;
       }
       double getThresh() {
           return thresh;
       }
       
       Threshold* setMaxVal(double max) {
           autoMax = false;
           maxval = max;
           return this;
       }
       double getMaxVal() {
           return maxval;
       }
       
       Threshold* setAutoMax() {
           autoMax = true;
           return this;
       }
       
       Threshold* setAdaptive(bool adaptive) {
           if (adaptive && type != cv::THRESH_BINARY_INV && type != cv::THRESH_BINARY) {
               type = cv::THRESH_BINARY_INV;
           }
           adaptive = true;
           return this;
       }
       
       Threshold* setTypeBinary(bool inverted) {
           type = inverted ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY;
           autoMax = true;
           return this;
       }
       
       Threshold* setTypeBinary(bool inverted, double max) {
           type = inverted ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY;
           maxval = max;
           autoMax = false;
           return this;
       }
       
       Threshold* setTypeToZero(bool inverted) {
           type = inverted ? cv::THRESH_TOZERO_INV : cv::THRESH_TOZERO;
           adaptive = false;
           return this;
       }
       
       Threshold* setTypeTruncated() {
           type = cv::THRESH_TRUNC;
           adaptive = false;
           return this;
       }
       
       Threshold* setAdaptiveBlockRadius(int size) {
           blockSize = size > 0 ? size*2-1 : 1;
           return this;
       }
       
       Threshold* setAdaptiveMethodMean() {
           adaptiveMethod = cv::ADAPTIVE_THRESH_MEAN_C;
           return this;
       }
       
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
