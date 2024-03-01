#pragma once

typedef struct
{
	int netHandle, //main network handle
		unk1, unk2, unk3, unk4, unk5, unk6, unk7, unk8, unk9, unk10, unk11, unk12;
} networkHandleMgr;
typedef struct
{
	int clanHandle, //main clan handle
		unk1, unk2, unk3, unk4, unk5, unk6, unk7, unk8, unk9, unk10, unk11, unk12, unk13,
		unk14, unk15, unk16, unk17, unk18, unk19, unk20,
		unk21; //isCrewActive
	int unk22; //char *crewRole
	int unk23; //char *creaTag
	int unk24, unk25, unk26, unk27, unk28, unk29,
		unk30, //isLeader
		unk31, //crewId
		unk32, unk33, unk34;
} networkClanMgr;
typedef struct
{
	int memHandle;
	char* unk1;
} networkMembershipMgr;

namespace Features {

	//extern bool blackhole;
	extern int drivespeed;
	extern std::vector<std::string> ini1;
	extern bool esper;
	
	extern int MoneyItem;
	extern int player_alpha;
	extern int timeerlevelcc;
	extern bool propgun;
	extern int Levels[8000];
	extern bool Fireammo;
	extern bool expoammo;
	extern bool expomeal;
	extern int playerWantedLevel;
	extern float pedwithh;
	extern float pedsizee;
	extern int drivestyle;
	extern float gameCamZoomInt;
	extern bool cargodmodebool;
	extern bool rchar;
	extern int danger;
	extern int red;
	extern int green;
	extern int blue;
	extern int customDropDelay;
	extern int customDropAmount;
	extern int customDropMode;
	extern bool customDropBool2;
	extern int customHeight;
	extern bool customFakedrop;
	
	extern int inviteSS;
	//extern int customDropAmount;
	extern bool showAmount2;
	extern bool showAmount;
	extern long long stealthMoneyCounter;
	extern long long droppedMoneyCounter;
	extern int nuattach;
	
	extern int keyIndex;
	extern int keyIndex2;
	extern int keyz[21];
	extern std::vector<std::string> keynames;
	
	extern int attachobj[100];
	void UpdateLoop();
	extern Player spoofKiller;
	extern bool killSpooferOn;
	extern bool Triggerbool;
	void trigger(bool toggle);
	void killSpoofer();
	extern bool tenkloop[33];
	void TenKPedMoney();
	int spawnStuff(char* name, Vector3 coords);
	extern int cargobob_strength;
	extern bool cargobob_active;
	extern int carCounter;
	extern int things[999];
	extern char* selectedthing;
	extern float locX;
	extern float locY;
	extern float locZ;
	extern bool blockX;
	extern bool blockY;
	extern bool blockZ;
	void Attachment(char* p0);
	void cargobobMagnet();
	void LoadPreset(std::string name);
	void loadNames();
	extern bool dowbool;
	extern bool bikeNoFall;
	extern bool stickToGround;
	extern bool rlbool;
	void HasPaintLoop(bool toggle);
	void vehStuckToGround();
	void nofallbike();
	void DriveOnWater(bool toggle);
	extern bool fcbool;
	void FlyingCarLoop(bool toggle);
	extern bool Drift;
	void DriftMode(bool toggle);
	extern int Horndelay;
	
	void carboost(bool toggle);
	extern bool Backboost;
	extern bool boostbool;
	void backboost(bool toggle);
	void flipup();
	void maxvehicle();
	extern int stealthDelay4088;
	extern bool Rneon;
	void RainbowNeon(bool toggle);
	extern bool ShootR;
	extern bool ShootT;
	extern bool ShootTankR;
	extern bool ShootBall;
	extern bool ShootFlare;
	extern bool ShootMini;
	extern bool Laser1;
	extern bool RLaser;
	extern bool CarLightning;
	extern bool Carelectric;
	extern bool Caralien2;
	extern bool Caralien1;
	extern bool Carfireworkloop;
	extern bool CarClownLoop;
	extern float carPTFXsize;
	void Rlaser(bool toggle);
	void laser1(bool toggle);
	void ShootMiniGun(bool toggle);
	void Shootflare(bool toggle);
	void ShootBalls(bool toggle);
	void ShootTankRounds(bool toggle);
	void ShootTanks(bool toggle);
	void ShootRocket(bool toggle);
	void drawMap(int option, std::string pic);
	void TPNearCar();
	void TPlastCar();
	void TPpersonalCar();
	void TPForward();
	extern bool tpbool;
	void tpHotkey(bool t, int key);

