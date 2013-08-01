//
//  CAKeyFrameFunctions.h
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

#ifndef CoreUIKitLayer_CAKeyFrameFunctions_h
#define CoreUIKitLayer_CAKeyFrameFunctions_h

/** define a function format */
typedef CGFloat (*CAKeyFrameCustomFunction)(CGFloat);

#pragma mark Curve Type

enum {
	CKCurveTypeLinear,
	CKCurveTypeQuadratic,
	CKCurveTypeCubic,
	CKCurveTypeQuartic,
	CKCurveTypeQuintic,
	CKCurveTypeSineWave,
	CKCurveTypeCircular,
	CKCurveTypeExponential,
	CKCurveTypeElastic,
	CKCurveTypeBack,
	CKCurveTypeBounce
}; typedef NSUInteger CKCurveType;

#pragma mark Curve Ease Type

enum {
	CKCurveEaseTypeIn,
	CKCurveEaseTypeOut,
	CKCurveEaseTypeInOut
}; typedef NSUInteger CKCurveEaseType;

#pragma mark -
#pragma mark FUNCTIONS

#pragma mark - LINEAR INTERPOLATION

/** Linear interpolation without ease.
 Model (line):
 y = x
 */
CGFloat CAKeyFrameAnLinearInterpolation(CGFloat t);

#pragma mark - QUADRATIC EASING ^2

/** Quadratic ease in function.
 Model is the parabola:
 y = x^2
 */
CGFloat CAKeyFrameAnQuadraticEaseIn(CGFloat t);

/** Quadratic ease out function.
 Model (inverse parabola):
 y = -x^2 + 2x
 */
CGFloat CAKeyFrameAnQuadraticEaseOut(CGFloat t);

/** Quadratic ease in/out function.
 Model (piecewise quadratic):
 [0.0,0.5]		=>		y = (1/2)((2x)^2)
 [0.5,1.0]		=>		y = -(1/2)((2x-1)*(2x-3) - 1)
 */
CGFloat CAKeyFrameAnQuadraticEaseInOut(CGFloat t);

#pragma mark - CUBIC EASING ^3

/** Cubic ease in function
 Model:
 y = x^3
 */
CGFloat CAKeyFrameAnCubicEaseIn(CGFloat t);

/**	Cubic ease out
 Model:
 y = (x - 1)^3 + 1
 */
CGFloat CAKeyFrameAnCubicEaseOut(CGFloat t);

/** Cubic ease in/out
 Model (piecewise cubic):
 [0.0,0.5]		=>		y=(1/2)((2x)^3)
 [0.5,1.0]		=>		y=(1/2)((2x-2)^3 + 2)
 */
CGFloat CAKeyFrameAnCubicEaseInOut(CGFloat t);

#pragma mark - QUARTIC EASING ^3

/**	Quartic ease in
 Model:
 y = x^4
 */
CGFloat CAKeyFrameAnQuarticEaseIn(CGFloat t);

/** Quartic ease out
 Model:
 y = 1 - (x - 1)^4
 */
CGFloat CAKeyFrameAnQuarticEaseOut(CGFloat t);

/**	Quartic ease in/out
 Model:
 [0.0,0.5]		=>		y = (1/2)((2x)^4)
 [0.5,1.0]		=>		y = -(1/2)((2x-2)^4 - 2)
 */
CGFloat CAKeyFrameAnQuarticEaseInOut(CGFloat t);

#pragma mark - QUINTIC EASING ^5

/**	Quintic ease in
 Model:
 y = x^5
 */
CGFloat CAKeyFrameAnQuinticEaseIn(CGFloat t);


/**	Quintic ease out
 Model:
 y = (x - 1)^5 + 1
 */
CGFloat CAKeyFrameAnQuinticEaseOut(CGFloat t);

/** Quintic ease in/out
 Model:
 [0.0,0.5]	=>		y = y = (1/2)((2x)^5)
 [0.0,0.5]	=>		y = y = (1/2)((2x)^5)
 */
CGFloat CAKeyFrameAnQuinticEaseInOut(CGFloat t);

#pragma mark - SINE WAVE EASING

/** SINE EASE IN
 Model:
 y = sin((p - 1) * M_PI_2) + 1
 */
CGFloat CAKeyFrameAnSineEaseIn(CGFloat t);

