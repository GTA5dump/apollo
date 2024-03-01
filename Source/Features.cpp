#include "stdafx.h"

#define PROP_MONEY_PAPERCASE_01 -1803909274
#define PROP_MONEY_PAPERBAG_01 -1666779307
#define PROP_MONEY_BAG_01 0x113FD533
#define PICKUP_MONEY_CASE 0x1E9A99F8

//********MATH**********//
#define PI 3.14159265
#define DEGTORAD(D)((D * PI) / 180.0) // Converts Degrees to radians
#define RADTODEG(R)((180.0 * R) / PI)//Converts Radians to Degrees 
int Features::MoneyItem = 0;
int fake_rank = 0;

enum keys
{
	NUM1 = 0x61,
	NUM3 = 0x63,
	NUM7 = 0x67,
	NUM9 = 0x69,
	PLUS = 0x6B,
	MINUS = 0x6D,
	DIVIDE = 0x6F,
	MULTIPLY = 0x6A,
	COMMA = 0x6E,
	F1 = 0x70,
	F2 = 0x71,
	F3 = 0x72,
	F4 = 0x73,
	F5 = 0x74,
	F6 = 0x75,
	F7 = 0x76,
	F8 = 0x77,
	F9 = 0x78,
	F10 = 0x79,
	F11 = 0x7A,
	F12 = 0x7B,
};
static std::string getMonthStr(int m) {
	switch (m)
	{
	case 1: {
		return "January"; }
	case 2: {
		return "February"; }
	case 3: {
		return "March"; }
	case 4: {
		return "April"; }
	case 5: {
		return "May"; }
	case 6: {
		return "June"; }
	case 7: {
		return "July"; }
	case 8: {
		return "August"; }
	case 9: {
		return "September"; }
	case 10: {
		return "October"; }
	case 11: {
		return "November"; }
	case 12: {
		return "December"; }
	default: {
		return "Month not found";
	}
	}
}
Hash moneyModel(int id) {
	switch (id) {
	
	}
}

bool is_ped_shooting(Ped ped) {
	Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped, 1);
	return PED::IS_PED_SHOOTING_IN_AREA(ped, coords.x, coords.y, coords.z, coords.x, coords.y, coords.z, true, true);
}

int Features::Online::selectedPlayer = 0;
char* CharKeyboard2(char* windowName = "", int maxInput = 21, char* defaultText = "")
{
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(0, "", "", defaultText, "", "", "", maxInput);
	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return "";
	return GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
}

void MessageAtBottomScreen(char* message, int timeMs)
{
	UI::BEGIN_TEXT_COMMAND_PRINT("STRING");
	UI::SET_TEXT_COLOUR(255, 255, 255, 255);
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(message);
	UI::END_TEXT_COMMAND_PRINT(timeMs, 1);
}

int Features::inviteSS = 1;
void Features::UpdateLoop() {
	
}

std::vector<std::string> Features::ini1;






networkClanMgr clanM, clanP;
BOOL IsPlayerInClan(Player player)
{
	if (NETWORK::NETWORK_IS_SESSION_ACTIVE())
	{
		networkHandleMgr net, net2;
		NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &net.netHandle, 13); NETWORK::NETWORK_HANDLE_FROM_PLAYER(PLAYER::PLAYER_ID(), &net2.netHandle, 13);
		if (NETWORK::_NETWORK_PLAYER_IS_IN_CLAN())
		{
			if (NETWORK::NETWORK_CLAN_PLAYER_IS_ACTIVE(&net2.netHandle) && NETWORK::NETWORK_CLAN_PLAYER_IS_ACTIVE(&net.netHandle))
			{
				if (NETWORK::NETWORK_CLAN_PLAYER_GET_DESC(&clanM.clanHandle, 35, &net2.netHandle) && NETWORK::NETWORK_CLAN_PLAYER_GET_DESC(&clanP.clanHandle, 35, &net.netHandle))
				{
					if (clanP.clanHandle == clanM.clanHandle)
					{
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

bool ShowSpeedoAsMph = false;
bool cruse = false;
RGBA shadowColor;
void CruiseControlLoop()
{
	static float CruiseSpeed = 0;
	static Vehicle prevVeh;
	if (players[selfPlayer].inVehicle)
	{
		static int tickcount;
		tickcount++;
		if (tickcount >= 150)
		{
			if (GetAsyncKeyState(VK_KEY_W) || CONTROLS::IS_CONTROL_PRESSED(2, BUTTON_RT)) {
				CruiseSpeed += 3.f;
				tickcount = 0;
			}
			if (GetAsyncKeyState(VK_KEY_S) || CONTROLS::IS_CONTROL_PRESSED(2, BUTTON_LT)) {
				CruiseSpeed -= 3.f;
				tickcount = 0;
			}
		}

		Menu::drawText(ShowSpeedoAsMph ? Menu::StringToChar(std::to_string((CruiseSpeed * 3.6) / 1.609344) + "~b~MPH") : Menu::StringToChar(std::to_string((CruiseSpeed * 3.6)) + "~b~KMH"), 7, { 0.5f, 0.5f }, { 0.25f, 0.25f }, { 0.f, 1.f }, Menu::Settings::titleTextt, true, false, true, 0, shadowColor, 0);

		Vehicle playerVeh = players[selfPlayer].veh;

		if (prevVeh != playerVeh)
			CruiseSpeed = ENTITY::GET_ENTITY_SPEED(players[selfPlayer].veh);

		if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(playerVeh) < 1)
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(playerVeh, CruiseSpeed);
	}
}


float accelerationmultiplier = 0;
float brakesmultiplier = 0;
float suspensionseight = 0;
void SetMultipliers() {

	if (accelerationmultiplier != 0) {
		Vehicle pedVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

		if (ENTITY::DOES_ENTITY_EXIST(pedVeh)) {
			if (GetAsyncKeyState('W') || CONTROLS::IS_CONTROL_PRESSED(2, INPUT_FRONTEND_RT)) {
				if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(pedVeh))
					ENTITY::APPLY_FORCE_TO_ENTITY(pedVeh, true, 0, accelerationmultiplier / 10, 0, 0, 0, 0, true, true, true, true, false, true);
			}
		}
	}
	if (brakesmultiplier != 0) {

		Vehicle pedVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

		if (ENTITY::DOES_ENTITY_EXIST(pedVeh)) {
			if (GetAsyncKeyState('S') || CONTROLS::IS_CONTROL_PRESSED(2, INPUT_FRONTEND_LT)) {
				if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(pedVeh))
					ENTITY::APPLY_FORCE_TO_ENTITY(pedVeh, true, 0, ((brakesmultiplier / 10) * -1), 0, 0, 0, 0, true, true, true, true, false, true);
			}
		}

	}

	if (suspensionseight != 0) {

		Vehicle pedVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		if (ENTITY::DOES_ENTITY_EXIST(pedVeh)) {
			ENTITY::APPLY_FORCE_TO_ENTITY(pedVeh, true, 0, 0, -suspensionseight / 10, 0, 0, 0, true, true, true, true, false, true);
		}
	}
}


bool Features::Triggerbool = false;
void Features::trigger(bool toggle)
{
	if (toggle)
	{
		const int ElementAmount = 10;
		const int ArrSize = ElementAmount * 4 + 2;

		Entity* peds = new Entity[ArrSize];
		peds[0] = ElementAmount;
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_INDEX(), 1);
		int PedFound = PED::GET_PED_NEARBY_PEDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::GET_PLAYER_INDEX()), peds, -1);
		for (int i = 0; i < PedFound; i++)
		{
			int OffsetID = i * 2 + 2;
			int bone = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(peds[OffsetID], "SKEL_Head");
			Vector3 pos = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(peds[OffsetID], bone);
			RequestControlOfEnt(peds[OffsetID]);
			if (ENTITY::DOES_ENTITY_EXIST(peds[OffsetID]) && PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::GET_PLAYER_INDEX()) != peds[OffsetID])
			{
				PED::SET_PED_SHOOTS_AT_COORD(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::GET_PLAYER_INDEX()), pos.x, pos.y, pos.z, true);
			}
		}

	}
}

void notify(const std::string& message)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(const_cast<char*>(message.c_str()));

	constexpr const char* name = "Apollo ~\u00A6~";
	constexpr const char* subtitle = "~b~Apollo Menu";
	constexpr const char* clan_tag = "___MENU";
	constexpr const char* picture = "CHAR_LESTER_DEATHWISH";

	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG(const_cast<char*>(picture), const_cast<char*>(picture), FALSE, 1, const_cast<char*>(name), const_cast<char*>(subtitle), 0.5f, const_cast<char*>(clan_tag));

	//	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2(const_cast<char*>(picture), const_cast<char*>(picture), TRUE, 1, const_cast<char*>(name), const_cast<char*>(subtitle), 1, const_cast<char*>(clan_tag), 4, 0);
	UI::_DRAW_NOTIFICATION(TRUE, FALSE);
}

static int bomber_ting;
static Vector3 bomb_coords;
static bool bomber_cooldown;
static bool bomber_countdown;
bool Bommmer = false;
void bombermode()
{

	if (PED::IS_PED_IN_ANY_HELI(PLAYER::PLAYER_PED_ID()) || PED::IS_PED_IN_ANY_PLANE(PLAYER::PLAYER_PED_ID())) {
		Vector3 c = ENTITY::GET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
		GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(c.x, c.y, c.z, &c.z, 0);
		if (!bomber_countdown)
			bomb_coords = c;
		GRAPHICS::DRAW_MARKER(6, bomb_coords.x, bomb_coords.y, bomb_coords.z, 0.f, 0.f, 0.f, 90.f, 0.f, 0.f, 15.f, 15.f, 15.f, 255, 0, 0, 150, 0, 0, 0, 0, NULL, NULL, 0);

		static auto ticker = GetTickCount();
		if (bomber_cooldown) {
			if ((GetTickCount() - ticker) >= 3500) {
				bomber_cooldown = true;
				ticker = GetTickCount();
			}
		}

		static auto ticcker = GetTickCount();
		if (bomber_countdown) {
			if ((GetTickCount() - ticcker) >= 1500) {
				FIRE::ADD_EXPLOSION(bomb_coords.x, bomb_coords.y, bomb_coords.z, ExplosionTypeBlimp, 10.f, true, false, 0.f);
				notify("~g~Completed.");
				bomber_ting = 0;
				bomber_countdown = false;
				ticcker = GetTickCount();
			}
		}

		if (IsKeyPressed(VK_SPACE) && !bomber_cooldown) {
			ticcker = GetTickCount();
			ticker = GetTickCount();
			notify("~s~Wait...");
			bomb_coords = c;
			bomber_countdown = true;
			bomber_cooldown = true;
		}
	}
}

int Features::spawnStuff(char* name, Vector3 coords) {
	Any output = NULL;
	DWORD model = GAMEPLAY::GET_HASH_KEY(name);
	STREAMING::REQUEST_MODEL(model);
	while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
	if (STREAMING::IS_MODEL_A_VEHICLE(model)) {
		output = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, 0, 1, 1);
	}
	else {
		output = OBJECT::CREATE_OBJECT(model, coords.x, coords.y, coords.z, true, 1, 0);
	}
	//Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, heading, 1, 1);
	return output;
	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
}
int Features::carCounter = 0;
int Features::things[999] = {};
char* Features::selectedthing = NULL;
float Features::locX = 0;
float Features::locY = 0;
float Features::locZ = 0;
bool Features::blockX = false;
bool Features::blockY = false;
bool Features::blockZ = false;

void Features::Attachment(char* p0) {
	int thing1 = Features::spawnStuff(p0, coordsOf(PLAYER::PLAYER_PED_ID()));
	Vehicle thing2 = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	Features::AttachThingToThing(thing1, thing2, Features::locX, Features::locY, Features::locZ, 0.0f, 0.0f, 0.0f);
	Features::things[Features::carCounter] = thing1;
	Features::carCounter += 1;
}

int Features::cargobob_strength = 1;
bool Features::cargobob_active = false;
void Features::cargobobMagnet() {
	Vehicle veh;
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) { veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()); }
	VEHICLE::_SET_CARGOBOB_PICKUP_MAGNET_ACTIVE(veh, Features::cargobob_active);
}