	void Teleport_to_marker();

	void changeWalkAnimation(char* movementAnimation);

	void resetWalkAnimation();

	

	void bypassChat(bool t);

	extern bool bypassChatBool;

	extern int volume;

	extern bool thunderbool;

	void setVolume();

	void thunder(bool t);

	extern bool moongrav;

	extern bool footstepBool;

	void MoonGrav(bool t);

	void footsteps();

	extern bool inTrain;

	extern float trainSpeed;
	extern Vehicle train;

	void controlTrainSpeed();

	void spawnTrain(int trainID);

	void deleteTrain();

	void PlaceObjectByHash(Hash hash, float x, float y, float z, float pitch, float roll, float yaw, float heading, int id);

	extern bool screenfx;

	extern int handy;

	void setPhone(int index);

	void ScreenFX(bool toggle, char* effect);

	void skipTutorial();

	extern bool thermalvisionbool;

	extern bool drunk;

	extern bool mobRadio;

	extern bool unlimitedorbitalcannon;

	extern bool HudBool;

	void HideHud();

	void UnlimitedORbitalCannon(bool t);

	void mobileRadio(bool t);

	void Drunk(bool t);

	void thermalvision(bool t);

	extern bool nightvisionbool;

	void nightvision(bool t);

	extern bool flagBool;

	extern bool DisplayFPS;

	void fDisplayFPS(bool toggle);

	void flagLoop();

	float get_stat(Hash stat_hash);

	bool isBanned();

	void customDrop2(bool t);

	void customFakedropp();

	int randomMoney();
	
	extern bool removee;
	extern bool stealthBool;
	extern int stealthAmount;
	extern bool toBank;
	extern int stealthDelay;
	extern bool stealthLooped;
	extern bool customRandoms;
	void stealthLoop(bool t);
	void removeMoney(int amount);

	extern bool useFakeRank;
	extern bool srank1;
	extern bool srank2;
	extern bool RPLoop;
	extern int RPLoopDelay;
	extern int bankAmount;
	
	void deposit(int amount);

	void withdraw(int amount);

	void research(int id);

	int researchId(int character);

	void rpLoop();

	void specialRank2();

	void specialRank1();

	void fakeRank();

	void spoofRank(int fakerank);

	bool HasModType(Vehicle veh, int mod);

	bool HasMod(Vehicle veh, int modType, int mod);

	void SetRank(int rpvalue);

	void setColor(Vehicle veh, int prim, int sec);

	void MaxUpgrade(Vehicle veh);
	
	extern int holePED;
	void hole(bool toggle);
	extern bool catgun;
	void catGun();

	void InfiniteAmmo0(bool toggle);
	extern float DMG;
	void featureFakeBags();

	void OSKR();
	extern bool FakeBags;
	void bulletdmg();
	void setFrameFlag2(uint32_t flag);
	void setFrameFlag(uint32_t flag);
	void fireammo();
	void explosiveammo();
	void exlosivemelle();
	
	void VehicleGun(Player player);
	void PropGun(Player player);
	extern bool spawnincar;
	extern bool spawnmaxed;
	void esp(Player target);
	extern int nuattach3;
	extern int attachobj3[100];
	extern bool NameESP;
	extern bool enableInfo;
	extern bool asteroidshower;
	extern bool esp2b;
	void esp2(Player target);
	void NameTagESP(bool toggle);
	
