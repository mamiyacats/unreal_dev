// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include "PluginEdition.generated.h"

UENUM()
enum class EPluginEdition : uint8
{
	Trial,
	Community,
	Professional,
	Enterprise,
	Unlimited
};
