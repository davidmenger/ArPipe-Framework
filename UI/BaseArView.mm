//
//  BaseArView.m
//  AR
//
//  Created by Menger David on 17.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#import "BaseArView.h"
#import "BaseFrameContainer.h"

@implementation BaseArView

@synthesize session;

void pushNewFrameContainer(ArPipe::BaseFrameContainer *frm)
{
    
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        
        connector = new ArPipe::PipeOutputConnector();
        connector->setOnNewFrameContainerCallback(&pushNewFrameContainer);
        
    }
    return self;
}

- (id)initWithFrameAndCaptureSession:(CGRect)frame captureSession:(AVCaptureSession *)captureSession
{
    self = [self initWithFrame:frame];
    if (self)
    {
        [self setSession:captureSession];
    }
    return self;
}

- (void)appendAsNextPipe:(ArPipe::BaseFrameSource *)frameSource
{
    frameSource->setNextPipe(connector);
}

- (void)showPreviewLayer
{
    if (!showPreview)
    {
        if (![self session]) {
            NSLog(@"For use preview layer, please set Capture Session");
        }
        if (!previewLayer) {
            previewLayer = [[AVCaptureVideoPreviewLayer alloc] initWithSession: session];
            
            CGRect bounds= [self layer].bounds;
            previewLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
            previewLayer.bounds=bounds;
            previewLayer.position=CGPointMake(CGRectGetMidX(bounds), CGRectGetMidY(bounds));
            
            [[self layer] insertSublayer:previewLayer atIndex:0];
        }
        [previewLayer setHidden:NO];
        showPreview = YES;
    }
}

-(void)hidePreviewLayer
{
    if (showPreview && previewLayer)
    {
        [previewLayer setHidden:YES];
        showPreview = FALSE;
    }
}


- (ArPipe::PipeOutputConnector*) pipeConnector
{
    return connector;
}


@end
