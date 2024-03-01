#pragma once
#include "stdafx.h"
typedef int SpawnerId;

struct Condition {

};

struct Proofs {
	bool bulletProof = false;
	bool fireProof = false;
	bool explosionProof = false;
	bool collisionProof = false;
	bool meleeProof = false;
	bool p6;
	bool p7;
	bool downProof;
};

struct Task {
	int task;
	int duration;
	int startTime;
	Vector3 coords;
	Vector3 coords2;
	Vector3 rot;
	Vector3 rot2;
	bool hasConditions;
	Condition conditions;
	bool active = false;
	float vehSpeed;
	int driveMode;
	float stopRange;
};

struct rgbi {
	int r;
	int g;
	int b;
	int i;
};

struct rgb {
	int r;
	int g;
	int b;
};

struct VehicleColors {
	rgbi primaryColor;
	rgbi secondaryColor;
	rgb neonColor;
	int pearlecentColor;
	int wheelColor;
	bool hasCustomPrimaryColor;
	bool hasCustomSecondaryColor;
};

struct Attachment {
	int boneIndex;
	Vector3 offset;
	Vector3 rot;
	bool fixedRot;
	int netId;
	bool attached;
};

struct Animation {
	char* dict = "";
	char* id = "";
	bool enabled;
	bool inplace;
};

struct Scenario {
	char* scenario = "";
	bool enabled;
	bool inplace;
};

struct Toggles
{
	bool frozenInPlace = false;
	bool dynamic = true;
	bool vehicleExtras[12] = { 0 };
	bool invincible = false;
	bool visible = true;
	bool collision = true;
	bool vehicleNeons[4] = { false };
};

struct Veh {
	int seat = 0;
	bool inVehicle = false;
	SpawnerId vehicle;
};

struct particle {
	bool hasParticle = false;
	float size = 1.f;
	int handle;
	char* dict;
	char* id;
	Vector3 offset;
	Vector3 rot;
	RGBA color;
};

struct Values {
	int health;
	int armor;
	int maxHealth;
	int vehicleMods[60] = { -1 };
	int clothing[3][12];
	Animation anim;
	Scenario scenario;
	Attachment attachment;
	VehicleColors vehicleColors;
	std::vector <particle> particle;
	int vehicleWheelType;
	int vehicleSeat;
	Veh vehicle;
	Proofs proofs;
	char* walkStyle;
};

struct Tasks {
	int startTime;
	int stage = 0;
	bool active = false;
	std::vector<Task> tasks;
};
struct saveInfo {
	bool saved = false;
	int saveId = 0;
};

struct SpawnerStruct
{
	int netId;
	Entity ent;
	char* name;
	Values values;
	Toggles toggles;
	Tasks tasks;
	saveInfo saveInfo;
};

