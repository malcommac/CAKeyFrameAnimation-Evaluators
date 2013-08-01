//
//  CAKeyFrameAnimation+Evaluators.m
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

#import "CAKeyFrameAnimation+Evaluators.h"

enum {
	NSValueTypeUnsupported = 0,
	NSValueTypeCGFloat,
	NSValueTypeCGPoint,
	NSValueTypeCGSize
}; typedef NSUInteger NSValueType;

@implementation CAKeyframeAnimation (Evaluators)

#pragma mark - Animation From Evaluator Object

+ (id) animationWithKeyPath:(NSString *) path
				  evaluator:(id<CAKeyFrameFunctionEvaluator>) evaluatorObj
					   from:(id) initialValue
						 to:(id) finalValue
					   rate:(size_t) keyFrameCount {
	
	NSValueType initalValueType = [CAKeyframeAnimation determinateTypeOfNSValue:initialValue];
	NSValueType finalValueType = [CAKeyframeAnimation determinateTypeOfNSValue:finalValue];
	if (initalValueType == NSValueTypeUnsupported || finalValueType == NSValueTypeUnsupported || initalValueType != finalValueType) {
		[NSException raise:NSInvalidArgumentException format:@"Unsupported type or initial/final values type mismatch"];
		return nil;
	}
	
		// We want to modelate a single second (1s) of our animation
		// Each second of the animation will contains keyframeCount frames (generally 1/60 is enough for a smooth animation)
	CGFloat t = 0.0f;
	CGFloat dt = 1.0f / (keyFrameCount-1); // this is our interval between each frame of the animation
	NSMutableArray *valueAtKeyframePoint = [[NSMutableArray alloc] initWithCapacity:keyFrameCount];
	
		// for each frame we want to evaluate the value of our animated property (opacity,x,y etc.) using
		// a specified function.
	for (size_t frameIdx = 0; frameIdx < keyFrameCount; ++frameIdx, t+=dt) {
		switch (initalValueType) {
			case NSValueTypeCGFloat: { // FLOAT
				CGFloat iValue = ((NSNumber*)initialValue).floatValue;
				CGFloat fValue = ((NSNumber*)finalValue).floatValue;
				CGFloat valueAtIdx = (iValue+[evaluatorObj evaluateAtPosition:t] * (fValue-iValue));
				[valueAtKeyframePoint addObject:@(valueAtIdx)];
				break;}
			case NSValueTypeCGPoint: { // CGPoint
				CGPoint iValue = ((NSValue*)initialValue).CGPointValue;
				CGPoint fValue = ((NSValue*)finalValue).CGPointValue;
				CGFloat x = iValue.x + [evaluatorObj evaluateAtPosition:t] * (fValue.x - iValue.x);
				CGFloat y = iValue.y + [evaluatorObj evaluateAtPosition:t] * (fValue.y - iValue.y);
				[valueAtKeyframePoint addObject:[NSValue valueWithCGPoint:CGPointMake(x, y)]];
				break;}
			case NSValueTypeCGSize: { // CGSize
				CGSize iValue = ((NSValue*)initialValue).CGSizeValue;
				CGSize fValue = ((NSValue*)finalValue).CGSizeValue;
				CGFloat w = iValue.width + [evaluatorObj evaluateAtPosition:t] * (fValue.width - iValue.width);
				CGFloat h = iValue.height + [evaluatorObj evaluateAtPosition:t] * (fValue.height - iValue.height);
				[valueAtKeyframePoint addObject:[NSValue valueWithCGSize:CGSizeMake(w, h)]];
				break;}
			default:
				break;
		}
	}
		// create our animation with frames values
	CAKeyframeAnimation *animation = [CAKeyframeAnimation animationWithKeyPath:path];
	[animation setValues:valueAtKeyframePoint];
	return animation;
}


