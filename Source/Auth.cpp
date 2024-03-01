#include "stdafx.h"
struct IUnknown;
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_ERRORS
#pragma warning(disable: 4996)
#include <iostream>
#include <string>
#include <Windows.h>
#include <atlutil.h>
#include <sstream>
#include <iomanip>
#include <locale>
#include <codecvt>
#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include "Auth/Networking/sha512.hh"
#include "Auth/Networking/WinHttpClient.h"
#include "Auth/Networking/Web2.0.h"
using std::string;
#define URL L"https://apollomenu.xyz/server/htua/htua.php"
int menu_version = 0;

int Auth::is_authed(const std::string& username, const std::string& password)
{
	char hwid[4096];
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	sprintf_s(hwid, "%I64i", statex.ullTotalPhys / 1024);

	TCHAR volumename[MAX_PATH + 1] = { 0 };
	TCHAR filesystemname[MAX_PATH + 1] = { 0 };
	DWORD serialnumber = 0, maxcomponentlen = 0, filesystemflags = 0;
	sprintf_s(hwid, "%s%li%ws%li", hwid, serialnumber, filesystemname, maxcomponentlen);

	TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD size = sizeof(computerName) / sizeof(computerName[0]);
	GetComputerName(computerName, &size);
	sprintf_s(hwid, "%s%ws", hwid, computerName);

	net::requests m_request(L"Mozilla/5.0 (Win64; x64) Destiny Menu (Menu; like Gecko)", false);
	auto answer = m_request.Post(
		false,
		URL,
		"username=%s&password=%s&hwid=%s",
		username.c_str(),
		password.c_str(),
		(sw::sha512::calculate(hwid)).c_str());

	if (answer == L"SAPPGNORW")
	{
		Log::Msg("Wrong password");
		exit(0);
	}
	if (answer == L"RESUGNORW")
	{
		Log::Msg("Username");
		exit(0);
	}
	if (answer == L"RORREDIWH") {
		Log::Msg("Wrong HWID");
		exit(0);
	}
	if (answer == L"UNEMON") {
		Log::Msg("No Menu Access");
		exit(0);
	}
	if (answer == L"6")
	{
		menu_version = 6;
		return 6;
	}
	return 0;
}