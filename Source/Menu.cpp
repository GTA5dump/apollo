#pragma once
#include "stdafx.h"
#include <filesystem>

std::string getUsername() {
	std::ostringstream str;
	str << get_gta_dir() << "\\Apollo\\Injector\\username.txt";
	//str << get_gta_dir() << "\\DestinyMenu\\Injector\\password.txt";
	std::fstream infile(str.str());
	std::string x;

	if (infile.is_open()) {
		while (infile.good()) {
			getline(infile, x);
			return x;
			infile.close();
		}
	}
}
std::string getPassword() {
	std::ostringstream str;
	str << get_gta_dir() << "\\Apollo\\Injector\\password.txt";
	std::fstream infile(str.str());
	std::string x;
	std::string output; // i know

	if (infile.is_open()) {
		while (infile.good()) {
			getline(infile, x);
			return x;
			infile.close();
		}
	}
}
void authcheack() {
	if (firsttime)
	{
		std::ostringstream str;
		str << get_gta_dir() << "\\Apollo\\Injector\\username.txt";
		std::ifstream inifile(str.str());

		if (!inifile.good()) {
			exit(0);
		}
		else {
			auto answer = Auth::is_authed(getUsername(), getPassword());
			if (answer != 6) {// about this old one and what about answer, first try with my currently, I'll add this answer okay
				answer = Auth::is_authed(getUsername(), getPassword());
				if (answer == 6) {
					Log::Msg("Sucessfully Authenticated 1");
					firsttime = false;// i know but if i do this it work as im try to do this watch I have one idea for it
				}
				else {
					Log::Msg("Failed to Authenticate");
					exit(0);
				}
			}
			else {
			Log::Msg("Sucessfully Authenticated");
				UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
				UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(answer == 6 ? "Logged in to Apollo Menu, Access: Moon" : "Logged in to Apollo Menu, Access: Moon");
				UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 8, "~r~Apollo Menu", "~c~Auth", 1, "___Moon", 9);
				UI::_DRAW_NOTIFICATION(FALSE, FALSE);
				firsttime = false;
			}
		}
	}
	
}
void main() {
	 
	authcheack();
	Thread::OnTick();
	switch (Menu::Settings::currentMenu) {
		
			
			//firsttime = false;
		
	case mainmenu:
	{
		
		//Menu::MenuLevelHandler::BackMenu();
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Main Menu");
		Menu::MenuOption("Protections", portections);//done
		Menu::MenuOption("Self", self);//done but few stuff left
		Menu::MenuOption("Online Players", online);//done
		Menu::MenuOption("Lobby", lobby);//done
		Menu::MenuOption("Weapons", weapons);//done but few stuff left
		Menu::MenuOption("Spawner", spawner);//done
		Menu::MenuOption("Vehicle", vehilce);
		Menu::MenuOption("Teleport", teleport);
		Menu::MenuOption("World", world);
		Menu::MenuOption("Misc", misc);//done
		Menu::MenuOption("Recover", recovery);// done
		Menu::MenuOption("Settings", settings);//done
		Menu::MenuOption("test outfits", test_outfits);//done
		//Menu::MenuOption("Test", testt);
		//Menu::MenuOption("Test2", testt2);
		if (Menu::Option("Unload")) {
			Unload::do_it = true;
		}

	}
	break;

#pragma region Vehicle
	case vehilce:
	{
		networkClanMgr Jclancxt;
		networkHandleMgr net;
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Vehicle");
		Menu::MenuOption("Vehicle Weapons", VehWeapon);
		//Menu::MenuOption("Vehicle Weapons 2", VehWeapontwo);
		Menu::MenuOption("Mobile LS Custom >", testt);
		Menu::MenuOption("Vehicle Acrobatics", acrobatic);
		Menu::MenuOption("PTFX Vehicle", ptfxveh);
		Menu::MenuOption("Neon Options", Neons);
		Menu::MenuOption("Cargobob mods", cargobobmods);
		Menu::MenuOption("Vehicle creator", createcar);
		Menu::MenuOption("INI vehicles", xmlvehicles);
		if (Menu::Toggle("Car Godmode", Features::cargodmodebool)) { Features::cargodmode(); }
		//Menu::Toggle("Speed Meter KM/h", Features::Speedometerbool, [] { Features::Speedometer(Features::Speedometerbool); });
		Menu::Toggle("~HUD_COLOUR_GOLD~Horn Boost", Features::boostbool, [] { Features::carboost(Features::boostbool); });
		if (Menu::Int("~HUD_COLOUR_GOLD~Delay", Features::Horndelay, 50, 1000))
		{
			if (IsKeyPressed(0x0D)) {
				Features::Horndelay = NumberKeyboard();
			}
		}

		Menu::Toggle("Backboost ", Features::Backboost, [] { Features::backboost(Features::Backboost); });
		//Menu::Toggle("Stop Car", Features::stopcar, [] { Features::stop(Features::stopcar); });
		Menu::Toggle("Drift Mode", Features::Drift, [] { Features::DriftMode(Features::Drift); });
		Menu::Toggle("Flying Car", Features::fcbool, [] { Features::FlyingCarLoop(Features::fcbool); });
		Menu::Toggle("Drive on Water", Features::dowbool);
		Menu::Toggle("Cruise Control", cruse);
		Menu::Toggle("Heli Bomb", Bommmer);
		if (Menu::Option("Test Something")) {
			IsPlayerInClan(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer));
			NETWORK::NETWORK_HANDLE_FROM_PLAYER(Features::Online::selectedPlayer, &net.netHandle, 13);
			Log::Msg("net.netHandle: %i\n", net.netHandle);
			Log::Msg("net.unk1: %i\n", net.unk1);
			Log::Msg("net.unk2: %i\n", net.unk2);
			Log::Msg("net.unk3: %i\n", net.unk3);
			Log::Msg("net.unk4: %i\n", net.unk4);
			Log::Msg("net.unk5: %i\n", net.unk5);
			Log::Msg("net.unk6: %i\n", net.unk6);
			Log::Msg("net.unk7: %i\n", net.unk7);
			Log::Msg("net.unk8: %i\n", net.unk8);
			Log::Msg("net.unk9: %i\n", net.unk9);
			Log::Msg("net.unk10: %i\n", net.unk10);
			Log::Msg("net.unk11: %i\n", net.unk11);
			Log::Msg("net.unk12: %i\n", net.unk12);
		}
		//Menu::Toggle("Drive on Water", Features::dowbool, [] { Features::DriveOnWater(Features::dowbool); });
		Menu::Toggle("No Bike Fall", Features::bikeNoFall);
		Menu::Toggle("Stick To Ground", Features::stickToGround);
		Menu::Toggle("Rainbow Car", Features::rlbool, [] { Features::HasPaintLoop(Features::rlbool); });
		if (Menu::Option("Add Vehicle Logo")) {
			Ped ped = PLAYER::PLAYER_PED_ID();

			if (PED::IS_PED_IN_ANY_VEHICLE(ped, 0))
			{
				Vehicle Veh = PED::GET_VEHICLE_PED_IS_USING(ped);
				Hash Model = ENTITY::GET_ENTITY_MODEL(Veh);

				Blip vBlip = UI::ADD_BLIP_FOR_ENTITY(Veh);
				UI::SET_BLIP_SCALE(vBlip, 1);
				if (VEHICLE::IS_THIS_MODEL_A_CAR(Model))
					UI::SET_BLIP_SPRITE(vBlip, 225);
				else if (VEHICLE::IS_THIS_MODEL_A_HELI(Model))
					UI::SET_BLIP_SPRITE(vBlip, 64);
				else if (VEHICLE::IS_THIS_MODEL_A_PLANE(Model))
					UI::SET_BLIP_SPRITE(vBlip, 16);
				else if (VEHICLE::IS_THIS_MODEL_A_BIKE(Model))
					UI::SET_BLIP_SPRITE(vBlip, 226);
				else
					UI::SET_BLIP_SPRITE(vBlip, 225);

				UI::SET_BLIP_NAME_FROM_TEXT_FILE(vBlip, "Pinned Vehicle");
				UI::SET_BLIP_COLOUR(vBlip, 0);
				UI::SET_BLIP_FLASHES(vBlip, false);
				UI::SET_BLIP_DISPLAY(vBlip, 2);
				UI::SET_BLIP_CATEGORY(vBlip, 1);
				UI::BEGIN_TEXT_COMMAND_SET_BLIP_NAME("Alliance's Vehicle");
				UI::END_TEXT_COMMAND_SET_BLIP_NAME(vBlip);
			}
			else notifyMap("~r~You are not in any vehicle!");
		}
		if (Menu::Option("Create Smoke"))
		{
			Ped playerPed = PLAYER::PLAYER_PED_ID();
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			VEHICLE::SET_VEHICLE_ENGINE_HEALTH(veh, false);
		}
		if (Menu::Option("~w~Auto Pilot"))
		{
			Vector3 Coords = get_blip_marker();
			AI::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(PLAYER::PLAYER_PED_ID(), PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), Coords.x, Coords.y, Coords.z, Features::drivespeed, Features::drivestyle, 0);
			if (get_blip_marker().x == 0 || get_blip_marker().y == 0 || get_blip_marker().z == 0) {
				//STOP
			}
			else
				notifyMap("~r~Waypoint isn't set");


		}
		if (Menu::Option("~w~Vehicle Jump   ~HUD_COLOUR_GOLD~[Press]")) {
			if ((VK_SPACE) && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, 0 + ENTITY::GET_ENTITY_FORWARD_X(veh), 0 + ENTITY::GET_ENTITY_FORWARD_Y(veh), 7, 0, 0, 0, 1, 0, 1, 1, 1, 1);
			}
		}
		if (Menu::Option("Add Ramp")) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
			{
				Vector3 Him = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
				int VehicleID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), true);
				STREAMING::REQUEST_MODEL(0xB157C9E4);
				if (STREAMING::HAS_MODEL_LOADED(0xB157C9E4))
				{
					Entity My_Objects = OBJECT::CREATE_OBJECT(0xB157C9E4, Him.x, Him.y, Him.z, 1, 1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(My_Objects))
					{
						ENTITY::SET_ENTITY_COLLISION(My_Objects, true, true);
						ENTITY::SET_ENTITY_ALPHA(My_Objects, 120, false);
						ENTITY::ATTACH_ENTITY_TO_ENTITY(My_Objects, VehicleID, 0, 0, 6.3, -0.3, 13.5, 0, 177.5, 0, 0, true, 0, 2, 1);
					}
				}
			}
			else { notifyMap("~r~You are not in Vehicle"); }
		}
		
		if (Menu::Option("Explode Vehicle"))
		{
			Ped playerPed = PLAYER::PLAYER_PED_ID();
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			VEHICLE::EXPLODE_VEHICLE(veh, false, false);
		}
		if (Menu::Option("Fix Car")) {
			uint Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()));
			VEHICLE::SET_VEHICLE_FIXED(Vehicle);
			VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(Vehicle);
			VEHICLE::SET_VEHICLE_DIRT_LEVEL(Vehicle, 0);
		}
		if (Menu::Option("Max Car")) {
			Features::maxvehicle();
		}
		Ped playerPed;
		if (Menu::Option("Wash Vehicle")) {
			GRAPHICS::WASH_DECALS_FROM_VEHICLE(PED::GET_VEHICLE_PED_IS_IN(playerPed, 0), 100.0f);
		}
		if (Menu::Option("Flip Car")) {
			Features::flipup();
		}
		if (Menu::Option("Open Doors   ~HUD_COLOUR_GOLD~[Disable Car Godmode]")) {
			VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0, true, false);
			VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 1, true, false);
			VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 2, true, false);
			VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 3, true, false);
			VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 4, true, false);
			VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 5, true, false);
			VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 6, true, false);
			VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 7, true, false);
		}
		if (Menu::Option("Close Doors")) {
			VEHICLE::SET_VEHICLE_DOORS_SHUT(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true);
		}
		if (Menu::Option("Open front left door")) { VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0, true, false); }
		if (Menu::Option("Open front right door")) { VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 1, true, false); }
		if (Menu::Option("Open back left door")) { VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 2, true, false); }
		if (Menu::Option("Open back right door")) { VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 3, true, false); }
		if (Menu::Option("Open hood")) { VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 4, true, false); }
		if (Menu::Option("Open trunk")) { VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 5, true, false); }
		if (Menu::Option("Open rear1")) { VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 6, true, false); }
		if (Menu::Option("Open rear2")) { VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 7, true, false); }
		if (Menu::Int("Vehicle Alpha", Menu::Settings::alpha, 0, 255))
		{
			int VehicleID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), true);
			ENTITY::SET_ENTITY_ALPHA(VehicleID, Menu::Settings::alpha, false);
		}
		if (Menu::Float("Acceleration Multiplier", accelerationmultiplier, 0.f, 3.f, 1.f)) {
			SetMultipliers();
		}
		if (Menu::Float("Brakes Multiplier", brakesmultiplier, 0.f, 3.f, 1.f)) {
			SetMultipliers();
		}
		if (Menu::Float("Suspension Height", suspensionseight, 0.f, 2.f, 1.f)) {
			SetMultipliers();
		}
	}
	
	break;
	
			case createcar:
			{
				Menu::Title(Menu::Settings::menuname);
				Menu::Break("Car creator");
				Menu::MenuOption("Select vehicles", attachcar);
				Menu::MenuOption("Select props", attachstuff);
				Menu::MenuOption("Set coords", moveA);
				if (Menu::Option("Attach it!")) {
					Features::Attachment(Features::selectedthing);
				}
			}
			break;
			case moveA:
			{
				Menu::Title(Menu::Settings::menuname);
				Menu::Break("Set coords");
				if (Menu::Option("Move 1 X+")) {
					Features::locX += 1;
				}
				if (Menu::Option("Move 1 Y+")) {
					Features::locY += 1;
				}
				if (Menu::Option("Move 1 Z+")) {
					Features::locZ += 1;
				}

				if (Menu::Option("Move 1 X-")) {
					Features::locX -= 1;
				}
				if (Menu::Option("Move 1 Y-")) {
					Features::locY -= 1;
				}
				if (Menu::Option("Move 1 Z-")) {
					Features::locZ -= 1;
				}

				if (Menu::Option("Reset X")) {
					Features::locX = 0;
				}
				if (Menu::Option("Reset Y")) {
					Features::locY = 0;
				}
				if (Menu::Option("Reset Z")) {
					Features::locZ = 0;
				}
				if (Menu::Option("Reset XYZ")) {
					Features::locX = 0;
					Features::locY = 0;
					Features::locZ = 0;
				}
			}
			break;
			case attachcar:
			{
				Menu::Title(Menu::Settings::menuname);
				Menu::Break(Features::selectedthing);
				for (auto car : Doomsday1) { Menu::Option(car, [car] { Features::selectedthing = car; }); }
				for (auto car : IMPORTEXPORT1) { Menu::Option(car, [car] { Features::selectedthing = car; }); }
				for (auto car : GUNRUNNING1) { Menu::Option(car, [car] { Features::selectedthing = car; }); }
				for (auto car : SMUGLERSRUN1) { Menu::Option(car, [car] { Features::selectedthing = car; }); }
				for (auto car : Super1) { Menu::Option(car, [car] { Features::selectedthing = car; }); }
				for (auto car : Sports1) { Menu::Option(car, [car] { Features::selectedthing = car; }); }
				for (auto car : OffRoad1) { Menu::Option(car, [car] { Features::selectedthing = car; }); }
			}
			break;
			case attachstuff:
			{
				Menu::Title(Menu::Settings::menuname);
				Menu::Break(Features::selectedthing);
				for (auto obj : objects2) { Menu::Option(obj, [obj] { Features::selectedthing = obj; }); }
			}

			break;
	case cargobobmods:
	{
		char* cargobob[4] = { "CARGOBOB", "CARGOBOB2", "CARGOBOB3", "CARGOBOB4" };
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Cargobob mods");
		Vehicle veh;
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) { veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()); }
		Menu::MenuOption("Spawner Settings", spawner_settings);
		if (Menu::Option("Spawn cargobob")) {
			Features::spawnincar = true;
			Features::spawn_vehicle(cargobob[0]);
			VEHICLE::CREATE_PICK_UP_ROPE_FOR_CARGOBOB(veh, 0);
		}
		if (Menu::Option("Spawn jetsam cargobob")) {
			Features::spawnincar = true;
			Features::spawn_vehicle(cargobob[1]);
			VEHICLE::CREATE_PICK_UP_ROPE_FOR_CARGOBOB(veh, 0);
		}
		if (Menu::Option("Attach magnet")) {
			VEHICLE::CREATE_PICK_UP_ROPE_FOR_CARGOBOB(veh, 1);
		}
		if (Menu::Option("Deatach magnet")) {
			VEHICLE::CREATE_PICK_UP_ROPE_FOR_CARGOBOB(veh, 0);
		}
		Menu::Toggle("Activate magnet", Features::cargobob_active, [] { Features::cargobobMagnet(); });
		if (Menu::Int("Set magnet strength", Features::cargobob_strength, 1, 100)) {
			VEHICLE::_SET_CARGOBOB_PICKUP_MAGNET_STRENGTH(veh, (float)Features::cargobob_strength);
		}
	}
	break;
	case Neons:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Neons");
		Menu::Toggle("Rainbow Neons", Features::Rneon, [] { Features::RainbowNeon(Features::Rneon); });
		if (Menu::Option("Enable Neons")) {
			int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 1);
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(VehID, 0, 1);
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(VehID, 1, 1);
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(VehID, 2, 1);
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(VehID, 3, 1);
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(VehID, 4, 1);
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(VehID, 5, 1);
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(VehID, 6, 1);
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(VehID, 7, 1);
		}
		if (Menu::Option("Red")) {
			int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 1);
			VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 255, 0, 0);
		}
		if (Menu::Option("Green")) {
			int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
			VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 0, 255, 0);
		}
		if (Menu::Option("Blue")) {
			int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
			VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 0, 0, 255);
		}
		if (Menu::Option("Hot Pink")) {
			int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
			VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 226, 35, 157);
		}
		if (Menu::Option("Yellow")) {
			int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
			VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 247, 244, 0);
		}
		if (Menu::Option("Orange")) {
			int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
			VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 247, 91, 0);
		}
		if (Menu::Option("Aqua")) {
			int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
			VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 40, 255, 255);
		}
		if (Menu::Option("White")) {
			int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
			VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 255, 255, 255);
		}
		if (Menu::Option("Magenta")) {
			int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
			VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 102, 0, 35);
		}
		if (Menu::Option("Purple")) {
			int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
			VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 53, 0, 83);
		}
		if (Menu::Option("Dark Green")) {
			int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
			VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 0, 118, 0);
		}
		if (Menu::Option("Rose Red")) {
			int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(VehID, 8);
			VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(VehID, 161, 0, 0);
		}
	}
	break;
	case ptfxveh:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("PTFX Vehicle");
		Menu::Toggle("Lightning", Features::CarLightning);
		Menu::Toggle("Clown Effects", Features::CarClownLoop);
		Menu::Toggle("Firework", Features::Carfireworkloop);
		Menu::Toggle("Alien 1", Features::Caralien1);
		Menu::Toggle("Alien 2", Features::Caralien2);
		Menu::Toggle("Electric", Features::Carelectric);
		//Menu::Toggle("Burial Dirt", Features::moneyeffect15);
	}
	break;
	case acrobatic:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Vehicle Acrobatics");
		if (Menu::Option("Front Flip")) {
			int veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, 0, 0, 6.0f, 0, -2.0f, 0, true, true, true, true, false, true);
		}
		if (Menu::Option("Back Flip")) {
			int veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, 0, 0, 6.0f, 0, 2.0f, 0, true, true, true, true, false, true);
		}
		if (Menu::Option("Kick Flip")) {
			int veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, 0, 0, 5.0f, 2.0f, 0, 0, true, true, true, true, false, true);
		}
		if (Menu::Option("Heel Flip")) {
			int veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, 0, 0, 5.0f, -2.0f, 0, 0, true, true, true, true, false, true);
		}
		if (Menu::Option("Bunny Hop")) {
			int veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, 0, 0, 7.0f, 0, 0, 0, true, true, true, true, false, true);
		}
		if (Menu::Option("Launch Up")) {
			int veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, 0, 0, 40.0f, 0, 0, 0, true, true, true, true, false, true);
		}
		if (Menu::Option("Crush Vehicle")) {
			int veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, 0, 0, -40.0f, 0, 0, 0, true, true, true, true, false, true);
		}
	}
	break;
	case VehWeapon:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Vehicle Weapons");
		Menu::Toggle("Shoot Rockets", Features::ShootR, [] { Features::ShootRocket(Features::ShootR); });
		Menu::Toggle("Shoot FireWorks", Features::ShootT, [] { Features::ShootTanks(Features::ShootT); });
		Menu::Toggle("Shoot Tank Rounds", Features::ShootTankR, [] { Features::ShootTankRounds(Features::ShootTankR); });
		Menu::Toggle("Shoot Balls", Features::ShootBall, [] { Features::ShootBalls(Features::ShootBall); });
		Menu::Toggle("Shoot flamethrower", Features::ShootFlare, [] { Features::Shootflare(Features::ShootFlare); });
		Menu::Toggle("Shoot Bullet", Features::ShootMini, [] { Features::ShootMiniGun(Features::ShootMini); });
		Menu::Toggle("Shoot Green Laser", Features::Laser1, [] { Features::laser1(Features::Laser1); });
		Menu::Toggle("Shoot Red Laser", Features::RLaser, [] { Features::Rlaser(Features::RLaser); });
	}
	break;