bool Features::dowbool = false;
void Features::DriveOnWater(bool toggle) {
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
	DWORD model = ENTITY::GET_ENTITY_MODEL(veh);
	Vector3 pos = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
	float height = 0;
	WATER::_SET_WAVES_INTENSITY(height);
	if ((!(VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(veh)))) && WATER::GET_WATER_HEIGHT_NO_WAVES(pos.x, pos.y, pos.z, &height)) {
		Object container = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(pos.x, pos.y, pos.z, 4.0, GAMEPLAY::GET_HASH_KEY("prop_container_ld2"), 0, 0, 1);
		if (ENTITY::DOES_ENTITY_EXIST(container) && height > -50.0f) {
			Vector3 pRot = ENTITY::GET_ENTITY_ROTATION(playerPed, 0);
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1)) pRot = ENTITY::GET_ENTITY_ROTATION(veh, 0);
			RequestControlOfEnt(container);
			ENTITY::SET_ENTITY_COORDS(container, pos.x, pos.y, height - 1.5f, 0, 0, 0, 1);
			ENTITY::SET_ENTITY_ROTATION(container, 0, 0, pRot.z, 0, 1);
			Vector3 containerCoords = ENTITY::GET_ENTITY_COORDS(container, 1);
			if (pos.z < containerCoords.z) {
				if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
					ENTITY::SET_ENTITY_COORDS(playerPed, pos.x, pos.y, containerCoords.z + 2.0f, 0, 0, 0, 1);
				}
				else {
					RequestControlOfEnt(veh);
					Vector3 vehc = ENTITY::GET_ENTITY_COORDS(veh, 1);
					ENTITY::SET_ENTITY_COORDS(veh, vehc.x, vehc.y, containerCoords.z + 2.0f, 0, 0, 0, 1);
				}
			}
		}
		else {
			Hash model = GAMEPLAY::GET_HASH_KEY("prop_container_ld2");
			STREAMING::REQUEST_MODEL(model);
			while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
			container = OBJECT::CREATE_OBJECT(model, pos.x, pos.y, pos.z, 1, 1, 0);
			RequestControlOfEnt(container);
			ENTITY::FREEZE_ENTITY_POSITION(container, 1);
			ENTITY::SET_ENTITY_ALPHA(container, 0, 1);
			ENTITY::SET_ENTITY_VISIBLE(container, 0);
		}
	}
	else {
		Object container = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(pos.x, pos.y, pos.z, 4.0, GAMEPLAY::GET_HASH_KEY("prop_container_ld2"), 0, 0, 1);
		if (ENTITY::DOES_ENTITY_EXIST(container)) {
			RequestControlOfEnt(container);
			ENTITY::SET_ENTITY_COORDS(container, 0, 0, -1000.0f, 0, 0, 0, 1);
			WAIT(10);
			ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&container);
			ENTITY::DELETE_ENTITY(&container);
			WATER::_RESET_WAVES_INTENSITY();
		}
	}
}

bool Features::fcbool = false;
void Features::FlyingCarLoop(bool toggle)
{
	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
	{
		int Vehid = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		ENTITY::APPLY_FORCE_TO_ENTITY(Vehid, 1, 0, 0, 20, 0, 0, 0, 1, false, true, true, true, true);
		if (CONTROLS::IS_CONTROL_PRESSED(2, 67) == true) //Forward
		{
			float Speed = ENTITY::GET_ENTITY_SPEED(Vehid) + 0.5;
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(Vehid, 25);

		}

		if ((CONTROLS::IS_CONTROL_PRESSED(2, 196) == true) && (!VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehid))) //Left
		{
			Vector3 Rot = ENTITY::GET_ENTITY_ROTATION(Vehid, 2);
			Rot.z = Rot.z + 1.0;
			ENTITY::SET_ENTITY_ROTATION(Vehid, Rot.x, Rot.y, Rot.z, 2, 1);
		}

		if ((CONTROLS::IS_CONTROL_PRESSED(2, 197) == true) && (!VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(Vehid))) //Right
		{
			Vector3 Rot = ENTITY::GET_ENTITY_ROTATION(Vehid, 2);
			Rot.z = Rot.z - 1.0;
			ENTITY::SET_ENTITY_ROTATION(Vehid, Rot.x, Rot.y, Rot.z, 2, 1);
		}
	}
}

bool Features::Drift = false;
void Features::DriftMode(bool toggle)
{
	if (toggle == true)
	{
		VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
	}
	else {
		VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0);
	}

}


int Features::Horndelay = 50;

bool Features::boostbool = false;
void Features::carboost(bool toggle) {
	if (PLAYER::IS_PLAYER_PRESSING_HORN(PLAYER::PLAYER_ID()))
	{
		UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("~g~Press E!");
		UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "~w~Apollo", "~w~Moon", 1, "UnlockAll", 9);
		UI::_DRAW_NOTIFICATION(FALSE, FALSE);

		Vehicle Veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), false);
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Veh);
		GRAPHICS::_START_SCREEN_EFFECT("RaceTurbo", 0, 0);
		if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Veh))
		{
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(Veh, Features::Horndelay);
		}
	}
}


bool Features::Backboost = false;
void Features::backboost(bool toggle) {
	Features::boostbool = false;
	if (PLAYER::IS_PLAYER_PRESSING_HORN(PLAYER::PLAYER_ID()))
	{
		UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("~g~Press E!");
		UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "~w~Apollo", "~w~Moon", 1, "UnlockAll", 9);
		UI::_DRAW_NOTIFICATION(FALSE, FALSE);

		int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		ENTITY::APPLY_FORCE_TO_ENTITY(VehID, 1, 0, -10, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1);
	}
}

void Features::flipup()
{
	VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));
}

void Features::maxvehicle()
{
	Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
	VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
	for (int i = 0; i < 50; i++)
	{
		VEHICLE::SET_VEHICLE_MOD(vehicle, i, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, i) - 1, false);
	}
	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle, "Apollo");
}


int r = 255, g = 0, b = 0;
void RGBFade()
{
	if (r > 0 && b == 0) {
		r--;
		g++;
	}
	if (g > 0 && r == 0) {
		g--;
		b++;
	}
	if (b > 0 && g == 0) {
		r++;
		b--;
	}
}

int Features::stealthDelay4088 = 100;
bool Features::Rneon = false;
void Features::RainbowNeon(bool toggle)
{
	if ((timeGetTime() - Features::TimePD3) > Features::stealthDelay4088)
	{
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		if (RainbowNeon)
		{
			RGBFade();
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			DWORD model = ENTITY::GET_ENTITY_MODEL(veh);

			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
			{
				if (VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(veh, 0) && VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(veh, 1) && VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(veh, 2) && VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(veh, 3))
				{
					VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, r, g, b);
				}
				else
				{
					VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
					VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
					VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
					VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
					VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, r, g, b);
				}
			}
		}
		Features::TimePD5 = timeGetTime();
	}
}

void WheelPTFX(char* streamName, char* PTFXName) {

	uint myVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

	STREAMING::REQUEST_NAMED_PTFX_ASSET(streamName);
	if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(streamName))
	{
		Vector3 pos = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(myVeh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(myVeh, "wheel_lf"));
		GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL(streamName);
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2(PTFXName, pos.x, pos.y, pos.z, 0.f, 0.f, 0.f, Features::carPTFXsize, false, false, false);

		Vector3 pos1 = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(myVeh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(myVeh, "wheel_lr"));
		GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL(streamName);
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2(PTFXName, pos1.x, pos1.y, pos1.z, 0.f, 0.f, 0.f, Features::carPTFXsize, false, false, false);

		Vector3 pos2 = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(myVeh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(myVeh, "wheel_rf"));
		GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL(streamName);
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2(PTFXName, pos2.x, pos2.y, pos2.z, 0.f, 0.f, 0.f, Features::carPTFXsize, false, false, false);

		Vector3 pos3 = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(myVeh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(myVeh, "wheel_rr"));
		GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL(streamName);
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2(PTFXName, pos3.x, pos3.y, pos3.z, 0.f, 0.f, 0.f, Features::carPTFXsize, false, false, false);
	}
	else STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
}
bool Features::CarClownLoop;
bool Features::Carfireworkloop;
bool Features::Caralien1;
bool Features::Caralien2;
bool Features::Carelectric;
bool Features::CarLightning;
float Features::carPTFXsize = 0.4;



DWORD featureWeaponVehShootLastTime = 0;


bool Features::RLaser = false;
void Features::Rlaser(bool toggle)
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("~g~press Lshift!");
	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "~w~Apollo", "~w~Moon", 1, "UnlockAll", 9);
	UI::_DRAW_NOTIFICATION(FALSE, FALSE);

	bool bSelect = GetAsyncKeyState(0xA0); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_ENEMY_LASER ");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, 0);
			while (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
				WAIT(0);
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		featureWeaponVehShootLastTime = GetTickCount();

	}
}

bool Features::Laser1 = false;
void Features::laser1(bool toggle)
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("~g~press LShift!");
	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "~w~Apollo", "~w~Moon", 1, "UnlockAll", 9);
	UI::_DRAW_NOTIFICATION(FALSE, FALSE);

	bool bSelect = GetAsyncKeyState(0xA0); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_PLAYER_LASER");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, 0);
			while (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
				WAIT(0);
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		featureWeaponVehShootLastTime = GetTickCount();

	}
}

bool Features::ShootMini = false;
void Features::ShootMiniGun(bool toggle)
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("~g~press LShift!");
	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "~w~Apollo", "~w~Moon", 1, "UnlockAll", 9);
	UI::_DRAW_NOTIFICATION(FALSE, FALSE);

	bool bSelect = GetAsyncKeyState(0xA0); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_PLAYER_BULLET");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, 0);
			while (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
				WAIT(0);
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		featureWeaponVehShootLastTime = GetTickCount();

	}
}

bool Features::ShootFlare = false;
void Features::Shootflare(bool toggle)
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("~g~press LShift!");
	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "~w~Apollo", "~w~Moon", 1, "UnlockAll", 9);
	UI::_DRAW_NOTIFICATION(FALSE, FALSE);

	bool bSelect = GetAsyncKeyState(0xA0); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_FLARE");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, 0);
			while (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
				WAIT(0);
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		featureWeaponVehShootLastTime = GetTickCount();

	}
}

bool Features::ShootBall = false;
void Features::ShootBalls(bool toggle)
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("~g~press LShift!");
	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "~w~Apollo", "~w~Moon", 1, "UnlockAll", 9);
	UI::_DRAW_NOTIFICATION(FALSE, FALSE);

	bool bSelect = GetAsyncKeyState(0xA0); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_BALL");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, 0);
			while (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
				WAIT(0);
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		featureWeaponVehShootLastTime = GetTickCount();

	}
}

bool Features::ShootTankR = false;
void Features::ShootTankRounds(bool toggle)
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("~g~press LShift!");
	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "~w~Apollo", "~w~Moon", 1, "UnlockAll", 9);
	UI::_DRAW_NOTIFICATION(FALSE, FALSE);

	bool bSelect = GetAsyncKeyState(0xA0); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("VEHICLE_WEAPON_TANK");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, 0);
			while (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
				WAIT(0);
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		featureWeaponVehShootLastTime = GetTickCount();

	}
}


bool Features::ShootT = false;
void Features::ShootTanks(bool toggle)
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("~g~press +LShift!");
	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "~w~Apollo", "~w~Moon", 1, "UnlockAll", 9);
	UI::_DRAW_NOTIFICATION(FALSE, FALSE);

	bool bSelect = GetAsyncKeyState(0xA0); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_FIREWORK");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, 0);
			while (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
				WAIT(0);
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		featureWeaponVehShootLastTime = GetTickCount();

	}
}

bool Features::ShootR = false;
void Features::ShootRocket(bool toggle)
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("~g~press LShit!");
	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "~w~Apollo", "~w~Moon", 1, "UnlockAll", 9);
	UI::_DRAW_NOTIFICATION(FALSE, FALSE);

	bool bSelect = GetAsyncKeyState(0xA0); // num plus
	if (bSelect && featureWeaponVehShootLastTime + 150 < GetTickCount() &&
		PLAYER::IS_PLAYER_CONTROL_ON(player) && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &v0, &v1);

		Hash weaponAssetRocket = GAMEPLAY::GET_HASH_KEY("WEAPON_VEHICLE_ROCKET");
		if (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
		{
			WEAPON::REQUEST_WEAPON_ASSET(weaponAssetRocket, 31, 0);
			while (!WEAPON::HAS_WEAPON_ASSET_LOADED(weaponAssetRocket))
				WAIT(0);
		}

		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -(v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, (v1.x + 0.25f), v1.y + 1.25f, 0.1);
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, -v1.x, v1.y + 100.0f, 0.1f);
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, v1.x, v1.y + 100.0f, 0.1f);

		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords0from.x, coords0from.y, coords0from.z,
			coords0to.x, coords0to.y, coords0to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords1from.x, coords1from.y, coords1from.z,
			coords1to.x, coords1to.y, coords1to.z,
			250, 1, weaponAssetRocket, playerPed, 1, 0, -1.0);
		featureWeaponVehShootLastTime = GetTickCount();

	}

}

int Features::Online::tpplayer = 0;
void Features::Online::TeleportToPlayer(Player player) {

	Entity handle;
	Vector3 coords = ENTITY::GET_ENTITY_COORDS(player, false);
	PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) ? handle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) : handle = PLAYER::PLAYER_PED_ID();
	ENTITY::SET_ENTITY_COORDS(handle, coords.x, coords.y, coords.z, false, false, false, false);
}


bool Features::bypassChatBool = false;
void Features::bypassChat(bool t) {
	NETWORK::NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS(PLAYER::PLAYER_PED_ID(), true);
	NETWORK::NETWORK_OVERRIDE_CHAT_RESTRICTIONS(PLAYER::PLAYER_PED_ID(), true);
}


int Features::volume = 100;
void Features::setVolume() {
	GRAPHICS::SET_TV_VOLUME((float)volume);
}

bool Features::thunderbool = false;
void Features::thunder(bool t) {
	GAMEPLAY::_CREATE_LIGHTNING_THUNDER();
}


bool Features::moongrav = false;
void Features::MoonGrav(bool t)
{
	if (t == true)
	{
		GAMEPLAY::SET_GRAVITY_LEVEL(2);
	}
	else
	{
		GAMEPLAY::SET_GRAVITY_LEVEL(0);
	}
}

bool Features::footstepBool = false;
void Features::footsteps() {
	GRAPHICS::_SET_FORCE_PED_FOOTSTEPS_TRACKS(true);
	GRAPHICS::_SET_FORCE_VEHICLE_TRAILS(true);
}

void Features::deleteTrain() {
	VEHICLE::DELETE_TRAIN(&Features::train);
	Features::trainSpeed = 0.0f;
	Features::inTrain = false;
}


