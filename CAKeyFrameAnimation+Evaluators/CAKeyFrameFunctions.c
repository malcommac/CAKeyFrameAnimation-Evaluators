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

#include <stdio.h>
#include <CoreGraphics/CoreGraphics.h>
#include <math.h>

CGFloat CAKeyFrameAnLinearInterpolation(CGFloat t) {
	return t;
}

CGFloat CAKeyFrameAnQuadraticEaseIn(CGFloat t) {
	return t * t;
}

CGFloat CAKeyFrameAnQuadraticEaseOut(CGFloat t) {
	return -(t * (t - 2));
}

CGFloat CAKeyFrameAnQuadraticEaseInOut(CGFloat t) {
	return (t < 0.5f ? (2 * t * t) : ((-2 * t * t) + (4 * t) - 1));
}

CGFloat CAKeyFrameAnCubicEaseIn(CGFloat t) {
	return (t * t * t);
}

CGFloat CAKeyFrameAnCubicEaseOut(CGFloat t) {
	CGFloat tPrev = (t - 1);
	return (tPrev * tPrev * tPrev) + 1;
}

CGFloat CAKeyFrameAnCubicEaseInOut(CGFloat t) {
	if (t < 0.5) {
		return 4 * t * t * t;
	} else {
		CGFloat f = ((2 * t) - 2);
		return 0.5 * f * f * f + 1;
	}
}

CGFloat CAKeyFrameAnQuarticEaseIn(CGFloat t) {
	return t * t * t * t;
}

CGFloat CAKeyFrameAnQuarticEaseOut(CGFloat t) {
	CGFloat f = (t - 1);
	return f * f * f * (1 - t) + 1;
}

CGFloat CAKeyFrameAnQuarticEaseInOut(CGFloat t) {
	if (t < 0.5) {
		return 8 * t * t * t * t;
	} else {
		CGFloat f = (t - 1);
		return -8 * f * f * f * f + 1;
	}
}

CGFloat CAKeyFrameAnQuinticEaseIn(CGFloat t) {
	return t * t * t * t * t;
}

CGFloat CAKeyFrameAnQuinticEaseOut(CGFloat t) {
	CGFloat f = (t - 1);
	return f * f * f * f * f + 1;
}

CGFloat CAKeyFrameAnQuinticEaseInOut(CGFloat t) {
	if(t < 0.5) {
		return 16 * t * t * t * t * t;
	} else {
		CGFloat f = ((2 * t) - 2);
		return  0.5 * f * f * f * f * f + 1;
	}
}

CGFloat CAKeyFrameAnSineEaseIn(CGFloat t) {
	return sin((t - 1) * M_PI_2) + 1;
}

CGFloat CAKeyFrameAnSineEaseOut(CGFloat t) {
	return sin(t * M_PI_2);
}

CGFloat CAKeyFrameAnSineEaseInOut(CGFloat t) {
	return 0.5 * (1 - cos(t * M_PI));
}

CGFloat CAKeyFrameAnCircularEaseIn(CGFloat t) {
	return 1 - sqrt(1 - (t * t));
}

CGFloat CAKeyFrameAnCircularEaseOut(CGFloat t) {
	return sqrt((2 - t) * t);
}

CGFloat CAKeyFrameAnCircularEaseInOut(CGFloat t) {
	if (t < 0.5)
		return 0.5 * (1 - sqrt(1 - 4 * (t * t)));
	else
		return 0.5 * (sqrt(-((2 * t) - 3) * ((2 * t) - 1)) + 1);
}

CGFloat CAKeyFrameAnExponentialEaseIn(CGFloat t) {
	return (t == 0.0 ? t : pow(2, 10 * (t - 1)));
}

CGFloat CAKeyFrameAnExponentialEaseOut(CGFloat t) {
	return (t == 1.0 ? t : 1 - pow(2, -10 * t));
}

CGFloat CAKeyFrameAnExponentialEaseInOut(CGFloat t) {
	if(t == 0.0 || t == 1.0) return t;
	
	if (t < 0.5)
		return 0.5 * pow(2, (20 * t) - 10);
	else
		return -0.5 * pow(2, (-20 * t) + 10) + 1;
}

CGFloat CAKeyFrameAnElasticEaseIn(CGFloat t) {
	return sin(13 * M_PI_2 * t) * pow(2, 10 * (t - 1));
}

CGFloat CAKeyFrameAnElasticEaseOut(CGFloat t) {
	return sin(-13 * M_PI_2 * (t + 1)) * pow(2, -10 * t) + 1;
}

CGFloat CAKeyFrameAnElasticEaseInOut(CGFloat t) {
	if(t < 0.5)
		return 0.5 * sin(13 * M_PI_2 * (2 * t)) * pow(2, 10 * ((2 * t) - 1));
	else
		return 0.5 * (sin(-13 * M_PI_2 * ((2 * t - 1) + 1)) * pow(2, -10 * (2 * t - 1)) + 2);
}

CGFloat CAKeyFrameAnBackEaseIn(CGFloat t) {
	return t * t * t - t * sin(t * M_PI);
}

CGFloat CAKeyFrameAnBackEaseOut(CGFloat t) {
	CGFloat f = (1 - t);
	return 1 - (f * f * f - f * sin(f * M_PI));
}

CGFloat CAKeyFrameAnBackEaseInOut(CGFloat t) {
	if (t < 0.5) {
		CGFloat f = 2 * t;
		return 0.5 * (f * f * f - f * sin(f * M_PI));
	} else {
		CGFloat f = (1 - (2*t - 1));
		return 0.5 * (1 - (f * f * f - f * sin(f * M_PI))) + 0.5;
	}
}

CGFloat CAKeyFrameAnBounceEaseOut(CGFloat t) {
	if (t < 4/11.0)
		return (121 * t * t)/16.0;
	else if (t < 8/11.0)
		return (363/40.0 * t * t) - (99/10.0 * t) + 17/5.0;
	else if (t < 9/10.0)
		return (4356/361.0 * t * t) - (35442/1805.0 * t) + 16061/1805.0;
	else
		return (54/5.0 * t * t) - (513/25.0 * t) + 268/25.0;
}

CGFloat CAKeyFrameAnBounceEaseIn(CGFloat t){
	return 1 - CAKeyFrameAnBounceEaseOut(1 - t);
}

CGFloat CAKeyFrameAnBounceEaseInOut(CGFloat t) {
	if (t < 0.5)
		return 0.5 * CAKeyFrameAnBounceEaseIn(t*2);
	else
		return 0.5 * CAKeyFrameAnBounceEaseOut(t * 2 - 1) + 0.5;
}
