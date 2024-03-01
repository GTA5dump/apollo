#pragma once
#ifndef __ASI_LOADER_H__
#define __ASI_LOADER_H__

#include "asiloader.h"
#include "PEImage.h"
#include "General.h"
#include "stdafx.h"

namespace ASILoader
{
	void Initialize();
};

#endif // __ASI_LOADER_H__

void LoadPlugins(const std::string& asiSearchFolder);