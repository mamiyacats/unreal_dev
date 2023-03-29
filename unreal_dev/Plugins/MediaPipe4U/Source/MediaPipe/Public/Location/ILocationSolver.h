// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include "ISolverProvider.h"
#include "LocationSolverLockSettings.h"

class ILocationSolver : public ISolverProvider
{
public:
	virtual FLocationSolverLockSettings GetLockSettings() const =0;
	virtual void SetLockSettings(const FLocationSolverLockSettings& Settings) = 0;
	virtual void SetCalibrateCountdownSeconds(int Seconds) = 0;
	virtual int GetCalibrateRemainingSeconds() = 0;
	virtual void SetMovementScale(const FVector& Scale) = 0;
	virtual void SetSpeed(float SpeedValue) = 0;
	virtual void SetAspectRatio(float Ratio) = 0;
	virtual void  InitFootInfo(const FFootInfo& Left, const FFootInfo& Right) = 0;
};
