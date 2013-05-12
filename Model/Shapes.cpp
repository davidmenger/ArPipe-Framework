//
//  Shapes.cpp
//  AR
//
//  Created by Menger David on 07.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "Shapes.h"

namespace ArPipe {
    
    Shapes* Shapes::clone()
    {
        Shapes *newShapes = new Shapes();
        newShapes->setMarkers(markers);
        newShapes->setHierarchy(hierarchy);
        newShapes->setContours(contours);
        return newShapes;
    }
    
}