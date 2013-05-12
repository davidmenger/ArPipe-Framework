//
//  DetectPolygons.cpp
//  AR
//
//  Created by Menger David on 13.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//  Using Aruco framework algorithms: http://www.uco.es/investiga/grupos/ava/node/26
//

#include "DetectPolygons.h"
#include <vector>
#include "Marker.h"

namespace ArPipe {
    
        
    bool DetectPolygons::processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource)
    {
        Shapes* shapes = frm->getShapes();
        std::vector<Point>  approxCurve;
        unsigned int size = 0;
        ///for each contour, analyze if it is a paralelepiped likely to be the marker
        for (unsigned int i=0;i<shapes->getContours().size();i++)
        {
            
            unsigned int contourSize = shapes->getContours()[i].size();
            //check it is a possible element by first checking is has enough points
            if (contourSize>(unsigned int)(frm->getFrame()->getMat().cols /15))
            {
                //approximate to a polygon - 1. limit slozitosti (pocet bodu krat cislo vs konstanta), 2. uzavreny
                
                double complexity = double(contourSize)*complexityKoef;
                complexity = complexity > maxComplexity ? maxComplexity : (complexity < minComplexity ? minComplexity : complexity);
                cv::approxPolyDP(  cv::Mat (shapes->getContours()[i]),approxCurve , complexity , onlyClosed);
                
                size = approxCurve.size();
                unsigned int one, two;
                
                if (approxCurve.size() >= 3) {
                    // remove inline points
                    for (unsigned int i = 0; i < size; i++) {
                        one = (i + 1)%size;
                        two = (i + 2)%size;
                        // rozdil smernic
                        double x1 = approxCurve[i].x, y1 =  approxCurve[i].y,
                               x2 = approxCurve[one].x, y2 =  approxCurve[one].y,
                               x3 = approxCurve[two].x, y3 =  approxCurve[two].y;
                        
                        float k = std::abs(((y2-y1)/(x2-x1)) - ((y3-y1)/(x3-x1)));
                        
                        float d1 = std::sqrt((float) (approxCurve[i].x-approxCurve[one].x)*(approxCurve[i].x-approxCurve[one].x) +
                                           (approxCurve[i].y-approxCurve[one].y)*(approxCurve[i].y-approxCurve[one].y));
                        
                        float d2 = std::sqrt((float) (approxCurve[i].x-approxCurve[two].x)*(approxCurve[i].x-approxCurve[two].x) +
                                             (approxCurve[i].y-approxCurve[two].y)*(approxCurve[i].y-approxCurve[two].y));
                            
                        // if angle is too small or points are too close
                        if (k < 0.2 || d1 < 0.04*d2) {
                            approxCurve.erase(approxCurve.begin()+one);
                            size--;
                        }
                    }
                }
                
                
                if (size >= minimalPolygonLines && size <= maximalPolygonLines)
                {
                    
                    //and is convex
                    if (!onlyConvex || cv::isContourConvex(Mat  (approxCurve)))
                    {
                        
                        float minDist=1e10;
                        if (minDistance > 0) {
                            for (int i=0;i<size;i++)
                            {
                                float d= std::sqrt((float) (approxCurve[i].x-approxCurve[(i+1)%size].x)*(approxCurve[i].x-approxCurve[(i+1)%size].x) +
                                                   (approxCurve[i].y-approxCurve[(i+1)%size].y)*(approxCurve[i].y-approxCurve[(i+1)%size].y));
                                if (d<minDist) minDist=d;
                            }
                        }
                        if (minDist>=minDistance)
                        {
                            shapes->getMarkers().push_back(Marker());
                            for (unsigned int i=0;i<size;i++)
                            {
                                shapes->getMarkers().back().push_back( Point2f(approxCurve[i].x,approxCurve[i].y));
                            }
                        }
                    }
                }
            }
        }
        
        /// remove these elements whise corners are too close to each other
        //first detect candidates
        size = shapes->getMarkers().size();
        
        if (minimalPolygonLines==4 && maximalPolygonLines == 4) {
            for (unsigned int i=0;i<shapes->getMarkers().size();i++)
            {
                
                //trace a line between the first and second point.
                //if the thrid point is at the right side, then the points are anti-clockwise
                double dx1 = shapes->getMarkers()[i][1].x - shapes->getMarkers()[i][0].x;
                double dy1 =  shapes->getMarkers()[i][1].y - shapes->getMarkers()[i][0].y;
                double dx2 = shapes->getMarkers()[i][2].x - shapes->getMarkers()[i][0].x;
                double dy2 = shapes->getMarkers()[i][2].y - shapes->getMarkers()[i][0].y;
                double o = (dx1*dy2)-(dy1*dx2);
                
                if (o  < 0.0)		 //if the third point is in the left side, then sort in anti-clockwise order
                {
                    swap(shapes->getMarkers()[i][1],shapes->getMarkers()[i][3]);
                }
            }
        }
        
        
        vector<pair<int,int>  > TooNearCandidates;
        for (unsigned int i=0;i < size;i++)
        {
            // 	cout<<"Marker i="<<i<<MarkerCanditates[i]<<endl;
            //calculate the average distance of each corner to the nearest corner of the other marker candidate
            for (unsigned int j=i+1;j<size;j++)
            {
                unsigned int vertexCount = shapes->getMarkers()[i].size();
                if (vertexCount == shapes->getMarkers()[j].size()) {
                    float dist=0;
                    for (unsigned int c=0;c<vertexCount;c++)
                        dist+= std::sqrt(  (shapes->getMarkers()[i][c].x-shapes->getMarkers()[j][c].x)*(shapes->getMarkers()[i][c].x-shapes->getMarkers()[j][c].x)+(shapes->getMarkers()[i][c].y-shapes->getMarkers()[j][c].y)*(shapes->getMarkers()[i][c].y-shapes->getMarkers()[j][c].y));
                    dist/=vertexCount;
                    //if distance is too small
                    if (dist< 14) {
                        TooNearCandidates.push_back(pair<int,int>(i,j));
                    }
                }
            }
        }
        //mark for removal the element of  the pair with smaller perimeter
        vector<bool> toRemove (shapes->getMarkers().size(),false);
        for (unsigned int i=0;i<TooNearCandidates.size();i++) {
            if ( perimeter(shapes->getMarkers()[TooNearCandidates[i].first ])>perimeter(shapes->getMarkers()[ TooNearCandidates[i].second] ))
                toRemove[TooNearCandidates[i].second]=true;
            else toRemove[TooNearCandidates[i].first]=true;
        }
        
        //remove the invalid ones
        removeElements(shapes->getMarkers(),toRemove);
        
        return true;
    }
    
    int DetectPolygons::perimeter(std::vector<cv::Point2f> &a)
    {
        int sum=0;
        for (unsigned int i=0;i<a.size();i++) {
            int i2=(i+1)%a.size();
            sum+= sqrt ( (a[i].x-a[i2].x)*(a[i].x-a[i2].x)+(a[i].y-a[i2].y)*(a[i].y-a[i2].y) ) ;
        }
        return sum;
    }
    
    /**Given a vector vinout with elements and a boolean vector indicating the lements from it to remove,
     * this function remove the elements
     * @param vinout
     * @param toRemove
     */
    template<typename T>
    void DetectPolygons::removeElements(std::vector<T> & vinout,const std::vector<bool> &toRemove)
    {
        //remove the invalid ones by setting the valid in the positions left by the invalids
        size_t indexValid=0;
        for (size_t i=0;i<toRemove.size();i++) {
            if (!toRemove[i]) {
                if (indexValid!=i) vinout[indexValid]=vinout[i];
                indexValid++;
            }
        }
        vinout.resize(indexValid);
    }
    
}