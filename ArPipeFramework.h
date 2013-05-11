//
//  ArPipeFramework.h
//  AR
//
//  Created by Menger David on 24.03.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#ifndef AR_ArPipeFramework_h
#define AR_ArPipeFramework_h

#include "./Model/BasePipeOutput.h"
#include "./Model/BasePipe.h"
#include "./Model/BaseFrameSource.h"
#include "./Model/BaseFrameContainer.h"
#include "./Model/Frame.h"
#include "./Model/PipeLine.h"
#include "./Pipes/Basic/PolarRotate.h"
#include "./Pipes/Effects/Threshold.h"
#include "./Pipes/Effects/BlackAndWhite.h"
#include "./Pipes/Effects/Canny.h"
#include "./Pipes/Effects/Blur.h"

#include "./Pipes/Recognizers/FindContours.h"
#include "./Pipes/Recognizers/DetectPolygons.h"

#include "./Pipes/Drawers/DrawContrours.h"

#include "./Pipes/CameraApply/CameraApply.h"

#include "./Pipes/MarkerIdentifiers/FiducidalMarkerIdentifier.h"

#endif