#pragma endregion

#pragma region world
	case world:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("World options");
		Menu::MenuOption("Time", world_timemenu);
		Menu::MenuOption("Weather", world_weathermenu);
		Menu::MenuOption("IPLs", world_iplmenu);
		Menu::MenuOption("Map Mods", world_mapmodmenu);
		Menu::MenuOption("Drive train", driveTrain);
		Menu::MenuOption("Black Hole", black_hole);
		Menu::Toggle("Footsteps", Features::footstepBool, [] { Features::footsteps(); });
		Menu::Toggle("Moon gravity", Features::moongrav, [] { Features::MoonGrav(Features::moongrav); });
		Menu::Toggle("Thunderstorm", Features::thunderbool, [] { Features::thunder(Features::thunderbool); });
		Menu::Toggle("Asteroid shower", Features::asteroidshower, [] { Features::AsteroidShower(Features::asteroidshower); });
	}
	break;
	case black_hole:

	case driveTrain:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Train options");
		Menu::Float("Train speed", Features::trainSpeed, 1, 100);
		if (Menu::Option("Delete train")) {
			Features::deleteTrain();
		}
		if (Menu::Option("Spawn train 1")) { Features::spawnTrain(Freight0); }
		if (Menu::Option("Spawn train 2")) { Features::spawnTrain(Freight01); }
		if (Menu::Option("Spawn train 3")) { Features::spawnTrain(Freight02); }
		if (Menu::Option("Spawn train 4")) { Features::spawnTrain(Freight03); }
		if (Menu::Option("Spawn train 5")) { Features::spawnTrain(Freight04); }
		if (Menu::Option("Spawn train 6")) { Features::spawnTrain(Freight05); }
		if (Menu::Option("Spawn train 7")) { Features::spawnTrain(Freight06); }
		if (Menu::Option("Spawn train 8")) { Features::spawnTrain(Freight07); }
		if (Menu::Option("Spawn train 9")) { Features::spawnTrain(Freight08); }
		if (Menu::Option("Spawn train 10")) { Features::spawnTrain(Freight09); }
		if (Menu::Option("Spawn train 11")) { Features::spawnTrain(Freight10); }
		if (Menu::Option("Spawn train 12")) { Features::spawnTrain(Freight11); }
		if (Menu::Option("Spawn train 13")) { Features::spawnTrain(Freight12); }
		if (Menu::Option("Spawn train 14")) { Features::spawnTrain(Freight13); }
		if (Menu::Option("Spawn train 15")) { Features::spawnTrain(Freight14); }
		if (Menu::Option("Spawn metro 1")) { Features::spawnTrain(Metro0); }
		if (Menu::Option("Spawn metro 2")) { Features::spawnTrain(Metro01); }

	}
	break;
	case world_mapmodmenu:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Map mods");
		Menu::MenuOption("Maze Bank Small Ramp", ramp1);
		Menu::MenuOption("Maze Bank Roof Ramp", ramp2);
		Menu::MenuOption("Beach Ramp", ramp3);
		Menu::MenuOption("Mount Chilliad Ramp", ramp4);
		Menu::MenuOption("Airport Mini Ramp", ramp5);
		Menu::MenuOption("Airport Gate Ramp", ramp6);
		Menu::MenuOption("Space Tower", ramp7);
		Menu::MenuOption("Exploit Quad Ramp", ramp8);
		Menu::MenuOption("Exploit Fort", ramp9);
		Menu::MenuOption("Halfpipe", ramp10);
		Menu::MenuOption("Airport Loop Ramp", ramp11);
		Menu::MenuOption("Mega Ramp", ramp12);
	}
	break;
	case world_timemenu:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Time");
		int h = TIME::GET_CLOCK_HOURS();
		int m = TIME::GET_CLOCK_MINUTES();
		int s = TIME::GET_CLOCK_SECONDS();
		Menu::Toggle("Sync System Time", synctime);
		if (Menu::Toggle("freeze Time", freezeTime)) { frozenTimeH = h; frozenTimeM = m; frozenTimeS = s; }
		if (Menu::Int("Hour",  h, 0, 23)) SetTime(h, m, s);
		if (Menu::Int("Minute",  m, 0, 60)) SetTime(h, m, s);
		if (Menu::Int("Second", s, 0, 60)) SetTime(h, m, s);

	}
	break;

	case world_weathermenu:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Weather");
		for (int i = 0; i < sizeof(weatherTypes) / sizeof(*weatherTypes); i++) {
				if (Menu::Option(weatherTypes[i])) SetWeather(weatherTypes[i]);
		}
	}
	break;
	case world_iplmenu:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("IPL");
		Menu::MenuOption("Cargoshop", world_iplmenu_cargoship);
		Menu::MenuOption("Train Crash Bridge", world_iplmenu_traincrashbridge);
		Menu::MenuOption("Clucking Bell", world_iplmenu_cluckingbell);
		Menu::MenuOption("Broken Stilt House", world_iplmenu_brokenstilthouse);
		Menu::MenuOption("Carrier", world_iplmenu_carrier);
		Menu::MenuOption("Yacht", world_iplmenu_yacht);
		Menu::MenuOption("Lester's Factory", world_iplmenu_lestersfactory);
		Menu::MenuOption("North Yankton", world_iplmenu_northyankton);
		Menu::MenuOption("Hospital", world_iplmenu_hospital);
		Menu::MenuOption("Life Invader", world_iplmenu_lifeinvader);
		Menu::MenuOption("Jewelry Store", world_iplmenu_jewelrystore);
		Menu::MenuOption("Morgue", world_iplmenu_morgue);
		Menu::MenuOption("FIB Lobby", world_iplmenu_fiblobby);
		Menu::MenuOption("Plane Crash", world_iplmenu_planecrash);
		Menu::MenuOption("UFOs", world_iplmenu_ufos);
		Menu::MenuOption("Bahama Mamas", world_iplmenu_bahamamamas);
		Menu::MenuOption("Stadium", world_iplmenu_stadium);
		Menu::MenuOption("Psych Office", world_iplmenu_psychoffice);
		Menu::MenuOption("Tequl la la", world_iplmenu_tequllala);
		Menu::MenuOption("Showroom", world_iplmenu_showroom);
		Menu::MenuOption("Union Deposity", world_iplmenu_uniondeposity);
	}
	break;
	case world_iplmenu_cargoship:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Cargoshop");
		bool loaded = STREAMING::IS_IPL_ACTIVE("cargoship");
		if (Menu::Toggle("Load", loaded)) { toggleCargoShip(loaded); }
		if (Menu::Option("Teleport")) TPto({ -162.8918f, 0, -2365.769f, 0, 0.f, 0 });
	}
	break;
	case world_iplmenu_traincrashbridge:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Traincrash Bridge IPL");
		bool loaded = STREAMING::IS_IPL_ACTIVE("canyonriver01");
		bool extra1 = STREAMING::IS_IPL_ACTIVE("canyonriver01_traincrash");
		if (Menu::Toggle("Load", loaded)) toggleTrainCrashBridge(loaded);
		if (Menu::Toggle("Destroyed", extra1)) toggleTrainCrashBridgeExtra1(extra1);
		if (Menu::Option("Teleport")) TPto({ -532.1309f, 0, 4526.187f, 0, 88.7955f, 0 });
	}
	break;
	case world_iplmenu_cluckingbell:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Clucking Bell IPL");
		bool loaded = STREAMING::IS_IPL_ACTIVE("CS1_02_cf_onmission1");
		bool extra1 = !STREAMING::IS_IPL_ACTIVE("CS1_02_cf_offmission");
		if (Menu::Toggle("Load", loaded)) toggleCluckingBell(loaded);
		if (Menu::Toggle("Open Gates", extra1)) toggleCluckingBellExtra1(extra1);
		if (Menu::Option("Teleport")) TPto({ -146.3837f, 0, 6161.5f, 0, 30.f, 0 });
	}
	break;
	case world_iplmenu_brokenstilthouse:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Broken Stilthouse IPL");
		bool loaded = STREAMING::IS_IPL_ACTIVE("DES_StiltHouse_imapstart");
		if (Menu::Toggle("Load",loaded)) toggleBrokenStiltHouse(loaded);
		if (Menu::Option("Teleport")) TPto({ -1020.5f, 0, 663.41f, 0, 154.75f , 0 });
	}
	break;
	case world_iplmenu_carrier:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Carrier IPL");
		bool loaded = STREAMING::IS_IPL_ACTIVE("hei_carrier");
		if (Menu::Toggle("Load", loaded)) toggleCarrier(loaded);
		if (Menu::Option("Teleport")) TPto({ 3069.98f, 0, -4632.49f, 0, 16.26f, 0 });
	}
	break;
	case world_iplmenu_yacht:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Yacht");
		bool loaded = STREAMING::IS_IPL_ACTIVE("hei_yacht_heist");
		if (Menu::Toggle("Load",loaded)) toggleYacht(loaded);
		if (Menu::Option("Teleport")) TPto({ -2043.974f, 0, -1031.582f, 0, 11.981f, 0 });
	}
	break;
	case world_iplmenu_lestersfactory:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Lester's factory");
		bool loaded = STREAMING::IS_IPL_ACTIVE("id2_14_during_door");
		bool extra1 = STREAMING::IS_IPL_ACTIVE("id2_14_on_fire");
		if (Menu::Toggle("Load",loaded)) toggleLestersFactory(loaded);
		if (Menu::Toggle("On Fire", extra1)) toggleLestersFactoryExtra1(extra1);
		if (Menu::Option("Teleport")) TPto({ 716.84f, 0, -962.05f, 0, 31.59f, 0 });
	}
	break;
	case world_iplmenu_northyankton:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("North Yankton");
		bool loaded = STREAMING::IS_IPL_ACTIVE("prologue01");
		if (Menu::Toggle("Load", loaded)) toggleNorthYankton(loaded);
		if (Menu::Option("Teleport")) TPto({ 3360.19f, 0, -4849.67f, 0, 111.8f, 0 });
	}
	break;
	case world_iplmenu_hospital:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Hospital");
		bool loaded = STREAMING::IS_IPL_ACTIVE("RC12B_HospitalInterior");
		if (Menu::Toggle("Load", loaded)) toggleHospital(loaded);
		if (Menu::Option("Teleport")) TPto({ 356.8f, 0, -590.1f, 0, 43.3f, 0 });
	}
	break;
	
	case world_iplmenu_lifeinvader:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Life Invader");
		bool loaded = STREAMING::IS_IPL_ACTIVE("facelobby");
		if (Menu::Toggle("Load", loaded)) toggleLifeInvader(loaded);
		if (Menu::Option("Teleport")) TPto({ -1047.9f, 0, -233.0f, 0, 39.0f, 0 });
	}
	break;
	case world_iplmenu_jewelrystore:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Jewelry Store");
		bool loaded = STREAMING::IS_IPL_ACTIVE("jewel2fake");
		if (Menu::Toggle("Load", loaded)) toggleJewelryStore(loaded);
		if (Menu::Option("Teleport")) TPto({ -630.4f, 0, -236.7f, 0, 40.0f, 0 });
	}
	break;
	case world_iplmenu_morgue:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Morgue");
		bool loaded = STREAMING::IS_IPL_ACTIVE("Coroner_Int_on");
		bool extra1 = STREAMING::IS_IPL_ACTIVE("coronertrash");
		if (Menu::Toggle("Load", loaded)) toggleMorgue(loaded);
		if (Menu::Toggle("Trashed", extra1)) toggleMorgueExtra1(extra1);
		if (Menu::Option("Teleport")) TPto({ 244.9f, 0, -1374.7f, 0, 39.5f, 0 });
	}
	break;
	case world_iplmenu_fiblobby:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("FIB Lobby");
		bool loaded = STREAMING::IS_IPL_ACTIVE("FIBlobby");
		if (Menu::Toggle("Load", loaded)) toggleFibLobby(loaded);
		if (Menu::Option("Teleport")) TPto({ 110.4f, 0, -744.2f, 0, 45.7f, 0 });
	}
	break;
	case world_iplmenu_planecrash:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Plane Crash");
		bool loaded = STREAMING::IS_IPL_ACTIVE("Plane_crash_trench");
		if (Menu::Toggle("Load", loaded)) togglePlaneCrash(loaded);
		if (Menu::Option("Teleport")) TPto({ 2814.7f, 0, 4758.5f, 0, 50.0f, 0 });
	}
	break;
	case world_iplmenu_ufos:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("UFOs");
		bool loaded = STREAMING::IS_IPL_ACTIVE("ufo");
		if (Menu::Toggle("Load", loaded)) toggleUFO(loaded);
		if (Menu::Option("Teleport (1)")) TPto({ -2051.99463f, 0, 3237.05835f, 0, 1456.97021f, 0 });
		if (Menu::Option("Teleport (2)")) TPto({ 2490.47729f, 0, 3774.84351f, 0, 2414.035f, 0 });
	}
	break;
	case world_iplmenu_bahamamamas:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Bahama Mamas");
		bool loaded = STREAMING::IS_IPL_ACTIVE("v_bahama");
		if (Menu::Toggle("Load", loaded)) toggleBahamaMamas(loaded);
		if (Menu::Option("Teleport")) TPto({ -1388.0013427734375f, 0, -618.419677734375f, 0, 30.819599151611328f, 0 });
	}
	break;
	case world_iplmenu_stadium:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Stadium");
		bool loaded = STREAMING::IS_IPL_ACTIVE("sp1_10_real_interior");
		if (Menu::Toggle("Load", loaded)) toggleStadium(loaded);
		if (Menu::Option("Teleport")) TPto({ 99.f, 0, 99.f, 0, 99.f, 0 });
	}
	break;
	case world_iplmenu_psychoffice:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Psych Office");
		bool loaded = STREAMING::IS_IPL_ACTIVE("v_psycheoffice");
		if (Menu::Toggle("Load", loaded)) togglePsychOffice(loaded);
		if (Menu::Option("Teleport")) TPto({ -1906.7857666015625f, 0, -573.7576293945312f, 0, 19.077299118041992f, 0 });
	}
	break;
	case world_iplmenu_tequllala:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Tequl La La");
		bool loaded = STREAMING::IS_IPL_ACTIVE("v_rockclub");
		if (Menu::Toggle("Load", loaded)) toggleTequllala(loaded);
		if (Menu::Option("Teleport")) TPto({ -556.5089111328125f, 0, 286.318115234375f, 0, 81.1763f, 0 });
	}
	break;
	case world_iplmenu_showroom:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Showroom");
		bool loaded = STREAMING::IS_IPL_ACTIVE("v_carshowroom");
		bool extra1 = STREAMING::IS_IPL_ACTIVE("shutter_open");
		if (Menu::Toggle("Load", loaded)) toggleShowRoom(loaded);
		if (Menu::Toggle("Open Shutters", extra1)) toggleShowRoomExtra1(extra1);
		if (Menu::Option("Teleport")) TPto({ -30.8793f, 0, -1088.336f, 0, 25.4221f, 0 });
	}
	break;
	case world_iplmenu_uniondeposity:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Union Deposity");
		bool loaded = STREAMING::IS_IPL_ACTIVE("FINBANK");
		bool extra1 = STREAMING::IS_IPL_ACTIVE("DT1_03_Shutter");;
		if (Menu::Toggle("Load", loaded)) toggleUnionDeposity(loaded);
		if (Menu::Toggle("Open Garage", extra1)) toggleUnionDeposityExtra1(extra1);
		if (Menu::Option("Teleport")) TPto({ 2.69689322f, 0, -667.0166f, 0, 16.1306286f, 0 });
		if (Menu::Option("Teleport (Garage)")) TPto({ 23.9346f, 0, -669.7552f, 0, 30.8853f, 0 });
	}
	break;