Object mapMods[250];
int mapModsIndex = 0;
void Features::PlaceObjectByHash(Hash hash, float x, float y, float z, float pitch, float roll, float yaw, float heading, int id)
{
	if (STREAMING::IS_MODEL_IN_CDIMAGE(hash)) {
		STREAMING::REQUEST_MODEL(hash);
		while (!STREAMING::HAS_MODEL_LOADED(hash)) WAIT(0);
		Object obj = OBJECT::CREATE_OBJECT_NO_OFFSET(hash, x, y, z, 1, 0, 0);
		//SET_ENTITY_HEADING(obj, heading);
		//SET_ENTITY_ROTATION(obj, pitch, roll, yaw, 2, 1);
		ENTITY::SET_ENTITY_LOD_DIST(obj, 696969);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(obj);
		ENTITY::FREEZE_ENTITY_POSITION(obj, 1);
		ENTITY::SET_ENTITY_ROTATION(obj, pitch, roll, yaw, 0, 1);
		mapMods[mapModsIndex] = obj;
		if (mapModsIndex <= 250) mapModsIndex++;
		WAIT(25);
	}
}

void toggleIPL(char* ipl, bool b00l) {
	if (b00l) {
		while (!STREAMING::IS_IPL_ACTIVE(ipl)) {
			STREAMING::REQUEST_IPL(ipl);
			WAIT(0);
		}
	}
	else {
		while (STREAMING::IS_IPL_ACTIVE(ipl)) {
			STREAMING::REMOVE_IPL(ipl);
			WAIT(0);
		}
	}
}

void toggleCargoShip(bool b00l) {
	toggleIPL("cargoship", b00l);
	
}

void toggleTrainCrashBridge(bool b00l) {
	toggleIPL("canyonriver01", b00l);
	toggleIPL("railing_start", b00l);
	toggleIPL("canyonriver01_traincrash", false);
	toggleIPL("railing_end", false);
}

void toggleTrainCrashBridgeExtra1(bool b00l) {
	toggleIPL("canyonriver01_traincrash", b00l);
	toggleIPL("railing_end", b00l);
}

void toggleCluckingBell(bool b00l) {
	toggleIPL("CS1_02_cf_offmission", true);
	toggleIPL("CS1_02_cf_onmission1", b00l);
	toggleIPL("CS1_02_cf_onmission2", b00l);
	toggleIPL("CS1_02_cf_onmission3", b00l);
	toggleIPL("CS1_02_cf_onmission4", b00l);
	toggleIPL("CS2_06_TriAf02", b00l);
}

void toggleCluckingBellExtra1(bool b00l) {
	toggleIPL("CS1_02_cf_offmission", b00l);
}

void toggleBrokenStiltHouse(bool b00l) {
	toggleIPL("DES_StiltHouse_imapstart", b00l);
	toggleIPL("DES_StiltHouse_imapend", !b00l);
	toggleIPL("des_stilthouse_rebuild", !b00l);
}

void toggleCarrier(bool b00l) {
	toggleIPL("hei_carrier", b00l);
	toggleIPL("hei_carrier_DistantLights", b00l);
	toggleIPL("hei_Carrier_int1", b00l);
	toggleIPL("hei_Carrier_int2", b00l);
	toggleIPL("hei_Carrier_int3", b00l);
	toggleIPL("hei_Carrier_int4", b00l);
	toggleIPL("hei_Carrier_int5", b00l);
	toggleIPL("hei_Carrier_int6", b00l);
	toggleIPL("hei_carrier_LODLights", b00l);
}

void toggleYacht(bool b00l) {
	toggleIPL("hei_yacht_heist", b00l);
	toggleIPL("hei_yacht_heist_Bar", b00l);
	toggleIPL("hei_yacht_heist_Bedrm", b00l);
	toggleIPL("hei_yacht_heist_Bridge", b00l);
	toggleIPL("hei_yacht_heist_DistantLights", b00l);
	toggleIPL("hei_yacht_heist_enginrm", b00l);
	toggleIPL("hei_yacht_heist_LODLights", b00l);
	toggleIPL("hei_yacht_heist_Lounge", b00l);
}

void toggleLestersFactory(bool b00l) {
	toggleIPL("id2_14_during_door", b00l);
	toggleIPL("id2_14_on_fire ", false);
}

void toggleLestersFactoryExtra1(bool b00l) {
	toggleIPL("id2_14_on_fire", b00l);
}

void toggleNorthYankton(bool b00l) {
	toggleIPL("prologue01", b00l);
	toggleIPL("Prologue01c", b00l);
	toggleIPL("Prologue01d", b00l);
	toggleIPL("Prologue01e", b00l);
	toggleIPL("Prologue01f", b00l);
	toggleIPL("Prologue01g", b00l);
	toggleIPL("prologue01h", b00l);
	toggleIPL("prologue01i", b00l);
	toggleIPL("prologue01j", b00l);
	toggleIPL("prologue01k", b00l);
	toggleIPL("prologue01z", b00l);
	toggleIPL("prologue02", b00l);
	toggleIPL("prologue03", b00l);
	toggleIPL("prologue03b", b00l);
	toggleIPL("prologue03_grv_cov", b00l);
	toggleIPL("prologue03_grv_dug", b00l);
	toggleIPL("prologue03_grv_fun", b00l);
	toggleIPL("prologue04", b00l);
	toggleIPL("prologue04b", b00l);
	toggleIPL("prologue04_cover", b00l);
	toggleIPL("prologue05", b00l);
	toggleIPL("prologue05b", b00l);
	toggleIPL("prologue06", b00l);
	toggleIPL("prologue06b", b00l);
	toggleIPL("prologue06_int", b00l);
	toggleIPL("prologuerd", b00l);
	toggleIPL("prologuerdb", b00l);
	toggleIPL("prologue_DistantLights", b00l);
	toggleIPL("prologue_grv_torch", b00l);
	toggleIPL("prologue_m2_door", b00l);
	toggleIPL("prologue_LODLights", b00l);
	toggleIPL("DES_ProTree_start", b00l);
	toggleIPL("DES_ProTree_start_lod", b00l);
}

void toggleHospital(bool b00l) {
	toggleIPL("RC12B_HospitalInterior", b00l);
	toggleIPL("RC12B_Destroyed", b00l);
}

void toggleLifeInvader(bool b00l) {
	toggleIPL("facelobby", b00l);
	toggleIPL("facelobbyfake", !b00l);
}

void toggleJewelryStore(bool b00l) {
	toggleIPL("jewel2fake", b00l);
	toggleIPL("post_heist_unload", b00l);
	toggleIPL("bh1_16_refurb", b00l);
}

void toggleMorgue(bool b00l) {
	toggleIPL("Coroner_Int_on", b00l);
	toggleIPL("Coroner_Int_off", !b00l);
	toggleIPL("coronertrash", false);
}

void toggleMorgueExtra1(bool b00l) {
	toggleIPL("coronertrash", b00l);
}

void toggleFibLobby(bool b00l) {
	toggleIPL("FIBlobby", b00l);
	toggleIPL("FIBlobbyfake", !b00l);
}

void togglePlaneCrash(bool b00l) {
	static int planeNetID;
	Entity shamalCrash = NETWORK::NET_TO_ENT(planeNetID);

	toggleIPL("Plane_crash_trench", b00l);

	if (b00l && !ENTITY::DOES_ENTITY_EXIST(shamalCrash)) {
		shamalCrash = OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY("prop_shamal_crash"), 2808.387f, 4795.484f, 46.2104f, true, true, true);
		planeNetID = NETWORK::VEH_TO_NET(shamalCrash);
		ENTITY::SET_ENTITY_ROTATION(shamalCrash, -1.2048f, -6.1718f, -12.3839f, 2, TRUE);
	}
	else {
		ENTITY::SET_ENTITY_COORDS(shamalCrash, 6400, 6400, 0, FALSE, FALSE, FALSE, FALSE);
		ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&shamalCrash);
		shamalCrash = 0;
	}
}

void toggleUFO(bool b00l) {
	toggleIPL("ufo", b00l);
}

void toggleBahamaMamas(bool b00l) {
	toggleIPL("v_bahama", b00l);
}

void toggleStadium(bool b00l) {
	toggleIPL("sp1_10_fake_interior", !b00l);
	toggleIPL("sp1_10_fake_interior_lod", !b00l);
	toggleIPL("sp1_10_real_interior", b00l);
	toggleIPL("sp1_10_real_interior_lod", b00l);
}

void togglePsychOffice(bool b00l) {
	toggleIPL("v_psycheoffice", b00l);
}

void toggleTequllala(bool b00l) {
	toggleIPL("v_rockclub", b00l);
}

void toggleShowRoom(bool b00l) {
	toggleIPL("v_carshowroom", b00l);
	toggleIPL("shutter_open", false);
	toggleIPL("shutter_closed", true);
	toggleIPL("shr_int", b00l);
	toggleIPL("csr_inMission", b00l);
	toggleIPL("fakeint", !b00l);
}

void toggleShowRoomExtra1(bool b00l) {
	toggleIPL("shutter_open", b00l);
	toggleIPL("shutter_closed", !b00l);
}

void toggleUnionDeposity(bool b00l) {
	toggleIPL("FINBANK", b00l);
	toggleIPL("DT1_03_Shutter", false);
}

void toggleUnionDeposityExtra1(bool b00l) {
	toggleIPL("DT1_03_Shutter", b00l);
}

void SetDate(int d, int m, int y)
{
	std::string dayStr;
	if (std::to_string(d).find("1") == std::to_string(d).length() && d != 11) {
		dayStr = std::to_string(d) + "st";
	}
	else if (std::to_string(d).find("2") == std::to_string(d).length() && d != 12) {
		dayStr = std::to_string(d) + "nd";
	}
	else if (std::to_string(d).find("3") == std::to_string(d).length() && d != 13) {
		dayStr = std::to_string(d) + "rd";
	}
	else {
		dayStr = std::to_string(d) + "th";
	}

	std::string monthStr = getMonthStr(m);

	TIME::SET_CLOCK_DATE(d, m, y);
	//UI::MessageAtBottomScreen(Menu::StringToChar("The date has been set to the " + dayStr + " of " + monthStr + " " + std::to_string(y)), 2000);
}


int frozenTimeH = 0;
int frozenTimeM = 0;
int frozenTimeS = 0;

static int getSystemSeconds()
{
	time_t now = time(0);
	tm* ltm = localtime(&now);

	return ltm->tm_sec;
}

static int getSystemMinutes()
{
	time_t now = time(0);
	tm* ltm = localtime(&now);

	return ltm->tm_min;
}

static int getSystemHour()
{
	time_t now = time(0);
	tm* ltm = localtime(&now);

	return ltm->tm_hour;
}

static int getSystemDay()
{
	time_t now = time(0);
	tm* ltm = localtime(&now);

	return ltm->tm_mday;
}

static int getSystemMonth()
{
	time_t now = time(0);
	tm* ltm = localtime(&now);

	return ltm->tm_mon;
}

static int getSystemYear()
{
	time_t now = time(0);
	tm* ltm = localtime(&now);

	return ltm->tm_year;
}

void SetWeather(char* weather)
{
	GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST(weather);
	//UI::MessageAtBottomScreen(Menu::StringToChar("Weather has been set to " + (std::string)weather), 2000);
}

void SetTime(int h, int m, int s)
{
	NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(h, m, s);
	//UI::MessageAtBottomScreen(Menu::StringToChar("The time has been set to " + std::to_string(h) + ":" + std::to_string(m) + ":" + std::to_string(s)), 2000);
}

bool freezeTime = false;
void FreezeTimeLoop()
{
	SetTime(frozenTimeH, frozenTimeM, frozenTimeS);
}

bool synctime = false;
void SyncSystemTimeLoop()
{
	SetTime(getSystemHour(), getSystemMinutes(), getSystemSeconds());
}

int Features::handy = -1;
void Features::setPhone(int index) {
	switch (index) {
	case -1:
		//nothing :P
		break;
	case 0:
		MOBILE::CREATE_MOBILE_PHONE(0);
		break;
	case 1:
		MOBILE::CREATE_MOBILE_PHONE(1);
		break;
	case 2:
		MOBILE::CREATE_MOBILE_PHONE(2);
		break;
	case 3:
		MOBILE::CREATE_MOBILE_PHONE(4);
		break;
	}
}

bool Features::screenfx = false;
void Features::ScreenFX(bool toggle, char* effect) {
	if (toggle) {
		GRAPHICS::_START_SCREEN_EFFECT(effect, 0, true);
	}
	else {
		GRAPHICS::_STOP_SCREEN_EFFECT(effect);
	}
}

void Features::skipTutorial() {
	if (NETWORK::NETWORK_IS_IN_TUTORIAL_SESSION()) {
		NETWORK::NETWORK_END_TUTORIAL_SESSION();
	}
}

bool Features::HudBool = false;
void Features::HideHud() {
	UI::HIDE_HUD_AND_RADAR_THIS_FRAME();
}

bool Features::unlimitedorbitalcannon = false;
void Features::UnlimitedORbitalCannon(bool t)
{
	if (t == true)
	{
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ORBITAL_CANNON_COOLDOWN"), 0, 0);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_ORBITAL_CANNON_COOLDOWN"), 0, 0);
	}
}

bool Features::mobRadio = false;
void Features::mobileRadio(bool t) {
	int station = AUDIO::GET_PLAYER_RADIO_STATION_INDEX();
	AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(t);
	AUDIO::SET_MOBILE_PHONE_RADIO_STATE(1);
	AUDIO::SET_RADIO_TO_STATION_INDEX(station);
}

bool Features::drunk;
void Features::Drunk(bool t)
{
	AUDIO::SET_PED_IS_DRUNK(PLAYER::PLAYER_PED_ID(), t);
}


