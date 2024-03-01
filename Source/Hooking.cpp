//Hooking.cpp
#pragma once
#include "stdafx.h"
#include "Hooking.h"
#include "Scriptthread.h"

using namespace Memory;

bool enable_coloading = true;
bool block_report_myself = true;

ScriptThread* (*GetActiveThread)() = nullptr;
HMODULE _hmoduleDLL;
HANDLE mainFiber;
DWORD wakeAt;
HMODULE Hooking::scriptDLL;
void* Hooking::invoker_return_address;
const char NOP = '\x90';
static char object_spawn[2];
static char model_bypass[24];
static void* m_model_bypass;
static void* m_object_spawn;

static uint8_t* m_int_checker;
static char int_check[7];
uint8_t og_int_checker;

void* Hooking::mon;
char* Hooking::loading_text = "Loading GTA Online With Wolfi & Hoboz";

bool Hooking::protect = false;
bool Hooking::dump = false;
bool Hooking::notify = false;
bool Hooking::redirect = false;
bool Hooking::blockall = false;
bool Hooking::smart_protex = false;
bool Hooking::smart_pro = false;
bool Hooking::logger = false;
bool Hooking::rdev = false;
bool Hooking::event_handler_on = false;
bool Hooking::e_weather_time = false;
bool Hooking::e_control = false;
bool Hooking::e_explosion = false;
bool Hooking::e_pickup = false;
bool Hooking::e_weapon = false;
bool Hooking::e_wanted = false;
bool Hooking::e_report = false;
bool Hooking::e_kick = false;
bool Hooking::e_freeze = false;
bool Hooking::e_stat = false;
bool Hooking::e_ptfx = false;
bool Hooking::e_redirect = false;
bool Hooking::e_notify = false;
bool Hooking::patch_checker = false;

bool Hooking::event_handler_notify = false;
bool Hooking::report_protex = false;
bool Hooking::kick_protex = false;
bool Hooking::explosion_protex = false;
bool Hooking::freeze_protex = false;
bool Hooking::weather_protex = false;
bool Hooking::time_protex = false;