#pragma endregion 

#pragma region misc
	case misc:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Misc options");
		Menu::MenuOption("Money items", m_items); //TO DO: Set to money drop, recovery, moneygun, ...
		Menu::MenuOption("Stat viewer", statview);
		Menu::MenuOption("Money display", cheatedmoney);
		Menu::MenuOption("Screen effects", drugs);
		Menu::MenuOption("Edit phone", phone);
		Menu::Toggle("Show FPS", Features::DisplayFPS, [] { Features::fDisplayFPS(Features::DisplayFPS); });
		Menu::Toggle("Nightvision", Features::nightvisionbool, [] { Features::nightvision(Features::nightvisionbool); });
		Menu::Toggle("Thermal vision", Features::thermalvisionbool, [] { Features::thermalvision(Features::thermalvisionbool); });
		Menu::Toggle("Drunk audio", Features::drunk, [] { Features::Drunk(Features::drunk); });
	//	Menu::Toggle("Mobile radio", Features::mobRadio, [] { Features::mobileRadio(Features::mobRadio); });
		Menu::Toggle("Unlimited orbital cannon", Features::unlimitedorbitalcannon, [] { Features::UnlimitedORbitalCannon(Features::unlimitedorbitalcannon); });
		if (Menu::Option("Reset vehicle sell time")) {
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VEHICLE_SELL_TIME"), 0, true);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MONEY_EARN_SELLING_VEH"), 50000, true);
			STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MONEY_EARN_SELLING_VEH"), 50000, true);
		}

	}
	break;
	case m_items:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Money items");
		switch (Features::MoneyItem) {
		case 19: Menu::Option("Selected: Ramp"); break;
		case 20: Menu::Option("Selected: Number 1"); break;
		case 21: Menu::Option("Selected: Number 2"); break;
		case 22: Menu::Option("Selected: Number 3"); break;
		case 23: Menu::Option("Selected: Plane"); break;
		case 24: Menu::Option("Selected: Cash pile"); break;
		case 25: Menu::Option("Selected: Donut"); break;
		case 26: Menu::Option("Selected: Ferris wheel"); break;
		}
		}
	}
	break;
