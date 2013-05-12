//
//  PipeLine.h
//  AR
//
//  Created by Menger David on 07.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__PipeLine__
#define __AR__PipeLine__

#include <iostream>
#include <vector>
#include "BasePipe.h"

namespace ArPipe {
    
    //! Pipeline object aggregates single Pipe object into PipeLine
    /**
     * This class can be used alone for creating single pipeline, or can be
     * extended to represent sophisticated single purpose functionality.
     */
    class PipeLine : public BasePipe
    {
    public:
        /**
         * Constructor to attach PipeLine after another frame source
         * @param previousPipe frame source to attach after
         */
        PipeLine(BaseFrameSource *previousPipe) : BasePipe(previousPipe) {}
        
        /**
         * Destructor
         */
        ~PipeLine();
        
        /**
         * Method called by previous pipe. It will pass frame container through 
         * all containing Pipes.
         * @param frm
         * @param frameSource
         * @return 
         */
        bool processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        
        /**
         * Adds pipe object to end of pipeline
         * @param pipe input pipe object
         * @return current pipepine. Supports fluent interface.
         */
        PipeLine* addPipe(BasePipe* pipe);
        
        /**
         * 
         * @return count of pipes inside pipeline
         */
        int getCount();
        
        /**
         * This method allows using pipeline as array of pipes
         */
        BasePipe* operator[](int i) const { return subPipes[i]; };
        
        /**
         * This method allows using pipeline as array of pipes
         */
        BasePipe* &operator[](int i) { return subPipes[i]; };
        
        /**
         * Returns first pipe in pipeline
         * @return first pipe
         */
        BasePipe* front()
        {
            return subPipes.front();
        }
        
        /**
         * Returns last pipe in pipeline
         * @return  last pipe
         */
        BasePipe* back()
        {
            return subPipes.back();
        }
        
    protected:
        std::vector<BasePipe*> subPipes;
    };
    
}

#endif /* defined(__AR__PipeLine__) */
