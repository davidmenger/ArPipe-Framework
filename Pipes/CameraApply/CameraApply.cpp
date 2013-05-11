//
//  CameraApply.cpp
//  AR
//
//  Created by Menger David on 11.05.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "CameraApply.h"

namespace ArPipe {
    
    bool CameraApply::processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource)
    {
        cv::Mat camMatrix = cp.CameraMatrix;
        cv::Mat distCoeff = cp.Distorsion;
        
        ///detect the position of detected markers if desired
        if (camMatrix.rows!=0  && markerSizeMeters>0 && cp.isValid())
        {
            for (unsigned int i=0;i<frm->getShapes()->getMarkers().size();i++) {
                frm->getShapes()->getMarkers()[i].calculateExtrinsics(markerSizeMeters,camMatrix,distCoeff);
                //this->draw3dCube(frm->getFrame()->getMat(), frm->getShapes()->getMarkers()[i]);
            }
        }
        
        
        
        return true;
    }
    
    
    /****
     *
     *
     *
     ****/
    void CameraApply::draw3dCube(cv::Mat &Image,Marker &m)
    {
        Mat objectPoints (8,3,CV_32FC1); //CV_32FC1
        float halfSize=m.ssize/2;
        objectPoints.at<float>(0,0)=-halfSize;
        objectPoints.at<float>(0,1)=0;
        objectPoints.at<float>(0,2)=-halfSize;
        objectPoints.at<float>(1,0)=halfSize;
        objectPoints.at<float>(1,1)=0;
        objectPoints.at<float>(1,2)=-halfSize;
        objectPoints.at<float>(2,0)=halfSize;
        objectPoints.at<float>(2,1)=0;
        objectPoints.at<float>(2,2)=halfSize;
        objectPoints.at<float>(3,0)=-halfSize;
        objectPoints.at<float>(3,1)=0;
        objectPoints.at<float>(3,2)=halfSize;
        
        objectPoints.at<float>(4,0)=-halfSize;
        objectPoints.at<float>(4,1)=m.ssize;
        objectPoints.at<float>(4,2)=-halfSize;
        objectPoints.at<float>(5,0)=halfSize;
        objectPoints.at<float>(5,1)=m.ssize;
        objectPoints.at<float>(5,2)=-halfSize;
        objectPoints.at<float>(6,0)=halfSize;
        objectPoints.at<float>(6,1)=m.ssize;
        objectPoints.at<float>(6,2)=halfSize;
        objectPoints.at<float>(7,0)=-halfSize;
        objectPoints.at<float>(7,1)=m.ssize;
        objectPoints.at<float>(7,2)=halfSize;
        
        
        
        vector<Point2f> imagePoints;
        //projectPoints( objectPoints, m.Rvec,m.Tvec,  CP.CameraMatrix,CP.Distorsion,   imagePoints);
        
        cv::projectPoints(objectPoints, m.Rvec, m.Tvec, cp.CameraMatrix, cp.Distorsion, imagePoints);
        //draw lines of different colours
        for (int i=0;i<4;i++) {
            cv::line(Image,imagePoints[i],imagePoints[(i+1)%4],Scalar(0,0,255,255),2,CV_AA);
            cv::line(Image,m[0],imagePoints[i+4],Scalar(0,0,255,255),2,CV_AA);
        }
        
        for (int i=0;i<4;i++) {
            cv::line(Image,imagePoints[i+4],imagePoints[4+(i+1)%4],Scalar(0,0,255,255),2,CV_AA);
            cv::line(Image,imagePoints[4+(i+1)%4],m[0],Scalar(0,0,255,255),2,CV_AA);
        }
        
        for (int i=0;i<4;i++) {
            cv::line(Image,imagePoints[i],imagePoints[i+4],Scalar(0,0,255,255),2,CV_AA);
            cv::line(Image,imagePoints[i],m[1],Scalar(0,0,255,255),2,CV_AA);
        }
        
        
    }
    
}