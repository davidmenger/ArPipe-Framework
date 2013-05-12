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
    
    class PipeMerge : public BasePipe
    {
    public:
        PipeMerge(BaseFrameSource *previousPipe) : BasePipe() {
            PipeMerge();
        }
        PipeMerge() : BasePipe() {
            
        }
        
        static PipeMerge* init() {
            return new PipeMerge();
        }
        
        bool processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        
        
        /*PipeMerge* set()
         {
         
         return this;
         }*/
        
        
        virtual void processFrameAndShapes();
        
        PipeMerge* setFrameSource(BasePipe *frameSource)
        {
            frameSourcePipe = frameSource;
            return this;
        }
        
        PipeMerge* setShapesSource(BasePipe *shapeSource)
        {
            shapesSourcePipe = shapeSource;
            return this;
        }
        
    protected:
        BasePipe *frameSourcePipe;
        BasePipe *shapesSourcePipe;
        
        BaseFrameContainer *frame;
        BaseFrameContainer *shapes;
        
        
    };
    
}
#endif /* defined(__AR__PipeMerge__) */
