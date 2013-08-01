//
//  CAKeyFrameEvaluators.m
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

#import "CAKeyFrameEvaluators.h"

#pragma mark - CAExponentialDecayEvaluator

@interface CAExponentialDecayEvaluator() {
	double coeff,offset,scale;
}
@end

@implementation CAExponentialDecayEvaluator

- (id)initWithCoefficient:(double)newCoeff {
	self = [super init];
	if (self != nil) {
		coeff = newCoeff;
		offset = exp(-coeff);
		scale = 1.0 / (1.0 - offset);
	}
	return self;
}

- (CGFloat) evaluateAtPosition:(CGFloat) t {
	return 1.0 - scale * (exp(t * -coeff) - offset);
}

@end

#pragma mark - CASecondOrderResponseEvaluator

@interface CASecondOrderResponseEvaluator() {
	double omega, zeta;
}
@end

@implementation CASecondOrderResponseEvaluator

- (id)initWithOmega:(double)newOmega zeta:(double)newZeta {
	self = [super init];
	if (self != nil)
	{
		omega = newOmega;
		zeta = newZeta;
	}
	return self;
}

- (CGFloat) evaluateAtPosition:(CGFloat) t {
	double beta = sqrt(1 - zeta * zeta);
	double phi = atan(beta / zeta);
	double result = 1.0 + -1.0 / beta * exp(-zeta * omega * t) * sin(beta * omega * t + phi);
	return result;
}

@end

#pragma mark - CABezierEvaluator

@interface CABezierEvaluator() {
	double firstControlPoint,secondControlPoint;
}
@end

@implementation CABezierEvaluator

- (id)initWithFirst:(double)newFirst second:(double)newSecond {
	self = [super init];
	if (self != nil) {
		firstControlPoint = newFirst;
		secondControlPoint = newSecond;
	}
	return self;
}

- (CGFloat) evaluateAtPosition:(CGFloat) t {
		// (1 - position) * (1 - position) * (1 - position) * 0.0 +
	return
	3 * t * (1 - t) * (1 - t) * firstControlPoint +
	3 * t * t * (1 - t) * secondControlPoint +
	t * t * t * 1.0;
}

@end