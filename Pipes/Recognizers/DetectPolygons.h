//
//  DetectPolygons.h
//  AR
//
//  Created by Menger David on 13.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__DetectPolygons__
#define __AR__DetectPolygons__

#include <iostream>
#include "BasePipe.h"
#include <vector>

namespace ArPipe {
    
    class DetectPolygons : public BasePipe
    {
    public:
        DetectPolygons(BaseFrameSource *previousPipe) : BasePipe() {
            DetectPolygons();
        }
        DetectPolygons() : BasePipe() {
            maxComplexity = 12;
            minComplexity = 4;
            minDistance = 10;
            complexityKoef = 0.05;
            simplifyPolygons = true;
            minimalPolygonLines = 4;
            maximalPolygonLines = INT_MAX;
            onlyConvex = false;
            onlyClosed = true;
        }
        
        static DetectPolygons* init() {
            return new DetectPolygons();
        }
        
        bool processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        
        /*DetectPolygons* set()
         {
         
         return this;
         }*/
        
        DetectPolygons* setMaxComplexity(int max = 12)
        {
            maxComplexity = max;
            return this;
        }
        
        DetectPolygons* setMinComplexity(int min = 2)
        {
            minComplexity = min;
            return this;
        }
        
        DetectPolygons* setMinDistance(int distance = 0)
        {
            minDistance = distance;
            return this;
        }
        
        DetectPolygons* setComplexityKoef(float koef = 0.05)
        {
            complexityKoef = koef;
            return this;
        }
        
        DetectPolygons* setStraightenLines(bool straighten = true)
        {
            simplifyPolygons = straighten;
            return this;
        }
        
        DetectPolygons* setMinimalSides(unsigned int sides = 4)
        {
            minimalPolygonLines = sides;
            return this;
        }
        
        DetectPolygons* setMaximalSides(unsigned int sides = INT_MAX)
        {
            maximalPolygonLines = sides;
            return this;
        }
        
        DetectPolygons* setRequiredSideCount(unsigned int sides)
        {
            maximalPolygonLines = minimalPolygonLines = sides;
            return this;
        }
        
        DetectPolygons* setOnlyConvexObjects(bool convex = true)
        {
            onlyConvex = convex;
            return this;
        }
        
        DetectPolygons* setNeedClosedObjects(bool closed = true)
        {
            onlyClosed = closed;
            return this;
        }
        
    protected:
        int maxComplexity;
        int minComplexity;
        int minDistance;
        float complexityKoef;
        bool simplifyPolygons;
        unsigned int minimalPolygonLines;
        unsigned int maximalPolygonLines;
        bool onlyConvex;
        bool onlyClosed;
        
        int perimeter(std::vector<cv::Point2f> &a);
        template<typename T>
        void removeElements(std::vector<T> & vinout,const std::vector<bool> &toRemove);
        
    };
    
}

#endif /* defined(__AR__DetectPolygons__) */
