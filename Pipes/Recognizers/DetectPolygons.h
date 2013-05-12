//
//  DetectPolygons.h
//  AR
//
//  Created by Menger David on 13.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//  Using Aruco framework algorithms: http://www.uco.es/investiga/grupos/ava/node/26
//

#ifndef __AR__DetectPolygons__
#define __AR__DetectPolygons__

#include <iostream>
#include "BasePipe.h"
#include <vector>

namespace ArPipe {
    
    //! Polygon detector pipe
    /**
     * Complex pipe useful for detecting polygons in contours
     */
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
        
        /**
         * Factory to create new DetectPolygons pipe
         * @return new instance
         */
        static DetectPolygons* init() {
            return new DetectPolygons();
        }
        
        bool processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        
        /**
         * Setter maximal feature complexity of contours.
         * @param max
         * @return current pipe object. Supports fluent interface
         */
        DetectPolygons* setMaxComplexity(int max = 12)
        {
            maxComplexity = max;
            return this;
        }
        
        /**
         * Setter minimal feature complexity of contours.
         * @param min
         * @return current pipe object. Supports fluent interface
         */
        DetectPolygons* setMinComplexity(int min = 2)
        {
            minComplexity = min;
            return this;
        }
        
        /**
         * Setter for minimal distance of points in contour
         * @param distance in pixels
         * @return current pipe object. Supports fluent interface
         */
        DetectPolygons* setMinDistance(int distance = 0)
        {
            minDistance = distance;
            return this;
        }
        
        /**
         * Setter for Complexity koef. relatively to image size 
         * @param koef
         * @return current pipe object. Supports fluent interface
         */
        DetectPolygons* setComplexityKoef(float koef = 0.05)
        {
            complexityKoef = koef;
            return this;
        }
        
        /**
         * Enables rounded lines detection and straighten them
         * @param straighten enables or disables feature
         * @return current pipe object. Supports fluent interface
         */
        DetectPolygons* setStraightenLines(bool straighten = true)
        {
            simplifyPolygons = straighten;
            return this;
        }
        
        /**
         * Setter for minimal polygon sides
         * @param sides desired minimal polygon sides
         * @return current pipe object. Supports fluent interface
         */
        DetectPolygons* setMinimalSides(unsigned int sides = 4)
        {
            minimalPolygonLines = sides;
            return this;
        }
        
        /**
         * Setter for maximal polygon sides
         * @param sides desired maximal polygon sides
         * @return current pipe object. Supports fluent interface
         */
        DetectPolygons* setMaximalSides(unsigned int sides = INT_MAX)
        {
            maximalPolygonLines = sides;
            return this;
        }
        
        /**
         * Sets both minimal and maximal sides of polygon to same value
         * @param sides desired polygon sides
         * @return current pipe object. Supports fluent interface
         */
        DetectPolygons* setRequiredSideCount(unsigned int sides)
        {
            maximalPolygonLines = minimalPolygonLines = sides;
            return this;
        }
        
        /**
         * Object must be convex only.
         * @param convex enables or disables feature
         * @return current pipe object. Supports fluent interface
         */
        DetectPolygons* setOnlyConvexObjects(bool convex = true)
        {
            onlyConvex = convex;
            return this;
        }
        
        /**
         * Find only closed polygons
         * @param closed enables or disables feature
         * @return current pipe object. Supports fluent interface
         */
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