#pragma endregion 

#pragma region recovery

	case recovery:
	{
		Menu::Title(Menu::Settings::menuname);
		//Menu::Break("Recovery");
		Menu::Break("Recovery options");
		Menu::Toggle("SC Page Stat", scstat);
		if (Features::enableMoney) { Menu::MenuOption("Money", r_money); }
		if (!Features::enableMoney) {
			if (Menu::Option("2 Mil Stealth"))
			{
				Any var0 = rndInt(0, INT_MAX - 1);
				Any var3[2] = { 0xFFFFFFFFA174F633, 0xFFFFFFFFAEF994E9 };
				UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&var0, 1474183246, Features::removee ? var3[1] : var3[0], Features::removee ? 537254313 : 1445302971, 2000000, Features::toBank ? 4 : 1);
				UNK3::_NETWORK_SHOP_CHECKOUT_START(var0);
				Log::Msg("Generated %i Dollars with the Hash 0x%i", 2000000, (int)var0);

				//optional
				
			}
			if (scstat) {
				int iVar0;
				int iVar1;
				STATS::STAT_GET_INT($("MPPLY_LAST_MP_CHAR"), &iVar0, 1);
				STATS::STAT_GET_INT($("MP" + std::to_string(iVar0) + "_MONEY_EARN_JOBS"), &iVar1, -1);
				STATS::STAT_SET_INT($("MP" + std::to_string(iVar0) + "_MONEY_EARN_JOBS"), iVar1 + 2000000, 1);

			}
		}
		Menu::MenuOption("Bank", moneybank);
		Menu::MenuOption("Levels", r_levels);
		Menu::MenuOption("Unlocks", r_unlocks);
		Menu::MenuOption("Stat editor", stateditor);
		Menu::MenuOption("Bunker research", bunkerresearch);
		Menu::MenuOption("Tunables", FeaturesS);
		Menu::MenuOption("Tunables (Risky)", online_tunablemenu);
	}
	break;

	case r_money:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Money options");
		//Menu::Toggle("Self drop (Normal)", Features::selfdrop, [] { Features::Selfdrop(Features::selfdrop, 1, Features::MoneyItem, 2500); });
		//Menu::Toggle("Self drop (spread)", Features::selfSpreadDropBool, [] { Features::selfSpreadDrop(Features::selfSpreadDropBool); });
		//Menu::Toggle("Self drop (rain)", Features::selfRainDropBool, [] { Features::selfRainDrop(Features::selfRainDropBool); });
		Menu::MenuOption("Custom drop", dropmenyoo2);
		//Menu::MenuOption("Custom stealth", customstealth);
		Menu::Toggle("To bank", Features::toBank);
		Menu::Toggle("Remove money", Features::removee);
		//Menu::Toggle("Self drop (10k)", Features::selftenkped, [] { Features::selfTenKPedMoney(Features::selftenkped); });
		
		
		if (Menu::Option("8 Mil Stealth"))
		{
			Any var0 = rndInt(0, INT_MAX - 1);
			globalHandle(0x41104F).As<int>() = var0;
			globalHandle(0x411054).As<int>() = 0;
			globalHandle(0x411053).As<int>() = 0;
			globalHandle(0x411051).As<int>() = 0xFFFFFFFFA174F633, 0xFFFFFFFFAEF994E9;
			globalHandle(0x411050).As<int>() = 8000000;
			globalHandle(0x41104E).As<int>() = Features::toBank;
			Log::Msg("Generated %i Dollars with the Hash 0x%i", 80000000, (int)var0);
			
		}
	
		if (Menu::Option("7 Mil Stealth"))
		{
			Any var0 = rndInt(0, INT_MAX - 1);
			Any var3[2] = { 0xFFFFFFFFA174F633, 0xFFFFFFFFAEF994E9 };
			UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&var0, 1474183246, Features::removee ? var3[1] : var3[0], Features::removee ? 537254313 : 1445302971, 7000000, toBank ? 4 : 1);
			UNK3::_NETWORK_SHOP_CHECKOUT_START(var0);
			Log::Msg("Generated %i Dollars with the Hash 0x%i", 7000000, (int)var0);
			Features::removee ? Features::stealthMoneyCounter -= 7000000 : Features::stealthMoneyCounter += 7000000;
		}
		if (Menu::Option("6 Mil Stealth"))
		{
			Any var0 = rndInt(0, INT_MAX - 1);
			Any var3[2] = { 0xFFFFFFFFA174F633, 0xFFFFFFFFAEF994E9 };
			UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&var0, 1474183246, Features::removee ? var3[1] : var3[0], Features::removee ? 537254313 : 1445302971, 6000000, toBank ? 4 : 1);
			UNK3::_NETWORK_SHOP_CHECKOUT_START(var0);
			Log::Msg("Generated %i Dollars with the Hash 0x%i", 6000000, (int)var0);
			Features::removee ? Features::stealthMoneyCounter -= 6000000 : Features::stealthMoneyCounter += 6000000;
		}
		if (Menu::Option("5 Mil Stealth"))
		{
			Any var0 = rndInt(0, INT_MAX - 1);
			Any var3[2] = { 0xFFFFFFFFA174F633, 0xFFFFFFFFAEF994E9 };
			UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&var0, 1474183246, Features::removee ? var3[1] : var3[0], Features::removee ? 537254313 : 1445302971, 5000000, toBank ? 4 : 1);
			UNK3::_NETWORK_SHOP_CHECKOUT_START(var0);
			Log::Msg("Generated %i Dollars with the Hash 0x%i", 5000000, (int)var0);
			Features::removee ? Features::stealthMoneyCounter -= 5000000 : Features::stealthMoneyCounter += 5000000;
		}
		if (Menu::Option("4 Mil Stealth"))
		{
			Any var0 = rndInt(0, INT_MAX - 1);
			Any var3[2] = { 0xFFFFFFFFA174F633, 0xFFFFFFFFAEF994E9 };
			UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&var0, 1474183246, Features::removee ? var3[1] : var3[0], Features::removee ? 537254313 : 1445302971, 4000000, toBank ? 4 : 1);
			UNK3::_NETWORK_SHOP_CHECKOUT_START(var0);
			Log::Msg("Generated %i Dollars with the Hash 0x%i", 4000000, (int)var0);
			Features::removee ? Features::stealthMoneyCounter -= 4000000 : Features::stealthMoneyCounter += 4000000;
		}
		if (Menu::Option("3 Mil Stealth"))
		{
			Any var0 = rndInt(0, INT_MAX - 1);
			Any var3[2] = { 0xFFFFFFFFA174F633, 0xFFFFFFFFAEF994E9 };
			UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&var0, 1474183246, Features::removee ? var3[1] : var3[0], Features::removee ? 537254313 : 1445302971, 3000000, toBank ? 4 : 1);
			UNK3::_NETWORK_SHOP_CHECKOUT_START(var0);
			Log::Msg("Generated %i Dollars with the Hash 0x%i", 3000000, (int)var0);
			Features::removee ? Features::stealthMoneyCounter -= 3000000 : Features::stealthMoneyCounter += 3000000;
		}
		if (Menu::Option("2 Mil Stealth"))
		{
			Any var0 = rndInt(0, INT_MAX - 1);
			Any var3[2] = { 0xFFFFFFFFA174F633, 0xFFFFFFFFAEF994E9 };
			UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&var0, 1474183246, Features::removee ? var3[1] : var3[0], Features::removee ? 537254313 : 1445302971, 2000000, toBank ? 4 : 1);
			UNK3::_NETWORK_SHOP_CHECKOUT_START(var0);
			Log::Msg("Generated %i Dollars with the Hash 0x%i", 2000000, (int)var0);
			Features::removee ? Features::stealthMoneyCounter -= 2000000 : Features::stealthMoneyCounter += 2000000;
		}
		if (Menu::Option("1 Mil Stealth"))
		{
			Any var0 = rndInt(0, INT_MAX - 1);
			Any var3[2] = { 0xFFFFFFFFA174F633, 0xFFFFFFFFAEF994E9 };
			UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&var0, 1474183246, Features::removee ? var3[1] : var3[0], Features::removee ? 537254313 : 1445302971, 1000000, toBank ? 4 : 1);
			UNK3::_NETWORK_SHOP_CHECKOUT_START(var0);
			Log::Msg("Generated %i Dollars with the Hash 0x%i", 1000000, (int)var0);
			Features::removee ? Features::stealthMoneyCounter -= 1000000 : Features::stealthMoneyCounter += 1000000;
		}
		/*if (Menu::Option("Remove all money")) {
			Features::flushMoney();
		}*/
	}
	break;
	case customstealth:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Custom stealth");
		Menu::Int("Amount", Features::stealthAmount, 100000, 8000000, 100000);
		Menu::Int("Delay", Features::stealthDelay, 0, 10000, 100);
		Menu::Toggle("To bank", Features::toBank);
		Menu::Toggle("Remove money", Features::removee);
		if (Features::stealthBool) {
			Menu::Option("Looped");
		}
		else {
			Menu::Toggle("Looped", Features::stealthLooped);
		}
		if (Features::stealthLooped) {
			Menu::Toggle("Stealth loop", Features::stealthBool, [] { Features::stealthLoop(Features::stealthBool); });
		}
		else {
			if (Menu::Option("Stealth")) {
				if (Features::stealthAmount < 10000001) {
					globalHandle(0x41104E + 1).As <int>() = INT_MAX - 1;
					globalHandle(0x41104E + 7).As <int>() = INT_MAX;
					globalHandle(0x41104E + 6).As <int>() = 0;
					globalHandle(0x41104E + 5).As <int>() = 0;
					globalHandle(0x41104E + 3).As <int>() = 312105838;
					globalHandle(0x41104E + 2).As <int>() = Features::stealthAmount;
					globalHandle(0x41104E).As <int>() = 1;

					//optional
					int iVar0;
					int iVar1;
					STATS::STAT_GET_INT($("MPPLY_LAST_MP_CHAR"), &iVar0, 1);
					STATS::STAT_GET_INT($("MP" + std::to_string(iVar0) + "_MONEY_EARN_JOBS"), &iVar1, -1);
					STATS::STAT_SET_INT($("MP" + std::to_string(iVar0) + "_MONEY_EARN_JOBS"), iVar1 + Features::stealthAmount, 1);
					Features::removee ? Features::stealthMoneyCounter -= Features::stealthAmount : Features::stealthMoneyCounter += Features::stealthAmount;
				}
				else {
					globalHandle(0x41104E + 1).As <int>() = INT_MAX - 1;
					globalHandle(0x41104E + 7).As <int>() = INT_MAX;
					globalHandle(0x41104E + 6).As <int>() = 0;
					globalHandle(0x41104E + 5).As <int>() = 0;
					globalHandle(0x41104E + 3).As <int>() = -1359375127;
					globalHandle(0x41104E + 2).As <int>() = Features::stealthAmount;
					globalHandle(0x41104E).As <int>() = 1;
					Features::removee ? Features::stealthMoneyCounter -= Features::stealthAmount : Features::stealthMoneyCounter += Features::stealthAmount;
				}
			}
		}
	}