threeBytes* Hooking::infinite_ammo;
threeBytes* Hooking::no_reload;
twoBytes* Hooking::m_ownedExplosionBypass;
BYTE* Hooking::m_ownedExplosionBypass2;
std::vector<LPVOID>                     Hooking::m_hooks;
uint64_t* Hooking::m_frameCount;
fpIsDLCPresent		                	Hooking::is_DLC_present;
TriggerScriptEvent	                	Hooking::trigger_script_event;
SetSessionWeather                       Hooking::set_session_weather;
fpStatSetInt		                	Hooking::stat_set_int;
fpStatSetBool                           Hooking::stat_set_bool;
fpStatSetFloat                          Hooking::stat_set_float;
GetEventData                            Hooking::get_script_event_data;
fpGetPlayerName                         Hooking::GPN;
addOwnedExplosion                       Hooking::add_owned_explosion;
fpGetEventData                          Hooking::get_event_data;
fpSetLobbyTime                          Hooking::set_lobby_time;
fpGetChatMessage                        Hooking::get_chat_message;
fpGetPlayerAddress                      Hooking::get_player_address;
fpAddressToEntity                       Hooking::address_to_entity;
fpEventHandler                          Hooking::event_handler;
fpSetName                               Hooking::set_name_kek;
fpSetSessionTime                        Hooking::set_session_time;
clockTime* Hooking::ClockTime;
fpSetEntityMaxHealth                    Hooking::set_entity_max_health;
fpCreateVehicle                         Hooking::create_vehicle;
fpSetVehicleMod                         Hooking::set_vehicle_mod;
fpClearPedTasksImmediately              Hooking::clear_ped_tasks_immediately;
fpGetNumberOfEvents                     Hooking::get_number_of_events;
fpNetworkIsSessionStarted               Hooking::is_session_started;
fpNetworkRequestControlOfNetworkId      Hooking::request_control_of_network_id;
fpNetworkRequestControlOfEntity         Hooking::request_control_of_entity;
fpNetworkHasControlOfEntity             Hooking::has_control_of_entity;
fpSetNetworkIdCanMigrate                Hooking::set_network_id_can_migrate;
fpGetNetworkTime                        Hooking::get_network_time;
fpDecorSetInt                           Hooking::decor_set_int;
fpDecorRegister                         Hooking::decor_register;
fpChatMessage                           Hooking::get_message;
fpGetSender                             Hooking::get_sender;
CReplayInterface* Hooking::m_replayIntf;
fpIncrementStatHook                     Hooking::increment_stat;
fpCreateAmbientPickup                   Hooking::create_ambient_pickup;
fpIntegrityCheck                        Hooking::integrity_check;
fpSetMobileRadioEnabledDuringGameplay   Hooking::set_mobile_radio_enabled_during_gameplay;
fpIsEntityUpsideDown                    Hooking::is_entity_upsidedown;
fpRequestIpl                            Hooking::request_ipl;
fpIsIplActive                           Hooking::is_ipl_active;
fpNetworkSessionKickPlayer              Hooking::network_session_kick_player;
fpNetworkShopCheckoutStart              Hooking::network_shop_checkout_start;
fpGetPlayerMaxArmour                    Hooking::get_player_max_armour;
fpGetEntityAttachedTo                   Hooking::get_entity_attached_to;
fpSetEntityCollision                    Hooking::set_entity_collision;
fpStatSetDate                           Hooking::stat_set_date;
fpStatGetInt                            Hooking::stat_get_int;
fpAddTextCompSubstrPlayerName	        Hooking::add_text_comp_substr_playername;
fpEndTextCmdDisplayText	                Hooking::end_text_command_display_text;
fpBeginTextCmdDisplayText	            Hooking::begin_text_command_display_text;
fpSendMessage                           Hooking::send_message;
fpClearPedBloodDamage                   Hooking::clear_ped_blood_damage;
fpSetVehicleOnGroundProperly            Hooking::set_vehicle_on_ground_properly;
fpSetVehicleNumberplateText             Hooking::set_vehicle_numberplate_text;
fpIsThisModelAPlane                     Hooking::is_this_model_a_plane;
fpIsThisModelAHeli                      Hooking::is_this_model_a_heli;
fpSetHeliBladesFullSpeed                Hooking::set_heli_blades_full_speed;
fpEndTextCommandGetWidth                Hooking::end_text_command_get_width;
fpRequestAnimDict                       Hooking::request_anim_dict;
fpHasAnimDictLoaded                     Hooking::has_anim_dict_loaded;
fpDrawNotification                      Hooking::draw_notification;
fpDrawNotification2                     Hooking::draw_notification_2;
fpPickupRewardMoneyIsApplicableToPlayer Hooking::pickup_is_applicable_to_player;
fpSetVehicleEngineOn                    Hooking::set_vehicle_engine_on;
fpSetVehicleUndriveable                 Hooking::set_vehicle_undriveable;
fpSetVehicleDriveable                   Hooking::set_vehicle_driveable;
fpGetDisplayNameFromVehicle             Hooking::get_display_name_from_vehicle;
fpToggleVehicleMod                      Hooking::toggle_vehicle_mod;
fpNetworkShopBeginService               Hooking::network_shop_begin_service;
fpGiveDelayedWeaponToPed                Hooking::give_delayed_weapon_to_ped;
fpRemoveAllPedWeapons                   Hooking::remove_all_ped_weapons;
fpRemoveWeaponFromPed                   Hooking::remove_weapon_from_ped;
fpGetPedInVehicleSeat                   Hooking::get_ped_in_vehicle_seat;
fpIsAimCamActive                        Hooking::is_aim_cam_active;
fpDrawRect                              Hooking::draw_rect;
fpDrawLine                              Hooking::draw_line;
fpGetGameplayCamRot                     Hooking::get_gameplay_cam_rot;
fpGetGameplayCamCoord                   Hooking::get_gameplay_cam_coord;
fpNetworkGetNetworkIdFromEntity         Hooking::get_network_id_from_entity;
fpNetworkCreateSynchronisedScene        Hooking::create_synchronised_scene;
fpNetworkAddPedToSynchronisedScene      Hooking::add_ped_to_synchronised_scene;
fpNetworkStartSynchronisedScene         Hooking::start_synchronised_scene;
fpIsVehicleDrivable                     Hooking::is_vehicle_driveable;
fpGetPlayerRadioStationIndex            Hooking::get_player_radio_station_index;
fpGetRadioStationName                   Hooking::get_radio_station_name;
fpSetVehicleForwardSpeed                Hooking::set_vehicle_forward_speed;
fpSetVehicleFixed                       Hooking::set_vehicle_fixed;
fpSetVehicleDeformationFixed            Hooking::set_vehicle_deformation_fixed;
fpIsVehicleSeatFree                     Hooking::is_vehicle_seat_free;
fpSetVehicleNumberPlateIndex            Hooking::set_vehicle_number_plate_index;
fpSetVehicleWheelType                   Hooking::set_vehicle_wheel_type;
fpGetNumVehicleMod                      Hooking::get_num_vehicle_mod;
fpSetNotificationTextEntry              Hooking::set_notification_text_entry;
fpUpdateOnscreenKeyboard                Hooking::update_onscreen_keyboard;
fpSetLocalPlayerVisibleLocally          Hooking::set_local_player_visible_locally;
fpAiTaskWanderStandard                  Hooking::ai_task_wander_standart;
fpAiTaskPlayAnim                        Hooking::ai_task_play_anim;
fpIsModelInCdimage                      Hooking::is_model_in_cdimage;
fpIsModelValid                          Hooking::is_model_valid;
fpIsModelAVehicle                       Hooking::is_model_a_vehicle;
fpRequestModel                          Hooking::request_model;
fpHasModelLoaded                        Hooking::has_model_loaded;
fpGetPedLastWeaponImpactCoord           Hooking::get_ped_last_weapon_impact_coord;
fpStartRayCast                          Hooking::start_ray_cast;
fpGetRayCast                            Hooking::get_ray_cast;
fpNetworkSetInSpectatorMode             Hooking::set_in_spectator_mode;
fpSetPedCombatAbility                   Hooking::set_ped_combat_ability;
fpAiTaskCombatPed                       Hooking::ai_task_combat_ped;
fpApplyVehicleColors                    Hooking::apply_vehicle_colors;
fpSetPlayerVisibleLocally               Hooking::set_player_visible_locally;
fpSetModelAsNoLongerNeeded              Hooking::set_model_as_no_longer_needed;
fpCreateObject                          Hooking::create_object;
fpSetOverrideWeather                    Hooking::set_override_weather;
fpGetCurrentPedWeapon                   Hooking::get_current_ped_weapon;
fpGetTextScreenLineCount                Hooking::get_text_screen_line_count;
fpRequestScaleformMovie                 Hooking::request_scaleform_movie;
fpDrawScaleformMovie                    Hooking::draw_scaleform_movie;
fpEndScaleformMovieMethod               Hooking::end_scaleform_movie_method;
fpIsDisabledControlPressed              Hooking::is_disabled_control_pressed;
fpIsPlayerFriend                        Hooking::is_player_friend;
fpGetLabelText                          Hooking::GetLabelText = nullptr;
fpGetScriptHandlerIfNetworked           Hooking::GetScriptHandlerIfNetworked = nullptr;
fpGetScriptHandler                      Hooking::GetScriptHandler = nullptr;
CViewPort* Hooking::m_viewPort;
screenReso* Hooking::m_resolution;
void* Hooking::m_objectHashTable;
void* Hooking::m_objectHashTableSectionEnd;
void* Hooking::m_onlineName;
CTextInfo* Hooking::m_textInfo;
char* Hooking::m_onscreenKeyboardResult;
clockTime* Hooking::m_clockTime;
uint64_t* Hooking::m_networkTime;
MemoryPool** Hooking::m_pedPool;
void* Hooking::m_gameInfo;
CPlayers* Hooking::m_players;
MemoryPool** Hooking::m_entityPool;