bool Features::thermalvisionbool = false;
void Features::thermalvision(bool t) {
	if (t) {
		GRAPHICS::SET_SEETHROUGH(true);
	}
	else {
		GRAPHICS::SET_SEETHROUGH(false);
	}
}




bool Features::nightvisionbool = false;
void Features::nightvision(bool t) {
	if (t) {
		GRAPHICS::SET_NIGHTVISION(true);
	}
	else {
		GRAPHICS::SET_NIGHTVISION(false);
	}
}


void setupdraw()
{
	UI::SET_TEXT_FONT(0);
	UI::SET_TEXT_SCALE(0.4f, 0.4f);
	UI::SET_TEXT_COLOUR(255, 255, 255, 255);
	UI::SET_TEXT_WRAP(0.0f, 1.0f);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::SET_TEXT_OUTLINE();
}

void drawstring(char* text, float X, float Y)
{
	UI::_SET_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	UI::_DRAW_TEXT(X, Y);
}
bool Features::DisplayFPS = false;
void Features::fDisplayFPS(bool toggle)
{
	float LastFrameTime = GAMEPLAY::GET_FRAME_TIME();
	int getFPS = (1.0f / LastFrameTime);
	char FPStext[60];
	snprintf(FPStext, sizeof(FPStext), "FPS : %d", getFPS);
	setupdraw();
	UI::SET_TEXT_FONT(6);
	UI::SET_TEXT_SCALE(0.5f, 0.5f);
	UI::SET_TEXT_COLOUR(145, 0, 255, 255);
	UI::SET_TEXT_CENTRE(0);
	drawstring(FPStext, 0
}


float Features::get_stat(Hash stat_hash) {
	float stat;
	STATS::STAT_GET_FLOAT(stat_hash, &stat, 0);
	return stat;
}

bool Features::stealthBool = false;
int Features::stealthAmount = 10000000;
bool Features::toBank = true;
int Features::stealthDelay = 600;
bool Features::stealthLooped = true;
void Features::stealthLoop(bool t) {
	if ((timeGetTime() - Features::TimePD10) > Features::stealthDelay) {
		if (Features::stealthAmount < 10000001) {
			globalHandle(0x41104E + 1).As <int>() = INT_MAX - 1;
			globalHandle(0x41104E + 7).As <int>() = INT_MAX;
			globalHandle(0x41104E + 6).As <int>() = 0;
			globalHandle(0x41104E + 5).As <int>() = 0;
			globalHandle(0x41104E + 3).As <int>() = 312105838;
			globalHandle(0x41104E + 2).As <int>() = Features::stealthAmount;
			globalHandle(0x41104E).As <int>() = Features::toBank;

			//optional
			int iVar0;
			int iVar1;
			STATS::STAT_GET_INT($("MPPLY_LAST_MP_CHAR"), &iVar0, 1);
			STATS::STAT_GET_INT($("MP" + std::to_string(iVar0) + "_MONEY_EARN_JOBS"), &iVar1, -1);
			STATS::STAT_SET_INT($("MP" + std::to_string(iVar0) + "_MONEY_EARN_JOBS"), iVar1 + Features::stealthAmount, Features::toBank);
			Features::removee ? Features::stealthMoneyCounter -= Features::stealthAmount : Features::stealthMoneyCounter += Features::stealthAmount;
		}
		else {
			globalHandle(0x41104E + 1).As <int>() = INT_MAX - 1;
			globalHandle(0x41104E + 7).As <int>() = INT_MAX;
			globalHandle(0x41104E + 6).As <int>() = 0;
			globalHandle(0x41104E + 5).As <int>() = 0;
			globalHandle(0x41104E + 3).As <int>() = 312105838;
			globalHandle(0x41104E + 2).As <int>() = Features::stealthAmount;
			globalHandle(0x41104E).As <int>() = Features::toBank;

			//optional
			int iVar0 = 312105838;
			int iVar1;
			STATS::STAT_GET_INT($("MPPLY_LAST_MP_CHAR"), &iVar0, 1);
			STATS::STAT_GET_INT($("MP" + std::to_string(iVar0) + "_MONEY_EARN_JOBS"), &iVar1, -1);
			STATS::STAT_SET_INT($("MP" + std::to_string(iVar0) + "_MONEY_EARN_JOBS"), iVar1 + Features::stealthAmount, Features::toBank);

			Any var0 = 312105838;
			UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&var0, 1474183246, Features::removee ? -1359375127 : -1586170317, Features::removee ? 537254313 : 1445302971, Features::stealthAmount, Features::toBank ? 4 : 1);
			UNK3::_NETWORK_SHOP_CHECKOUT_START(var0);
			Features::removee ? Features::stealthMoneyCounter -= Features::stealthAmount : Features::stealthMoneyCounter += Features::stealthAmount;
		}
		Features::TimePD10 = timeGetTime();
	}
}

bool Features::removee = false;
void Features::removeMoney(int amount) {
	Any aVar0 = INT_MAX;
	UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&aVar0, 1474183246, -1359375127, 537254313, amount, Features::toBank ? 4 : 1);
	UNK3::_NETWORK_SHOP_CHECKOUT_START(aVar0);
}


int Features::bankAmount = 10000000;

void Features::deposit(int amount) { //In bank
	Any var0 = 312105838;
	/*UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&var0, 1474183246, -1586170317, 1445302971, amount, 4);
	UNK3::_NETWORK_SHOP_CHECKOUT_START(var0);
	UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&var0, 1474183246, -1359375127, 537254313, amount, 1);
	UNK3::_NETWORK_SHOP_CHECKOUT_START(var0);*/
	int iVar0;
	STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_LAST_MP_CHAR"), &iVar0, 1);
	UNK3::_NETWORK_TRANSFER_WALLET_TO_BANK(iVar0, amount);
	UNK3::_NETWORK_SHOP_CASH_TRANSFER_SET_TELEMETRY_NONCE_SEED();
}

void Features::withdraw(int amount) { //In wallet
	int iVar0;
	STATS::STAT_GET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_LAST_MP_CHAR"), &iVar0, 1);
	UNK3::_NETWORK_TRANSFER_BANK_TO_WALLET(iVar0, amount);
	UNK3::_NETWORK_SHOP_CASH_TRANSFER_SET_TELEMETRY_NONCE_SEED();
}

bool Features::rchar = false;


int Features::Levels[8000] = { 0, 800, 2100, 56400, 63000, 69900, 77100, 84700, 92500, 100700, 109200, 118000, 127100, 136500, 146200 };


void Features::SetRank(int rpvalue)
{
	if (rpvalue > 8000)
	{
		rpvalue = 8000;
	}

	if (rpvalue < 0)
	{
		rpvalue = 1;
	}

	//STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_XP_FM"), Features::Levels[rpvalue], 0);
	//STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_XP_FM"), Features::Levels[rpvalue], 0);
	STATS::STAT_SET_INT($("MP0_CHAR_SET_RP_GIFT_ADMIN"), Features::Levels[rpvalue - 1], 1);
	STATS::STAT_SET_INT($("MP1_CHAR_SET_RP_GIFT_ADMIN"), Features::Levels[rpvalue - 1], 1);

}


void Features::setColor(Vehicle veh, int prim, int sec) {
	VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh);
	VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh);
	VEHICLE::SET_VEHICLE_COLOURS(veh, prim, sec);
}

void Features::MaxUpgrade(Vehicle veh)
{
	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

	VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, VehicleWheelTypeHighEnd);

	for (int i = 60; i > -1; i--)
	{
		if (i > MOD_ARMOR && i < MOD_FRONTWHEELS)
			VEHICLE::TOGGLE_VEHICLE_MOD(veh, i, TRUE);
		else
			VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1, TRUE);
	}

	VEHICLE::SET_VEHICLE_MOD(veh, MOD_HORNS, 1, FALSE);

	for (int i = 3; i > -1; i--)
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, i, TRUE);

	VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, 0, 0);
	VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, Menu::Settings::titleText.r, Menu::Settings::titleText.g, Menu::Settings::titleText.b);
	VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, VehicleWindowTintLimo);
	VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, Menu::Settings::titleText.r, Menu::Settings::titleText.g, Menu::Settings::titleText.b);
	VEHICLE::SET_VEHICLE_COLOURS(veh, VehicleColorMettalicBlackBlue, VehicleColorMettalicBlackBlue);
	VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, Menu::Settings::titleRect.r, Menu::Settings::titleRect.g, Menu::Settings::titleRect.b);
	VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, Menu::Settings::titleText.r, Menu::Settings::titleText.g, Menu::Settings::titleText.b);

	for (int i = 12; i > -1; i--)
	{
		if (VEHICLE::DOES_EXTRA_EXIST(veh, i))
			VEHICLE::SET_VEHICLE_EXTRA(veh, i, FALSE);
	}
}

bool Features::HasModType(Vehicle veh, int mod)
{
	int tmp = VEHICLE::GET_NUM_VEHICLE_MODS(veh, mod);
	return tmp > 0;
}

bool Features::HasMod(Vehicle veh, int modType, int mod)
{

	return VEHICLE::GET_VEHICLE_MOD(veh, modType) == mod;
}

int MoneyTicker22 = GetCurrentTime();
bool Features::Online::moneydropbool[35] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
int MoneyTicker23 = GetCurrentTime();
void Features::Online::moneydrop(Player player) {
	if (static_cast<int>(GetCurrentTime()) - MoneyTicker22 >= 300)
	{

		int amount = 2500;
		int CashHash = -1666779307;  // prop_paper_bag_small = -1803909274
		int PickupHash = GAMEPLAY::GET_HASH_KEY("PICKUP_MONEY_WALLET");
		Ped iPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		STREAMING::REQUEST_MODEL(CashHash);
		if (!STREAMING::HAS_MODEL_LOADED(CashHash)) {
			SYSTEM::WAIT(0);
		}
		else {
			Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(iPed, FALSE);
			OBJECT::CREATE_AMBIENT_PICKUP(PickupHash, playerPosition.x, playerPosition.y, playerPosition.z + 0.5f, 0, amount, CashHash, FALSE, TRUE);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(CashHash);
		}

		MoneyTicker22 = GetCurrentTime();

	}
}



long long Features::Online::droppedMoneyCounter = 0;
int Features::Online::MoneyItem = 0;

void Features::Online::DropWeapon(Hash weapon, Vector3 coords)
{
	WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), weapon, 9999, 1);
}

bool Features::Online::customDropBool[35] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
int Features::Online::customDropDelay = 400;
int Features::Online::customDropAmount = 2500;
int Features::Online::customDropMode = 0;
bool Features::Online::customDropBool2 = false;

int Features::Online::customHeight = 0;
bool Features::Online::customFakedrop = false;
bool Features::Online::customRandom = false;

int Features::Online::randomMoney() {
	int rnd = rndInt(1, 2500);
	Features::Online::customDropAmount = rnd;
	return rnd;
}

void Features::Online::customFakedropp() {
	Features::Online::customDropAmount = 0;
}

bool fx_gun1 = false;
bool fx_gun2 = false;
bool fx_gun3 = false;
bool fx_gun4 = false;
bool fx_gun5 = false;
bool fx_gun6 = false;
bool fx_gun7 = false;
bool fx_gun8 = false;
bool fx_gun9 = false;

void PTFXgun(char* PTFX_LOADED, char* FX_LOOPED)
{
	if (is_ped_shooting(PLAYER::PLAYER_PED_ID())) {
		STREAMING::REQUEST_NAMED_PTFX_ASSET(PTFX_LOADED);
		while (!STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(PTFX_LOADED)) WAIT(0);

		Entity pWeapon = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID());
		Vector3 v0, v1;
		GAMEPLAY::GET_MODEL_DIMENSIONS(WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID()), &v0, &v1);

		GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL(PTFX_LOADED);
		GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_ENTITY_2(FX_LOOPED, pWeapon, (v0.x - v1.x) / 2.0f + 0.7f, 0.f, 0.f, 0.f, 180.f, 0.f, 1.f, 1, 1, 1);
	}

}




void RequestControl(Entity input)
{
	NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(input);

	int tick = 0;
	while (tick <= 50)
	{
		if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(input))
			WAIT(0);
		else
			return;
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(input);
		tick++;
	}
}

PlayerData players[32];
Player selfPlayer;

void UpdatePlayers()
{
	for (int i = 32; i--;)
	{
		if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)))
		{
			players[i].playing = true;
			players[i].ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
			players[i].name = PLAYER::GET_PLAYER_NAME(i);
			NETWORK::NETWORK_HANDLE_FROM_PLAYER(i, &*players[i].netHandle, 13);
			players[i].alive = !ENTITY::IS_ENTITY_DEAD(players[i].ped);
			players[i].coords = ENTITY::GET_ENTITY_COORDS(players[i].ped, players[i].alive);
			players[i].male = PED::IS_PED_MALE(players[i].ped);
			players[i].veh = PED::GET_VEHICLE_PED_IS_IN(players[i].ped, FALSE);
			players[i].inVehicle = PED::IS_PED_IN_ANY_VEHICLE(players[i].ped, FALSE);
			players[i].heading = ENTITY::GET_ENTITY_HEADING(players[i].ped);
			players[i].group = PED::GET_PED_GROUP_INDEX(players[i].ped);
		}
		else
			players[i].playing = false;
	}
	selfPlayer = PLAYER::PLAYER_ID();
}