+ (id) animationWithKeyPath:(NSString *) path
				   function:(CAKeyFrameCustomFunction) evaluationFunction
					   from:(id) initialValue
						 to:(id) finalValue
					   rate:(size_t) keyFrameCount {
	
	NSValueType initalValueType = [CAKeyframeAnimation determinateTypeOfNSValue:initialValue];
	NSValueType finalValueType = [CAKeyframeAnimation determinateTypeOfNSValue:finalValue];
	if (initalValueType == NSValueTypeUnsupported || finalValueType == NSValueTypeUnsupported || initalValueType != finalValueType) {
		[NSException raise:NSInvalidArgumentException format:@"Unsupported type or initial/final values type mismatch"];
		return nil;
	}
	
		// We want to modelate a single second (1s) of our animation
		// Each second of the animation will contains keyframeCount frames (generally 1/60 is enough for a smooth animation)
	CGFloat t = 0.0f;
	CGFloat dt = 1.0f / (keyFrameCount-1); // this is our interval between each frame of the animation
	NSMutableArray *valueAtKeyframePoint = [[NSMutableArray alloc] initWithCapacity:keyFrameCount];
	
		// for each frame we want to evaluate the value of our animated property (opacity,x,y etc.) using
		// a specified function.
	for (size_t frameIdx = 0; frameIdx < keyFrameCount; ++frameIdx, t+=dt) {
		switch (initalValueType) {
			case NSValueTypeCGFloat: { // FLOAT
				CGFloat iValue = ((NSNumber*)initialValue).floatValue;
				CGFloat fValue = ((NSNumber*)finalValue).floatValue;
				CGFloat valueAtIdx = (iValue+evaluationFunction(t) * (fValue-iValue));
				[valueAtKeyframePoint addObject:@(valueAtIdx)];
				break;}
			case NSValueTypeCGPoint: { // CGPoint
				CGPoint iValue = ((NSValue*)initialValue).CGPointValue;
				CGPoint fValue = ((NSValue*)finalValue).CGPointValue;
				CGFloat x = iValue.x + evaluationFunction(t) * (fValue.x - iValue.x);
				CGFloat y = iValue.y + evaluationFunction(t) * (fValue.y - iValue.y);
				[valueAtKeyframePoint addObject:[NSValue valueWithCGPoint:CGPointMake(x, y)]];
				break;}
			case NSValueTypeCGSize: { // CGSize
				CGSize iValue = ((NSValue*)initialValue).CGSizeValue;
				CGSize fValue = ((NSValue*)finalValue).CGSizeValue;
				CGFloat w = iValue.width + evaluationFunction(t) * (fValue.width - iValue.width);
				CGFloat h = iValue.height + evaluationFunction(t) * (fValue.height - iValue.height);
				[valueAtKeyframePoint addObject:[NSValue valueWithCGSize:CGSizeMake(w, h)]];
				break;}
			default:
				break;
		}
	}
		// create our animation with frames values
	CAKeyframeAnimation *animation = [CAKeyframeAnimation animationWithKeyPath:path];
	[animation setValues:valueAtKeyframePoint];
	return animation;
}

+ (NSValueType) determinateTypeOfNSValue:(id) targetValue {
	if ([targetValue isKindOfClass:[NSNumber class]]) {
		return NSValueTypeCGFloat;
	} else if ([targetValue isKindOfClass:[NSValue class]]) {
		if (strcmp((const char *)[((NSValue*)targetValue) objCType],(const char *)@encode(CGPoint))==0)
			return NSValueTypeCGPoint;
		else if (strcmp((const char *)[((NSValue*)targetValue) objCType],(const char *)@encode(CGSize))==0)
			return NSValueTypeCGSize;
		else
			return NSValueTypeUnsupported;
	}
	return NSValueTypeUnsupported;
}

#pragma mark - Functions

