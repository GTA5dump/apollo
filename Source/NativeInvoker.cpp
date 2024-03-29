//NativeInvoker.cpp
#include "stdafx.h"
#include "Hooking.h"
#include "return_spoof.hpp"
static NativeManagerContext g_context;

static UINT64 g_hash;

void(*scrNativeCallContext::SetVectorResults)(scrNativeCallContext*) = nullptr;

DLL_EXPORT void nativeInit(UINT64 hash) {

	g_context.Reset();
	g_hash = hash;
}

DLL_EXPORT void nativePush64(UINT64 value) {

	g_context.Push(value);
}

DLL_EXPORT uint64_t* nativeCall()
{
	auto fn = Hooking::GetNativeHandler(g_hash);

	if (fn != nullptr)
	{
		static void* exceptionAddress;

		__try
		{
			//fuck you
			scrNativeCallContext::SetVectorResults(&g_context);
		}
		__except (exceptionAddress = (GetExceptionInformation())->ExceptionRecord->ExceptionAddress, EXCEPTION_EXECUTE_HANDLER)
		{
			Log::Error("executing native 0x%016llx at address %p.", g_hash, exceptionAddress);
		}
	}

	return reinterpret_cast<uint64_t*>(g_context.GetResultPointer());
}