Hash propGunModel;
int GetAimAngle(Player player)
{
	Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

	Vector3 lHand = PED::GET_PED_BONE_COORDS(playerPed, SKEL_L_Hand, 0.f, 0.f, 0.f);
	Vector3 lShoulder = PED::GET_PED_BONE_COORDS(playerPed, SKEL_L_Clavicle, 0.f, 0.f, 0.f);
	Vector3 MiddleLine = { lHand.x, 0, lHand.y, 0, lShoulder.z, 0 };

	float SZ = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(lShoulder.x, lShoulder.y, lShoulder.z, lHand.x, lHand.y, lHand.z, TRUE);
	float AZ = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(MiddleLine.x, MiddleLine.y, MiddleLine.z, lShoulder.x, lShoulder.y, lShoulder.z, FALSE);

	float tmp = AZ / SZ;

	int angle = (int)floor(RADTODEG(acosf(tmp)));

	if (lHand.z < lShoulder.z)
		angle = -(angle);

	return angle;
}

Vector3 GetForwardPos(Vector3 basecoords, float angle, float heading, float distance)
{

	float tZ = angle * 0.0174532924F;
	float tX = heading * 0.0174532924F;
	float absX = abs(cos(tX));

	return{ basecoords.x + (-sin(tZ) * absX) * distance, 0,
		basecoords.y + (cos(tZ) * absX) * distance, 0,
		basecoords.z + (sin(tX)) * distance, 0 };
}

Hash vehicleGunmodel;
bool Features::vehiclegun = false;
void Features::VehicleGun(Player player)
{
	static int tickcount = 0;
	tickcount++;
	if (!STREAMING::HAS_MODEL_LOADED(vehicleGunmodel))
		STREAMING::REQUEST_MODEL(vehicleGunmodel);

	if (is_ped_shooting(players[player].ped) && tickcount >= 15)
	{
		float DistanceFromplayer;
		Vector3 size1, size2;
		GAMEPLAY::GET_MODEL_DIMENSIONS(vehicleGunmodel, &size1, &size2);
		DistanceFromplayer = size2.y * 1.6f;
		Vector3 tmp = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(players[player].ped, 0.f, DistanceFromplayer, 0.f);
		Vector3 startCoords = { tmp.x, 0, tmp.y, 0, GetForwardPos(players[player].coords, (float)floor(GetAimAngle(player)), 0.f, DistanceFromplayer).z, 0 };
		Vector3 endCoords = GetForwardPos(players[player].coords, (float)floor(GetAimAngle(player)), 0, 2000);

		float aimAngle = (float)floor(GetAimAngle(player));

		Vehicle veh = VEHICLE::CREATE_VEHICLE(vehicleGunmodel, startCoords.x, startCoords.y, startCoords.z, players[player].heading, TRUE, TRUE);
		ENTITY::SET_ENTITY_ROTATION(veh, aimAngle, 0.f, players[player].heading, 0, TRUE);
		ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, 0.f, 500.f, endCoords.z + 0.5f, 0.f, 0.f, 0.f, 0, TRUE, FALSE, TRUE, FALSE, TRUE);
		ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&veh);
		tickcount = 0;
	}
}

bool Features::propgun = false;
void Features::PropGun(Player player)
{
	static int tickcount = 0;
	tickcount++;
	if (!STREAMING::HAS_MODEL_LOADED(propGunModel))
		STREAMING::REQUEST_MODEL(propGunModel);

	if (is_ped_shooting(players[player].ped) && tickcount >= 15)
	{
		float DistanceFromplayer;
		Vector3 size1, size2;
		GAMEPLAY::GET_MODEL_DIMENSIONS(propGunModel, &size1, &size2);
		DistanceFromplayer = size2.y * 1.6f;
		Vector3 tmp = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(players[player].ped, 0.f, DistanceFromplayer, 0.f);
		Vector3 startCoords = { tmp.x, 0, tmp.y, 0, GetForwardPos(players[player].coords, (float)floor(GetAimAngle(player)), 0.f, DistanceFromplayer).z, 0 };
		Vector3 endCoords = GetForwardPos(players[player].coords, GetAimAngle(player), 0.f, 500.f);

		float aimAngle = (float)floor(GetAimAngle(player));

		Object obj = OBJECT::CREATE_OBJECT(propGunModel, startCoords.x, startCoords.y, startCoords.z, TRUE, TRUE, TRUE);
		ENTITY::SET_ENTITY_ROTATION(obj, aimAngle, 0.f, players[player].heading, 0, TRUE);
		ENTITY::APPLY_FORCE_TO_ENTITY(obj, 1, 0.f, 500.f, endCoords.z + 0.5f, 0.f, 0.f, 0.f, 0, TRUE, FALSE, TRUE, FALSE, TRUE);
		ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&obj);
		tickcount = 0;
	}
}

bool Features::esper = false;
void Features::esp(Player target)
{
	if (target != PLAYER::PLAYER_ID() && ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target)))
	{
		Vector3 locationOne = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target), false);
		Vector3 locationTwo = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
		GRAPHICS::DRAW_LINE(locationOne.x, locationOne.y, locationOne.z, locationTwo.x, locationTwo.y, locationTwo.z, Features::red, Features::green, Features::blue, 255);
	}
}



bool Features::esp2b = false;
void Features::esp2(Player target)
{
	if (target != PLAYER::PLAYER_PED_ID() && ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target)))
	{
		Vector3 entitylocation = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target), false);
		Vector3 top1world = { entitylocation.x + 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z + .8f, NULL };
		Vector3 top2world = { entitylocation.x - 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z + .8f, NULL };
		Vector3 top3world = { entitylocation.x + 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z + .8f, NULL };
		Vector3 top4world = { entitylocation.x - 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z + .8f, NULL };
		Vector3 bottom1world = { entitylocation.x + 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z - .8f, NULL };
		Vector3 bottom2world = { entitylocation.x - 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z - .8f, NULL };
		Vector3 bottom3world = { entitylocation.x + 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z - .8f, NULL };
		Vector3 bottom4world = { entitylocation.x - 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z - .8f, NULL };

		GRAPHICS::DRAW_LINE(top1world.x, top1world.y, top1world.z, top2world.x, top2world.y, top2world.z, Features::red, Features::green, Features::blue, 255);
		GRAPHICS::DRAW_LINE(top2world.x, top2world.y, top2world.z, top4world.x, top4world.y, top4world.z, Features::red, Features::green, Features::blue, 255);
		GRAPHICS::DRAW_LINE(top4world.x, top4world.y, top4world.z, top3world.x, top3world.y, top3world.z, Features::red, Features::green, Features::blue, 255);
		GRAPHICS::DRAW_LINE(top1world.x, top1world.y, top1world.z, top3world.x, top3world.y, top3world.z, Features::red, Features::green, Features::blue, 255);

		GRAPHICS::DRAW_LINE(bottom1world.x, bottom1world.y, bottom1world.z, bottom2world.x, bottom2world.y, bottom2world.z, Features::red, Features::green, Features::blue, 255);
		GRAPHICS::DRAW_LINE(bottom2world.x, bottom2world.y, bottom2world.z, bottom4world.x, bottom4world.y, bottom4world.z, Features::red, Features::green, Features::blue, 255);
		GRAPHICS::DRAW_LINE(bottom3world.x, bottom3world.y, bottom3world.z, bottom4world.x, bottom4world.y, bottom4world.z, Features::red, Features::green, Features::blue, 255);
		GRAPHICS::DRAW_LINE(bottom3world.x, bottom3world.y, bottom3world.z, bottom1world.x, bottom1world.y, bottom1world.z, Features::red, Features::green, Features::blue, 255);

		GRAPHICS::DRAW_LINE(top1world.x, top1world.y, top1world.z, bottom1world.x, bottom1world.y, bottom1world.z, Features::red, Features::green, Features::blue, 255);
		GRAPHICS::DRAW_LINE(top2world.x, top2world.y, top2world.z, bottom2world.x, bottom2world.y, bottom2world.z, Features::red, Features::green, Features::blue, 255);
		GRAPHICS::DRAW_LINE(top3world.x, top3world.y, top3world.z, bottom3world.x, bottom3world.y, bottom3world.z, Features::red, Features::green, Features::blue, 255);
		GRAPHICS::DRAW_LINE(top4world.x, top4world.y, top4world.z, bottom4world.x, bottom4world.y, bottom4world.z, Features::red, Features::green, Features::blue, 255);
	}
}
bool Features::NameESP = false;
void Features::NameTagESP(bool toggle)
{
	Player playerPed = PLAYER::PLAYER_PED_ID();
	for (int i = 0; i < 32; i++)
	{
		Player playerHandle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
		Vector3 handleCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerHandle, 0, 0, 0);
		Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
		char* Name = PLAYER::GET_PLAYER_NAME(PLAYER::INT_TO_PLAYERINDEX(i));

		if (ENTITY::DOES_ENTITY_EXIST(playerHandle))
		{
			float x1;
			float y1;

			BOOL screenCoords = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(handleCoords.x, handleCoords.y, handleCoords.z, &x1, &y1);

			std::string playerName = PLAYER::GET_PLAYER_NAME(PLAYER::INT_TO_PLAYERINDEX(i));

			std::string nameSetupRed = "~HUD_COLOUR_RED~" + playerName;
			std::string nameSetupGreen = "~HUD_COLOUR_GREEN~" + playerName;

			char* playerInfoRed = new char[nameSetupRed.length() + 1];
			char* playerInfoGreen = new char[nameSetupGreen.length() + 1];

			std::strcpy(playerInfoRed, nameSetupRed.c_str());
			std::strcpy(playerInfoGreen, nameSetupGreen.c_str());

			UI::SET_TEXT_FONT(7);
			UI::SET_TEXT_SCALE(0.0, 0.40);
			UI::SET_TEXT_COLOUR(Features::red, Features::green, Features::blue, 255);
			UI::SET_TEXT_CENTRE(0);
			UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
			UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(playerPed, playerHandle, 17))
			{
				UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(playerInfoGreen);
			}
			else
			{
				UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(playerInfoRed);
			}
			UI::END_TEXT_COMMAND_DISPLAY_TEXT(x1, y1);
			UI::SET_TEXT_OUTLINE();
			UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
		}
	}
}



void Features::TSE(int input, int player) {
	unsigned int Bit = (1 << Features::Online::selectedPlayer);
	uint64_t EvEnT[4] = { input, player, 0, 0 };
	Hooking::trigger_script_event(1, EvEnT, 4, Bit);
}

void Features::TSEall(int input) {
	for (int i = 0; i < 33; i++) {
		
			unsigned int Bit = (1 << i);
			uint64_t EvEnT[4] = { input, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 0, 0 };
			Hooking::trigger_script_event(1, EvEnT, 4, Bit);
		
	}
}



void Features::remoteSpawnVehicle(std::string vehicle, Player p)
{
	int playa = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(p);
	Hash model = GAMEPLAY::GET_HASH_KEY((char*)_strdup(vehicle.c_str()));
	if (STREAMING::IS_MODEL_VALID(model))
	{
		STREAMING::REQUEST_MODEL(model);
		while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);

		float forward = 5.f;
		float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
		float xVector = forward * sin(degToRad(heading)) * -1.f;
		float yVector = forward * cos(degToRad(heading));
		Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coordsOf(playa).x + xVector, coordsOf(playa).y + yVector, coordsOf(playa).z, heading, true, true);

		Vehicle VEHICLE1 = PED::GET_VEHICLE_PED_IS_IN(playa, true);
		Vector3 coords1 = ENTITY::GET_ENTITY_COORDS(VEHICLE1, false);

		RequestControlOfEnt(veh);
		VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true, true);
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
		DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
		auto networkId = NETWORK::VEH_TO_NET(veh);
		ENTITY::_SET_ENTITY_SOMETHING(veh, true);
		if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(veh))
			NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
		
		WAIT(150);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
	}
}
//int Features::customDropAmount = 2500;

bool Features::enableMoney = true;
void Features::remoteTP(int player, int TPid) {
	//TPid = 1 - 115
	unsigned int Bit = (1 << player);
	uint64_t rteleport[9] = { 1481, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), 0, -1, 1, TPid, 0, 0, 0 }; //TODO: fix!
	Hooking::trigger_script_event(1, rteleport, 9, Bit);
}

bool Features::minimenu[35] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

bool Features::mm_godmode = false;
bool Features::mm_spawn = false;
bool Features::mm_money = false;
bool Features::mm_weather = false;
bool Features::mm_explode = false;
bool Features::mm_teleport = false;





bool Features::playerKarma[35] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
void Features::playerKarmaa(Player p) {
	Ped killa = PED::GET_PED_SOURCE_OF_DEATH(p);
	if (killa != NULL && killa != PLAYER::PLAYER_PED_ID() && killa != PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(p)) {
		Vector3 coords = coordsOf(killa);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords.x, coords.y, coords.z + 5, coords.x, coords.y, coords.z, 100, 1, GAMEPLAY::GET_HASH_KEY("WEAPON_AIRSTRIKE_ROCKET"), PLAYER::PLAYER_PED_ID(), 1, 1, 100);
		killa = NULL;
	}
}

void Features::CopyOutfit(Player player)
{
	for (int i = 0; i < 12; i++)
	{
		PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, PED::GET_PED_DRAWABLE_VARIATION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), i), PED::GET_PED_TEXTURE_VARIATION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), i), PED::GET_PED_PALETTE_VARIATION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), i));
		for (int i = 0; i < 2; i++) {
			WAIT(0);
		}
	}
}

