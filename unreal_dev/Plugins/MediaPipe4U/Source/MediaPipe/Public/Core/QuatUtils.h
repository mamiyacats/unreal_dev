// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"

class MEDIAPIPE_API QuatUtils
{
public:
	static float Dot(const FQuat& Q1, const FQuat& Q2);
	static FQuat GetAxis(const FQuat& Quat, const FVector& Axis);
	static FQuat RemoveAxis(const FQuat& TargetQuat, const FQuat& OriginQuat, const FVector& Axis);
	static FQuat LimitAxis(const FQuat& Quat, const FVector& Axis, float MinAngleDegrees, float MaxAngleDegrees);
	static double WrapAngleRad(double AngleRad);
	static double WrapAngleDegree(double AngleDegree);
};
