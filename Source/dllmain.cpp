// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

DWORD WINAPI ControlThread(LPVOID lpParam) {

	Log::Msg("Initializing Apollo");
	Hooking::Start((HMODULE)lpParam);
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved ) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {		
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ControlThread, hModule, NULL, NULL);
	}
	return TRUE;
}