long long Features::droppedMoneyCounter = 0;
long long Features::stealthMoneyCounter = 0;
bool Features::showAmount = false;
bool Features::showAmount2 = false;
int Features::danger = -1;
void Features::showDroppedMoney() {
	if (stealthMoneyCounter < 500000001 || droppedMoneyCounter < 2000001) {
		danger = -1;
	}
	else if ((stealthMoneyCounter > 500000000 && droppedMoneyCounter < 1000000001) || (droppedMoneyCounter > 2000000 && droppedMoneyCounter < 4000001)) {
		danger = 0;
	}
	else if (stealthMoneyCounter > 1000000000 || droppedMoneyCounter > 4000000) {
		danger = 1;
	}

	/*if (showAmount && showAmount2) {
		int amount = Features::droppedMoneyCounter + Features::stealthMoneyCounter;
		if (stealthMoneyCounter < 500000001 || droppedMoneyCounter < 2000001) {
			ostringstream droppppppp;
			droppppppp << "~g~Cheated money: " << amount << "$";
			notifyBottom((char*)droppppppp.str().c_str());
		}
		else if ((stealthMoneyCounter > 500000000 && droppedMoneyCounter < 1000000001) || (droppedMoneyCounter > 2000000 && droppedMoneyCounter < 4000001)) {
			ostringstream droppppppp;
			droppppppp << "~y~Cheated money: " << amount << "$";
			notifyBottom((char*)droppppppp.str().c_str());
		}
		else if (stealthMoneyCounter > 1000000000 || droppedMoneyCounter > 4000000) {
			ostringstream droppppppp;
			droppppppp << "~r~Cheated money: " << amount << "$";
			notifyBottom((char*)droppppppp.str().c_str());
		}
	}*/
	else if (showAmount) {

	}
}


int Features::pricustomred;
int Features::pricustomgreen;
int Features::pricustomblue;
int Features::seccustomred;
int Features::seccustomgreen;
int Features::seccustomblue;
bool Features::setcustompricolour;
bool Features::setcustomseccolour;
bool Features::spawnwithblip = false;
void Features::spawn_vehicle(std::string vehicle)
{
	Hash model = GAMEPLAY::GET_HASH_KEY((char*)_strdup(vehicle.c_str()));
	if (STREAMING::IS_MODEL_VALID(model))
	{
		STREAMING::REQUEST_MODEL(model);
		while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
		Vector3 ourCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
		float forward = 5.f;
		float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
		float xVector = forward * sin(degToRad(heading)) * -1.f;
		float yVector = forward * cos(degToRad(heading));
		Vehicle veh = VEHICLE::CREATE_VEHICLE(model, ourCoords.x + xVector, ourCoords.y + yVector, ourCoords.z, heading, true, true);
		//test();
		Vehicle VEHICLE1 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), true);
		Vector3 coords1 = ENTITY::GET_ENTITY_COORDS(VEHICLE1, false);

		RequestControlOfEnt(veh);
		VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true, true);
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
		DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
		auto networkId = NETWORK::VEH_TO_NET(veh);
		ENTITY::_SET_ENTITY_SOMETHING(veh, true);
		if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(veh))
			NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
		if (spawnincar)
		{
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
		}
		if (spawnmaxed)
		{
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
			for (int i = 0; i < 50; i++)
			{
				VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1, false);
			}
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, "Sinister");
		}
		if (Features::setcustompricolour)
		{
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, Features::pricustomred, Features::pricustomgreen, Features::pricustomblue);
		}
		if (Features::setcustomseccolour)
		{
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, Features::seccustomred, Features::seccustomgreen, Features::seccustomblue);
		}
		if (spawnwithblip)
		{
			UI::SET_BLIP_COLOUR(225, 67);
			UI::SET_BLIP_COORDS(225, coords1.x, coords1.y, coords1.z);
		}
		if (cargodmodebool) {
			Features::cargodmode();
		}
		WAIT(150);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
	}
}
void Features::cargodmode()
{

	if (VEHICLE::_IS_VEHICLE_DAMAGED(vehicle))
	{
		for (int i = 0; i < 10; i++)
		{
			try {
				VEHICLE::SET_VEHICLE_TYRE_FIXED(vehicle, i);
			}
			catch (...) {
				return;
			}
		}
	}
}

bool Features::cargodmodebool = false;
void Features::cargodmode2(Player playa)
{

	
		if (VEHICLE::_IS_VEHICLE_DAMAGED(vehicle))
		{
			for (int i = 0; i < 10; i++)
			{
				try {
					VEHICLE::SET_VEHICLE_TYRE_FIXED(vehicle, i);
				}
				catch (...) {
					return;
				}
			}
		}
	}
}

char* Features::enemyWeapon = NULL;
char* Features::enemyModel = NULL;
void Features::spawnEnemy(Player victim, char* model, char* weapon) {
	
	enemyindex++;
}


bool Features::glitch[35] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
void Features::glitchPlayer(Player p) {
	NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(p), true));
	if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(p), true)))
	{
		ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(p), true), 1, 0, 0, 20, 0, 0, 0, 1, false, true, true, true, true);
	}
}

void Features::write2(std::string path, std::string content) {
	std::ofstream file;
	file.open(path, std::ios::out | std::ios::app);
	file.exceptions(file.exceptions() | std::ios::failbit | std::ifstream::badbit);

	file << content << std::endl;
}

void Features::grabDatIP(Player p) {
	Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(p);
	char ipBuf[32] = {};
	static auto IPadre = (std::uintptr_t(*)(int))(Memory::pattern("40 53 ? 7´4").count(1).get(0).get<void>(-89));
	auto ipadre_ = IPadre(p);

	if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(p)) {
		if (ipadre_) {
			auto faggot = *(uintptr_t*)(ipadre_ + 0x10b8);
			if (faggot) {
				auto ip = (BYTE*)(faggot + 0x44);
				std::snprintf(ipBuf, sizeof(ipBuf) - 1, "%u.%u.%u.%u", ip[3], ip[2], ip[1], *ip);
			}
		}
	}
	std::string content = (std::string)PLAYER::GET_PLAYER_NAME(p) + ": " + ipBuf;
	Features::write2("Apollo//IP/IP.txt", content);
}

int SwarmAttackChopperTarget = 0;
int vehattackers;
bool Features::hostilebuzzard = false;
bool Features::vehspawncheck;
int pedattackers;
int pedattackers1;
int pedattackers2;
int pedattackers3;
bool Features::Hostilebuzzard(int selectedPlayer)
{
	if (Features::hostilebuzzard)
	{
		if (Features::vehspawncheck)
		{
			int model = GAMEPLAY::GET_HASH_KEY("buzzard");
			float speed = ENTITY::GET_ENTITY_SPEED(PLAYER::PLAYER_PED_ID());
			STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("buzzard"));
			if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("buzzard")))
			{
				Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(-50, 50), GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(-50, 50), GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(25, 75));
				vehattackers = VEHICLE::CREATE_VEHICLE(GAMEPLAY::GET_HASH_KEY("buzzard"), coords.x, coords.y, coords.z, 0, 1, 0);
				if (ENTITY::DOES_ENTITY_EXIST(vehattackers))
				{
					Features::vehspawncheck = false;
					pedattackers = true;
					pedattackers1 = true;
					pedattackers2 = true;
					pedattackers3 = true;
					if (pedattackers, pedattackers1, pedattackers2, pedattackers3)
					{
						STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01"));
						if (STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01")))
						{
							Vector3 coords_ = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), 6.0, 0.0, 0.0);
							pedattackers = PED::CREATE_PED(21, GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01"), coords_.x, coords_.y, coords_.z, 1, 1, 0);
							pedattackers1 = PED::CREATE_PED(21, GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01"), coords_.x, coords_.y, coords_.z, 1, 1, 0);
							pedattackers2 = PED::CREATE_PED(21, GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01"), coords_.x, coords_.y, coords_.z, 1, 1, 0);
							pedattackers3 = PED::CREATE_PED(21, GAMEPLAY::GET_HASH_KEY("s_m_y_blackops_01"), coords_.x, coords_.y, coords_.z, 1, 1, 0);
							if (ENTITY::DOES_ENTITY_EXIST(pedattackers))
							{
								
								return true;
							}
							return false;
						}
						return false;
					}
					return false;
				}
				return false;
			}
			return false;
		}
		//what is this code even lmao
	}
}

bool Features::fakedropbool = false;
void Features::fakedrop(bool t, Player player) {
	if ((timeGetTime() - Features::TimePD3) > 400) // Time between drops
	{
		STREAMING::REQUEST_MODEL(moneyModel(Features::MoneyItem));
		if (!STREAMING::HAS_MODEL_LOADED(moneyModel(Features::MoneyItem))) {
			WAIT(0);
		}
		else {
			OBJECT::CREATE_AMBIENT_PICKUP(PICKUP_MONEY_CASE, coordsOf(player).x, coordsOf(player).y, coordsOf(player).z, 1, 1, moneyModel(Features::MoneyItem), false, true);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(moneyModel(Features::MoneyItem));

			Features::TimePD3 = timeGetTime();
		}
	}
}

bool Features::freezed[35] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
void Features::Freezer(Player target) {
	Ped vic = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
	AI::CLEAR_PED_TASKS_IMMEDIATELY(vic);
	AI::CLEAR_PED_TASKS(vic);
	AI::CLEAR_PED_SECONDARY_TASK(vic);
}

bool Features::playerwaterloop[35] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
void Features::WaterLoop(Player target)
{
	Player selectedPlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
	Vector3 Pos = coordsOf(selectedPlayer);
	FIRE::ADD_EXPLOSION(Pos.x, Pos.y, Pos.z, 13, 5, true, 0, 0);
}

bool Features::playerfireloop[35] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
void Features::FireLoop(Player target)
{
	Player selectedPlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
	Vector3 Pos = coordsOf(selectedPlayer);
	FIRE::ADD_EXPLOSION(Pos.x, Pos.y, Pos.z, 12, 5, true, 0, 0);
}

void Features::CREATE_OBJECT_WITH_ROTATION(DWORD model, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float rotW, bool dynamic, bool visible)
{
	if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))
	{
		STREAMING::REQUEST_MODEL(model);
		while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
		Object obj = OBJECT::CREATE_OBJECT(model, posX, posY, posZ, true, false, dynamic);
		ENTITY::SET_ENTITY_QUATERNION(obj, rotX, rotY, rotZ, rotW);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(obj, true, true);
		ENTITY::SET_ENTITY_DYNAMIC(obj, false);
		if (!visible)
		{
			ENTITY::SET_ENTITY_VISIBLE(obj, false);
		}
		ENTITY::SET_ENTITY_PROOFS(obj, true, true, true, true, true, true, true, true);
		ENTITY::SET_ENTITY_INVINCIBLE(obj, true);
		WAIT(500);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
	}
}

}

void Features::trapcage(Ped ped)
{
	Vector3 remotePos = ENTITY::GET_ENTITY_COORDS(ped, 0);
	Object obj = OBJECT::CREATE_OBJECT($("prop_gold_cont_01"), remotePos.x, remotePos.y, remotePos.z - 1.f, true, false, false);
}

void Features::stealCar(Player p) {
	Vehicle veh;
	Player player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(p);
	if (PED::IS_PED_IN_ANY_VEHICLE(player, 0))
	{
		veh = PED::GET_VEHICLE_PED_IS_USING(player);
		RequestControlOfEnt(veh);
		PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -2);
		AI::CLEAR_PED_TASKS_IMMEDIATELY(player);
		AI::CLEAR_PED_TASKS(player);
		AI::CLEAR_PED_SECONDARY_TASK(player);
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
			veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
		}
	}
}

void Features::blamee(Player p) {
	Player victim = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(p);
	Hooking::ownedExplosionBypass(true);
	for (int i = 0; i < 33; i++) {
		Player pl = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
		Vector3 crd = coordsOf(pl);
		if (pl != victim) {
			//FIRE::ADD_OWNED_EXPLOSION(victim, crd.x, crd.y, crd.z, EXP_TAG_GRENADE, 5.0f, true, false, 0.1f);
			Hooking::add_owned_explosion(victim, crd, 29, 5.0f, true, false, 0.1f);
		}
	}
	Hooking::ownedExplosionBypass(false);
}

void Features::beachFire(Player p)
{ // prop_beach_fire
	Player playerHandle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(p);
	Hash beach_fire = GAMEPLAY::GET_HASH_KEY("prop_beach_fire");
	STREAMING::REQUEST_MODEL(beach_fire);
	while (!STREAMING::HAS_MODEL_LOADED(beach_fire)) WAIT(0);
	Object object = OBJECT::CREATE_OBJECT(beach_fire, 0, 0, 0, true, true, false);
	ENTITY::ATTACH_ENTITY_TO_ENTITY(object, playerHandle, 31086, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(beach_fire);
}

void Features::TeleportVehicleToMe(Player player) {
	int CurrentPlayersVehicle = PED::GET_VEHICLE_PED_IS_USING(player);
	Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
	if (CurrentPlayersVehicle) {
		RequestControlOfEnt(CurrentPlayersVehicle);
		ENTITY::SET_ENTITY_COORDS(CurrentPlayersVehicle, MyCoords.x, MyCoords.y, MyCoords.z + 1.0f, false, false, false, false);
	}
}

bool Features::spectate[32] = { false };
void Features::specter(Player target)
{
	if (Features::spectate[target] == true) {
		NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(Features::spectate[target], PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target));
	}
	else if (Features::spectate[target] == false) {
		NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, PLAYER::PLAYER_PED_ID());
	}
}
void Features::TeleportToPlayer(Player player) {

	Entity handle;
	Vector3 coords = ENTITY::GET_ENTITY_COORDS(player, false);
	PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) ? handle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) : handle = PLAYER::PLAYER_PED_ID();
	ENTITY::SET_ENTITY_COORDS(handle, coords.x, coords.y, coords.z, false, false, false, false);
}