	void TSE(int input, int player);
	void TSEall(int input);
	void AsteroidShower(bool toggle);
	void info(int option, const char* txt1, const char* txt2);
	void info(int option, const char* txt1);
	void info(int option);
	void info(int start, int end, const char* txt1, const char* txt2);
	void info(int start, int end, const char* txt1);
	void info(int start, int end);
	void attachobjects3(char* object);
	void g_hud();
	void ceoban(int player);
	void ceokick(int player);
	void kick(int player);
	void sp_kick(int player);
	void forceMission(int player);
	void infiniteLoading(int player);
	void sound(int player);
	void remoteTPp(int player, int TPid);
	extern bool tspamallbool;
	extern bool transSpamBool[35];
	extern bool iLoopBoolall;
	void inviteLoopAll(bool t, int a);
	void sendToRoller(Player p);
	void remoteCrash(Player p);
	void remoteStealth(Player p);
	void remoteXXX(Player p);
	void disableCEO(Player target);
	extern bool disableCEObool[35];
	void disableCEOall(bool t);
	extern bool disableCEOallBool;
	void trasactionSpam(Player p);
	void screen(Player p);
	void ceokick2(Player p);
	void ceoban2(Player p);
	void clubkick(Player p);
	void remoteoffradar(Player p);
	extern bool remoteOrBool[35];
	void remoteoffradarall(bool t);
	extern bool remoteOrBoolAll;
	void tspamall(bool t);
	void remoteSpectateMsg(Player p);
	void remoteMoneyMsg(Player p, int index, int amount);
	void gentleKick(Player p);
	extern bool gentleKbool[35];
	void banner2(Player p);
	void kick2(Player p);
	void rotateCam(Player p);
	void giveWanted(Player p);
	extern bool camforwbool[35];
	void esp222(Player target);
	extern bool ntesp2bool[35];
	extern bool esp22bool[35];
	extern bool esp222bool[35];
	void esp22(Player target);
	void NameTagESP2(Player p);
	void attachobjects2(char* object);
	void remoteSpawnVehicle(std::string vehicle, Player p);
	void remoteTP(int player, int TPid);
	void remoteBan(int player);
	void inviteSpam(int player, int a);
	void inviteSpamEvery(int a);
	extern bool iLoopBool[35];
	void inviteLoop(Player p, int a);
	void miniMenu(Player p);
	extern bool minimenu[35];
	extern bool mm_godmode;
	extern bool mm_spawn;
	extern bool mm_money;
	extern bool mm_weather;
	extern bool mm_explode;
	extern bool mm_teleport;
	extern bool enableMoney;
	extern bool osk;
	void giveMenuWeapons(Player p);
	void playerKarmaa(Player p);
	extern bool playerKarma[35];
	void CopyOutfit(Player player);
	void showDroppedMoney();
	void remoteMoneygun(Player p);
	extern bool remoteMoneygunbool[35];
	void playerAsteroidGun(Player p);
	extern bool playerAsteroidBool[35];
	void remoteExplo(Player p);
	extern bool remoteExplobool[35];
	void semigod();
	void maxvehicle2(Player playa);
	extern int pricustomred;
	extern int pricustomgreen;
	extern int pricustomblue;
	extern int seccustomred;
	extern int seccustomgreen;
	extern int seccustomblue;
	extern bool setcustompricolour;
	extern bool setcustomseccolour;
	extern bool spawnwithblip;
	Object SpawnObject(char* name, Vector3 coords);
	Vehicle SpawnVehicle(char* modelg, Vector3 coords, bool tpinto, float heading);
	void spawn_vehicle(std::string vehicle);
	void cargodmode();
	void write2(std::string path, std::string content);
	extern bool glitch[35];
	void cargodmode2(Player playa);
	void spawnEnemy(Player victim, char* model, char* weapon);
	extern char* enemyWeapon;
	extern char* enemyModel;
	void glitchPlayer(Player p);
	void grabDatIP(Player p);
	extern bool explodeLoopBool[35];
	extern bool camshaker[35];
	bool Hostilebuzzard(int selectedPlayer);
	extern bool vehspawncheck;
	extern bool hostilebuzzard;
	void fuckhandling(Player player);
	extern bool fuckedhandling[35];
	extern bool InfiniteAmmo;
	extern bool remoteMoneygunn;
	void shakecam(Player target);
	void explodeloop(Player target);
	void ramWithVeh(Player target);
	void AttachThingToThing(Any p0, Any p1, float x, float y, float z, float rx, float ry, float rz);
	void attachCar(Player pimmel);
	void kicknibba(Player playa);
	void AirStrike1(Player playa);
	extern bool playerwaterloop[35];
	extern bool fakedropbool;
	void fakedrop(bool t, Player player);
	void Freezer(Player target);
	void WaterLoop(Player target);
	void FireLoop(Player target);
	void CREATE_OBJECT_WITH_ROTATION(DWORD model, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float rotW, bool dynamic, bool visible);
	void cage2(Player p);
	extern bool playerfireloop[35];
	void trapcage(Ped ped);
	void stealCar(Player p);
	void blamee(Player p);
	void beachFire(Player p);
	void TeleportVehicleToMe(Player player);
	extern bool spectate[32];
	void specter(Player target);
	void TeleportToPlayer(Player player);
	void TeleportIntoVehicle(Player player);
	void setplayername(std::string& name);
	void NameChanger();
	void setname(std::string& name);
	char* setPlayerName(int player, char* tag);
	bool isPlayerFriend(Player player, bool& result);
	void AutoRegArmour(bool toggle);
	extern bool isAutoRegArmour;
	void flex(bool toggle);
	extern bool Flex;
	void settimechangcc(int level);
	void ChangeWanted(int level);
	extern bool freezed[35];
	void zoomCam();
	extern bool gameCamZoom;
	void pedscale(bool toggle);
	extern bool Pedscale;
	extern Vector3 location;
	void clearanim();
	void doAnimation(char* anim, char* animid);
	void nobody();
	extern bool ignored;
	void copsturnblind();
	void Bullshark();
	void freecam(bool toggle);
	extern bool noClipBool;
	void noClip(bool toggle);

