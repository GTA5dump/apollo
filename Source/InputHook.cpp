//InputHook.cpp
#include "stdafx.h"

#define GXLPARAM(lp) ((short)LOWORD(lp))
#define GYLPARAM(lp) ((short)HIWORD(lp))

InputHook iHook;
WNDPROC	oWndProc;

//using namespace Utility;

static std::set<InputHook::TKeyboardFn> g_keyboardFunctions;

void InputHook::keyboardHandlerRegister(TKeyboardFn function) {

	g_keyboardFunctions.insert(function);
}

void InputHook::keyboardHandlerUnregister(TKeyboardFn function) {

	g_keyboardFunctions.erase(function);
}

bool InputHook::Initialize() {

	hWindow = NULL;
	while (hWindow == NULL) {
		Sleep(100);
	}
	oWndProc = (WNDPROC)SetWindowLongPtr(hWindow, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
	if (oWndProc == NULL) {

		Log::Error("Failed to attach input hook");
		return false;
	}
	else {

		keyboardHandlerRegister(OnKeyboardMessage);
		DEBUGMSG("Input hook attached:  WndProc 0x%p", (DWORD_PTR)oWndProc);
		return true;
	}
}

void InputHook::Remove() {

	SetWindowLongPtr(hWindow, GWLP_WNDPROC, (LONG_PTR)oWndProc);
	DEBUGMSG("Removed input hook");
}

LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);
}