static eGameState* m_gameState;
static uint64_t												m_worldPtr;
static BlipList* m_blipList;
static Hooking::NativeRegistrationNew** m_registrationTable;
static std::unordered_map<uint64_t, Hooking::NativeHandler>	m_handlerCache;
static std::vector<LPVOID>									m_hookedNative;
static __int64** m_globalPtr;

const int EVENT_COUNT = 78;
static std::vector<void*> EventPtr;
static char EventRestore[EVENT_COUNT] = {};

bool twoBytes::empty()
{
	bool	r = true;
	for (int i = 0; i < 2; ++i)
		if (this->byte[i] != 0)
		{
			r = false;
			break;
		}
	return r;
}

bool threeBytes::empty()
{
	bool	r = true;
	for (int i = 0; i < 3; ++i)
		if (this->byte[i] != 0)
		{
			r = false;
			break;
		}
	return r;
}

/* Start Hooking */

void Hooking::Start(HMODULE hmoduleDLL)
{
	std::shared_ptr<UpdateScript> ptr_update = std::make_shared<UpdateScript>();
	std::shared_ptr<ControlScript> ptr_control = std::make_shared<ControlScript>();

	Thread::AddScript(ptr_control);
	Thread::AddScript(ptr_update);

	Log::Msg("Started Hooking");
	if ((int)hmoduleDLL < 0) {
		Log::Msg("Module Address: 0x%i", (int)hmoduleDLL * -1);
	}
	else {
		Log::Msg("Module Address: 0x%i", (int)hmoduleDLL);
	}
	//nt_query_mem = GetProcAddress(LoadLibrary((LPCWSTR)"ntdll.dll"), "NtQueryVirtualMemory");
	_hmoduleDLL = hmoduleDLL;
	scriptDLL = hmoduleDLL;
	Log::Init(hmoduleDLL);
	FindPatterns();
	if (!InitializeHooks()) Cleanup();
}
BOOL Hooking::InitializeHooks()
{
	BOOL returnVal = TRUE;

	if (!iHook.Initialize()) {

		Log::Error("Failed to initialize InputHook");
		returnVal = FALSE;
	}

	if (MH_Initialize() != MH_OK) {
		Log::Error("MinHook failed to initialize");
		returnVal = FALSE;
	}

	if (!HookNatives()) { //if (!MAIN_HOOK_CONTROLLER())

		Log::Error("Failed to initialize NativeHooks");
		returnVal = FALSE;
	}

	return returnVal;
}

template <typename T>
bool Native(DWORD64 hash, LPVOID hookFunction, T** trampoline)
{
	if (*reinterpret_cast<LPVOID*>(trampoline) != NULL)
		return true;
	auto originalFunction = Hooking::GetNativeHandler(hash);
	if (originalFunction != 0) {
		MH_STATUS createHookStatus = MH_CreateHook(originalFunction, hookFunction, reinterpret_cast<LPVOID*>(trampoline));
		if (((createHookStatus == MH_OK) || (createHookStatus == MH_ERROR_ALREADY_CREATED)) && (MH_EnableHook(originalFunction) == MH_OK))
		{
			m_hookedNative.push_back((LPVOID)originalFunction);
			DEBUGMSG("Hooked Native 0x%#p", hash);
			return true;
		}
	}

	return false;
}

uint64_t CMetaData::m_begin = 0;
uint64_t CMetaData::m_end = 0;
DWORD CMetaData::m_size = 0;

uint64_t CMetaData::begin()
{
	return m_begin;
}
uint64_t CMetaData::end()
{
	return m_end;
}
DWORD CMetaData::size()
{
	return m_size;
}

void CMetaData::init()
{
	if (m_begin && m_size)
		return;

	m_begin = (uint64_t)GetModuleHandleA(nullptr);
	const IMAGE_DOS_HEADER* headerDos = (const IMAGE_DOS_HEADER*)m_begin;
	const IMAGE_NT_HEADERS* headerNt = (const IMAGE_NT_HEADERS64*)((const BYTE*)headerDos + headerDos->e_lfanew);
	m_size = headerNt->OptionalHeader.SizeOfCode;
	m_end = m_begin + m_size;
	return;
}
fpIsDLCPresent	OG_IS_DLC_PRESENT = nullptr;
BOOL __cdecl HK_IS_DLC_PRESENT(uint32_t dlchash)
{
	static uint64_t	last = 0;
	uint64_t		cur = *Hooking::m_frameCount;
	if (last != cur)
	{
		last = cur;
		Hooking::onTickInit();
	}
	return OG_IS_DLC_PRESENT(dlchash);
}

