//
//  BaseFrameContainer.h
//  AR
//
//  Created by Menger David on 17.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__BaseFrameContainer__
#define __AR__BaseFrameContainer__

#include <iostream>
#include <opencv2/opencv.hpp>

#include "Frame.h"
#include "Shapes.h"


namespace ArPipe {
    
    //! Basic Frame and Shapes container
    /**
     * This object contains image, contours and marker data. BaseFrameContainer can be extended by user.
     */
    class BaseFrameContainer {
      
    public:
        /**
         * Constructor used for fast creation with cv::Mat image matrix
         * @param frameMat initial cv::Mat
         */
        BaseFrameContainer(cv::Mat frameMat);
        
        /**
         * Constructor used for fast creation with Frame object
         * @param frm Frame object
         */
        BaseFrameContainer(Frame* frm);
        
        ~BaseFrameContainer();
        
        /**
         * 
         * @return Contained Frame object
         */
        Frame* getFrame();
        
        /**
         * 
         * @return Contained Shapes object
         */
        Shapes* getShapes();
        
        /**
         * Clone method is used, when PipeLine is forked
         * @return duplicate of called BaseFrameContainer
         */
        BaseFrameContainer* clone();
        
        /**
         * Replaces current Frame with new. The old one will be deallocated. 
         * @param frameReplacement
         */
        void setFrame(Frame* frameReplacement);
        
        /**
         * Replaces current shapes object with new. The old one will be deallocated. 
         * @param shapesReplacement new Shapes object to replace current
         */
        void setShapes(Shapes* shapesReplacement);
        
    protected:
        Frame* frame;
        Shapes* shapes;
        
    };
    
}

#endif /* defined(__AR__BaseFrameContainer__) */
