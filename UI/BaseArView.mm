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

volatile CGImageRef cgImageRef;
volatile Boolean hasNewFrame;
Boolean shownFrameOutput;

void pushNewFrameContainer(ArPipe::BaseFrameContainer *frm)
{
    if (shownFrameOutput && !hasNewFrame) {
        
        cv::Mat mat = frm->getFrame()->getMat();
        NSData *data = [NSData dataWithBytes:mat.data length: mat.elemSize()*mat.total()];
        CGColorSpaceRef colorSpace;
        
        if (frm->getFrame()->getMat().elemSize() == 1) {
            colorSpace = CGColorSpaceCreateDeviceGray();
        } else {
            colorSpace = CGColorSpaceCreateDeviceRGB();
        }
        
        //CGDataProviderRef provider = CGDataProviderCreateWithCFData((__bridge CFDataRef)data);
        CGDataProviderRef provider = CGDataProviderCreateWithCFData((CFDataRef)data);
        
        // Creating CGImage from cv::Mat
        cgImageRef =  CGImageCreate(mat.cols, mat.rows,                                 //height
                                            8,                                          //bits per component
                                            8 * mat.elemSize(),                       //bits per pixel
                                            mat.step[0],                            //bytesPerRow
                                            colorSpace,                                 //colorspace
                                            kCGImageAlphaNone|kCGBitmapByteOrderDefault,// bitmap info
                                            provider,                                   //CGDataProviderRef
                                            NULL,                                       //decode
                                            false,                                      //should interpolate
                                            kCGRenderingIntentDefault                   //intent
                                            );
        
        CGDataProviderRelease(provider);
        CGColorSpaceRelease(colorSpace);
        hasNewFrame = TRUE;
    }
}



- (void) drawView: (id) sender
{
        if (hasNewFrame && shownFrameOutput) {
            //CGImageRef ref = (CGImageRef) frameOutputLayer.contents;
            [frameOutputLayer setContents: (id) cgImageRef];
            CFRelease(cgImageRef);
            hasNewFrame = FALSE;
        } else if (hasNewFrame) {
            CFRelease(cgImageRef);
            hasNewFrame = FALSE;
        }
    
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        
        connector = new ArPipe::PipeOutputConnector();
        connector->setOnNewFrameContainerCallback(&pushNewFrameContainer);
        
        displayLinkSupported = FALSE;
        frameRate = 1;
        hasNewFrame = FALSE;
        
        // A system version of 3.1 or greater is required to use CADisplayLink. The NSTimer
		// class is used as fallback when it isn't available.
		NSString *reqSysVer = @"3.1";
		NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
		if ([currSysVer compare:reqSysVer options:NSNumericSearch] != NSOrderedAscending)
			displayLinkSupported = TRUE;
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
    frameSource->addNextPipe(connector);
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

- (void) showFrameOutput
{
    if (!shownFrameOutput) {
        if (!frameOutputLayer) {
            frameOutputLayer = [[CALayer alloc] init];
            CGRect bounds = [self layer].bounds;
            [frameOutputLayer setBounds:bounds];
            
            [frameOutputLayer setFrame:[self frame]];
            [frameOutputLayer setContentsGravity: kCAGravityResizeAspectFill];
            
            
            [[self layer] addSublayer:frameOutputLayer];
            
            UIImage* img = [UIImage imageNamed:@"original-coffee-88.jpg"];
            [frameOutputLayer setContents: (id) img.CGImage];
        }
        
        if (displayLinkSupported)
		{
			// CADisplayLink is API new to iPhone SDK 3.1. Compiling against earlier versions will result in a warning, but can be dismissed
			// if the system version runtime check for CADisplayLink exists in -initWithCoder:. The runtime check ensures this code will
			// not be called in system versions earlier than 3.1.
			
			displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(drawView:)];
			[displayLink setFrameInterval: frameRate];
            [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
		}
		else
			animationTimer = [NSTimer scheduledTimerWithTimeInterval:(NSTimeInterval)((1.0 / 60.0) * frameRate) target:self selector:@selector(drawView:) userInfo:nil repeats:TRUE];
		
        
        [frameOutputLayer setHidden:NO];
        shownFrameOutput = YES;
    }
}

- (void) hideFrameOutput
{
    if (shownFrameOutput && frameOutputLayer)
    {
        [frameOutputLayer setHidden:YES];
        shownFrameOutput = FALSE;
    }
}

@end