fpGetLabelText ogGetLabelText = nullptr;
const char* __cdecl hkGetLabelText(void* this_, const char* label)
{
	if (std::strcmp(label, "HUD_JOINING") == 0)
	{
		return Hooking::loading_text;
	}

	/*if (std::strcmp(label, "HUD_TRANSP") == 0)
	{
	return Hooking::loading_text;
	}*/

	return ogGetLabelText(this_, label);
}

fpStatSetInt OG_STAT_SET_INT = nullptr;
bool Hooking::reportNotification = false;
bool __cdecl HK_STAT_SET_INT(Hash statName, int value, bool save)
{
	return OG_STAT_SET_INT(statName, value, save);
} //Report

Hooking::NativeHandler ORIG_WAIT = NULL;
void* __cdecl MY_WAIT(NativeContext* cxt)
{
	static int lastThread = 0;
	int threadId = SCRIPT::GET_ID_OF_THIS_THREAD();
	if (!lastThread)
	{
		char* name = SCRIPT::_GET_NAME_OF_THREAD(threadId);
		if (strcmp(name, "main_persistent") == 0)
		{
			lastThread = threadId;
			Log::Msg("Hooked Script NAME: %s ID: %i", name, threadId);
		}
	}
	if (threadId == lastThread) Hooking::onTickInit();
	ORIG_WAIT(cxt);
	return cxt;
}

Hooking::NativeHandler  ORIG_NETWORK_SESSION_KICK_PLAYER = NULL;
void* __cdecl MY_NETWORK_SESSION_KICK_PLAYER(NativeContext* cxt)
{
	Player player = cxt->GetArgument<int>(0);
	if (player == PLAYER::PLAYER_ID())
	{
		ORIG_NETWORK_SESSION_KICK_PLAYER(cxt);
	}
	return nullptr;
}


Hooking::NativeHandler  ORIG_NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE = NULL;
void* __cdecl MY_NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(NativeContext* cxt)
{
	Player player = cxt->GetArgument<int>(0);
	if (player == PLAYER::PLAYER_ID())
	{
		ORIG_NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(cxt);
	}
	return nullptr;
}

Hooking::NativeHandler  ORIG_ATTACH_ENTITY_TO_ENTITY = NULL;
void* __cdecl MY_ATTACH_ENTITY_TO_ENTITY(NativeContext* cxt)
{
	Player player = cxt->GetArgument<int>(0);
	if (player == PLAYER::PLAYER_ID())
	{
		ORIG_ATTACH_ENTITY_TO_ENTITY(cxt);
	}
	return nullptr;
}

Hooking::NativeHandler ORIG_CLEAR_PED_TASKS_IMMEDIATELY = NULL;
void* __cdecl MY_CLEAR_PED_TASKS_IMMEDIATELY(NativeContext* cxt)
{
	if (cxt->GetArgument<Ped>(0) != PLAYER::PLAYER_PED_ID())
	{
		ORIG_CLEAR_PED_TASKS_IMMEDIATELY(cxt);
	}

	return nullptr;
}

Hooking::NativeHandler ORIG_CLEAR_PED_TASKS = NULL;
void* __cdecl MY_CLEAR_PED_TASKS(NativeContext* cxt)
{
	if (cxt->GetArgument<Ped>(0) != PLAYER::PLAYER_PED_ID())
	{
		ORIG_CLEAR_PED_TASKS(cxt);
	}

	return nullptr;
}

Hooking::NativeHandler ORIG_CLEAR_PED_SECONDARY_TASK = NULL;
void* __cdecl MY_CLEAR_PED_SECONDARY_TASK(NativeContext* cxt)
{
	if (cxt->GetArgument<Ped>(0) != PLAYER::PLAYER_PED_ID())
	{
		ORIG_CLEAR_PED_SECONDARY_TASK(cxt);
	}
	return nullptr;
}

Hooking::NativeHandler ORIG_CLONE_PED = NULL;
void* __cdecl MY_CLONE_PED(NativeContext* cxt)
{
	if (cxt->GetArgument<Ped>(0) != PLAYER::PLAYER_PED_ID())
	{
		ORIG_CLONE_PED(cxt);
	}
	return nullptr;
}

static std::size_t get_module_size(HMODULE hmod)
{
	auto dosHeader = PIMAGE_DOS_HEADER(hmod);
	auto ntHeader = PIMAGE_NT_HEADERS(PBYTE(hmod) + dosHeader->e_lfanew);

	return ntHeader->OptionalHeader.SizeOfImage;
}
fpNtQueryVirtualMemory ogNtQueryVirtualMemory = nullptr;
int hkNtQueryVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, int MemoryInformationClass, PVOID MemoryInformation, SIZE_T MemoryInformationLength, PSIZE_T ReturnLength)
{
	if (MemoryInformationClass == 0
		&& ProcessHandle == GetCurrentProcess()
		&& std::uintptr_t(BaseAddress) >= std::uintptr_t(_hmoduleDLL)
		&& std::uintptr_t(BaseAddress) <= std::uintptr_t(_hmoduleDLL) + get_module_size(_hmoduleDLL))
	{
		return 0xC;
	}

	return static_cast<decltype(&hkNtQueryVirtualMemory)>(ogNtQueryVirtualMemory)
		(ProcessHandle, BaseAddress, MemoryInformationClass, MemoryInformation, MemoryInformationLength, ReturnLength);
}
fpNtQueryVirtualMemory Hooking::NtQueryVirtualMemory = nullptr;