#pragma endregion

	case testt:
	{
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
		Menu::Drawing::Spriter("textures", "lsc", Menu::Settings::menuX, Menu::Settings::menuY + 0.0820f, Menu::Settings::menuWidth, Menu::Settings::headerHeight, 0.f, 255, 255, 255, Menu::Settings::headerTransparancy);
		//Menu::Title(Menu::Settings::menuname);
		Menu::Break("LSC Customs");
		Vehicle veh = getVeh(getPlayer());
		
		    if (Menu::Option("Max Upgrade")) Features::MaxUpgrade(veh);
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
			bool turbo = VEHICLE::IS_TOGGLE_MOD_ON(veh, VehicleToggleModTurbo);
			if (Menu::VehicleModOption("Turbo", turbo)) VEHICLE::TOGGLE_VEHICLE_MOD(veh, VehicleToggleModTurbo, !turbo);
			Menu::MenuOption("Lights", vehiclemod_lightmenu);
			Menu::MenuOption("Paint", vehiclemod_paintmenu);
			Menu::MenuOption("Wheels Options", Wheels);
			for (int i = 0; i < 48; i++) {
				if (Features::HasModType(veh, i)) {
					
						if (Menu::MenuOption(getModName(veh, i), vehiclemod_selectedmodmenu)) selectedModShopType = i;
					
				}
			}
			Menu::MenuOption("Extras", vehiclemod_extramenu);
		
	}
	break;



