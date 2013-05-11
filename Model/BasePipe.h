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
    
    
    class BasePipe : public BaseFrameSource {
  
    public:
        BasePipe(BaseFrameSource *previousPipe);
        BasePipe(){};
        virtual ~BasePipe(){};
        
        void pushNewFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        virtual bool processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource)=0;
        
        template< class T>
            static T init();
    protected:
        virtual bool canDestroyUnprocessedContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        BaseFrameContainer *containerToPush;
    
    };
    
}

#endif /* defined(__AR__BasePipe__) */

