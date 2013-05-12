//
//  DrawContrours.cpp
//  AR
//
//  Created by Menger David on 07.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//  Using Aruco framework algorithms: http://www.uco.es/investiga/grupos/ava/node/26
//

#include "DrawContrours.h"

namespace ArPipe {
    
    bool DrawContours::processFrameContainer(BaseFrameContainer* frm, BaseFrameSource* frameSource)
    {
        if (frm->getShapes()->getHierarchy().size() == frm->getShapes()->getContours().size() && frm->getShapes()->getContours().size() > 0) {
            cv::drawContours(frm->getFrame()->getMat(), frm->getShapes()->getContours(), -1, color,
                             thickness, lineType, frm->getShapes()->getHierarchy(), maxLevel);
        } else if (frm->getShapes()->getContours().size()) {
            cv::drawContours(frm->getFrame()->getMat(), frm->getShapes()->getContours(), -1, color,
                             thickness, lineType);
        }
        
        for (std::vector<Marker>::iterator i = frm->getShapes()->getMarkers().begin();
                    i != frm->getShapes()->getMarkers().end(); ++i) {
            i->draw(frm->getFrame()->getMat(), cv::Scalar(0, 255, 0, 255), 1, true);
        }
        return true;
    }
    
}