#pragma region Weapons
	case weapons:
	{
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
		Menu::Drawing::Spriter("textures", "weapons", Menu::Settings::menuX, Menu::Settings::menuY + 0.0820f, Menu::Settings::menuWidth, Menu::Settings::headerHeight, 0.f, 255, 255, 255, Menu::Settings::headerTransparancy);
		//Menu::Title(Menu::Settings::menuname);
		Menu::Break("Weapons");
		Menu::MenuOption("Give weapons", giveweaponz);
		//Menu::MenuOption("Weapon customization", weaponlsc);
		//Menu::MenuOption("Vehicle Gun", vehiclegun);
		Menu::MenuOption("Prop Gun", propgun);
		Menu::MenuOption("Weapon FX", wep_fx);
		Menu::MenuOption("Kill Spoofer", killspoofer_1);
		if (Menu::Option("Max Ammo"))
		{
			Hash weaponhash;
			WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponhash, 1);
			WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), weaponhash, 9999);
		}
		Menu::Float("Bullet Damage", Features::DMG, 1.0f, 10000.0f, 1000.0f);
		Menu::Toggle("Triggerbot", Features::Aimbot);
		Menu::Toggle("Aim bot", Features::Triggerbool);
		Menu::Toggle("Explosive Ammo", Features::Fireammo);
		Menu::Toggle("Fire  Ammo", Features::expoammo);
		Menu::Toggle("Explosive  Melee", Features::expomeal);
		Menu::Toggle("One Shot Kill", Features::osk);
		Menu::Toggle("Infinite Ammo", Features::InfiniteAmmo);
		Menu::Toggle("Money Ammo", Features::remoteMoneygunn);
		Menu::Toggle("Fake Money Ammo", Features::FakeBags);
		Menu::Toggle("Rapid Fire", rapidfirer);
		Menu::Toggle("Teleport Gun", TeleportGun);
		Menu::Toggle("Rain Rocket", rainrocketss);
		Menu::Toggle("Valkyire Rocket", VALKYIREROCKET);
		Menu::Toggle("Shoot Weapons", rainweapoms);
		Menu::Toggle("Laser", Laser);
		Menu::Toggle("Gravity Gun (Pistol Only)", gravegun);
		Menu::Toggle("Airstrike Gun", airestrickgun);

	}
	break;
	

#pragma region protections 

#pragma endregion
#pragma region self option
	case self:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Self Option");
		Menu::MenuOption("Animations", animationself);
		Menu::MenuOption("Model changer", modelchanger);
		Menu::MenuOption("Walking Styles", Walking);
		Menu::MenuOption("Scenarios", player_scenariomenu);
		Menu::MenuOption("Ped Size Changer", sizze);
		Menu::MenuOption("Outfit menu", OutfitMenu);
		Menu::MenuOption("Particles", player_ptfxmenu);
		Menu::MenuOption("Change Name", change_name);
		Menu::Toggle("Godmode", Features::GodMode, [] { Features::godmode(Features::GodMode); });
		Menu::Toggle("Armor", Features::isAutoRegArmour, [] { Features::AutoRegArmour(Features::isAutoRegArmour); });
		}
		Menu::Toggle("Cops turn blind eye", Features::ctbBool, [] { Features::copsturnblind(); });
		Menu::Toggle("Ignored by all peds", Features::ignored, [] { Features::nobody(); });
		Menu::Option("Clean Ped", [] { int Ped = PLAYER::PLAYER_PED_ID(); PED::CLEAR_PED_BLOOD_DAMAGE(Ped); PED::RESET_PED_VISIBLE_DAMAGE(Ped); });
		if (Menu::Option("New Look")) { PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), true); }
		if (Menu::Option("Reset Player")) { Ped playerPed = PLAYER::PLAYER_PED_ID(); PED::SET_PED_DEFAULT_COMPONENT_VARIATION(playerPed); }
	}
	break;

	case player_ptfxmenu:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Particles");
		for (int i = 0; i < sizeof(ptfxs) / sizeof(*ptfxs); i++)
		{
			if (Menu::Option(ptfxs[i][0])) Features::startTriggerFX(ptfxs[i][1], ptfxs[i][2]);
		}
		if (Menu::MenuOption("All Particles", allptfxmenu)) { globalTitleText = "Player"; playerPtfxTarget = true; pPtfxsTarget = selfPlayer; }
	}
	break;
	
	case player_scenariomenu:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Scenarios");
		if (Menu::Option("None")) Features::stopAnimation();
		for (int i = 0; i < sizeof(sceneraios) / sizeof(*sceneraios); i++)
		{
			if (Menu::Option(getScenerioName($(sceneraios[i])))) Features::playScenario(sceneraios[i]);
		}
	}

	case Walking:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Walk Animations");
		if (Menu::Option("Reset")) Features::resetWalkAnimation();
		for (int i = 0; i < sizeof(WalkStyles) / sizeof(*WalkStyles); i++)
		{
			if (Menu::Option(WalkStyles[i][0]))
				//Menu::StringToChar(std::string(WalkStyles[i][0])) 
				Features::changeWalkAnimation(WalkStyles[i][1]);
		}
	}
	break;


