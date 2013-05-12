//
//  BaseFrameSource.h
//  AR
//
//  Created by Menger David on 17.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__BaseFrameSource__
#define __AR__BaseFrameSource__

#include <iostream>
#include <vector>
#include "BaseFrameContainer.h"

namespace ArPipe {
    
    class BasePipe;

    //! Basic frame container source
    /**
     * Subclasses of this class represents any source of image or vector data.
     * Every pipeline must start with instance of BaseFrameSource subclass.
     */
    class BaseFrameSource {
    
    public:
        /**
         * Destructor
         */
        ~BaseFrameSource();
        
        /**
         * Method for adding next BasePipe. Frame container will be passed to 
         * this pipe after data processing.
         * @param pipe next pipe to send processed data
         * @return inserted BasePipe object. Supports Fluent interface.
         */
        BasePipe* addNextPipe(BasePipe *pipe);
        
        /**
         * When frame container is ready to push further, this method is
         * responsible for pass it to all next pipes. When current pipe not
         * contains any next pipe and dontDeleteFrame is set to false, 
         * frame will be deallocated.
         * @param container BaseFrameContainer to push
         * @param dontDeleteFrame determines that frame will be destroyed
         *      when nextPipes vector is empty.
         */
        void pushFrameConainerToNextPipes(BaseFrameContainer *container, bool dontDeleteFrame = false);
        
    protected:
        
        /**
         * Contains next pipe objects
         */
        std::vector<BasePipe*> nextPipes;
        
        
        
    };
    
}

#endif /* defined(__AR__BaseFrameSource__) */