	void antiAFK(bool t);
	
	void changeClothes(char* family, int model, int texture);
	
	extern bool antiAFKbool;
	extern bool badsportbool;
	void firebreath(bool toggle);
	extern bool FIREBREATH;
	
	void badsport(bool t);
	void Dragon(bool t);
	extern bool dragon;
	void TinyPlayer(bool toggle);
	extern bool betiny;
	void SwimFast(bool toggle);
	extern bool fastswim;
	void ultraJump();
	extern bool ujump;
	void superjump(bool toggle);
	extern bool Superjump;
	void Invisibility(bool toggle);
	extern bool playerinvisibility;
	void NoRagdoll(bool toggle);
	extern bool playernoragdoll;
	void OffRadar(bool toggle);
	extern bool orbool;
	void NeverWanted(bool toggle);
	extern bool neverwanted;
	extern bool antitse;
	void antiTSE(bool t);
	extern bool antiweatherTime;
	void antiWeatherTime(bool t);
	extern bool antiEvery;
	void AntiEverything(bool t);
	extern bool antiControl;
	void AntiControl(bool t);
	extern bool antiPickup;
	void AntiPickup(bool t);
	extern bool antiWeapon;
	void AntiWeapon(bool t);
	extern bool antiExplosion;
	void AntiExplosion(bool t);
	extern bool antiStars;
	void AntiStars(bool t);
	extern bool antiReport;
	void AntiReport(bool t);
	extern bool antiKick;
	void AntiKick(bool t);
	extern bool antiFreeze;
	void AntiFreeze(bool t);
	extern bool antiFreeze;
	extern bool antiSound;
	void AntiSound(bool t);
	extern bool antiStat;
	extern bool antiPtfx;
	void AntiStat(bool t);
	//extern bool antiSound;
	void AntiPtfx(bool t);
	extern bool antiBlame;
	extern bool antiAttachment;
	void AntiAttachment(bool t);
	extern bool eventShieldBool;
	void blameProtex();

