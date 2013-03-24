//
//  BaseArView.h
//  AR
//
//  Created by Menger David on 17.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "GLView.h"
#import "PipeOutputConnector.h"


@interface BaseArView : UIView {
    
@protected
    GLView *glView;
    UIView *previewView;
    ArPipe::PipeOutputConnector *connector;
    Boolean showPreview;
    AVCaptureVideoPreviewLayer *previewLayer;
}

@property (retain) AVCaptureSession* session;

- (id) initWithFrameAndCaptureSession:(CGRect) frame captureSession:(AVCaptureSession*) captureSession;
- (void) appendAsNextPipe: (ArPipe::BaseFrameSource*) frameSource;
- (void) showPreviewLayer;
- (void) hidePreviewLayer;

@end
