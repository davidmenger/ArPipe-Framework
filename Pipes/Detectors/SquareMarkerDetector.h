//
//  SquareMarkerDetector.h
//  AR
//
//  Created by Menger David on 14.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//  Using Aruco framework algorithms: http://www.uco.es/investiga/grupos/ava/node/26
//

#ifndef __AR__SquareMarkerDetector__
#define __AR__SquareMarkerDetector__

#include <iostream>
#include "PipeMerge.h"

namespace ArPipe {
    
    enum CornerRefinementMethod {NONE,HARRIS,SUBPIX};
    
    //! Abstract class providing interface to identify detected markers
    /**
     * Extend this class to create own marker detector
     */
    class SquareMarkerDetector : public PipeMerge
    {
    public:
        
        SquareMarkerDetector() : PipeMerge() {
            _markerWarpSize = 56;
            _cornerMethod = HARRIS;
        }
        
        /**
         * Method to override in extending class to process marker
         * @param in Normalized marker image data
         * @param nRotations number of rotations
         * @return 
         */
        virtual int detectMarker(const cv::Mat &in,int &nRotations)=0;
        
        void processFrameAndShapes();
                
    protected:
        vector<Marker>  detectedMarkers;
        int _markerWarpSize;
        CornerRefinementMethod _cornerMethod;
        
        void doTheDetection();
        
        /**Given the iput image with markers, creates an output image with it in the canonical position
         * @param in input image
         * @param out image with the marker
         * @param size of out
         * @param points 4 corners of the marker in the image in
         */
        void warp(cv::Mat &in,cv::Mat &out,cv::Size size, std::vector<cv::Point2f> points)throw (cv::Exception);
        
        //detection of the
        void findBestCornerInRegion_harris(const cv::Mat  & grey,vector<cv::Point2f> &  Corners,int blockSize);
        
        /**
         */
        bool isInto(cv::Mat &contour,std::vector<cv::Point2f> &b);
        /**
         */
        int perimeter(std::vector<cv::Point2f> &a);
        
        /**Given a vector vinout with elements and a boolean vector indicating the lements from it to remove,
         * this function remove the elements
         * @param vinout
         * @param toRemove
         */
        template<typename T>
        void removeElements(vector<T> & vinout,const vector<bool> &toRemove)
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
        
    };
    
}

#endif /* defined(__AR__SquareMarkerDetector__) */