	void eventShield();
	extern int evIndex;
	extern bool msgBool;
	extern bool dumpBool;
	uint64_t dumpEvent(bool t);
	void logEvent(bool msg);
	extern bool GodMode;
	void godmode(bool toggle);
	extern bool otr2bool;
	void otr2(bool t);
	void startTriggerFX(char* fxAsset, char* fx);
	void playScenario(char* scenario);
	void stopAnimation();
	extern bool fastRun;
	void runFast(bool toggle);
	extern bool Aimbot;
	void aimbot(bool toggle);
	void LoadPlayerInfo(char* playerName, Player p);
	bool is_player_in_interior(Player player);
	bool isPlayerModder(Player p);
	extern bool free_cam;
	extern bool ctbBool;
	extern int TimePD17;
	extern int TimePD16;
	extern int TimePD15;
	extern int TimePD14;
	extern int TimePD13;
	extern int TimePD12;
	extern int TimePD11;
	extern int TimePD10;
	extern int TimePD9;
	extern int TimePD8;
	extern int TimePD7;
	extern int TimePD6;
	extern int TimePD5;
	extern int TimePD4;
	extern int TimePD3;
	extern int TimePD2;
	extern int TimePD1;
	extern int TimePD;
	extern bool vehiclegun;
	namespace Online {
		extern long long droppedMoneyCounter;
		extern bool customDropBool[35];
		extern int customDropDelay;
		extern int customDropAmount;
		extern int customDropMode;
		extern bool customDropBool2;
		extern int customHeight;
		extern bool customFakedrop;
		extern bool customRandom;
		extern int MoneyItem;
		extern bool moneydropbool[35];
		extern int selectedPlayer;
		extern int tpplayer;
		void TeleportToPlayer(Player player);
		void moneydrop(Player player);
		void DropWeapon(Hash weapon, Vector3 coords);
		extern int randomMoney();
		void customFakedropp();
		void customDrop2(bool t);
		void customDrop(Player p);
	}
}

namespace TUNABLE {
	template <typename T>
	T NETWORK_GET_TUNABLE(int index)
	{
		return *globalHandle(262145).At(index).Get<T>();
	}

	template <typename T>
	void NETWORK_SET_TUNABLE(int index, T value)
	{
		globalHandle(262145).At(index).As<T>() = value;
	}
}

bool eventData(int eventGroup, int eventIndex, uint64_t* argv, unsigned int argc);

char* CharKeyboard(char* windowName, int maxInput, char* defaultText);

void shootAtPed(Player selectedPlayer);

extern Hash vehicleGunmodel;

extern Hash propGunModel;;

struct PlayerToggles {
	bool ESP = false;
	bool freeze = false;
	bool camShake = false;
	bool karma = false;
	Hash forcedWeapon;
	bool forceGiveWeapon = false;
	bool hornBoost = false;
	bool invincibleVeh = false;
	bool autoflip = false;
	bool driveOnWater = false;
	int stealthMoneyAmount = 50000;
	bool stealthMoney = false;
};

struct PlayerData {
	Ped ped;
	Vehicle veh;
	Vector3 coords;
	float heading;
	Group group;
	char* name;
	bool inVehicle;
	bool male;
	bool driveOnWater = false;
	bool alive;
	std::vector<int> AttachedEntities;
	bool playing;
	int netHandle[13];
	PlayerToggles toggles;
};
extern PlayerData players[32];

void UpdatePlayers();
void test();
static Vector3 getCoords(Entity entity);
extern bool fx_gun1;
extern bool fx_gun2;
extern bool fx_gun3;
extern bool fx_gun4;
extern bool fx_gun5;
extern bool fx_gun6;
extern bool fx_gun7;
extern bool fx_gun8;
extern bool fx_gun9;
Hash moneyModel(int id);
void MessageAtBottomScreen(char* message, int timeMs);
extern float accelerationmultiplier;
extern float brakesmultiplier;
extern float suspensionseight;

BOOL IsPlayerInClan(Player player);