#pragma endregion
#pragma region online players
	case online:
	{
		Menu::Title(Menu::Settings::menuname);
		Menu::Break("Online Players");

		for (int i = 0; i < 32; ++i) {
			Player isFriend = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);

			int index = 1383712;
			char* headShot;

			char buffer[0x400];
			//bool is_mod = Features::isPlayerGodmodder(ped);
			bool is_friend;
			bool handle_valid = Features::isPlayerFriend(i, is_friend);
			//bool isIn = INTERIOR::IS_VALID_INTERIOR(INTERIOR::GET_INTERIOR_FROM_ENTITY(ped));

			if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) {

				int index = 1383712;
				char* headShot;
				Player isFriend = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
				bool is_friend;
				bool handle_valid = Features::isPlayerFriend(i, is_friend);
				const char* playerTag;


				if (NETWORK::NETWORK_IS_SESSION_STARTED()) {
					for (int x = 0; x <= 150; x += 5) {
						int playerId = globalHandle(index).At(x).As<int>();

						if (playerId == i) {
							int logo = globalHandle(index).At(x).At(1).As<int>();
							headShot = PED::GET_PEDHEADSHOT_TXD_STRING(logo);

							if (NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0) == i) {
								playerTag = Features::setPlayerName(i, " ~y~[HOST]");
							}
							else if (handle_valid && is_friend) {
								playerTag = Features::setPlayerName(i, " ~g~[FRIEND]");
							}
								else if (Features::isPlayerModder(i)) {
									playerTag = Features::setPlayerName(i, " ~r~[MODDER]");
								}
							else if (isFriend == PLAYER::PLAYER_PED_ID()) {
								playerTag = Features::setPlayerName(i, " ~b~[SELF]");
							}
							else {
								playerTag = PLAYER::GET_PLAYER_NAME(i);
							}

							Menu::MenuPlayer(playerTag, headShot, onlinemenu_selected, i) ? Features::Online::selectedPlayer = i : NULL;
						}
					}
				}
				else {
					selected, i) ? Features::Online::selectedPlayer = i : NULL;
					break;
				}
			}


		}


	}
	break;

	case onlinemenu_selected: 
	{
		networkClanMgr Jclancxt;
		networkHandleMgr net;
		networkMembershipMgr memShip;
		
		if (selecArrow) {
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), false);
			GRAPHICS::DRAW_MARKER(offradardpl, coords.x, coords.y, coords.z + 1.3f, 0, 0, 0, 0, 180, 0, 0.3, 0.3, 0.3, r1, g1, b1, 200, 1, 1, 1, 0, 0, 0, 0);
		}
		Features::LoadPlayerInfo(PLAYER::GET_PLAYER_NAME(Features::Online::selectedPlayer), Features::Online::selectedPlayer);
		Menu::Title(Menu::Settings::menuname);
		Menu::Break(PLAYER::GET_PLAYER_NAME(Features::Online::selectedPlayer));
			Menu::Toggle("Spectate", Features::spectate[Features::Online::selectedPlayer], [] {
				Features::specter(Features::spectate[Features::Online::selectedPlayer]);
				});
		Menu::MenuOption("Marker Type", arrowsdraw);
		Menu::MenuOption("Teleport", playertp);
		Menu::MenuOption("Troll", playertroll);
		Menu::MenuOption("Spawn custom attacker", customenemy);
		Menu::MenuOption("Be Nice", playernice);
		Menu::MenuOption("Attachments", trollattachments);
		Menu::MenuOption("Vehicle acrobatics", acrobatics);
		Menu::MenuOption("Money Drop", money_drop);
		Menu::MenuOption("ESP", playeresp);
		Menu::MenuOption("Remote Troll", playerremote);
		Menu::MenuOption("Remote Teleport", playerremotetp);
	}
	break;

	case money_drop:
	{
		if (selecArrow) {
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), false);
			GRAPHICS::DRAW_MARKER(offradardpl, coords.x, coords.y, coords.z + 1.3f, 0, 0, 0, 0, 180, 0, 0.3, 0.3, 0.3, r1, g1, b1, 200, 1, 1, 1, 0, 0, 0, 0);
		}
		Features::LoadPlayerInfo(PLAYER::GET_PLAYER_NAME(Features::Online::selectedPlayer), Features::Online::selectedPlayer);
		Menu::Title(Menu::Settings::menuname);
		Menu::Break(PLAYER::GET_PLAYER_NAME(Features::Online::selectedPlayer));
	}
	break;
	case rPlanes:
		Menu::Title(Menu::Settings::menuname);
		Menu::Break(" ");
		for (auto car : Planes1) { Menu::Option(car, [car] { Features::remoteSpawnVehicle(car, Features::Online::selectedPlayer); }); }
		break;

	case rSUV:
		Menu::Title(Menu::Settings::menuname);
		Menu::Break(" ");
		for (auto car : SUVs1) { Menu::Option(car, [car] { Features::remoteSpawnVehicle(car, Features::Online::selectedPlayer); }); }
		break;
	case rTrailer:
		Menu::Title(Menu::Settings::menuname);
		Menu::Break(" ");
		for (auto car : Trailer1) { Menu::Option(car, [car] { Features::remoteSpawnVehicle(car, Features::Online::selectedPlayer); }); }
		break;
	case rTrains:
		Menu::Title(Menu::Settings::menuname);
		Menu::Break(" ");
		for (auto car : Trains1) { Menu::Option(car, [car] { Features::remoteSpawnVehicle(car, Features::Online::selectedPlayer); }); }
		break;
	case rUtility:
		Menu::Title(Menu::Settings::menuname);
		Menu::Break(" ");
		for (auto car : Utility1) { Menu::Option(car, [car] { Features::remoteSpawnVehicle(car, Features::Online::selectedPlayer); }); }
		break;
	case rVans:
		Menu::Title(Menu::Settings::menuname);
		Menu::Break(" ");
		for (auto car : Vans1) { Menu::Option(car, [car] { Features::remoteSpawnVehicle(car, Features::Online::selectedPlayer); }); }
		break;
	case rtrucks:
		Menu::Title(Menu::Settings::menuname);
		Menu::Break(" ");
		for (auto car : trucks1) { Menu::Option(car, [car] { Features::remoteSpawnVehicle(car, Features::Online::selectedPlayer); }); }
		break;

	}
	break;

	case playernice:
	{
		if (selecArrow) {
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), false);
			GRAPHICS::DRAW_MARKER(offradardpl, coords.x, coords.y, coords.z + 1.3f, 0, 0, 0, 0, 180, 0, 0.3, 0.3, 0.3, r1, g1, b1, 200, 1, 1, 1, 0, 0, 0, 0);
		}
		Features::LoadPlayerInfo(PLAYER::GET_PLAYER_NAME(Features::Online::selectedPlayer), Features::Online::selectedPlayer);
		Menu::Title(Menu::Settings::menuname);
		Menu::Break(PLAYER::GET_PLAYER_NAME(Features::Online::selectedPlayer));
		Menu::MenuOption("Mini-menu", minimenyoo);
		Menu::MenuOption("Give vehicle", mm_spawnvehicle);
	
		if (Menu::Option("Vehicle godmode")) {
			RequestControlOfEnt(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer));
			RequestControlOfEnt(PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer)));
			Features::cargodmode2(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer));
		}
		if (Menu::Option("Max vehicle")) {
			RequestControlOfEnt(PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer)));
			RequestControlOfEnt(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer));
			Features::maxvehicle2(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer));
		}
		//Menu::MenuOption("Invisible car", invisibleRemote);
		if (Menu::Option("Semi godmode")) {
			Features::semigod();
		}
		//Menu::Toggle("Horn boost", Features::remoteCarboostbool[Features::Online::selectedPlayer], [] { Features::remoteCarboost(Features::remoteCarboostbool[Features::Online::selectedPlayer]); });
		Menu::Toggle("Explosive gun", Features::remoteExplobool[Features::Online::selectedPlayer], [] { Features::remoteExplo(Features::remoteExplobool[Features::Online::selectedPlayer]); });
		Menu::Toggle("Asteroid gun", Features::playerAsteroidBool[Features::Online::selectedPlayer], [] { Features::playerAsteroidGun(Features::playerAsteroidBool[Features::Online::selectedPlayer]); });
		Menu::Toggle("Moneygun", Features::remoteMoneygunbool[Features::Online::selectedPlayer], [] { 
			Features::remoteMoneygun(Features::remoteMoneygunbool[Features::Online::selectedPlayer]);
			}); 
		
		if (Menu::Option("Whitelist")) { Features::write2("Apollo/friends/friend.txt", PLAYER::GET_PLAYER_NAME(Features::Online::selectedPlayer)); }
		if (Menu::Option("Copy outfit")) {
			Features::CopyOutfit(Features::Online::selectedPlayer);
		}
			Features::cage2(Features::Online::selectedPlayer);
		}
		Menu::Toggle("Fire loop", Features::playerfireloop[Features::Online::selectedPlayer], [] { Features::FireLoop(Features::playerfireloop[Features::Online::selectedPlayer]); });
		Menu::Toggle("Water loop", Features::playerwaterloop[Features::Online::selectedPlayer], [] { Features::WaterLoop(Features::playerwaterloop[Features::Online::selectedPlayer]); });
		if (Menu::Option("Clone Player"))
		{
			PED::CLONE_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), 1, 1, 1);
		}
		int eclone[1000];
		int egcount = 1;
		if (Menu::Option("OH DAMN!!!")) {
			Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
			if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
			Hash railgun = GAMEPLAY::GET_HASH_KEY("WEAPON_RAILGUN");
			Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
			Hash pedm = GAMEPLAY::GET_HASH_KEY("U_M_M_Jesus_01");
			STREAMING::REQUEST_MODEL(pedm);
			while (!STREAMING::HAS_MODEL_LOADED(pedm))
				WAIT(0);
			eclone[egcount] = PED::CREATE_PED(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
			ENTITY::SET_ENTITY_INVINCIBLE(eclone[egcount], false);
			PED::SET_PED_COMBAT_ABILITY(eclone[egcount], 100);
			WEAPON::GIVE_WEAPON_TO_PED(eclone[egcount], railgun, railgun, 9999, 9999);
			PED::SET_PED_CAN_SWITCH_WEAPON(eclone[egcount], true);
			AI::TASK_COMBAT_PED(eclone[egcount], selectedplayer, 1, 1);
			PED::SET_PED_ALERTNESS(eclone[egcount], 1000);
			PED::SET_PED_COMBAT_RANGE(eclone[egcount], 1000);
			egcount++;
		}
		
		Menu::Toggle("Freeze", Features::freezed[Features::Online::selectedPlayer], [] { Features::Freezer(Features::freezed[Features::Online::selectedPlayer]); });
		Menu::Toggle("Fake moneydrop", Features::fakedropbool, [] { Features::fakedrop(Features::fakedropbool, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer)); });
		if (Menu::Option("Airstrike"))
		{
			Features::AirStrike1(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer));
		}
		if (Menu::Option("Host kick")) {
			Features::kicknibba(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer));
		}
		if (Menu::Option("Crash")) {
			int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
			for (int i = 0; i < 33; i++) {
				PED::CLONE_PED(Handle, 1, 1, 1);
				PED::CLONE_PED(Handle, 1, 1, 1);
				PED::CLONE_PED(Handle, 1, 1, 1);
			}
		}
		if (Menu::Option("Attach vehicle to me"))
		{
			Features::attachCar(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer));
		}
		if (Menu::Option("Taze player")) {
			int currentAttempt = 0;
			int maxAttempts = 20;
			while (!ENTITY::IS_ENTITY_DEAD(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer)))
			{
				if (currentAttempt >= maxAttempts)
				{
					break;
				}
				else
				{
					Vector3 destination = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), SKEL_ROOT, 0.0f, 0.0f, 0.0f);
					Vector3 origin = PED::GET_PED_BONE_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), SKEL_R_Hand, 0.0f, 0.0f, 0.2f);
					Hash tazerHash = GAMEPLAY::GET_HASH_KEY((char*)"WEAPON_STUNGUN");
					GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(origin.x, origin.y, origin.z, destination.x, destination.y, destination.z, 1, 0, tazerHash, PLAYER::PLAYER_PED_ID(), false, false, 1);
					currentAttempt++;
				}
				WAIT(0);
			}
		}
		if (Menu::Option("Pop Tires")) {
			Vehicle selectedlPlayerveh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), false);
			bool isveh = PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), false);
			if (isveh)
			{
				RequestControlOfEnt(selectedlPlayerveh);
				VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(selectedlPlayerveh, true);
				for (int i = 5; i--;)
					VEHICLE::SET_VEHICLE_TYRE_BURST(selectedlPlayerveh, i, true, 1000.f);

			}
		}
		if (Menu::Option("Rocket Kill")) {
			Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer);
			if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
			Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
			FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z - 1, 38, 0.5f, true, false, 0.0f);
		}
		if (Menu::Option("Slingshot Car")) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), true));
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), true)));
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), true), 1, 0, 0, 20, 0, 0, 0, 1, false, true, true, true, true);
			}
		}
		if (Menu::Option("Ram with vehicle")) {
			Features::ramWithVeh(Features::Online::selectedPlayer);
		}
		Menu::Toggle("Explode loop", Features::explodeLoopBool[Features::Online::selectedPlayer], [] { Features::explodeloop(Features::explodeLoopBool[Features::Online::selectedPlayer]); });
	break;
	case playertp:
	{
		Features::LoadPlayerInfo(PLAYER::GET_PLAYER_NAME(Features::Online::selectedPlayer), Features::Online::selectedPlayer);
		Menu::Title(Menu::Settings::menuname);
		Menu::Break(PLAYER::GET_PLAYER_NAME(Features::Online::selectedPlayer));
		if (selecArrow) {
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), false);
			GRAPHICS::DRAW_MARKER(offradardpl, coords.x, coords.y, coords.z + 1.3f, 0, 0, 0, 0, 180, 0, 0.3, 0.3, 0.3, r1, g1, b1, 200, 1, 1, 1, 0, 0, 0, 0);
		}
		Menu::Option("Teleport To player", [] {Features::TeleportToPlayer(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer)); });
		Menu::Option("Teleport into vehicle", [] {Features::TeleportIntoVehicle(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer)); });
		Menu::Option("Teleport vehicle to me", [] {Features::TeleportVehicleToMe(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer)); });
	}
	break;
	case arrowsdraw:
	{
		Features::LoadPlayerInfo(PLAYER::GET_PLAYER_NAME(Features::Online::selectedPlayer), Features::Online::selectedPlayer);
		Menu::Title(Menu::Settings::menuname);
		Menu::Break(PLAYER::GET_PLAYER_NAME(Features::Online::selectedPlayer));
		if (selecArrow) {
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), false);
			GRAPHICS::DRAW_MARKER(offradardpl, coords.x, coords.y, coords.z + 1.3f, 0, 0, 0, 0, 180, 0, 0.3, 0.3, 0.3, r1, g1, b1, 200, 1, 1, 1, 0, 0, 0, 0);
		}
		Menu::Int("Select Marker Type", offradardpl, 0, 43);

		Menu::Int("R", r1, 0, 255);
		Menu::Int("G", g1, 0, 255);
		Menu::Int("B", b1, 0, 255);
	}
	break;
	case customenemy:
	{
		Features::LoadPlayerInfo(PLAYER::GET_PLAYER_NAME(Features::Online::selectedPlayer), Features::Online::selectedPlayer);
		Menu::Title(Menu::Settings::menuname);
		Menu::Break(PLAYER::GET_PLAYER_NAME(Features::Online::selectedPlayer));
		if (selecArrow) {
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), false);
			GRAPHICS::DRAW_MARKER(offradardpl, coords.x, coords.y, coords.z + 1.3f, 0, 0, 0, 0, 180, 0, 0.3, 0.3, 0.3, r1, g1, b1, 200, 1, 1, 1, 0, 0, 0, 0);
		}
		Menu::MenuOption("Select model", customenemymodel);
		Menu::MenuOption("Select weapon", customenemyweapon);
		Menu::Option(Features::enemyModel);
		Menu::Option(Features::enemyWeapon);
		if (Features::enemyModel != NULL && Features::enemyWeapon != NULL) {
			if (Menu::Option("Spawn attacker")) {
				Features::spawnEnemy(Features::Online::selectedPlayer, Features::enemyModel, Features::enemyWeapon);
			}
		}
		else {
			Menu::Option("Spawn attacker (Arguments missing!)");
		}
	}
	break;
	case customenemymodel:
	{
		Features::LoadPlayerInfo(PLAYER::GET_PLAYER_NAME(Features::Online::selectedPlayer), Features::Online::selectedPlayer);
		Menu::Title(Menu::Settings::menuname);
		Menu::Break(Features::enemyModel);
		if (selecArrow) {
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), false);
			GRAPHICS::DRAW_MARKER(offradardpl, coords.x, coords.y, coords.z + 1.3f, 0, 0, 0, 0, 180, 0, 0.3, 0.3, 0.3, r1, g1, b1, 200, 1, 1, 1, 0, 0, 0, 0);
		}
		for (auto i : pedModels) { Menu::Option(i, [i] { Features::enemyModel = i; }); }
	}
	break;
	case customenemyweapon:
	{
		Features::LoadPlayerInfo(PLAYER::GET_PLAYER_NAME(Features::Online::selectedPlayer), Features::Online::selectedPlayer);
		Menu::Title(Menu::Settings::menuname);
		Menu::Break(Features::enemyWeapon);
		if (selecArrow) {
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Features::Online::selectedPlayer), false);
			GRAPHICS::DRAW_MARKER(offradardpl, coords.x, coords.y, coords.z + 1.3f, 0, 0, 0, 0, 180, 0, 0.3, 0.3, 0.3, r1, g1, b1, 200, 1, 1, 1, 0, 0, 0, 0);
		}
		if (Menu::Option("Pistol")) { Features::enemyWeapon = "WEAPON_PISTOL"; }
		if (Menu::Option("AP-Pistol")) { Features::enemyWeapon = "WEAPON_APPISTOL"; }
		if (Menu::Option("SMG")) { Features::enemyWeapon = "WEAPON_SMG"; }
		if (Menu::Option("Carbine")) { Features::enemyWeapon = "WEAPON_CARBINERIFLE"; }
		if (Menu::Option("MG")) { Features::enemyWeapon = "WEAPON_MG"; }
		if (Menu::Option("Pump shotgun")) { Features::enemyWeapon = "WEAPON_PUMPSHOTGUN"; }
		if (Menu::Option("Assault shotgun")) { Features::enemyWeapon = "WEAPON_ASSAULTSHOTGUN"; }
		if (Menu::Option("Stungun")) { Features::enemyWeapon = "WEAPON_STUNGUN"; }
		if (Menu::Option("Sniper")) { Features::enemyWeapon = "WEAPON_SNIPERRIFLE"; }
		if (Menu::Option("Heavy sniper")) { Features::enemyWeapon = "WEAPON_HEAVYSNIPER"; }
		if (Menu::Option("Grenade launcher")) { Features::enemyWeapon = "WEAPON_GRENADELAUNCHER"; }
		if (Menu::Option("RPG")) { Features::enemyWeapon = "WEAPON_RPG"; }
		if (Menu::Option("Minigun")) { Features::enemyWeapon = "WEAPON_MINIGUN"; }
		if (Menu::Option("Grenade")) { Features::enemyWeapon = "WEAPON_GRENADE"; }
		if (Menu::Option("Sticky bomb")) { Features::enemyWeapon = "WEAPON_STICKYBOMB"; }
		if (Menu::Option("Railgun")) { Features::enemyWeapon = "WEAPON_RAILGUN"; }
	}
	break;
#pragma endregion
#pragma region Settings Menu
#pragma endregion
	}
	
	Menu::End();
	
}

void ScriptMain() {
	while (true) {
		main();
	}
}