bool detourHook(LPVOID target, LPVOID hook, LPVOID orig) {
	MH_STATUS status;
	status = MH_CreateHook(target, hook, (void**)& orig);
	if ((status != MH_OK && status != MH_ERROR_ALREADY_CREATED) || MH_EnableHook(target) != MH_OK)
		return false;
	Hooking::m_hooks.push_back(target);
	return true;
}

bool Hooking::HookNatives()
{
	MH_STATUS status;

	status = MH_CreateHook(Hooking::is_DLC_present, HK_IS_DLC_PRESENT, (void**)&OG_IS_DLC_PRESENT);
	if ((status != MH_OK && status != MH_ERROR_ALREADY_CREATED) || MH_EnableHook(Hooking::is_DLC_present) != MH_OK)
	return false;
	Hooking::m_hooks.push_back(Hooking::is_DLC_present);

	status = MH_CreateHook(Hooking::GetLabelText, hkGetLabelText, (void**)& ogGetLabelText);
	if ((status != MH_OK && status != MH_ERROR_ALREADY_CREATED) || MH_EnableHook(Hooking::GetLabelText) != MH_OK)
		return false;
	Hooking::m_hooks.push_back(Hooking::GetLabelText);

	status = MH_CreateHook(Hooking::NtQueryVirtualMemory, hkNtQueryVirtualMemory, (void**)& ogNtQueryVirtualMemory);
	if ((status != MH_OK && status != MH_ERROR_ALREADY_CREATED) || MH_EnableHook(Hooking::NtQueryVirtualMemory) != MH_OK)
		return false;
	Hooking::m_hooks.push_back(Hooking::NtQueryVirtualMemory);

	return true;
}


void __stdcall ScriptFunction(LPVOID lpParameter)
{
	try
	{
		ScriptMain();
	}
	catch (...)
	{
		Log::Fatal("Nogger");
	}
}

void Hooking::onTickInit()
{
	mainFiber = IsThreadAFiber() ? GetCurrentFiber() : ConvertThreadToFiber(nullptr);

	if (timeGetTime() < wakeAt)
		return;

	static HANDLE scriptFiber;
	if (scriptFiber)
		SwitchToFiber(scriptFiber);
	else
		scriptFiber = CreateFiber(NULL, ScriptFunction, nullptr);
}

void Hooking::FailPatterns(const char* name)
{
	char buf[4096];
	sprintf_s(buf, "finding %s", name);
	Log::Error(buf);
	Cleanup();
}

/*
//CPatternResult
*/

CPatternResult::CPatternResult(void* pVoid) :
	m_pVoid(pVoid)
{}
CPatternResult::CPatternResult(void* pVoid, void* pBegin, void* pEnd) :
	m_pVoid(pVoid),
	m_pBegin(pBegin),
	m_pEnd(pEnd)
{}
CPatternResult::~CPatternResult() {}

/*
//CPattern Public
*/

CPattern::CPattern(char* szByte, char* szMask) :
	m_szByte(szByte),
	m_szMask(szMask),
	m_bSet(false)
{}
CPattern::~CPattern() {}

CPattern& CPattern::find(int i, uint64_t startAddress)
{
	match(i, startAddress, false);
	if (m_result.size() <= i)
		m_result.push_back(nullptr);
	return *this;
}

CPattern& CPattern::virtual_find(int i, uint64_t startAddress)
{
	match(i, startAddress, true);
	if (m_result.size() <= i)
		m_result.push_back(nullptr);
	return *this;
}

CPatternResult	CPattern::get(int i)
{
	if (m_result.size() > i)
		return m_result[i];
	return nullptr;
}

/*
//CPattern Private
*/
bool	CPattern::match(int i, uint64_t startAddress, bool virt)
{
	if (m_bSet)
		return false;
	uint64_t	begin = 0;
	uint64_t	end = 0;
	if (!virt)
	{
		CMetaData::init();
		begin = CMetaData::begin() + startAddress;
		end = CMetaData::end();
		if (begin >= end)
			return false;
	}
	int		j = 0;
	do
	{
		if (virt)
			begin = virtual_find_pattern(startAddress, (BYTE*)m_szByte, m_szMask) + 1;
		else
			begin = find_pattern(begin, end, (BYTE*)m_szByte, m_szMask) + 1;
		if (begin == NULL)
			break;
		j++;
	} while (j < i);

	m_bSet = true;
	return true;
}

bool	CPattern::byte_compare(const BYTE* pData, const BYTE* btMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++btMask)
		if (*szMask == 'x' && *pData != *btMask)
			break;
	if ((*szMask) != 0)
		return false;
	return true;
}


uint64_t	CPattern::find_pattern(uint64_t address, uint64_t end, BYTE* btMask, char* szMask)
{
	size_t len = strlen(szMask) + 1;
	for (uint64_t i = 0; i < (end - address - len); i++)
	{
		BYTE* ptr = (BYTE*)(address + i);
		if (byte_compare(ptr, btMask, szMask))
		{
			m_result.push_back(CPatternResult((void*)(address + i)));
			return address + i;
		}
	}
	return NULL;
}