void CruiseControlLoop();
extern bool cruse;
void SetMultipliers();
void bombermode();
extern bool Bommmer;
std::string ReadPresetKey(std::string name, std::string section, std::string key);
bool DoesPresetKeyExists(std::string name, std::string section, std::string key);
Vehicle SpawnVehicleH(DWORD model, Vector3 coords, bool tpinto, float heading);
Vehicle LoadVehicle(std::string name);
ObjectInfo ReadCustomPreset(std::string name, int id);
std::vector<std::string> listPresets(LPCSTR directory);
Object AttachObjectToVehicleByHash(Hash hash, float x, float y, float z, float rotx, float roty, float rotz, Vehicle veh);
bool getFileContent(std::string fileName, std::vector<std::string>& vecOfStrs);
void RGBFade();
void WheelPTFX(char* streamName, char* PTFXName);
bool reportCalculator();
void PTFXgun(char* PTFX_LOADED, char* FX_LOOPED);
extern Player selfPlayer;
void RequestControl(Entity input);

void GravityGun();

void PreditorGun();
extern bool gravegun;
void rainwep();
extern bool airestrickgun;
void laser();
extern bool Laser;
extern bool rainweapoms;

void valkyirerocket();
extern bool VALKYIREROCKET;
void rainrockets();
extern bool rainrocketss;
extern int rainrocketscooldown;

Vector3 addVector(Vector3 vector, Vector3 vector2);

double DegreeToRadian(double n);

Vector3 RotationToDirection(Vector3 rot);

Vector3 multiplyVector(Vector3 vector, float inc);
extern Vector3 oregano;
void rapidmaker();
extern bool TeleportGun;
extern bool rapidfirer;
void featureTeleportGun();

void moneyGun();
extern bool synctime;
extern bool freezeTime;
extern int frozenTimeH;
extern int frozenTimeM;
extern int frozenTimeS;
void SetWeather(char* weather);
void SetTime(int h, int m, int s);
void FreezeTimeLoop();
void SyncSystemTimeLoop();
extern float BH_FORCE;
extern bool blackhole;

void SetDate(int d, int m, int y);

std::vector<int32_t> aquire_dough();

std::vector<int32_t> add_tomato_sauce();

void BLACKHOLE();

void teleportloop();

void TPto(Vector3 Coords);

void toggleIPL(char* ipl, bool b00l);

void toggleCargoShip(bool b00l);

void toggleTrainCrashBridge(bool b00l);

void toggleTrainCrashBridgeExtra1(bool b00l);

void toggleCluckingBell(bool b00l);

void toggleCluckingBellExtra1(bool b00l);

void toggleBrokenStiltHouse(bool b00l);

void toggleCarrier(bool b00l);

void toggleYacht(bool b00l);

void toggleLestersFactory(bool b00l);

void toggleLestersFactoryExtra1(bool b00l);

void toggleNorthYankton(bool b00l);

void toggleHospital(bool b00l);

void toggleLifeInvader(bool b00l);

void toggleJewelryStore(bool b00l);

void toggleMorgue(bool b00l);

void toggleMorgueExtra1(bool b00l);

void toggleFibLobby(bool b00l);

void togglePlaneCrash(bool b00l);

void toggleUFO(bool b00l);

void toggleBahamaMamas(bool b00l);

void toggleStadium(bool b00l);

void togglePsychOffice(bool b00l);

void toggleTequllala(bool b00l);

void toggleShowRoom(bool b00l);

void toggleShowRoomExtra1(bool b00l);

void toggleUnionDeposity(bool b00l);

void toggleUnionDeposityExtra1(bool b00l);


class Ini
{
private:
	std::string inifile;
public:
	Ini(std::string file)
	{
		this->inifile = file;
	}
	void WriteString(std::string string, std::string app, std::string key)
	{
		WritePrivateProfileStringA(app.c_str(), key.c_str(), string.c_str(), this->inifile.c_str());
	}
	std::string GetString(std::string app, std::string key)
	{
		char buf[100];
		GetPrivateProfileStringA(app.c_str(), key.c_str(), "NULL", buf, 100, this->inifile.c_str());
		return (std::string)buf;
	}
	void WriteInt(int value, std::string app, std::string key)
	{
		WriteString(std::to_string(value), app, key);
	}
	int GetInt(std::string app, std::string key)
	{
		return std::stoi(GetString(app, key));
	}
	void WriteFloat(float value, std::string app, std::string key)
	{
		WriteString(std::to_string(value), app, key);
	}
	float GetFloat(std::string app, std::string key)
	{
		return std::stof(GetString(app, key));
	}
};