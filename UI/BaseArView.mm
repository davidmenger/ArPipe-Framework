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
@synthesize glview = _glview;

- (GLView*) glview
{
    if (_glview == nil) {
        _glview = [[GLView alloc] initWithFrame:self.frame];
        [self addSubview:_glview];
        [_glview setHidden:YES];
    }
    return _glview;
}


volatile Boolean hasNewFrame;
volatile Boolean processingFrame;
UIImage *img;
NSData *data;
UIImageView* frameOutputView;
id slf;
Boolean shownFrameOutput;
Boolean shownGlView;

void pushNewFrameContainer(ArPipe::BaseFrameContainer *frm)
{
    if (shownFrameOutput && !hasNewFrame && !processingFrame) {
        processingFrame = TRUE;
        
        if (shownFrameOutput) {
            cv::Mat mat = frm->getFrame()->getMat();
            
            if (data) {
                [data release];
                data = nil;
            }
            data = [[NSData alloc] initWithBytes:mat.data length: mat.elemSize()*mat.total()];
            
            CGColorSpaceRef colorSpace;
            
            if (frm->getFrame()->getMat().elemSize() == 1) {
                colorSpace = CGColorSpaceCreateDeviceGray();
            } else {
                colorSpace = CGColorSpaceCreateDeviceRGB();
            }
            
            CGDataProviderRef provider = CGDataProviderCreateWithCFData((CFDataRef) data);
            
            // Creating CGImage from cv::Mat
            CGImageRef cgImageRef =  CGImageCreate(mat.cols, mat.rows,                                 //height
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
            
            if (img) {
                [img release];
                img = nil;
            }
            
            img = [[UIImage alloc] initWithCGImage:cgImageRef];
            
            
            CGImageRelease(cgImageRef);
            CGDataProviderRelease(provider);
            CGColorSpaceRelease(colorSpace);
            
            
            
            processingFrame = FALSE;
            hasNewFrame = TRUE;
            
            dispatch_async(dispatch_get_main_queue(), ^{
                [slf setNeedsDisplay];
            });
            
            
            if (shownGlView) {
                
                //dispatch_async(dispatch_get_main_queue(), ^{
                    BaseArView *arv = (BaseArView*) slf;
                    
                    for (unsigned int i = 0; i < frm->getShapes()->getMarkers().size(); i++) {
                        
                        double proj_matrix[16];
                        arv->cp.glGetProjectionMatrix(frm->getFrame()->getMat().size(), frm->getFrame()->getMat().size(), proj_matrix, 0.1, 100.0);
                        [arv.glview setProjectionMatrix:proj_matrix];
                        
                        
                        double model_matrix[16];
                        frm->getShapes()->getMarkers()[i].glGetModelViewMatrix(model_matrix);
                        [arv.glview setModelViewMatrix:model_matrix];
                    }
                
                //});
                
                
            }
        }
    }
}

- (void) drawRect:(CGRect)rect
{
    [super drawRect:rect];
    if (hasNewFrame && shownFrameOutput && !processingFrame) {
        processingFrame = TRUE;
        
        UIImage *tmp = [img copy];
        [frameOutputView setImage: tmp];
        [tmp release];
        
        
        hasNewFrame = FALSE;
        processingFrame = false;
    }
}


- (void) drawView: (id) sender
{
    
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
        processingFrame = FALSE;
        slf = self;
        img = nil;
        data = nil;
        
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

- (void) showGlView
{
    if (!shownGlView) {
        shownGlView = TRUE;
        [[self glview] setHidden:NO];
    }
}

- (void) showFrameOutput
{
    if (!shownFrameOutput) {
        if (!frameOutputView) {
            frameOutputView = [[UIImageView alloc] init];
            CGRect bounds = [self layer].bounds;
            [frameOutputView setBounds:bounds];
            
            [frameOutputView setFrame:[self frame]];
            
            
            
            [self addSubview:frameOutputView];
            
            [frameOutputView setImage: [UIImage imageNamed:@"original-coffee-88.jpg"]];
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
			animationTimer = [NSTimer scheduledTimerWithTimeInterval:(NSTimeInterval)((1.0 / 30.0) * frameRate) target:self selector:@selector(drawView:) userInfo:nil repeats:TRUE];
		
        
        [frameOutputView setHidden:NO];
        shownFrameOutput = YES;
    }
}

- (void) hideFrameOutput
{
    if (shownFrameOutput && frameOutputView)
    {
        [frameOutputView setHidden:YES];
        shownFrameOutput = FALSE;
    }
}

@end