uint64_t	CPattern::virtual_find_pattern(uint64_t address, BYTE* btMask, char* szMask)
{
	MEMORY_BASIC_INFORMATION mbi;
	char* pStart = nullptr;
	char* pEnd = nullptr;
	char* res = nullptr;
	size_t	maskLen = strlen(szMask);

	while (res == nullptr && sizeof(mbi) == VirtualQuery(pEnd, &mbi, sizeof(mbi)))
	{
		pStart = pEnd;
		pEnd += mbi.RegionSize;
		if (mbi.Protect != PAGE_READWRITE || mbi.State != MEM_COMMIT)
			continue;

		for (int i = 0; pStart < pEnd - maskLen && res == nullptr; ++pStart)
		{
			if (byte_compare((BYTE*)pStart, btMask, szMask))
			{
				m_result.push_back(CPatternResult((void*)pStart, mbi.BaseAddress, pEnd));
				res = pStart;
			}
		}

		mbi = {};
	}
	return (uint64_t)res;
}

void	failPat(const char* name)
{
	Log::Fatal("Failed to find %s pattern.", name);
	exit(0);
}

template <typename T>
void	setPat
(
	char* name,
	char* pat,
	char* mask,
	T** out,
	bool		rel,
	int			offset = 0,
	int			deref = 0,
	int			skip = 0
)
{
	T* ptr = nullptr;

	CPattern pattern(pat, mask);
	pattern.find(1 + skip);
	if (rel)
		ptr = pattern.get(skip).get_rel<T>(offset);
	else
		ptr = pattern.get(skip).get<T>(offset);

	while (true)
	{
		if (ptr == nullptr) {
			//failPat(name);		
			if (enable_coloading) {
				Log::Msg("Skipped %s pattern", name);
			}
			else {
				failPat(name);
			}
		}

		if (deref <= 0)
			break;
		ptr = *(T * *)ptr;
		--deref;
	}

	*out = ptr;
	return;
}

template <typename T>
void	setFn
(
	char* name,
	char* pat,
	char* mask,
	T* out,
	int			skip = 0
)
{
	char* ptr = nullptr;

	CPattern pattern(pat, mask);
	pattern.find(1 + skip);
	ptr = pattern.get(skip).get<char>(0);

	if (ptr == nullptr) {
		//failPat(name);
		if (enable_coloading) {
			Log::Msg("Skipped %s pattern", name);
		}
		else {
			failPat(name);
		}
	}
	else {
		Hooking::foundPtr(name);
	}

	*out = (T)ptr;
	return;
}