/**	SINE EASE OUT
 Model:
 quarter-cycle of sine wave (different phase)
 */
CGFloat CAKeyFrameAnSineEaseOut(CGFloat t);

/** SINE EASE IN/OUT
 Model (sine wave)
 */
CGFloat CAKeyFrameAnSineEaseInOut(CGFloat t);

#pragma mark - CIRCULAR EASING

/** CIRCULAR EASE IN
 Model (shifted quadrant IV of unit circle)
 */
CGFloat CAKeyFrameAnCircularEaseIn(CGFloat t);

/** CIRCULAR EASE OUT
 (hifted quadrant II of unit circle)
 */
CGFloat CAKeyFrameAnCircularEaseOut(CGFloat t);

/** CIRCULAR EASE IN/OUT
 (piecewise circular function)
 [0.0,0.5]		=>		y = (1/2)(1 - sqrt(1 - 4x^2))
 [0.5,1.0]		=>		y = (1/2)(sqrt(-(2x - 3)*(2x - 1)) + 1)
 */
CGFloat CAKeyFrameAnCircularEaseInOut(CGFloat t);

#pragma mark - EXPONENTIAL EASING

/** EXPONENTIAL FUNCTION
 y = 2^(10(x - 1))
 */
CGFloat CAKeyFrameAnExponentialEaseIn(CGFloat t);

/** EXPONENTIAL EASE OUT
 (exponential function)
 y = -2^(-10x) + 1
 */
CGFloat CAKeyFrameAnExponentialEaseOut(CGFloat t);


/** EXPONENTIAL EASE IN OUT
 [0.0,0.5]		=>		y = (1/2)2^(10(2x - 1))
 [0.5,1.0]		=>		y = -(1/2)*2^(-10(2x - 1))) + 1
 */
CGFloat CAKeyFrameAnExponentialEaseInOut(CGFloat t);

#pragma mark - ELASTIC EASING

/** ELASTIC SINE WAVE
 (damped sine wave)
 y = sin(13pi/2*x)*pow(2, 10 * (x - 1))
 */
CGFloat CAKeyFrameAnElasticEaseIn(CGFloat t);

/** ELASTIC EASE OUT
 (damped sine wave)
 y = sin(-13pi/2*(x + 1))*pow(2, -10x) + 1
 */
CGFloat CAKeyFrameAnElasticEaseOut(CGFloat t);


/** ELASTIC EASE IN OUT
 (piecewise exponentially-damped sine wave)
 [0.0,0.5]		=>		y = (1/2) * sin(13 pi/2*(2*x)) * pow(2, 10 * ((2*x) - 1))
 [0.5,1.0]		=>		y = (1/2) * (sin(-13 pi/2*((2x-1)+1)) * pow(2,-10(2*x-1)) + 2)
 */
CGFloat CAKeyFrameAnElasticEaseInOut(CGFloat t);

#pragma mark - BACK EASING

/** BACK EASE IN
 (overshooting cubic)
 y = x^3-x*sin(x*pi)
 */
CGFloat CAKeyFrameAnBackEaseIn(CGFloat t);

/** BACK EASE OUT
 (overshooting cubic)
 y = 1-((1-x)^3-(1-x)*sin((1-x)*pi))
 */
CGFloat CAKeyFrameAnBackEaseOut(CGFloat t);

#pragma mark - BOUNCE EASING

/** BACK EASE IN OUT
 (piecewise overshooting cubic function)
 [0.0,0.5]		=>		y = (1/2)*((2x)^3-(2x)*sin(2*x*pi))
 [0.5,1.0]		=>		y = (1/2)*(1-((1-x)^3-(1-x)*sin((1-x)*pi))+1)
 */
CGFloat CAKeyFrameAnBackEaseInOut(CGFloat t);

/** BOUNCE EASE IN */
CGFloat CAKeyFrameAnBounceEaseIn(CGFloat t);

/** BOUNCE EASE OUT */
CGFloat CAKeyFrameAnBounceEaseOut(CGFloat t);

/** BOUNCE EASE IN OUT */
CGFloat CAKeyFrameAnBounceEaseInOut(CGFloat t);

#pragma mark - OTHER

/** EXPONENTIAL DECAY BEHAVIOR */
CGFloat CAKeyFrameAnExponentialDecay(CGFloat t);

#endif