void Features::TeleportIntoVehicle(Player player) {
	if (PED::IS_PED_IN_ANY_VEHICLE(player, false))
	{
		Vehicle selectedVehicle = PED::GET_VEHICLE_PED_IS_USING(player);
		int numSeats = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(selectedVehicle);
		for (int i = numSeats; i >= -1; i--)
		{
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), selectedVehicle, i);
		}
	}
}

void Features::setplayername(std::string & name)
{
	size_t newLen = name.size() + 1;
	if (newLen <= 1 || newLen > 20)
		return;
	char    buffer[0x20] = {};
	char* pSearch = (char*)0x7D;
	size_t    curLen = strlen(pSearch) + 1;
	strncpy_s(buffer, pSearch, curLen);
	for (uint32_t i = 0, found = 0, match = 0; found < 4; ++pSearch)
	{
		i = match = 0;
	}
	strncpy(nullptr, &name[0], newLen);
}


char* Features::setPlayerName(int player, char* tag) {
	ostringstream playerOption;
	playerOption << PLAYER::GET_PLAYER_NAME(player) << tag;
	return (char*)playerOption.str().c_str();
}
bool Features::isPlayerFriend(Player player, bool& result)
{
	int NETWORK_HANDLE[76];
	NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &NETWORK_HANDLE[0], 13);
	if (NETWORK::NETWORK_IS_HANDLE_VALID(&NETWORK_HANDLE[0], 13))
	{
		result = NETWORK::NETWORK_IS_FRIEND(&NETWORK_HANDLE[0]);
		return true;
	}
	return false;
}

decltype(Features::player_alpha) Features::player_alpha = 255;

bool Features::isAutoRegArmour = false;
void Features::AutoRegArmour(bool toggle) {

	

}


bool Features::Flex = false;
void Features::flex(bool toggle)
{
	
}

int Features::timeerlevelcc = 0;
void Features::settimechangcc(int level) {
	GAMEPLAY::SET_FAKE_WANTED_LEVEL(Features::timeerlevelcc);
}

int Features::playerWantedLevel = 0;
void Features::ChangeWanted(int level) {
	Memory::set_value<int32_t>({ (2 * 4 * 2) / 2, 4 * 1000 + 280, 500 * 4 - 70 + 70 + 72 }, Features::playerWantedLevel - 1 + 1 - 0 + 1 - 1);
}

float Features::gameCamZoomInt = 1.0f;
bool Features::gameCamZoom = false;
void Features::zoomCam() {
	CAM::_ANIMATE_GAMEPLAY_CAM_ZOOM(Features::gameCamZoomInt, Features::gameCamZoomInt);
}

float Features::pedsizee = 1.0f;
float Features::pedwithh = 1.0f;
bool Features::Pedscale = false;
void Features::pedscale(bool toggle)
{
	;
}

void Features::clearanim()
{
	AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());

}

void Features::doAnimation(char* anim, char* animid)
{
	int pPlayer = PLAYER::PLAYER_PED_ID();
	RequestNetworkControl(pPlayer);
	STREAMING::REQUEST_ANIM_DICT(anim);
	if (STREAMING::HAS_ANIM_DICT_LOADED((anim)))
	{
		AI::TASK_PLAY_ANIM(pPlayer, anim, animid, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
	}
}


bool Features::ignored = false;
void Features::nobody() {
	set_all_nearby_peds_to_calm();
}

bool Features::ctbBool = false;
void Features::copsturnblind() {
	globalHandle(2528542).At(4546).As<int>() = 5;
}

void Features::Bullshark() {
	globalHandle(2437022).At(3876).As<int>() = NETWORK::GET_NETWORK_TIME();
}
static Vector3 getCoords(Entity entity)
{
	return ENTITY::GET_ENTITY_COORDS(entity, false);
}

bool Features::free_cam = false;
void Features::freecam(bool toggle)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (GetAsyncKeyState(VK_SPACE) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, ControlFrontendLb)) {
		float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
		ENTITY::SET_ENTITY_HEADING(playerPed, heading);

		pos.z += 0.5;
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
	}
}


bool Features::noClipBool = false;
void Features::noClip(bool toggle) {

	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vector3 pos = ENTITY::GET_ENTITY_COORDS(playerPed, false);
	ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
	}
}

bool Features::antiAFKbool = false;
void Features::antiAFK(bool t) {
	
}


int Features::TimePD;
int Features::TimePD1;
int Features::TimePD2;
int Features::TimePD3;
int Features::TimePD4;
int Features::TimePD5;
int Features::TimePD6;
int Features::TimePD7;
int Features::TimePD8;
int Features::TimePD9;
int Features::TimePD10;
int Features::TimePD11;
int Features::TimePD12;
int Features::TimePD13;
int Features::TimePD14;
int Features::TimePD15;
int Features::TimePD16;
int Features::TimePD17;


bool cstrcmp(const char* s1, const char* s2)
{
	return nullptr;
}

int fam;
void Features::changeClothes(char* family, int model, int texture)
{
	if (cstrcmp(family, "HATS") || cstrcmp(family, "GLASSES") || cstrcmp(family, "EARS"))
	{
		if (cstrcmp(family, "HATS"))
			fam = 0;
		else if (cstrcmp(family, "GLASSES"))
			fam = 1;
		else if (cstrcmp(family, "EARS"))
			fam = 2;
	}
	else
	{
		if (cstrcmp(family, "FACE"))
			fam = 0;
		else if (cstrcmp(family, "MASK"))
			fam = 1;
		else if (cstrcmp(family, "HAIR"))
			fam = 2;
		else if (cstrcmp(family, "TORSO"))
			fam = 3;
		else if (cstrcmp(family, "LEGS"))
			fam = 4;
		else if (cstrcmp(family, "HANDS"))
			fam = 5;
	}
}

bool Features::badsportbool = false;
void Features::badsport(bool t) {
	Features::changeClothes("HATS", 2, 0);
}

bool Features::dragon = false;
void Features::Dragon(bool t)
{
	Vector3 Mouth = PED::GET_PED_BONE_COORDS(PLAYER::PLAYER_PED_ID(), 39317, 0.1f, 0.0f, 0.0f);
	FIRE::ADD_EXPLOSION(Mouth.x, Mouth.y, Mouth.z, 28, 1.0f, true, false, 0.0f);
	FIRE::ADD_EXPLOSION(Mouth.x, Mouth.y, Mouth.z, 27, 1.0f, true, false, 0.0f);
}

bool Features::betiny = false;
void Features::TinyPlayer(bool toggle)
{
	PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, toggle);
}


bool Features::fastswim = false;
void Features::SwimFast(bool toggle)
{
	if (!fastswim)
	{
		Memory::set_value<float>({ OFFSET_PLAYER , OFFSET_PLAYER_INFO , OFFSET_PLAYER_INFO_SWIM_SPD }, 1);
	}
	else
	{
		Memory::set_value<float>({ OFFSET_PLAYER , OFFSET_PLAYER_INFO , OFFSET_PLAYER_INFO_SWIM_SPD }, 2.5);
	}
}


bool Features::ujump = false;
void Features::ultraJump() {
	Player playerPed = PLAYER::PLAYER_PED_ID();
	GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(playerPed);
	WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, GAMEPLAY::GET_HASH_KEY("GADGET_PARACHUTE"));
	if (PED::IS_PED_JUMPING(playerPed) && IsKeyPressed(VK_SPACE))
	{
		ENTITY::APPLY_FORCE_TO_ENTITY(playerPed, true, 0, 0, 5, 0, 0, 0, true, true, true, true, false, true);
	}
}

bool Features::Superjump = false;
void Features::superjump(bool toggle)
{
	Player playerPed = PLAYER::PLAYER_PED_ID();
	GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
	GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(playerPed);
}

bool Features::playerinvisibility = false;
void Features::Invisibility(bool toggle)
{
	if (playerinvisibility)
	{
		ENTITY::SET_ENTITY_VISIBLE1(PLAYER::PLAYER_PED_ID(), false, 0);
	}
	else
	{
		ENTITY::SET_ENTITY_VISIBLE1(PLAYER::PLAYER_PED_ID(), true, 0);
	}
}

bool Features::playernoragdoll = false;
void Features::NoRagdoll(bool toggle)
{
	PED::SET_PED_RAGDOLL_ON_COLLISION(PLAYER::PLAYER_PED_ID(), !toggle);
	PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), !toggle);
	PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), !toggle);
}

bool Features::orbool = false;
void Features::OffRadar(bool toggle)
{
	globalHandle(2423801).At(PLAYER::PLAYER_ID(), 413).At(200).As<int>() = 1;
	globalHandle(2437022).At(70).As<int>() = NETWORK::GET_NETWORK_TIME() + 5000;
	//Global_2423801[PLAYER::PLAYER_ID() /*413*/].f_200
	//Global_2437022.f_70
}

bool Features::neverwanted = false;
void Features::NeverWanted(bool toggle)
{
	Memory::set_value<int32_t>({ (2 * 4 * 2) / 2, 4 * 1000 + 280, 500 * 4 - 70 + 70 + 72 }, -1 + 1 - 0 + 1 - 1);
}

bool Features::antitse = false;
void Features::antiTSE(bool t) {
	globalHandle(1386431).At(300).As<int>() = 300; //Superkick II
	globalHandle(1386431).At(709).As<int>() = 709; //Superkick I
}

bool Features::antiweatherTime = false;
void Features::antiWeatherTime(bool t) {
	Hooking::defuseEvent(GAME_CLOCK_EVENT, t);
	Hooking::defuseEvent(GAME_WEATHER_EVENT, t);
}

bool Features::antiEvery = false;
void Features::AntiEverything(bool t) {
	Hooking::defuseEvent(NETWORK_START_SYNCED_SCENE_EVENT, t);
	Hooking::defuseEvent(CACHE_PLAYER_HEAD_BLEND_DATA_EVENT, t);
	Hooking::defuseEvent(REMOVE_PED_FROM_PEDGROUP_EVENT, t);
	Hooking::defuseEvent(REPORT_MYSELF_EVENT, t);
	Hooking::defuseEvent(REPORT_CASH_SPAWN_EVENT, t);
	Hooking::defuseEvent(ACTIVATE_VEHICLE_SPECIAL_ABILITY_EVENT, t);
	Hooking::defuseEvent(NETWORK_CHECK_CATALOG_CRC, t);
}

bool Features::antiControl = false;
void Features::AntiControl(bool t) {
	Hooking::defuseEvent(REQUEST_CONTROL_EVENT, t);
	Hooking::defuseEvent(GIVE_CONTROL_EVENT, t);
	Hooking::defuseEvent(VEHICLE_COMPONENT_CONTROL_EVENT, t);
}

bool Features::antiPtfx = false;
void Features::AntiPtfx(bool t) {
	Hooking::defuseEvent(NETWORK_PTFX_EVENT, t);
}

