//
//  PipeOutputConnector.h
//  AR
//
//  Created by Menger David on 24.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__PipeOutputConnector__
#define __AR__PipeOutputConnector__

#include <iostream>
#include "BasePipeOutput.h"

namespace ArPipe {
    
    //! Class used to connect pipeline to ObjectiveC class
    /**
     * Encapsulate this object in your ObjectiveC data output
     */
    class PipeOutputConnector : public BasePipeOutput
    {
    public:
        PipeOutputConnector(){};
        
        /**
         * Callback will be called, when new BaseFrameContainer is received
         * @param callback function to invoke
         */
        void setOnNewFrameContainerCallback(void (*callback)(BaseFrameContainer *frm));
        
        /**
         * Don't call directly. 
         */
        bool processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        
    protected:
        void (*newFrameCallback)(BaseFrameContainer *frm);
    };
    
}

#endif /* defined(__AR__PipeOutputConnector__) */
