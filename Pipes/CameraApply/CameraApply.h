//
//  CameraApply.h
//  AR
//
//  Created by Menger David on 11.05.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef __AR__CameraApply__
#define __AR__CameraApply__

#include <iostream>
#include "BasePipe.h"
#include "cameraparameters.h"

namespace ArPipe {
    
    class CameraApply : public BasePipe
    {
    public:
        CameraApply(BaseFrameSource *previousPipe) : BasePipe() {
            CameraApply();
        }
        CameraApply() : BasePipe() {
            markerSizeMeters = 0.2;
            
            cv::Mat intrinsic_matrix = cv::Mat::eye(3,3,CV_32FC1);
            cv::Mat distortion_coeffs = cv::Mat::zeros(5,1,CV_32FC1);
            
            
            intrinsic_matrix.ptr<float>(0)[0] = 627.7718f;
            intrinsic_matrix.ptr<float>(0)[2] = 247.064377f;
            intrinsic_matrix.ptr<float>(1)[1] = 642.30059f;
            intrinsic_matrix.ptr<float>(1)[2] = 180.0777f;
            intrinsic_matrix.ptr<float>(2)[2] = 1.0f;
            
            //intrinsic_matrix.ptr<float>(0)[0] = 1560;
            //intrinsic_matrix.ptr<float>(0)[2] = 685;
            //intrinsic_matrix.ptr<float>(1)[1] = 1555;
            //intrinsic_matrix.ptr<float>(1)[2] = 325;
            
            /*
             fx = 1560
             > fy = 1555
             > cx = 685
             > cy = 325
             */
            
            //-4.1802327176423804e-001 5.0715244063187526e-001 0. 0. -5.7843597214487474e-001
            distortion_coeffs.ptr<float>(0)[0] = -6.1802327176423804e-001f;//4
            distortion_coeffs.ptr<float>(1)[0] = 5.0715244063187526e-001f;
            distortion_coeffs.ptr<float>(4)[0] = -5.7843597214487474e-001f;
            
            //distortion_coeffs.ptr<float>(0)[0] = -4.1802327176423804e-001f;//4
            //distortion_coeffs.ptr<float>(1)[0] = 5.0715244063187526e-001f;
            //distortion_coeffs.ptr<float>(4)[0] = -5.7843597214487474e-001f;
            
            cp.setParams(intrinsic_matrix, distortion_coeffs, cvSize(320, 240));
        }
        
        static CameraApply* init() {
            return new CameraApply();
        }
        
        bool processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        
        CameraApply* setCameraParameters(aruco::CameraParameters cameraParameters)
        {
            cp = cameraParameters;
            return this;
        }
        
        aruco::CameraParameters &getCameraParameters()
        {
            return cp;
        }
        
        
        /*CameraApply* set()
         {
         
         return this;
         }*/
        
        
    protected:
        aruco::CameraParameters cp;
        float markerSizeMeters;
        
        void draw3dCube(cv::Mat &Image,Marker &m);
        
    };
    
}
#endif /* defined(__AR__CameraApply__) */
