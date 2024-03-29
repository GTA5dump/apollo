#pragma once
#ifndef __PE_IMAGE__
#define __PE_IMAGE__

#include "asiloader.h"
#include "PEImage.h"
#include "General.h"
#include "stdafx.h"

namespace Utilityyy
{
	typedef const IMAGE_NT_HEADERS64 NT64H;
	typedef std::vector<char> bufferVec;

	class PEImage {
	public:

		PEImage();
		~PEImage();

		bool			Load(const std::string& path);

		bool			IsOpenVHookCompatible();

		bool			PatchCompatibility();

	private:

		uint64_t		GetDirectoryAddress(int index);
		uint64_t		RVAToVA(uint32_t rva) const;

		bool			ParsePE();

	private:

		std::string		filePath;
		bufferVec		fileBuffer;
		NT64H* ntHeader = nullptr;
	};

}

#endif // __PE_IMAGE__