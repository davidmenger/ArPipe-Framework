//
//  GLRenderer.m
//  AR
//
//  Created by Menger David on 17.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#import "GLRenderer.h"

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

@implementation GLRenderer



bool _setUpped = false;

- (void)setModelViewMatrix: (double[16]) proj_matrix  {
	if (!_modelViewMatrix)  _modelViewMatrix = (float *) malloc(16*sizeof(float));
    
    
    for (int i=0; i<16; i++) {
        _modelViewMatrix[i] = [[NSString stringWithFormat:@"%f", proj_matrix[i]] floatValue];
    }
    
    //_modelViewMatrix[12] = -139.273804f;
    //_modelViewMatrix[13] = -70.511909f;
    //_modelViewMatrix[14] = 508.147858f;
    
	[self render];
}

- (void)setProjectionMatrix:(double[16]) proj_matrix {
    if (!_projectionMatrix)  _projectionMatrix = (float *) malloc(16*sizeof(float));
    
    for (int i=0; i<16; i++) {
        _projectionMatrix[i] = (float) proj_matrix[i];
    }
    _setUpped = false;
	//[self render];
}

// Create an ES 1.1 context
- (id) init
{
    
    
    
	if (self = [super init])
	{
        
        _projectionMatrix = (float *) malloc(16*sizeof(float));
        _projectionMatrix[0] = 2.190473f;
        _projectionMatrix[1] = 0.000000f;
        _projectionMatrix[2] = 0.000000f;
        _projectionMatrix[3] = 0.000000f;
        _projectionMatrix[4] = 0.000000f;
        _projectionMatrix[5] = -4.033856f;
        _projectionMatrix[6] = 0.000000f;
        _projectionMatrix[7] = 0.000000f;
        _projectionMatrix[8] = -0.010938f;
        _projectionMatrix[9] = -0.343518f;
        _projectionMatrix[10] = 1.000020f;
        _projectionMatrix[11] = 1.000000f;
        _projectionMatrix[12] = 0.000000f;
        _projectionMatrix[13] = 0.000000f;
        _projectionMatrix[14] = -0.200002f;
        _projectionMatrix[15] = 0.000000f;
        
        _modelViewMatrix = (float *) malloc(16*sizeof(float));
        _modelViewMatrix[0] = -0.793850f;
        _modelViewMatrix[1] = -0.574968f;
        _modelViewMatrix[2] = -0.198026f;
        _modelViewMatrix[3] = 0.000000f;
        _modelViewMatrix[4] = -0.464765f;
        _modelViewMatrix[5] = 0.783651f;
        _modelViewMatrix[6] = -0.412170f;
        _modelViewMatrix[7] = 0.000000f;
        _modelViewMatrix[8] = 0.392168f;
        _modelViewMatrix[9] = -0.235165f;
        _modelViewMatrix[10] = -0.889327f;
        _modelViewMatrix[11] = 0.000000f;
        _modelViewMatrix[12] = -139.273804f;
        _modelViewMatrix[13] = -70.511909f;
        _modelViewMatrix[14] = 508.147858f;
        _modelViewMatrix[15] = 1.000000f;
        
		context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
        
        if (!context || ![EAGLContext setCurrentContext:context])
		{
            NSLog(@"no context");
            [self release];
            return nil;
        }
		
		// Create default framebuffer object. The backing will be allocated for the current layer in -resizeFromLayer
		glGenFramebuffersOES(1, &defaultFramebuffer);
		glGenRenderbuffersOES(1, &colorRenderbuffer);
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, defaultFramebuffer);
		glBindRenderbufferOES(GL_RENDERBUFFER_OES, colorRenderbuffer);
		glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, colorRenderbuffer);
        
        // This call associates the storage for the current render buffer with the EAGLDrawable (our CAEAGLLayer)
        // allowing us to draw into a buffer that will later be rendered to screen wherever the layer is (which corresponds with our view).
        //[context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:(id<EAGLDrawable>)self.layer];
        //glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, colorRenderbuffer);
        
        //glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
        //glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);
	}
	
	return self;
}

