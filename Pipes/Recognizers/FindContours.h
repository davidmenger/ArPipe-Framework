//
//  FindContours.h
//  AR
//
//  Created by Menger David on 07.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__FindContours__
#define __AR__FindContours__

#include <iostream>
#include "BasePipe.h"
#include <opencv2/opencv.hpp>

namespace ArPipe {
    
    //! Encapsulated OpenCV find contours function
    /**
     * Contours detector using findContours function
     */
    class FindContours : public BasePipe
    {
    public:
        FindContours(BaseFrameSource *previousPipe) : BasePipe() {
            FindContours();
        }
        FindContours() : BasePipe() {
            mode = CV_RETR_TREE;
            method = CV_CHAIN_APPROX_NONE;
        }
        
        /**
         * Factory to create new FindContours pipe
         * @return new instance
         */
        static FindContours* init() {
            return new FindContours();
        }
        
        bool processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        
        /**
         * Detect only external contours
         * @return current pipe object. Supports fluent interface
         */
        FindContours* setTypeOnlyExternal()
        {
            mode = CV_RETR_EXTERNAL;
            return this;
        }
        
        /**
         * Create list hierarchy of contours
         * @return current pipe object. Supports fluent interface
         */
        FindContours* setTypeList()
        {
            mode = CV_RETR_LIST;
            return this;
        }
        
        /**
         * Creates tree hierarchy of contours
         * @return current pipe object. Supports fluent interface
         */
        FindContours* setTypeTree()
        {
            mode = CV_RETR_TREE;
            return this;
        }
        
        /**
         * 
         * @return current pipe object. Supports fluent interface
         */
        FindContours* setCComp()
        {
            mode = CV_RETR_CCOMP;
            return this;
        }
        
        /**
         * Use no approximation method
         * @return current pipe object. Supports fluent interface
         */
        FindContours* setAproxNone()
        {
            method = CV_CHAIN_APPROX_NONE;
            return this;
        }
        
        /**
         * Uses TC89 Chain approximation method
         * @return current pipe object. Supports fluent interface
         */
        FindContours* setAproxTc(bool kcos)
        {
            method = kcos ? CV_CHAIN_APPROX_TC89_KCOS : CV_CHAIN_APPROX_TC89_L1;
            return this;
        }
        
        
       
    
    protected:
        int mode;
        int method;
    
    };
    
}

#endif /* defined(__AR__FindContours__) */
