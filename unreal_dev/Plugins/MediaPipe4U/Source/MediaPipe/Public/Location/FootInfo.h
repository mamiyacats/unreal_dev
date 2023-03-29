// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include "FootInfo.generated.h"

USTRUCT()
struct FFootInfo
{
	GENERATED_BODY()
	
	float FootHeight = -1.0f;
	float FootAngle = 0.0f;

	bool IsValid() const { return FootHeight >= 0; }
};