- (void) render {
    
    if (true) {
        
        [EAGLContext setCurrentContext:context];
        
        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            NSLog(@"A: Error glGetError: glError: 0x%04X", err);
        }
        
        if (!_setUpped) {
            
            glBindFramebufferOES(GL_FRAMEBUFFER_OES, defaultFramebuffer);
            
            
            /*const GLfloat			lightAmbient[] = {1.0, 1.0, 1.0, 1.0};
             const GLfloat			lightDiffuse[] = {1.0, 1.0, 1.0, 1.0};
             const GLfloat			matAmbient[] = {1.0, 1.0, 1.0, 1.0};
             const GLfloat			matDiffuse[] = {1.0, 1.0, 1.0, 1.0};
             const GLfloat			matSpecular[] = {1.0, 1.0, 1.0, 1.0};
             const GLfloat			lightPosition[] = {1.0, 1.0, 1.0, 1.0};
             const GLfloat			lightShininess = 100.0;
             
             glEnable(GL_LIGHTING);
             glEnable(GL_LIGHT0);
             glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
             glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
             glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
             glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, lightShininess);
             glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
             glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
             glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); 	*/
            glShadeModel(GL_SMOOTH);
            glEnable(GL_DEPTH_TEST);
            
            err = glGetError();
            if (err != GL_NO_ERROR) {
                NSLog(@"B: Error glGetError: glError: 0x%04X", err);
            }
            
            /*configure the projection*/
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            if (_projectionMatrix) glLoadMatrixf(_projectionMatrix);
            
            //glViewport(0, 0, self.bounds.size.width, self.bounds.size.height);
            glViewport(0, 0, backingWidth, backingHeight);
            
            //NSLog(@"bounds: [%d, %d], ", backingWidth, backingHeight);
            
            glEnable(GL_DEPTH_TEST); /* enable depth testing; required for z-buffer */
            glEnable(GL_CULL_FACE); /* enable polygon face culling */
            glCullFace(GL_CLEAR);
            
            //Make the OpenGL modelview matrix the default
            //glMatrixMode(GL_MODELVIEW);
            
            //We enable normalization
            glEnable(GL_NORMALIZE);
            
            
            
            const GLfloat squareVertices2[] = {
                // FRONT
                -0.1f, -0.1f,  0.1f,
                0.1f, -0.1f,  0.1f,
                -0.1f,  0.1f,  0.1f,
                0.1f,  0.1f,  0.1f,
                // BACK
                -0.1f, -0.1f, -0.1f,
                -0.1f,  0.1f, -0.1f,
                0.1f, -0.1f, -0.1f,
                0.1f,  0.1f, -0.1f,
                // LEFT
                -0.1f, -0.1f,  0.1f,
                -0.1f,  0.1f,  0.1f,
                -0.1f, -0.1f, -0.1f,
                -0.1f,  0.1f, -0.1f,
                // RIGHT
                0.1f, -0.1f, -0.1f,
                0.1f,  0.1f, -0.1f,
                0.1f, -0.1f,  0.1f,
                0.1f,  0.1f,  0.1f,
                // TOP
                -0.1f,  0.1f,  0.1f,
                0.1f,  0.1f,  0.1f,
                -0.1f,  0.1f, -0.1f,
                0.1f,  0.1f, -0.1f,
                // BOTTOM
                -0.1f, -0.1f,  0.1f,
                -0.1f, -0.1f, -0.1f,
                0.1f, -0.1f,  0.1f,
                0.1f, -0.1f, -0.1f,
            };
            
            
            
            //glDisableClientState(GL_VERTEX_ARRAY);
            //glDisableClientState(GL_NORMAL_ARRAY);
            //glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            //glDisable(GL_TEXTURE_2D);
            
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            err = glGetError();
            if (err != GL_NO_ERROR) {
                NSLog(@"E: Error glGetError: glError: 0x%04X", err);
            }
            
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, squareVertices2);
            
            err = glGetError();
            if (err != GL_NO_ERROR) {
                NSLog(@"X: Error glGetError: glError: 0x%04X", err);
            }
            
            
            _setUpped = true;
        } else {
            
            
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
        }
        
        glMatrixMode(GL_MODELVIEW);
        if (_modelViewMatrix) {
            glLoadIdentity();
            glLoadMatrixf(_modelViewMatrix);
            //glScalef(50.0f, 50.0f, 50.0f);
            glTranslatef(0.0f, 0.1f, 0.0f);
        }
        
        err = glGetError();
        if (err != GL_NO_ERROR) {
            NSLog(@"Y: Error glGetError: glError: 0x%04X", err);
        }
        
        
        //glRotatef(25.0f, 1.0f, 0.0f, 1.0f);
        glColor4f(1.0f, 0.0f, 0.0f, 0.6f);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glColor4f(0.8f, 0.8f, 0.0f, 0.6f);
        glDrawArrays(GL_TRIANGLE_STRIP, 4, 4); //GL_TRIANGLE_STRIP
        
        glColor4f(0.0f, 1.0f, 0.0f, 0.6f);
        glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
        glColor4f(0.0f, 0.8f, 0.8f, 0.6f);
        glDrawArrays(GL_TRIANGLE_STRIP, 12, 4);
        
        glColor4f(0.0f, 0.0f, 1.0f, 0.6f);
        glDrawArrays(GL_TRIANGLE_STRIP, 16, 4);
        glColor4f(0.8f, 0.0f, 0.8f, 0.6f);
        glDrawArrays(GL_TRIANGLE_STRIP, 20, 4);
        
        
        
        
        
        
        
        //glClear(GL_DEPTH_BUFFER_BIT);
        //glFlush ();
        
        glBindRenderbufferOES(GL_RENDERBUFFER_OES, colorRenderbuffer);
        [context presentRenderbuffer:GL_RENDERBUFFER_OES];
        
        err = glGetError();
        if (err != GL_NO_ERROR) {
            NSLog(@"Z: Error glGetError: glError: 0x%04X", err);
        }
    } else {
        
        
        // Replace the implementation of this method to do your own custom drawing
        
        const GLfloat squareVertices[] = {
            -0.1f, -0.1f,
            0.1f,  -0.1f,
            -0.1f,  0.1f,
            0.1f,   0.1f,
        };
        const GLubyte squareColors[] = {
            255, 255,   0,   5,
            0,   255, 255, 255,
            0,     0,   0,   0,
            255,   0, 255, 255,
        };
        
        [EAGLContext setCurrentContext:context];
        
        glBindFramebufferOES(GL_FRAMEBUFFER_OES, defaultFramebuffer);
        glViewport(0, 0, backingWidth, backingHeight);
        //glLoadMatrixf(<#const GLfloat *m#>)
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        if (_projectionMatrix) glLoadMatrixf(_projectionMatrix);
        else glOrthof(-1.0f, 1.0f, -1.5f, 1.5f, -1.0f, 1.0f);
        glMatrixMode(GL_MODELVIEW);
        if (_modelViewMatrix) {
            //glLoadIdentity();
            //glLoadMatrixf(_modelViewMatrix);
            //glScalef(0.91f, 0.91f, 0.91f);
        }
        glRotatef(3.0f, 0.0f, 0.0f, 1.0f);
        
        
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glVertexPointer(2, GL_FLOAT, 0, squareVertices);
        glEnableClientState(GL_VERTEX_ARRAY);
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, squareColors);
        glEnableClientState(GL_COLOR_ARRAY);
        
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        
        glBindRenderbufferOES(GL_RENDERBUFFER_OES, colorRenderbuffer);
        [context presentRenderbuffer:GL_RENDERBUFFER_OES];
        
    }
}

- (BOOL) resizeFromLayer:(CAEAGLLayer *)layer
{
	// Allocate color buffer backing based on the current layer size
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, colorRenderbuffer);
    [context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:layer];
	glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);
	
    if (glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES) != GL_FRAMEBUFFER_COMPLETE_OES)
	{
		NSLog(@"Failed to make complete framebuffer object %x", glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES));
        return NO;
    }
    
    return YES;
}

- (void) dealloc
{
	// Tear down GL
	if (defaultFramebuffer)
	{
		glDeleteFramebuffersOES(1, &defaultFramebuffer);
		defaultFramebuffer = 0;
	}
	
	if (colorRenderbuffer)
	{
		glDeleteRenderbuffersOES(1, &colorRenderbuffer);
		colorRenderbuffer = 0;
	}
	
	// Tear down context
	if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
	
	[context release];
	context = nil;
	
	[super dealloc];
}

@end