class SpawnerObject
{
public:
	static int getNetId(SpawnerId id);
	static char* getName(SpawnerId id);
	static Entity getEntity(SpawnerId id);
	static bool getIdFromEntity(Entity ent, SpawnerId* id);
	static int getSpawnCount();
	static Vector3 getCoords(SpawnerId id);
	static Vector3 getRotation(SpawnerId id);
	static void setCoords(SpawnerId id, Vector3 coords);
	static void setRotation(SpawnerId id, Vector3 rot);
	static bool getFrozenInPlace(SpawnerId id);
	static void freezeInPlace(SpawnerId id, bool freeze);
	static bool requestControl(SpawnerId id);
	static int getHealth(SpawnerId id);
	static void setHealth(SpawnerId id, int health);
	static void deleteEntity(SpawnerId id);
	static Animation getAnimation(SpawnerId id);
	static void setAnimation(SpawnerId id, char* animDict, char* animId, bool inplace);
	static Scenario getScenario(SpawnerId id);
	static void startScenario(SpawnerId id, char* scenario, bool inplace);
	static void stopAnimation(SpawnerId id);
	static void stopScenario(SpawnerId id);
	static void getClothing(SpawnerId id, int* drawable, int* texture, int* palette);
	static void setClothing(SpawnerId id, int component, int drawable, int texture, int palette);
	static void getVehicleMods(SpawnerId id, int* mods);
	static void setVehicleMod(SpawnerId id, int type, int value);
	static void getVehicleExtras(SpawnerId id, int* extras);
	static void setVehicleExtra(SpawnerId id, int extra, bool value);
	static void setDynamic(SpawnerId id, bool dynamic);
	static bool getDynamic(SpawnerId id);
	static void setInvincible(SpawnerId id, bool invincible);
	static bool getInvincible(SpawnerId id);
	static void setVisible(SpawnerId id, bool visible);
	static bool getVisible(SpawnerId id);
	static int getEntitiesAttachedToEntity(SpawnerId id, SpawnerId* entities);
	static void setCollision(SpawnerId id, bool collision);
	static bool getCollision(SpawnerId id);
	static rgbi getVehiclePrimaryColor(SpawnerId id);
	static rgbi getVehicleSecondaryColor(SpawnerId id);
	static void setVehicleColors(SpawnerId id, int primaryColor, int secondaryColor, bool primary, bool secondary);
	static void setVehicleCustomColors(SpawnerId id, rgb primaryColor, rgb secondaryColor, bool primary, bool secondary);
	static void getNeons(SpawnerId id, bool* neons);
	static void setNeons(SpawnerId id, bool* neons);
	static rgb getNeonColor(SpawnerId id);
	static int getOpacity(SpawnerId id);
	static void getOpacity(SpawnerId id, int alpha);
	static void setWheelType(SpawnerId id, int type);
	static int getWheelType(SpawnerId id);
	static void setWheelColor(SpawnerId id, int color);
	static int getWheelColor(SpawnerId id);
	static void setPearlecentColor(SpawnerId id, int color);
	static int getPearlecentColor(SpawnerId id);
	static void attachToEntity(SpawnerId id, SpawnerId to, Vector3 offsets, Vector3 rot, int boneIndex, bool fixedRot);
	static void detachFromEntity(SpawnerId id);
	static Attachment getAttachmentInfo(SpawnerId id);
	static bool isVehicle(SpawnerId id);
	static bool isPed(SpawnerId id);
	static bool isObject(SpawnerId id);
	static void setAttachmentOffsets(SpawnerId id, Vector3 offsets);
	static void setAttachmentRotation(SpawnerId id, Vector3 rot);
	static void setFixedAttachmentRot(SpawnerId id, bool fixedRot);
	static void setAttachmentBone(SpawnerId id, int bone);
	static void addTask(SpawnerId id, int task, Task args);
	static void removeTask(SpawnerId id, int taskId);
	static char* getTaskName(int task);
	static int getTask(SpawnerId id, int taskId);
	static bool doesTaskExist(int task);
	static bool hasTask(SpawnerId id, int task);
	static bool isTaskActive(SpawnerId id, int taskId);
	static int getActiveTask(SpawnerId id);
	static void resetTaskSequince(SpawnerId id);
	static void startTask(SpawnerId id, int taskId);
	static bool hasActiveTask(SpawnerId id);
	static void skipCurrentTask(SpawnerId id);
	static int getVehicleSeat(SpawnerId id);
	static SpawnerId getVehicle(SpawnerId id);
	static bool getInVehicle(SpawnerId id);
	static void moveEntity(SpawnerId id);
	static bool isSaved(SpawnerId id);
	static int getSaveId(SpawnerId id);
	static SpawnerId getIdFromNetId(int netId);
	static Hash getModel(SpawnerId id);
	static int getType(SpawnerId id);
	static void startLoopedParticleFX(SpawnerId id, char* ptfxAsset, char* ptfxId);
	static void setLoopedParticleOffset(SpawnerId id, int particleId, Vector3 offset);
	static void setLoopedParticleRotation(SpawnerId id, int particleId, Vector3 rot);
	static void setLoopedParticleScale(SpawnerId id, int particleId, float size);
	static void setLoopedParticleColor(SpawnerId id, int particleId, RGBA color);
	static void deleteLoopedParticle(SpawnerId id, int particleId);
	static particle getLoopedParticle(SpawnerId id, int particleId);
	static int getArmor(SpawnerId id);
	static void setArmor(SpawnerId id, int amount);
	static int getMaxArmor(SpawnerId id);
	static int getMaxHealth(SpawnerId id);
	static void setMaxHealth(SpawnerId id, int amount);
	static Proofs getProofInfo(SpawnerId id);
	static void setBulletProof(SpawnerId id, bool b00l);
	static void setFireProof(SpawnerId id, bool b00l);
	static void setExplosionProof(SpawnerId id, bool b00l);
	static void setCollisionProof(SpawnerId id, bool b00l);
	static void setMeleeProof(SpawnerId id, bool b00l);
	static void setP6Proof(SpawnerId id, bool b00l);
	static void setP7Proof(SpawnerId id, bool b00l);
	static void setDownProof(SpawnerId id, bool b00l);
	static char* getWalkStyle(SpawnerId id);
	static void setWalkStyle(SpawnerId id, char* walkStyle);
	static void resetWalkStyle(SpawnerId id);
	static void removeEntity(SpawnerId id);
	static void highlight(SpawnerId id);
protected:
	static std::vector <SpawnerStruct>Entities;
private:
	static Cam movingCam;
};

class Spawner : SpawnerObject
{
public:
	//0 = map, 1 = vehicle, 2 = outfit
	static void saveFile(const std::string& spawnerName, int type);
	//0 = obj, 1 = veh, 2 = ped
	static int spawnEntity(char* entity, int type, Vector3 coords, float heading, bool maxVehicle);
	//0 = obj, 1 = veh, 2 = ped
	static void loadFile(std::string name, int type);
	static bool isFreeCamActive();
	static void removeAllEntities();
	static void deleteAllEntities();
	static void loadMayoFile(std::string file);
private:
	static bool freeCam;
};

void DrawTriangle(Vector3 coords);

void Teleport(Vector3 coords, bool notification);

void changeModelHash(Hash model);
