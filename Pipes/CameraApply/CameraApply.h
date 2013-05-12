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
    
    //! Object used for applying camera parameters to detected Markers
    /**
     * Object contains default camera data for iPhone 4S
     */
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

            distortion_coeffs.ptr<float>(0)[0] = -6.1802327176423804e-001f;//4
            distortion_coeffs.ptr<float>(1)[0] = 5.0715244063187526e-001f;
            distortion_coeffs.ptr<float>(4)[0] = -5.7843597214487474e-001f;
            
            cp.setParams(intrinsic_matrix, distortion_coeffs, cvSize(320, 240));
        }
        
        /**
         * Factory to create new CameraApply pipe
         * @return new instance
         */
        static CameraApply* init() {
            return new CameraApply();
        }
        
        bool processFrameContainer(BaseFrameContainer *frm, BaseFrameSource *frameSource);
        
        /**
         * Setter for camera parameters
         * @param cameraParameters aruco::CameraParameters object 
         * @return current pipe object. Supports fluent interface
         */
        CameraApply* setCameraParameters(aruco::CameraParameters cameraParameters)
        {
            cp = cameraParameters;
            return this;
        }
        
        /**
         * Returns current camera parameters object
         * @return 
         */
        aruco::CameraParameters &getCameraParameters()
        {
            return cp;
        }
        
        
    protected:
        aruco::CameraParameters cp;
        float markerSizeMeters;
        
        void draw3dCube(cv::Mat &Image,Marker &m);
        
    };
    
}
#endif /* defined(__AR__CameraApply__) */
