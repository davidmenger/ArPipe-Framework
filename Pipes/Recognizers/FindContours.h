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
        
        static FindContours* init() {
            return new FindContours();
        }
        
        bool processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        
        /*FindContours* set()
        {
            
            return this;
        }*/
        
        FindContours* setTypeOnlyExternal()
        {
            mode = CV_RETR_EXTERNAL;
            return this;
        }
        
        FindContours* setTypeList()
        {
            mode = CV_RETR_LIST;
            return this;
        }
        
        FindContours* setTypeTree()
        {
            mode = CV_RETR_TREE;
            return this;
        }
        
        FindContours* setCComp()
        {
            mode = CV_RETR_CCOMP;
            return this;
        }
        
        FindContours* setAproxNone()
        {
            method = CV_CHAIN_APPROX_NONE;
            return this;
        }
        
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
