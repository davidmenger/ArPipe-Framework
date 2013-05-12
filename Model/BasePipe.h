//
//  BasePipe.h
//  AR
//
//  Created by Menger David on 17.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__BasePipe__
#define __AR__BasePipe__

#include <iostream>

#include "BaseFrameSource.h"
#include "BaseFrameContainer.h"

namespace ArPipe {
    
    //! Basic abstract class for building Pipes
    /**
     * Every new Pipe object should extend this class and simply override 
     * processFrameContainer method, which is used for image processing.
     * New pipe object must contain static init method, which returns 
     * new instance of pipe object.
     */
    class BasePipe : public BaseFrameSource {
  
    public:
        
        /**
         * Constructor used for appending object after 
         * previous BasePipe or BaseFrameSource
         * @param previousPipe previous pipe to append after
         */
        BasePipe(BaseFrameSource *previousPipe);
        
        /**
         * Empty constructor
         */
        BasePipe(){};
        
        /**
         * Virtual empty destructor
         */
        virtual ~BasePipe(){};
        
        /**
         * Method which receives BaseFrameContainer from previous 
         * pipe to process it. This method is responsible for passing frame 
         * container to process it and for pushing to another pipes.
         * It's not intended to call it directly.
         * @param frm container with Frame and Shapes data
         * @param frameSource link to previous pipe object, from which is 
         *      container received
         */
        void pushNewFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        
        /**
         * The most important method for image processing. In overriding method
         * you should process image data.
         * @param frm container with Frame and Shapes data
         * @param frameSource link to previous pipe object, from which is 
         *      container received
         * @return boolean, which identifies that data can be passed 
         *      to following pipes. This method normally should return true, 
         *      otherwise frame container will not be passed further.
         */
        virtual bool processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource)=0;
        
        /**
         * Template for static factory init method, which simply returns 
         * new instance of BasePipe class provided in T variable. It's 
         * recommended to create own static init method in every subclass of 
         * BasePipe.
         * @return new instance of T class
         */
        template< class T>
            static T init();
    protected:
        
        /**
         * This method is called, when processFrameContainer method returns 
         * false. When this method returns true, frame container will be 
         * deallocated, otherwise not. This method returns false by default. 
         * If you need to destroy frame container, override it.
         * @param frm
         * @param frameSource
         * @return 
         */
        virtual bool canDestroyUnprocessedContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        
        /**
         * When data are processed in processFrameContainer method, this 
         * variable contains frame container which will be pushed to next pipes.
         */
        BaseFrameContainer *containerToPush;
    
    };
    
}

#endif /* defined(__AR__BasePipe__) */