+ (CAKeyFrameCustomFunction) functionWithCurve:(CKCurveType) aCurve andEase:(CKCurveEaseType) aEase {
	switch (aCurve) {
		case CKCurveTypeLinear:				/** LINEAR */
			return CAKeyFrameAnLinearInterpolation;
		case CKCurveTypeQuadratic:			/** QUADRATIC */
			if (aEase == CKCurveEaseTypeIn)
				return CAKeyFrameAnQuadraticEaseIn;
			else if (aEase == CKCurveEaseTypeOut)
				return CAKeyFrameAnQuadraticEaseOut;
			else
				return CAKeyFrameAnQuadraticEaseOut;
			break;
		case CKCurveTypeCubic:				/** CUBIC */
			if (aEase == CKCurveEaseTypeIn)
				return CAKeyFrameAnCubicEaseIn;
			else if (aEase == CKCurveEaseTypeOut)
				return CAKeyFrameAnCubicEaseOut;
			else
				return CAKeyFrameAnCubicEaseInOut;
			break;
		case CKCurveTypeQuartic:			/** QUARTIC */
			if (aEase == CKCurveEaseTypeIn)
				return CAKeyFrameAnQuarticEaseIn;
			else if (aEase == CKCurveEaseTypeOut)
				return CAKeyFrameAnQuarticEaseOut;
			else
				return CAKeyFrameAnQuarticEaseInOut;
			break;
		case CKCurveTypeQuintic:			/** QUINTIC */
			if (aEase == CKCurveEaseTypeIn)
				return CAKeyFrameAnQuinticEaseIn;
			else if (aEase == CKCurveEaseTypeOut)
				return CAKeyFrameAnQuinticEaseOut;
			else
				return CAKeyFrameAnQuinticEaseInOut;
			break;
		case CKCurveTypeSineWave:			/** SINE */
			if (aEase == CKCurveEaseTypeIn)
				return CAKeyFrameAnSineEaseIn;
			else if (aEase == CKCurveEaseTypeOut)
				return CAKeyFrameAnSineEaseOut;
			else
				return CAKeyFrameAnSineEaseInOut;
			break;
		case CKCurveTypeCircular:			/** CIRCULAR */
			if (aEase == CKCurveEaseTypeIn)
				return CAKeyFrameAnCircularEaseIn;
			else if (aEase == CKCurveEaseTypeOut)
				return CAKeyFrameAnCircularEaseOut;
			else
				return CAKeyFrameAnCircularEaseInOut;
			break;
		case CKCurveTypeExponential:		/** EXPONENTIAL */
			if (aEase == CKCurveEaseTypeIn)
				return CAKeyFrameAnExponentialEaseIn;
			else if (aEase == CKCurveEaseTypeOut)
				return CAKeyFrameAnExponentialEaseOut;
			else
				return CAKeyFrameAnExponentialEaseInOut;
			break;
		case CKCurveTypeElastic:			/** ELASTIC */
			if (aEase == CKCurveEaseTypeIn)
				return CAKeyFrameAnElasticEaseIn;
			else if (aEase == CKCurveEaseTypeOut)
				return CAKeyFrameAnElasticEaseOut;
			else
				return CAKeyFrameAnElasticEaseInOut;
			break;
		case CKCurveTypeBack:				/** BACK */
			if (aEase == CKCurveEaseTypeIn)
				return CAKeyFrameAnBackEaseIn;
			else if (aEase == CKCurveEaseTypeOut)
				return CAKeyFrameAnBackEaseOut;
			else
				return CAKeyFrameAnBackEaseInOut;
			break;
		case CKCurveTypeBounce:				/** BOUNCE */
			if (aEase == CKCurveEaseTypeIn)
				return CAKeyFrameAnBounceEaseIn;
			else if (aEase == CKCurveEaseTypeOut)
				return CAKeyFrameAnBounceEaseOut;
			else
				return CAKeyFrameAnBounceEaseInOut;
			break;
	}
	return NULL;
}


@end