void Hooking::FindPatterns()
{
	HANDLE steam = GetModuleHandleA("steam_api64.dll");

	auto p_activeThread = pattern("E8 ? ? ? ? 48 8B 88 10 01 00 00");
	auto p_blipList = pattern("4C 8D 05 ? ? ? ? 0F B7 C1");
	auto p_fixVector3Result = pattern("83 79 18 00 48 8B D1 74 4A FF 4A 18");
	auto p_gameLegals = pattern("72 1F E8 ? ? ? ? 8B 0D");
	auto p_gameLogos = pattern("70 6C 61 74 66 6F 72 6D 3A");
	auto p_gameState = pattern("83 3D ? ? ? ? ? 8A D9 74 0A");
	auto p_modelCheck = pattern("48 85 C0 0F 84 ? ? ? ? 8B 48 50");
	auto p_nativeTable = pattern("76 32 48 8B 53 40 48 8D 0D");
	auto p_worldPtr = pattern("48 8B 05 ? ? ? ? 45 ? ? ? ? 48 8B 48 08 48 85 C9 74 07");
	auto p_globalPtr = pattern("4C 8D 05 ? ? ? ? 4D 8B 08 4D 85 C9 74 11");
	auto p_eventHook = pattern("48 83 EC 28 E8 ? ? ? ? 48 8B 0D ? ? ? ? 4C 8D 0D ? ? ? ? 4C 8D 05 ? ? ? ? BA 03");
	auto p_chatnameaddr = pattern("48 8B 05 ? ? ? ? C3 8A D1");

	char* c_location = nullptr;
	void* v_location = nullptr;

	setPat<uint64_t>("frame count",
		"\x8B\x15\x00\x00\x00\x00\x41\xFF\xCF",
		"xx????xxx",
		&Hooking::m_frameCount,
		true,
		2);

	setFn<fpIsDLCPresent>("is_dlc_present",
		"\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x81\xF9\x00\x00\x00\x00",
		"xxxx?xxxxxxx????",
		&Hooking::is_DLC_present);

	setFn<TriggerScriptEvent>("trigger_script_event",
		"\x48\x8B\xC4\x48\x89\x58\x08\x48\x89\x68\x10\x48\x89\x70\x18\x48\x89\x78\x20\x41\x56\x48\x81\xEC\x00\x00\x00\x00\x45\x8B\xF0\x41\x8B\xF9",
		"xxxxxxxxxxxxxxxxxxxxxxxx????xxxxxx",
		&Hooking::trigger_script_event);

	setFn<SetSessionWeather>("set_session_weather",
		"\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x30\x40\x8A\xE9",
		"xxxx?xxxx?xxxx?xxxxxxxx",
		&Hooking::set_session_weather);

	setFn<fpSetEntityMaxHealth>("set_entity_max_health",
		"\x40\x53\x48\x83\xEC\x20\xE8\x00\x00\x00\x00\x48\x8B\xD8\x48\x85\xC0\x74\x19\x4C\x8B\x00\x8B\x15\x00\x00\x00\x00\x48\x8B\xC8\x41\xFF\x50\x08\x84\xC0\x74\x05\x48\x8B\xC3\xEB\x02\x33\xC0\x48\x83\xC4\x20\x5B\xC3\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x56\x57",
		"xxxxxxx????xxxxxxxxxx?xx????xxxxxxxxxxxxxxxxxxxxxxxxxxxx?xxxx?xx",
		&Hooking::set_entity_max_health);

	setFn<fpCreateVehicle>("create_vehicle",
		"\x48\x89\x5C\x24\x00\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8B\xEC\x48\x83\xEC\x50\xF3\x0F\x10\x02",
		"xxxx?xxxxxxxxxxxxxxxxxxxxxx",
		&Hooking::create_vehicle);

	setFn<fpClearPedTasksImmediately>("clear_ped_tasks_immediately",
		"\x40\x53\x48\x83\xEC\x30\xE8\x00\x00\x00\x00\x48\x8B\xD8\x48\x85\xC0\x0F\x84",
		"xxxxxxx????xxxxxxxx",
		&Hooking::clear_ped_tasks_immediately);

	setFn<fpGetPlayerName>("get_player_name",
		"\x40\x53\x48\x83\xEC\x20\x80\x3D\x00\x00\x00\x00\x00\x8B\xD9\x74\x22",
		"xxxxxxxx?????xxxx",
		&Hooking::GPN);

	setFn<fpCreateAmbientPickup>("create_ambient_pickup",
		"\x48\x8B\xC4\x48\x89\x58\x10\x48\x89\x70\x18\x48\x89\x78\x20\x55\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x68\xC1\x48\x81\xEC\x00\x00\x00\x00\x45\x8B\xF9\x41\x8B\xF0\x4C\x8B\xEA\xE8\x00\x00\x00\x00\x0F\xB7\x0D\x00\x00\x00\x00\x33\xFF\x44\x8B\xC7\x44\x8B\xD7\x44\x8B\xE0\x85\xC9\x7E\x1C\x48\x8B\x1D\x00\x00\x00\x00",
		"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxx????xxx????xxxxxxxxxxxxxxxxxx????",
		&Hooking::create_ambient_pickup);

	setFn<fpSetMobileRadioEnabledDuringGameplay>("set_mobile_radio",
		"\x40\x53\x48\x83\xEC\x20\x8A\xD9\x48\x8D\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x48\x8D\x0D\x00\x00\x00\x00\x8B\xD0\xE8\x00\x00\x00\x00\x48\x85\xC0\x74\x10",
		"xxxxxxxxxxx????x????xxx????xxx????xxxxx",
		&Hooking::set_mobile_radio_enabled_during_gameplay);

	setFn<fpGetLabelText>("get_label_text",
		"\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x48\x8B\xDA\x48\x8B\xF9\x48\x85\xD2\x75\x44\xE8",
		"xxxx?xxxxxxxxxxxxxxxxx",
		&Hooking::GetLabelText);

	setFn<fpRequestIpl>("request_ipl",
		"\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x48\x8B\x05\x00\x00\x00\x00\x48\x8B\xF9\x4C\x8B\xC1\x48\x8D\x54\x24\x00\x48\x8D\x0D\x00\x00\x00\x00\xFF\x50\x10\x8B\x18",
		"xxxx?xxxxxxxx????xxxxxxxxxx?xxx????xxxxx",
		&Hooking::request_ipl);

	setFn<fpIsIplActive>("is_ipl_active",
		"\x48\x83\xEC\x28\x48\x8B\x05\x00\x00\x00\x00\x4C\x8B\xC1",
		"xxxxxxx????xxx",
		&Hooking::is_ipl_active);

	setFn<fpGetPlayerMaxArmour>("get_player_max_armour",
		"\x40\x53\x48\x83\xEC\x20\x33\xDB\x38\x1D\x00\x00\x00\x00\x74\x1C",
		"xxxxxxxxxx????xx",
		&Hooking::get_player_max_armour);

	setFn<fpGetDisplayNameFromVehicle>("get_display_name_from_vehicle",
		"\x48\x83\xEC\x28\x48\x8D\x54\x24\x00\xC7\x44\x24\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x48\x85\xC0\x74\x16",
		"xxxxxxxx?xxx?????x????xxxxx",
		&Hooking::get_display_name_from_vehicle);

	setPat<threeBytes>("infinite ammo",
		"\x41\x2B\xD1\xE8",
		"xxxx",
		&Hooking::infinite_ammo,
		false);

	setPat<threeBytes>("no reload",
		"\x41\x2B\xC9\x3B\xC8\x0F",
		"xxxxxx",
		&Hooking::no_reload,
		false);

	Sleep(5000);

	Log::Msg("Getting Game State");
	c_location = p_gameState.count(1).get(0).get<char>(2);
	c_location == nullptr ? FailPatterns("gameState") : m_gameState = reinterpret_cast<decltype(m_gameState)>(c_location + *(int32_t*)c_location + 5);

	Log::Msg("Getting vector3 result fixer func");
	v_location = p_fixVector3Result.count(1).get(0).get<void>(0);
	if (v_location != nullptr) scrNativeCallContext::SetVectorResults = (void(*)(scrNativeCallContext*))(v_location);

	Log::Msg("Getting native registration table");
	c_location = p_nativeTable.count(1).get(0).get<char>(9);
	c_location == nullptr ? FailPatterns("native registration table") : m_registrationTable = reinterpret_cast<decltype(m_registrationTable)>(c_location + *(int32_t*)c_location + 4);

	Log::Msg("Getting World Pointer");
	c_location = p_worldPtr.count(1).get(0).get<char>(0);
	c_location == nullptr ? FailPatterns("world Pointer") : m_worldPtr = reinterpret_cast<uint64_t>(c_location) + *reinterpret_cast<int*>(reinterpret_cast<uint64_t>(c_location) + 3) + 7;

	Log::Msg("Getting Blip List");
	c_location = p_blipList.count(1).get(0).get<char>(0);
	c_location == nullptr ? FailPatterns("blip List") : m_blipList = (BlipList*)(c_location + *reinterpret_cast<int*>(c_location + 3) + 7);

	Log::Msg("Bypassing Object restrictions");
	CPattern pattern_modelCheck("\x48\x85\xC0\x0F\x84\x00\x00\x00\x00\x8B\x48\x50", "xxxxx????xxx");
	m_model_bypass = pattern_modelCheck.find(0).get(0).get<char>(0);
	Log::Msg("Hooking Model Check Bypass...");
	if (nullptr != m_model_bypass)
	{
	memcpy_s(model_bypass, sizeof(model_bypass), m_model_bypass, sizeof(model_bypass));
	memset(m_model_bypass, NOP, sizeof(model_bypass));
	Log::Msg("Hooking Model Check Bypass completed sucessfull!");
	}
	else
	{
		Log::Msg("Error in finding the Model Check Bypass");
	}

	auto pattern_int_checker = Memory::pattern("80 3D ? ? ? ? ? 0F 85 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 08 48 39 0D ? ? ? ? 0F 85");
	m_int_checker = pattern_int_checker.count(1).get(0).get<std::uint8_t>(0);
	if (m_int_checker == nullptr) {
		Log::Error("Failed to find Integrity Checker");
	}
	else {
		og_int_checker = m_int_checker[0];
		memcpy_s(int_check, sizeof(int_check), m_int_checker, sizeof(int_check));
		m_int_checker[0] = 0xC3;
		memset(m_int_checker, NOP, sizeof(int_check));
		FlushInstructionCache(GetCurrentProcess(), m_int_checker, 8);
	}

	Log::Msg("Getting active script thread");
	c_location = p_activeThread.count(1).get(0).get<char>(1);
	c_location == nullptr ? FailPatterns("Active Script Thread") : GetActiveThread = reinterpret_cast<decltype(GetActiveThread)>(c_location + *(int32_t*)c_location + 4);

	Log::Msg("Getting World Pointer");
	c_location = p_globalPtr.count(1).get(0).get<char>(0);
	__int64 patternAddr = NULL;
	c_location == nullptr ? FailPatterns("globalTable") : patternAddr = reinterpret_cast<decltype(patternAddr)>(c_location);
	m_globalPtr = (__int64**)(patternAddr + *(int*)(patternAddr + 3) + 7);

	Log::Msg("Getting Event Hook");
	if ((c_location = p_eventHook.count(1).get(0).get<char>(0)))
	{
		int i = 0, j = 0, matches = 0, found = 0;
		char* pattern = "\x4C\x8D\x05";
		while (found != EVENT_COUNT)
		{
			if (c_location[i] == pattern[j])
			{
				if (++matches == 3)
				{
					EventPtr.push_back((void*)(reinterpret_cast<uint64_t>(c_location + i - j) + *reinterpret_cast<int*>(c_location + i + 1) + 7));
					found++;
					j = matches = 0;
				}
				j++;
			}
			else
			{
				matches = j = 0;
			}
			i++;
		}
	}

	Log::Msg("Initializing natives");
	CrossMapping::initNativeMap();

	Log::Msg("Checking if GTA V is ready");
	while (*m_gameState != GameStatePlaying) {
		Sleep(200);
	}
	
	Log::Msg("GTA V ready");
}

