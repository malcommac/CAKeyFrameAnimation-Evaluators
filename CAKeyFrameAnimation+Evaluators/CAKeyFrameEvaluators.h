//
//  CAKeyFrameEvaluators.h
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


#import <Foundation/Foundation.h>

#pragma mark CAKeyFrameFunctionEvaluator Protocol

@protocol CAKeyFrameFunctionEvaluator <NSObject>
- (CGFloat) evaluateAtPosition:(CGFloat) t;
@end

#pragma mark - Sample Evaluators

@interface CAExponentialDecayEvaluator : NSObject <CAKeyFrameFunctionEvaluator>
- (id)initWithCoefficient:(double)newCoeff;
@end


@interface CASecondOrderResponseEvaluator : NSObject <CAKeyFrameFunctionEvaluator>
- (id)initWithOmega:(double)newOmega zeta:(double)newZeta;
@end

@interface CABezierEvaluator : NSObject <CAKeyFrameFunctionEvaluator>
- (id)initWithFirst:(double)newFirst second:(double)newSecond;
@end