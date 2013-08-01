//
//  CAKeyFrameAnimation+Evaluators.h
//
//  Created by Daniele Margutti on 5/31/13.
//  Copyright (c) 2013 Daniele Margutti. All rights reserved.
//
//  Permission is given to use this source code file without charge in any
//  project, commercial or otherwise, entirely at your risk, with the condition
//  that any redistribution (in part or whole) of source code must retain
//  this copyright and permission notice. Attribution in compiled projects is
//  appreciated but not required.
//

#import <QuartzCore/QuartzCore.h>

#import "CAKeyFrameFunctions.h"
#import "CAKeyFrameEvaluators.h"

#define CAKeyFrameDefaultRate		60.0f	// You can use the default rate for animation (60fps)

#pragma mark - CAKeyframeAnimation

@interface CAKeyframeAnimation (Evaluators)

	// Build a new CAKeyFrameAnimation using an evaluator object. Evaluator object is a simple NSObject which can mantain variables state during
	// the build process and must respond to CAKeyFrameFunctionEvaluator protocol to return the value at given time t of the animation
	// Both initialValue and finalValue can be NSValue (CGPoint,CGSize) or CGFloat (encoded as NSNumber).
	// keyFrameCount is the rate of the animation (you can pass CAKeyFrameDefaultRate)

+ (id) animationWithKeyPath:(NSString *) path
				  evaluator:(id<CAKeyFrameFunctionEvaluator>) evaluatorObj
					   from:(id) initialValue
						 to:(id) finalValue
					   rate:(size_t) keyFrameCount;

	// Build a new CAKeyFrameAnimation using a simple C function (must be of type CAKeyFrameCustomFunction)
	// Both initialValue and finalValue can be NSValue (CGPoint,CGSize) or CGFloat (encoded as NSNumber).
	// keyFrameCount is the rate of the animation (you can pass CAKeyFrameDefaultRate)

+ (id) animationWithKeyPath:(NSString *) path
				   function:(CAKeyFrameCustomFunction) evaluationFunction
					   from:(id) initialValue
						 to:(id) finalValue
					   rate:(size_t) keyFrameCount;

#pragma mark - Use a pre-configured function

+ (CAKeyFrameCustomFunction) functionWithCurve:(CKCurveType) aCurve andEase:(CKCurveEaseType) aEase;

@end