static Hooking::NativeHandler _Handler(uint64_t origHash)
{
	uint64_t newHash = CrossMapping::MapNative(origHash);
	if (newHash == 0)
	{
		return nullptr;
	}

	Hooking::NativeRegistrationNew* table = m_registrationTable[newHash & 0xFF];

	for (; table; table = table->getNextRegistration())
	{
		for (uint32_t i = 0; i < table->getNumEntries(); i++)
		{
			if (newHash == table->getHash(i))
			{
				return table->handlers[i];
			}
		}
	}
	return nullptr;
}

Hooking::NativeHandler Hooking::GetNativeHandler(uint64_t origHash)
{
	auto& handler = m_handlerCache[origHash];

	if (handler == nullptr)
	{
		handler = _Handler(origHash);
	}

	return handler;
}

eGameState Hooking::GetGameState()
{
	return *m_gameState;
}

uint64_t Hooking::getWorldPtr()
{
	return m_worldPtr;
}
void WAIT(DWORD ms)
{
	wakeAt = timeGetTime() + ms;
	SwitchToFiber(mainFiber);
}

void Hooking::Cleanup()
{
	Log::Msg("Cleaning up hooks");
	MH_Uninitialize();
	Log::Msg("Uninitialize finished");
}

void Hooking::defuseEvent(RockstarEvent e, bool toggle)
{
	static const unsigned char retn = 0xC3;
	char* p = (char*)EventPtr[e];
	if (toggle)
	{
		if (EventRestore[e] == 0)
			EventRestore[e] = p[0];
		*p = retn;
	}
	else
	{
		if (EventRestore[e] != 0)
			* p = EventRestore[e];
	}
}

__int64** Hooking::getGlobalPtr()
{
	return m_globalPtr;
}

__int64* Hooking::getGlobalPtr1(int index)
{
	return &Hooking::getGlobalPtr()[index >> 18 & 0x3F][index & 0x3FFFF];
}

BlipList* Hooking::GetBlipList()
{
	return m_blipList;
}