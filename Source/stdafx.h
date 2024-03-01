// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#define DLL_EXPORT __declspec( dllexport )
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define PI 3.14159265
#define DEGTORAD(D)((D * PI) / 180.0) // Converts Degrees to radians
#define RADTODEG(R)((180.0 * R) / PI)//Converts Radians to Degrees 
//#define FMT(fmt, ...) (false ? std::to_string(printf(fmt, ##__VA_ARGS__)) : string_format(fmt, ##__VA_ARGS__ ))
// Windows Library Files:
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "sinister.lib")
//using json = nlohmann::json;

// Windows Header Files:
#include <cstdint> //CMDS
#include <windows.h>
#include <Mmsystem.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <Psapi.h>
#include <MinHook.h>
#include <timeapi.h>
#include <time.h>
//#include <memory>

// Additional Header Files:
#include "Log.h"
#include "Memory.h"
#include "types.h"
#include "enums.h"
#include "InputHook.h"
#include "keyboard.h"
#include "CrossMapping.h"
#include "NativeInvoker.h"
#include "nativeCaller.h"
#include "natives.h"
#include "Hooking.h"




// Menu Files:
#include "GUI.h"
#include "subs.h"
#include "Features.h"
#include "menu.h"
#include "ingamekeyboard.h"
#include "types.h"
#include "Functions.h"
#include "Structs.h"
#include "Scanner.h"
#include "return_spoof.hpp"
#include <locale>
#include <codecvt>
#include <stdio.h>
#include "Auth/Networking/sha512.hh"
#include "Auth/Networking/Web2.0.h"
#include "pugixml.hpp"
#include "XMLWrapper.h"
#include "XMLWriter.h"
#include <atomic>
#include <chrono>
#include <deque>
#include <filesystem>
#include <iomanip>
#include <limits>
#include <mutex>
#include <stack>
#include <thread>
#include <type_traits>
#include "Spawner.h"
#include "Unload.h"
#include "Ini.h"
#include "Weissernigger.h"
#include "WinHeaders.h"
#include "Sigscan.h"
#include "raycast.h"
#include "reclass.h"
#include "JSON/json.hpp"
#include "Auth.h"
#include "Scriptthread.h"
#include "asiloader.h"
#include "PEImage.h"
#include "General.h"
#include "StackWalker.h"
#include <winternl.h>
#include <ntstatus.h>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

class globalHandle
{
private:
	void* _handle;

public:
	globalHandle(int index)
		: _handle(&Hooking::getGlobalPtr()[index >> 18 & 0x3F][index & 0x3FFFF])
	{ }

	globalHandle(void* p)
		: _handle(p)
	{ }

	globalHandle(const globalHandle& copy)
		: _handle(copy._handle)
	{ }

	globalHandle At(int index)
	{
		return globalHandle(reinterpret_cast<void**>(this->_handle) + (index));
	}

	globalHandle At(int index, int size)
	{
		// Position 0 = Array Size
		return this->At(1 + (index * size));
	}

	template <typename T>
	T* Get()
	{
		return reinterpret_cast<T*>(this->_handle);
	}

	template <typename T>
	T& As()
	{
		return *this->Get<T>();
	}
};