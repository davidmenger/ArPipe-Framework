//
//  PipeMerge.h
//  AR
//
//  Created by Menger David on 11.05.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__PipeMerge__
#define __AR__PipeMerge__

#include <iostream>
#include "BasePipe.h"
namespace ArPipe {
    
    //! Node for merge two leaves of tree
    /**
     * This class is used for merge Frame and Shapes data from frame containers
     * to one frame container. Useful for recognize image features separately.
     */
    class PipeMerge : public BasePipe
    {
    public:
        
        /*
         * Constructor to attach PipeLine after another frame source
         * @param previousPipe frame source to attach after
         */
        PipeMerge(BaseFrameSource *previousPipe) : BasePipe() {
            PipeMerge();
        }
        
        
        PipeMerge() : BasePipe() {
            
        }
        
        /**
         * Factory for creating instances
         * @return new pipe object. Supports fluent interface
         */
        static PipeMerge* init() {
            return new PipeMerge();
        }
        
        /**
         * Don't call this method directly. This will 
         * @param frm
         * @param frameSource
         */
        bool processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        
        /**
         * When this class is extended, override this method to implement own
         * Frame and Shape processing. This will be called, when both Frame and 
         * Shape data will be collected.
         */
        virtual void processFrameAndShapes();
        
        /**
         * Sets pipe as source of Frame data
         * @param frameSource previously connected pipe
         * @return current pipe object. Supports fluent interface
         */
        PipeMerge* setFrameSource(BasePipe *frameSource)
        {
            frameSourcePipe = frameSource;
            return this;
        }
        
        /**
         * Sets pipe as source of Shapes data
         * @param frameSource previously connected pipe
         * @return current pipe object. Supports fluent interface
         */
        PipeMerge* setShapesSource(BasePipe *shapeSource)
        {
            shapesSourcePipe = shapeSource;
            return this;
        }
        
    protected:
        
        BasePipe *frameSourcePipe;
        BasePipe *shapesSourcePipe;
        
        /**
         * Variable will contain BaseFrameContainer from frameSourcePipe
         */
        BaseFrameContainer *frame;
        
        /**
         * Variable will contain BaseFrameContainer from shapesSourcePipe
         */
        BaseFrameContainer *shapes;
        
        
    };
    
}
#endif /* defined(__AR__PipeMerge__) */
