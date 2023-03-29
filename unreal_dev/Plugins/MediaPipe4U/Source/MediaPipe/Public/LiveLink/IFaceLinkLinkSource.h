// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "ILiveLinkSource.h"
#include "ARTrackable.h"

class MEDIAPIPE_API IFaceLinkLinkSource: public ILiveLinkSource
{
public:
	static TSharedPtr<IFaceLinkLinkSource> CreateSource();
	
	virtual void SetSubjectName(const FName& SubjectName) = 0;
	virtual FName GetSubjectName() const = 0;
	virtual void Active() = 0;
	virtual void Deactivate() = 0;
	virtual void WriteFaceExpression(const FARBlendShapeMap& ExpressionWeights) = 0;
};