bool Features::antiAttachment = false;
void Features::AntiAttachment(bool t) {
	Hooking::defuseEvent(REQUEST_DETACHMENT_EVENT, t);
	char* objects[136] = { "prop_bskball_01", "PROP_MP_RAMP_03", "PROP_MP_RAMP_02", "PROP_MP_RAMP_01", "PROP_JETSKI_RAMP_01", "PROP_WATER_RAMP_03", "PROP_VEND_SNAK_01", "PROP_TRI_START_BANNER", "PROP_TRI_FINISH_BANNER", "PROP_TEMP_BLOCK_BLOCKER", "PROP_SLUICEGATEL", "PROP_SKIP_08A", "PROP_SAM_01", "PROP_RUB_CONT_01B", "PROP_ROADCONE01A", "PROP_MP_ARROW_BARRIER_01", "PROP_HOTEL_CLOCK_01", "PROP_LIFEBLURB_02", "PROP_COFFIN_02B", "PROP_MP_NUM_1", "PROP_MP_NUM_2", "PROP_MP_NUM_3", "PROP_MP_NUM_4", "PROP_MP_NUM_5", "PROP_MP_NUM_6", "PROP_MP_NUM_7", "PROP_MP_NUM_8", "PROP_MP_NUM_9", "prop_xmas_tree_int", "prop_bumper_car_01", "prop_beer_neon_01", "prop_space_rifle", "prop_dummy_01", "prop_rub_trolley01a", "prop_wheelchair_01_s", "PROP_CS_KATANA_01", "PROP_CS_DILDO_01", "prop_armchair_01", "prop_bin_04a", "prop_chair_01a", "prop_dog_cage_01", "prop_dummy_plane", "prop_golf_bag_01", "prop_arcade_01", "hei_prop_heist_emp", "prop_alien_egg_01", "prop_air_towbar_01", "hei_prop_heist_tug", "prop_air_luggtrolley", "PROP_CUP_SAUCER_01", "prop_wheelchair_01", "prop_ld_toilet_01", "prop_acc_guitar_01", "prop_bank_vaultdoor", "p_v_43_safe_s", "p_spinning_anus_s", "prop_can_canoe", "prop_air_woodsteps", "Prop_weed_01", "prop_a_trailer_door_01", "prop_apple_box_01", "prop_air_fueltrail1", "prop_barrel_02a", "prop_barrel_float_1", "prop_barrier_wat_03b", "prop_air_fueltrail2", "prop_air_propeller01", "prop_windmill_01", "prop_Ld_ferris_wheel", "p_tram_crash_s", "p_oil_slick_01", "p_ld_stinger_s", "p_ld_soc_ball_01", "prop_juicestand", "p_oil_pjack_01_s", "prop_barbell_01", "prop_barbell_100kg", "p_parachute1_s", "p_cablecar_s", "prop_beach_fire", "prop_lev_des_barge_02", "prop_lev_des_barge_01", "prop_a_base_bars_01", "prop_beach_bars_01", "prop_air_bigradar", "prop_weed_pallet", "prop_artifact_01", "prop_attache_case_01", "prop_large_gold", "prop_roller_car_01", "prop_water_corpse_01", "prop_water_corpse_02", "prop_dummy_01", "prop_atm_01", "hei_prop_carrier_docklight_01", "hei_prop_carrier_liferafts", "hei_prop_carrier_ord_03", "hei_prop_carrier_defense_02", "hei_prop_carrier_defense_01", "hei_prop_carrier_radar_1", "hei_prop_carrier_radar_2", "hei_prop_hei_bust_01", "hei_prop_wall_alarm_on", "hei_prop_wall_light_10a_cr", "prop_afsign_amun", "prop_afsign_vbike", "prop_aircon_l_01", "prop_aircon_l_02", "prop_aircon_l_03", "prop_aircon_l_04", "prop_airhockey_01", "prop_air_bagloader", "prop_air_blastfence_01", "prop_air_blastfence_02", "prop_air_cargo_01a", "prop_air_chock_01", "prop_air_chock_03", "prop_air_gasbogey_01", "prop_air_generator_03", "prop_air_stair_02", "prop_amb_40oz_02", "prop_amb_40oz_03", "prop_amb_beer_bottle", "prop_amb_donut", "prop_amb_handbag_01", "prop_amp_01", "prop_anim_cash_pile_02", "prop_asteroid_01", "prop_arm_wrestle_01", "prop_ballistic_shield", "prop_bank_shutter", "prop_barier_conc_02b", "prop_barier_conc_05a", "prop_barrel_01a", "prop_bar_stool_01", "prop_basejump_target_01" };
	for (int i = 0; i < 999; i++) for (;;) {
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		GAMEPLAY::CLEAR_AREA_OF_PEDS(coords.x, coords.y, coords.z, 2, 0);
		GAMEPLAY::CLEAR_AREA_OF_OBJECTS(coords.x, coords.y, coords.z, 2, 0);
		GAMEPLAY::CLEAR_AREA_OF_VEHICLES(coords.x, coords.y, coords.z, 2, 0, 0, 0, 0, 0);
		for (int i = 0; i < 136; i++) {
			Object obj = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(coords.x, coords.y, coords.z, 4.0, GAMEPLAY::GET_HASH_KEY(objects[i]), 0, 0, 1);

			if (ENTITY::DOES_ENTITY_EXIST(obj) && ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(obj, PLAYER::PLAYER_PED_ID())) {
				RequestControlOfEnt(obj);
				int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(obj);
				NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
				RequestControlOfid(netID);
				ENTITY::DETACH_ENTITY(obj, 1, 1);
				if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(obj)) {
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(obj, 1, 1);
					ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&obj);
					ENTITY::DELETE_ENTITY(&obj);
				}
			}
		}
	}
}
bool Features::antiBlame = false;
void Features::blameProtex() {
	NETWORK::NETWORK_SET_FRIENDLY_FIRE_OPTION(true);
}

bool Features::eventShieldBool = false;
void Features::eventShield() {
	uint64_t var0[10];
	bool data = Hooking::get_script_event_data(1, 0, var0, 10);
}


bool Features::dumpBool = false;
bool Features::msgBool = false;
int Features::evIndex = 10;

bool eventData(int eventGroup, int eventIndex, uint64_t* argv, unsigned int argc)
{
	return result;
}

uint64_t Features::dumpEvent(bool t) {
	uint64_t Var0[10];
	if (eventData(1, 0, Var0, 10)) {
		for (int i = 0; i < 10; i++) {
			return Var0[i];
		}
	}
}

void Features::logEvent(bool msg) {
	int result1 = Features::dumpEvent(true);
	std::string result2 = std::to_string(result1);
	//Log::Msg(result2.c_str());
	if (msg) {
		notifyMap(result2.c_str());
	}
}

bool Features::GodMode = false;
void Features::godmode(bool toggle)
{
	if (Memory::get_value<BYTE>({ 0x08, 0x189 }) != toggle) Memory::set_value({ 0x08, 0x189 }, Setter);
}

bool Features::otr2bool = false;
void Features::otr2(bool t) {
	if (t) {
		Features::GodMode = true;
		Memory::set_value<float>({ OFFSET_PLAYER , OFFSET_ENTITY_HEALTH }, 0);
	}
	else {
		Memory::set_value<float>({ OFFSET_PLAYER , OFFSET_ENTITY_HEALTH }, 100);
	}
}

char* CharKeyboard(char* windowName = "", int maxInput = 21, char* defaultText = "")
{
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(0, "", "", defaultText, "", "", "", maxInput);
	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return "";
	return GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
}

void Features::startTriggerFX(char* fxAsset, char* fx)
{
	if (!STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(fxAsset))
		STREAMING::REQUEST_NAMED_PTFX_ASSET(fxAsset);
	while (!STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(fxAsset)) {
		WAIT(0);
	}

	GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL(fxAsset);
	GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_ENTITY_2(fx, players[selfPlayer].ped, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, TRUE, TRUE, TRUE);
	MessageAtBottomScreen("TriggerFX has been played", 2000);
}

std::string get_ingame_keyboard_result()
{
	std::string    r = "!!INVALID!!";
	if (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD())
	{
		char* pCh = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
		if (pCh != nullptr)
			r = pCh;
	}
	return r;
}

void Features::NameChanger()
{
	CharKeyboard("", 21, "");
	std::string str = get_ingame_keyboard_result();
	if (str != "!!INVALID!!" && str != "")
	{
		Features::setname(str);
	}
}

void Features::playScenario(char* scenario)
{
	AI::TASK_START_SCENARIO_IN_PLACE(players[selfPlayer].ped, scenario, 0, FALSE);
	MessageAtBottomScreen("Scenario has been started", 2000);
}

void Features::stopAnimation()
{
	AI::CLEAR_PED_TASKS_IMMEDIATELY(players[selfPlayer].ped);
	MessageAtBottomScreen("Current animation/scenario has been stopped", 2000);
}

bool Features::fastRun = false;
void Features::runFast(bool toggle)
{
	if (!fastRun)
	{
		Memory::set_value<float>({ 0x08, 0x10B8, 0x14C }, 1);
	}
	else
	{
		Memory::set_value<float>({ 0x08, 0x10B8, 0x14C }, 2.0f);
	}
}
void Features::resetWalkAnimation()
{
	PED::CLEAR_PED_ALTERNATE_WALK_ANIM(players[selfPlayer].ped, 0.f);
}

void Features::changeWalkAnimation(char* movementAnimation)
{
	STREAMING::REQUEST_ANIM_SET(movementAnimation);
	while (!STREAMING::HAS_ANIM_SET_LOADED(movementAnimation)) {
		WAIT(0);
	}

	PED::SET_PED_MOVEMENT_CLIPSET(players[selfPlayer].ped, movementAnimation, 1.f);
	MessageAtBottomScreen("Your walk animation has been changed", 2000);
}

void shootAtPed(Player selectedPlayer)
{
	Vector3 Mouth = PED::GET_PED_BONE_COORDS(selectedPlayer, SKEL_Head, 0.1f, 0.0f, 0.0f);
	PED::SET_PED_SHOOTS_AT_COORD(PLAYER::PLAYER_PED_ID(), Mouth.x, Mouth.y, Mouth.z, true);
}

bool Features::Aimbot = false;
void Features::aimbot(bool toggle)
{
	Entity AimedAtEntity;
	if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &AimedAtEntity))
	{
		if (ENTITY::IS_ENTITY_A_PED(AimedAtEntity) && !ENTITY::IS_ENTITY_DEAD(AimedAtEntity) && PED::IS_PED_A_PLAYER(AimedAtEntity) && ENTITY::GET_ENTITY_ALPHA(AimedAtEntity) == 255)
		{
			shootAtPed(AimedAtEntity);
		}
	}
}

void Features::LoadPlayerInfo(char* playerName, Player p) {

	Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(p);

	RequestControlOfEnt(ped);

	Vector3 __coords = ENTITY::GET_ENTITY_COORDS(ped, 0);
	char buf[0x80]; snprintf(buf, sizeof(buf), "X: ~g~%f", __coords.x);
	char buf1[0x80]; snprintf(buf1, sizeof(buf1), "~s~Y: ~g~%f", __coords.y);
	char buf2[0x80]; snprintf(buf2, sizeof(buf2), "~s~Z: ~g~%f", __coords.z);

	string money2 = to_string(tempMoney);
	int insertPosition = money2.length() - 3;
	while (insertPosition > 0) {
		money2.insert(insertPosition, ",");
		insertPosition -= 3;
	}

	float health = ENTITY::GET_ENTITY_HEALTH(ped);
	float maxHealth = ENTITY::GET_ENTITY_MAX_HEALTH(ped);
	float healthPercent = health * 100 / maxHealth;
	ostringstream Health; Health << "Health:~s~ " << healthPercent;
	float armor = PED::GET_PED_ARMOUR(ped);
	float maxArmor = PLAYER::GET_PLAYER_MAX_ARMOUR(p);
	float armorPercent = armor * 100 / maxArmor;
	ostringstream Armor; Armor << "Armor:~s~ " << armorPercent;
	bool alive = !PED::IS_PED_DEAD_OR_DYING(ped, 1);
	char* aliveStatus;
	if (alive) aliveStatus = "Yes"; else aliveStatus = "No";
	ostringstream Alive; Alive << "Alive:~s~ " << aliveStatus;
	bool inVehicle = PED::IS_PED_IN_ANY_VEHICLE(ped, 0);
	ostringstream VehicleModel; VehicleModel << "Vehicle:~s~ ";
	ostringstream Speed; Speed << "Speed:~s~ ";
	ostringstream IsInAVehicle; IsInAVehicle << "In Vehicle:~s~ ";
	if (inVehicle) {
		IsInAVehicle << "Yes";
		Hash vehHash = ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(ped, 0));
		VehicleModel << UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(vehHash));
		float vehSpeed = ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(ped, 0));
		float vehSpeedConverted;
		vehSpeedConverted = round(vehSpeed * 1.6);
		Speed << vehSpeedConverted << " KM/H";
	}
	else {
		IsInAVehicle << "No";
		float speed = round(ENTITY::GET_ENTITY_SPEED(ped) * 100) / 100;
		Speed << speed << " M/S";
		VehicleModel << "--------";
	}

	ostringstream WantedLevel; WantedLevel << "Wanted Level:~s~ " << PLAYER::GET_PLAYER_WANTED_LEVEL(p);
	ostringstream Weapon; Weapon << "Weapon: ~s~";
	Hash weaponHash;
	else Weapon << "Unarmed";
	
	Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped, 1);
	ostringstream Zone; Zone << "Zone: ~s~" << UI::_GET_LABEL_TEXT(ZONE::GET_NAME_OF_ZONE(coords.x, coords.y, coords.z));
	
	Menu::PlayerInfoTitle(playerName);
	Menu::PlayerInfoLine((char*)Health.str().c_str(), 0);
	Menu::PlayerInfoLine((char*)Armor.str().c_str(), 1);
	Menu::PlayerInfoLine((char*)Alive.str().c_str(), 2);
	Menu::PlayerInfoLine((char*)IsInAVehicle.str().c_str(), 3);
	Menu::PlayerInfoLine((char*)VehicleModel.str().c_str(), 4);
	Menu::PlayerInfoLine((char*)Speed.str().c_str(), 5);
	Menu::PlayerInfoLine((char*)WantedLevel.str().c_str(), 6);
	Menu::PlayerInfoLine((char*)Weapon.str().c_str(), 7);
	Menu::PlayerInfoLine((char*)Zone.str().c_str(), 8);
	Menu::PlayerInfoLine((char*)Money.str().c_str(), 9);
	Menu::PlayerInfoLine((char*)Moneybank.str().c_str(), 10);
	Menu::PlayerInfoLine((char*)RP.str().c_str(), 11);
	Menu::PlayerInfoLine((char*)Rank.str().c_str(), 12);
	Menu::PlayerInfoLine((char*)Kills.str().c_str(), 13);
	Menu::PlayerInfoLine((char*)Deaths.str().c_str(), 14);
	Menu::PlayerInfoLine((char*)KD.str().c_str(), 15);
	Menu::PlayerInfoLine(ipBuf, 16);
	Menu::PlayerInfoLine(buf, 17);
	Menu::PlayerInfoLine(buf1, 18);
	Menu::PlayerInfoLine(buf2, 19);
	Menu::PlayerInfoLine((char*)Earnings.str().c_str(), 20);
	Menu::PlayerInfoLine((char*)Money1.str().c_str(), 21);
	Menu::PlayerInfoLine((char*)Death.str().c_str(), 22);
	Menu::PlayerInfoLine((char*)Deathlost.str().c_str(), 23);
	Menu::PlayerInfoLine((char*)Races.str().c_str(), 24);
	Menu::PlayerInfoLine((char*)Raceslost.str().c_str(), 25);

}

bool Features::is_player_in_interior(Player player)
{
	Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
	int currentInterior = INTERIOR::GET_INTERIOR_FROM_ENTITY(ped);
	return INTERIOR::IS_VALID_INTERIOR(currentInterior);
}

bool Features::isPlayerModder(Player p) {
	if (kd > max_legit_kd) {
		modderValue += 1;
		if (kills > max_legit_kills) {
			modderValue += 1;
		}
		if (deaths > max_legit_deaths) {
			modderValue += 1;
		}
	}

	if (modderValue > 10) {
		return true;
	}
	return false;
}