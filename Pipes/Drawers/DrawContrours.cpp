//
//  DrawContrours.cpp
//  AR
//
//  Created by Menger David on 07.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "DrawContrours.h"

namespace ArPipe {
    
    void DrawContours::processFrameContainer(BaseFrameContainer* frm, BaseFrameSource* frameSource)
    {
        if (frm->getShapes()->getHierarchy().size() == frm->getShapes()->getContours().size() && frm->getShapes()->getContours().size() > 0) {
            cv::drawContours(frm->getFrame()->getMat(), frm->getShapes()->getContours(), -1, color,
                             thickness, lineType, frm->getShapes()->getHierarchy(), maxLevel);
        } else if (frm->getShapes()->getContours().size()) {
            cv::drawContours(frm->getFrame()->getMat(), frm->getShapes()->getContours(), -1, color,
                             thickness, lineType);
        }        
    }
    
}