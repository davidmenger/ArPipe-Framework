//
//  SquareMarkerDetector.cpp
//  AR
//
//  Created by Menger David on 14.04.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "SquareMarkerDetector.h"

using namespace cv;
namespace ArPipe {
    
    bool SquareMarkerDetector::processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource)
    {
        if (frameSource == frameSourcePipe) {
            frame = frm;
        } else if (frameSource == shapesSourcePipe) {
            shapes = frm;
        }
        if (frame != NULL && shapes != NULL) {
            this->doTheDetection();
            return true;
        } else {
            return false;
        }
        
    }
    
    void SquareMarkerDetector::doTheDetection()
    {
        Shapes *shapes = this->shapes->getShapes();
        ///identify the markers
        detectedMarkers.clear();
        for (unsigned int i=0;i<shapes->getMarkers().size();i++)
        {
            //Find proyective homography
            Mat canonicalMarker;
            warp(frame->getFrame()->getMat(),canonicalMarker,Size(_markerWarpSize,_markerWarpSize),shapes->getMarkers()[i]);
            int nRotations;
            int id= this->detectMarker(canonicalMarker,nRotations);
            if (id!=-1)
            {
                detectedMarkers.push_back(shapes->getMarkers()[i]);
                detectedMarkers.back().id=id;
                //sort the points so that they are always in the same order no matter the camera orientation
                std::rotate(detectedMarkers.back().begin(),detectedMarkers.back().begin()+4-nRotations,detectedMarkers.back().end());
            }
            /*else
                _candidates.push_back(shapes->getMarkers()[i]);*/
        }
        
        
        ///refine the corner location if desired
        if (detectedMarkers.size()>0 && _cornerMethod!=NONE)
        {
            vector<Point2f> Corners;
            for (unsigned int i=0;i<detectedMarkers.size();i++)
                for (int c=0;c<4;c++)
                    Corners.push_back(detectedMarkers[i][c]);
            if (_cornerMethod==HARRIS)
                findBestCornerInRegion_harris(frame->getFrame()->getMat(), Corners,18);
            else if (_cornerMethod==SUBPIX)
                cornerSubPix(frame->getFrame()->getMat(), Corners,cvSize(1,1), cvSize(-1,-1)   ,cvTermCriteria ( CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,3,0.05 ));
            
            //copy back
            for (unsigned int i=0;i<detectedMarkers.size();i++)
                for (int c=0;c<4;c++)     detectedMarkers[i][c]=Corners[i*4+c];
        }
        //sort by id
        std::sort(detectedMarkers.begin(),detectedMarkers.end());
        //there might be still the case that a marker is detected twice because of the double border indicated earlier,
        //detect and remove these cases
        vector<bool> toRemove (detectedMarkers.size(),false);
        for (int i=0;i<int(detectedMarkers.size())-1;i++) {
            if (detectedMarkers[i].id==detectedMarkers[i+1].id && !toRemove[i+1] ) {
                //deletes the one with smaller perimeter
                if (perimeter(detectedMarkers[i])>perimeter(detectedMarkers[i+1])) toRemove[i+1]=true;
                else toRemove[i]=true;
            }
        }
        //remove the markers marker
        removeElements(detectedMarkers, toRemove);
        
        frame->getShapes()->setMarkers(detectedMarkers);
        containerToPush = frame;
        delete this->shapes;
        this->shapes = NULL;
    }
    
    
    
    /**
     *
     *
     */
    void SquareMarkerDetector::warp(Mat &in,Mat &out,Size size, vector<Point2f> points)throw (cv::Exception)
    {
        
        if (points.size()!=4)    throw cv::Exception(9001,"point.size()!=4","MarkerDetector::warp",__FILE__,__LINE__);
        //obtain the perspective transform
        Point2f  pointsRes[4],pointsIn[4];
        for (int i=0;i<4;i++) pointsIn[i]=points[i];
        pointsRes[0]=(Point2f(0,0));
        pointsRes[1]= Point2f(size.width-1,0);
        pointsRes[2]= Point2f(size.width-1,size.height-1);
        pointsRes[3]= Point2f(0,size.height-1);
        Mat M=getPerspectiveTransform(pointsRes,pointsIn);
        cv::warpPerspective(in, out,  M, size,cv::INTER_NEAREST+cv::WARP_INVERSE_MAP);
    }
    
    /**
     *
     *
     */
    void SquareMarkerDetector::findBestCornerInRegion_harris(const cv::Mat  & grey,vector<cv::Point2f> &  Corners,int blockSize)
    {
        int halfSize=blockSize/2;
        for (size_t i=0;i<Corners.size();i++) {
            //check that the region is into the image limits
            cv::Point2f min(Corners[i].x-halfSize,Corners[i].y-halfSize);
            cv::Point2f max(Corners[i].x+halfSize,Corners[i].y+halfSize);
            if (min.x>=0  &&  min.y>=0 && max.x<grey.cols && max.y<grey.rows) {
                cv::Mat response;
                cv::Mat subImage(grey,cv::Rect(Corners[i].x-halfSize,Corners[i].y-halfSize,blockSize ,blockSize ));
                vector<Point2f> corners2;
                goodFeaturesToTrack(subImage, corners2, 10, 0.001, halfSize);
                float minD=9999;
                int bIdx=-1;
                cv::Point2f Center(halfSize,halfSize);
                for (size_t j=0;j<corners2.size();j++) {
                    float dist=cv::norm(corners2[j]-Center);
                    if (dist<minD) {
                        minD=dist;
                        bIdx=j;
                    }
                }
            }
        }
    }
    
    
    
    /************************************
     *
     *
     *
     *
     ************************************/
    bool SquareMarkerDetector::isInto(Mat &contour,vector<Point2f> &b)
    {
        
        for (unsigned int i=0;i<b.size();i++)
            if ( pointPolygonTest( contour,b[i],false)>0) return true;
        return false;
    }
    /************************************
     *
     *
     *
     *
     ************************************/
    int SquareMarkerDetector:: perimeter(vector<Point2f> &a)
    {
        int sum=0;
        for (unsigned int i=0;i<a.size();i++) {
            int i2=(i+1)%a.size();
            sum+= sqrt ( (a[i].x-a[i2].x)*(a[i].x-a[i2].x)+(a[i].y-a[i2].y)*(a[i].y-a[i2].y) ) ;
        }
        return sum;
    }
    
}
