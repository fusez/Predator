#if defined predator_included
	#endinput
#endif
#define predator_included

#include <a_samp>
#include <colandreas>
#include <streamer>
native IsValidVehicle(vehicleid);

//------------------------------------------------------------------------------
// Configuration

#define PREDATOR_MISSILE_MODEL			3786
#define PREDATOR_TARGET_DISTANCE		500.0
#define PREDATOR_MOVE_DISTANCE			5.0
#define PREDATOR_FADE_TIME_MIN			100 // time in ms
#define PREDATOR_FADE_TIME_MAX			10000 // time in ms
#define PREDATOR_GUI_DIST_MAX			400.0 // should equal lesser than target distance!
#define PREDATOR_FUEL_MAX				10000
#define PREDATOR_EXPLOSION_RADIUS		25.0

#define PREDATOR_STATEUPDATE_INTERVAL   1000 // time in ms
#define PREDATOR_FADEUPDATE_INTERVAL	33 // time in ms
#define PREDATOR_VEHCOLLISION_INTERVAL  1000 // time in ms
#define PREDATOR_EXPLOSION_INTERVAL	 	200 // time in ms

#define PREDATOR_THRUST_TOT_MIN		 	100.0
#define PREDATOR_THRUST_TOT_MAX		 	200.0
#define PREDATOR_THRUST_TOT_DEFAULT	 	PREDATOR_THRUST_TOT_MIN
#define PREDATOR_THRUST_ADD_MAX	 		10.0
#define PREDATOR_THRUST_ADD_MIN	 		-PREDATOR_THRUST_ADD_MAX
#define PREDATOR_THRUST_ADD_DEFAULT 	0.0
#define PREDATOR_THRUST_ADD_INCREMENT	0.5

#define PREDATOR_PITCH_TOT_MIN		  	5.0
#define PREDATOR_PITCH_TOT_MAX			120.0
#define PREDATOR_PITCH_TOT_DEFAULT	  	PREDATOR_PITCH_TOT_MIN
#define PREDATOR_PITCH_ADD_INCREMENT 	0.5
#define PREDATOR_PITCH_ADD_MAX		  	3.0
#define PREDATOR_PITCH_ADD_MIN		  	-PREDATOR_PITCH_ADD_MAX
#define PREDATOR_PITCH_ADD_DEFAULT	  	0.0

#define PREDATOR_YAW_TOT_MIN 			0.0
#define PREDATOR_YAW_TOT_MAX 			360
//#define PREDATOR_YAW_TOT_DEFAULT	  	0.0 // comment or remove this line to randomize jaw.
#define PREDATOR_YAW_ADD_MAX			6.0
#define PREDATOR_YAW_ADD_MIN			-PREDATOR_YAW_ADD_MAX
#define PREDATOR_YAW_ADD_INCREMENT	  	0.5
#define PREDATOR_YAW_ADD_DEFAULT		0.0

enum {
	PREDATORSTATE_OFF,
	PREDATORSTATE_INTRO, // waiting for screen to fade
	PREDATORSTATE_WAIT_SPEC, // waiting for spectating state...
	PREDATORSTATE_ACTIVE, // predator missile is active
	PREDATORSTATE_WAIT_SPAWN, // waiting for player spawn...
	PREDATORSTATE_OUTRO, // waiting for screen to fade
	PREDATORSTATE_WAIT_EXPLODE, // waiting for explosion sequence to stop
}

enum {
	FADESTATE_OFF,
	FADESTATE_TO_OPAQUE,
	FADESTATE_TO_TRANSP
}

enum {
	GUI_KEY_THRUST,
	GUI_KEY_PITCH_ADD,
	GUI_KEY_PITCH_SUB,
	GUI_KEY_YAW_ADD,
	GUI_KEY_YAW_SUB,
	GUI_KEY_DESTROY,
	MAX_GUI_KEYS
}

//------------------------------------------------------------------------------
// Variables

enum eFadeData {
	eFadeState,
	eFadeStartTick,
	eFadeEndTick,
	eFadeDuration,
	eFadePassedTime,
	eFadeAlpha,
	Float:eFadeProgress,
}

enum ePredatorData {
	ePredatorState,
	ePredatorMissileObject,
	ePredatorSmokeObject,
	ePredatorFlareObject,
	ePredatorTargetObject,
	Float: ePredatorPitchAdd,
	Float: ePredatorYawAdd,
	Float: ePredatorThrustAdd,
	Float: ePredatorThrust, // Hold Spacebar for boost
	Float: ePredatorBoost, // Thrust boost in percent
	Float: ePredatorPitch, // Up/Down
	Float: ePredatorYaw, // Left/Right
	Float: ePredatorFuel,
	Float: ePredatorFromX,
	Float: ePredatorFromY,
	Float: ePredatorFromZ,
	Float: ePredatorToX,
	Float: ePredatorToY,
	Float: ePredatorToZ,
	Float: ePredatorPrevTargetX,
	Float: ePredatorPrevTargetY,
	Float: ePredatorPrevTargetZ,
	Float: ePredatorTargetX,
	Float: ePredatorTargetY,
	Float: ePredatorTargetZ,
	Float: ePredatorTargetDist,
	Float: ePredatorFromCamX,
	Float: ePredatorFromCamY,
	Float: ePredatorFromCamZ,
	Float: ePredatorToCamX,
	Float: ePredatorToCamY,
	Float: ePredatorToCamZ,
	ePredatorMoveTimeMS,
	ePredatorReplacementActor,
	ePredatorDamageBy,
	ePredatorExplosionsLeft
}

enum eSpawnData {
	eSpawnSkin,
	Float:eSpawnX,
	Float:eSpawnY,
	Float:eSpawnZ,
	Float:eSpawnA,
	eSpawnVehicleID,
	eSpawnVehicleSeat,
	eSpawnWeaponData[13],
	eSpawnAmmoData[13],
	eSpawnInterior,
	eSpawnWorld,
	Float:eSpawnArmour,
	Float:eSpawnHealth,
	eSpawnMoney,
}

enum {
	Text: eGTDGUIDataBG,
	Text: eGTDGUIDataCaption,

	Text: eGTDGUIDataTotThrustBG,
	Text: eGTDGUIDataTotThrustBar,

	Text: eGTDGUIDataAddThrustBG,
	Text: eGTDGUIDataAddThrustNeg,
	Text: eGTDGUIDataAddThrustPos,
	Text: eGTDGUIDataAddThrustBar,

	Text: eGTDGUIDataTotPitchBG,
	Text: eGTDGUIDataTotPitchBar,

	Text: eGTDGUIDataAddPitchBG,
	Text: eGTDGUIDataAddPitchNeg,
	Text: eGTDGUIDataAddPitchPos,
	Text: eGTDGUIDataAddPitchBar,

	Text: eGTDGUIDataTotYawBG,
	Text: eGTDGUIDataTotYawBar,

	Text: eGTDGUIDataAddYawBG,
	Text: eGTDGUIDataAddYawNeg,
	Text: eGTDGUIDataAddYawPos,
	Text: eGTDGUIDataAddYawBar,

	Text: eGTDGUIDataTotFuelBG,
	Text: eGTDGUIDataTotFuelBar,

	Text: eGTDGUIDataTotDistBG,
	Text: eGTDGUIDataTotDistBar,

	Text: eGTDGUIKeyBG,
	Text: eGTDGUIKeyCaption,
	Text: eGTDGUIKeyL[MAX_GUI_KEYS],
	Text: eGTDGUIKeyR[MAX_GUI_KEYS],

	MAX_GUI_GLOBAL_TEXTDRAWS
}

enum {
	PlayerText: ePTDGUITotThrustText,
	PlayerText: ePTDGUIAddThrustText,
	PlayerText: ePTDGUITotPitchText,
	PlayerText: ePTDGUIAddPitchText,
	PlayerText: ePTDGUITotYawText,
	PlayerText: ePTDGUIAddYawText,
	PlayerText: ePTDGUITotFuelText,
	PlayerText: ePTDGUITotDistText,

	MAX_GUI_PLAYER_TEXTDRAWS
}

new
	gPredatorData[MAX_PLAYERS][ePredatorData],
	gSpawnData[MAX_PLAYERS][eSpawnData],

	gFadeData[MAX_PLAYERS][eFadeData],
	Text: gFadeTD,

	Text: gGUIGTD[MAX_GUI_GLOBAL_TEXTDRAWS],
	PlayerText: gGUIPTD[MAX_PLAYERS][MAX_GUI_PLAYER_TEXTDRAWS],
	gGUIString[50+1],

	gVehicleColArea[MAX_VEHICLES],
	
	gPredatorStateTimer,
	gPredatorFadeTimer,
	gVehCollisionAreaTimer,
	gExplosionTimer
;

//------------------------------------------------------------------------------
// Math Methods

FloatClamp(&Float:value, Float:min, Float:max) {
	value = value < min ? min : (value > max ? max : value);
}

Float:fixrot(Float:r) {
	new laps = floatround(r / 360.0, floatround_floor);
	return laps ? r - (laps * 360.0) :  r;
}


Float:GetDistanceBetweenPoints3D(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2) {
	return VectorSize(x1-x2,y1-y2,z1-z2); // Thanks to AbyssMorgan
}

// Renamed GetAttachedObjectPos (Original made by Stylock)
PositionFromOffset(
	Float:  input_x,
	Float:  input_y,
	Float:  input_z,
	Float:  input_rx,
	Float:  input_ry,
	Float:  input_rz,
	Float:  offset_x,
	Float:  offset_y,
	Float:  offset_z,
	&Float: ret_x,
	&Float: ret_y,
	&Float: ret_z
) {
	new
		Float:cos_x = floatcos(input_rx, degrees),
		Float:cos_y = floatcos(input_ry, degrees),
		Float:cos_z = floatcos(input_rz, degrees),
		Float:sin_x = floatsin(input_rx, degrees),
		Float:sin_y = floatsin(input_ry, degrees),
		Float:sin_z = floatsin(input_rz, degrees)
	;

	ret_x = input_x + offset_x * cos_y * cos_z - offset_x * sin_x * sin_y * sin_z - offset_y * cos_x * sin_z + offset_z * sin_y * cos_z + offset_z * sin_x * cos_y * sin_z;
	ret_y = input_y + offset_x * cos_y * sin_z + offset_x * sin_x * sin_y * cos_z + offset_y * cos_x * cos_z + offset_z * sin_y * sin_z - offset_z * sin_x * cos_y * cos_z;
	ret_z = input_z - offset_x * cos_x * sin_y + offset_y * sin_x + offset_z * cos_x * cos_y;
}

//------------------------------------------------------------------------------
// Predator Methods

InitPredator() {
	InitVehicleCollisionAreaData(); // Initialize default values

	CreateFadeTextdraw(); // Create Fade Textdraw (opaque <-> transparent textdraw)

	CreateGUIGlobalTextdraws(); // Create GUI (Global / Non-Player textdraws)

	CA_Init(); // Initialize ColAndreas

	gPredatorStateTimer = SetTimer("UpdatePredatorState", PREDATOR_STATEUPDATE_INTERVAL, true); // Update Predator State

	gPredatorFadeTimer = SetTimer("UpdatePredatorFade", PREDATOR_FADEUPDATE_INTERVAL, true); // Update Predator Fade

	gExplosionTimer = SetTimer("UpdateExplosionSequence", PREDATOR_EXPLOSION_INTERVAL, true); // Create explosion if sequence is active

	gVehCollisionAreaTimer = SetTimer("UpdateVehicleCollisionAreas", PREDATOR_VEHCOLLISION_INTERVAL, true); // create missing / remove invalid vehicle collision areas
}

ExitPredator() {
	KillTimer(gPredatorStateTimer);
	KillTimer(gPredatorFadeTimer);
	KillTimer(gVehCollisionAreaTimer);
	KillTimer(gExplosionTimer);

	DestroyVehicleCollisionAreas(); // Destroy vehicle collision areas

	DestroyFadeTextdraw(); // Destroy Fade Textdraw

	DestroyGUIGlobalTextdraws(); // Destroy GUI (Global / Non-Player textdraws)

	for(new playerid, max_playerid = GetPlayerPoolSize(); playerid <= max_playerid; playerid ++) {
		if( !IsPlayerConnected(playerid) ) {
			continue;
		}

		if( gPredatorData[playerid][ePredatorState] == PREDATORSTATE_OFF ) {
			continue;
		}

		if( gPredatorData[playerid][ePredatorState] == PREDATORSTATE_ACTIVE ) {
			DestroyPredator(playerid);
			DestroyPredatorTarget(playerid);

			DestroyGUIPlayerTextdraws(playerid);
			PlayPredatorMusic(playerid, .toggle = false);
		}

		if( GetPlayerState(playerid) == PLAYER_STATE_SPECTATING ) {
			TogglePlayerSpectating(playerid, false);
		}
	}
}

DefaultPredatorMovementData(playerid) {
	gPredatorData[playerid][ePredatorPitchAdd] = PREDATOR_PITCH_ADD_DEFAULT; // 0.0
	gPredatorData[playerid][ePredatorYawAdd] = PREDATOR_YAW_ADD_DEFAULT; // 0.0
	gPredatorData[playerid][ePredatorThrustAdd] = PREDATOR_THRUST_ADD_DEFAULT;
	gPredatorData[playerid][ePredatorThrust] = PREDATOR_THRUST_TOT_DEFAULT;
	gPredatorData[playerid][ePredatorPitch] = PREDATOR_PITCH_TOT_DEFAULT;
	#if defined PREDATOR_YAW_TOT_DEFAULT
		gPredatorData[playerid][ePredatorYaw] = PREDATOR_YAW_TOT_DEFAULT;
	#else
		gPredatorData[playerid][ePredatorYaw] = random(PREDATOR_YAW_TOT_MAX);
	#endif
	gPredatorData[playerid][ePredatorFuel] = PREDATOR_FUEL_MAX;
}

CreatePredatorTarget(playerid, Float:x, Float:y, Float:z) {
	gPredatorData[playerid][ePredatorTargetObject] = CreatePlayerObject(playerid, 3438, x, y, z, 0.0000, 0.0000, 0.0000, PREDATOR_TARGET_DISTANCE); //target
	SetPlayerObjectMaterial(playerid, gPredatorData[playerid][ePredatorTargetObject], 0, 16640, "a51", "ws_carparkwall2", 0xFFFF0000);
}

DestroyPredatorTarget(playerid) {
	DestroyPlayerObject(playerid, gPredatorData[playerid][ePredatorTargetObject]);
}

ApplyPredatorTargetMovement(playerid) {
	MovePlayerObject(playerid,
		.objectid = gPredatorData[playerid][ePredatorTargetObject],
		.X = gPredatorData[playerid][ePredatorTargetX],
		.Y = gPredatorData[playerid][ePredatorTargetY],
		.Z = gPredatorData[playerid][ePredatorTargetZ],
		.Speed = gPredatorData[playerid][ePredatorThrust] * 10,
		.RotX = 0.0,
		.RotY = gPredatorData[playerid][ePredatorPitch] + 270,
		.RotZ = -gPredatorData[playerid][ePredatorYaw] + 270
	);
}

CreatePredator(playerid, Float:x, Float:y, Float:z) {
	gPredatorData[playerid][ePredatorFromX] = x;
	gPredatorData[playerid][ePredatorFromY] = y;
	gPredatorData[playerid][ePredatorFromZ] = z;

	gPredatorData[playerid][ePredatorMissileObject] =
		CreateObject(PREDATOR_MISSILE_MODEL, x, y, z, 0.0, 0.0, 0.0);
	SetObjectMaterial(gPredatorData[playerid][ePredatorMissileObject], 0, 19597, "lsbeachside", "ceilingtiles4-128x128", 0xFF696969);
	SetObjectMaterial(gPredatorData[playerid][ePredatorMissileObject], 1, 14668, "711c", "cj_white_wall2", 0xFFFFD700);
	SetObjectMaterial(gPredatorData[playerid][ePredatorMissileObject], 2, 14668, "711c", "cj_white_wall2", 0xFFFFD700);

	gPredatorData[playerid][ePredatorSmokeObject] = CreateObject(18714, x, y, z, 0.0000, 0.0000, 0.0000); //smoke
	gPredatorData[playerid][ePredatorFlareObject] = CreateObject(354, x, y, z, 0.0000, 0.0000, 0.0000); //flare

	AttachObjectToObject(gPredatorData[playerid][ePredatorSmokeObject], gPredatorData[playerid][ePredatorMissileObject], 0.0000, 0.0000, -1.7000, 0.0000, 0.0000, 0.0000); // smoke to predator
	AttachObjectToObject(gPredatorData[playerid][ePredatorFlareObject], gPredatorData[playerid][ePredatorMissileObject], 1.4, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000); // flare
}

DestroyPredator(playerid) {
	DestroyObject(gPredatorData[playerid][ePredatorMissileObject]);
	gPredatorData[playerid][ePredatorMissileObject] = INVALID_OBJECT_ID;

	DestroyObject(gPredatorData[playerid][ePredatorSmokeObject]);
	gPredatorData[playerid][ePredatorSmokeObject] = INVALID_OBJECT_ID;

	DestroyObject(gPredatorData[playerid][ePredatorFlareObject]);
	gPredatorData[playerid][ePredatorFlareObject] = INVALID_OBJECT_ID;
}

CalculatePredatorMovement(playerid) {
	new keys, ud, lr;
	GetPlayerKeys(playerid, keys, ud, lr);

	// modify thrust add
	if( keys & KEY_SPRINT ) {
		gPredatorData[playerid][ePredatorThrustAdd] += PREDATOR_THRUST_ADD_INCREMENT;
		FloatClamp(gPredatorData[playerid][ePredatorThrustAdd], PREDATOR_THRUST_ADD_DEFAULT, PREDATOR_THRUST_ADD_MAX);
	} else {
		if( gPredatorData[playerid][ePredatorThrust] > PREDATOR_THRUST_TOT_MIN ) {
			gPredatorData[playerid][ePredatorThrustAdd] -= PREDATOR_THRUST_ADD_INCREMENT;
			FloatClamp(gPredatorData[playerid][ePredatorThrustAdd], PREDATOR_THRUST_ADD_MIN, PREDATOR_THRUST_ADD_DEFAULT);
		} else {
			gPredatorData[playerid][ePredatorThrustAdd] = PREDATOR_THRUST_ADD_DEFAULT;
		}
	}

	// modify pitch add
	if( ud == KEY_UP ) {
		gPredatorData[playerid][ePredatorPitchAdd] += PREDATOR_PITCH_ADD_INCREMENT;
		FloatClamp(gPredatorData[playerid][ePredatorPitchAdd], PREDATOR_PITCH_ADD_MIN, PREDATOR_PITCH_ADD_MAX);
	} else if( ud == KEY_DOWN ) {
		gPredatorData[playerid][ePredatorPitchAdd] -= PREDATOR_PITCH_ADD_INCREMENT;
		FloatClamp(gPredatorData[playerid][ePredatorPitchAdd], PREDATOR_PITCH_ADD_MIN, PREDATOR_PITCH_ADD_MAX);
	} else {
		gPredatorData[playerid][ePredatorPitchAdd] *= 0.5;
		FloatClamp(gPredatorData[playerid][ePredatorPitchAdd], PREDATOR_PITCH_ADD_MIN, PREDATOR_PITCH_ADD_MAX);
	}

	// modify yaw add
	if( lr == KEY_LEFT ) {
		gPredatorData[playerid][ePredatorYawAdd] -= PREDATOR_YAW_ADD_INCREMENT;
		FloatClamp(gPredatorData[playerid][ePredatorYawAdd], PREDATOR_YAW_ADD_MIN, PREDATOR_YAW_ADD_MAX);
	} else if( lr == KEY_RIGHT ) {
		gPredatorData[playerid][ePredatorYawAdd] += PREDATOR_YAW_ADD_INCREMENT;
		FloatClamp(gPredatorData[playerid][ePredatorYawAdd], PREDATOR_YAW_ADD_MIN, PREDATOR_YAW_ADD_MAX);
	} else {
		gPredatorData[playerid][ePredatorYawAdd] *= 0.5;
		FloatClamp(gPredatorData[playerid][ePredatorYawAdd], PREDATOR_YAW_ADD_MIN, PREDATOR_YAW_ADD_MAX);
	}

	// modify thrust
 	gPredatorData[playerid][ePredatorThrust] += gPredatorData[playerid][ePredatorThrustAdd];
	FloatClamp(gPredatorData[playerid][ePredatorThrust], PREDATOR_THRUST_TOT_MIN, PREDATOR_THRUST_TOT_MAX);
	gPredatorData[playerid][ePredatorBoost] = gPredatorData[playerid][ePredatorThrust] / PREDATOR_THRUST_TOT_MIN;

	// modify pitch
 	gPredatorData[playerid][ePredatorPitch] += gPredatorData[playerid][ePredatorPitchAdd] / (gPredatorData[playerid][ePredatorBoost] * gPredatorData[playerid][ePredatorBoost]);
	FloatClamp(gPredatorData[playerid][ePredatorPitch], PREDATOR_PITCH_TOT_MIN, PREDATOR_PITCH_TOT_MAX);

	// modify yaw
 	gPredatorData[playerid][ePredatorYaw] += gPredatorData[playerid][ePredatorYawAdd] / (gPredatorData[playerid][ePredatorBoost] * gPredatorData[playerid][ePredatorBoost]);
 	gPredatorData[playerid][ePredatorYaw] = fixrot(gPredatorData[playerid][ePredatorYaw]);
}

CalculatePredatorFuel(playerid) {
	gPredatorData[playerid][ePredatorFuel] -= floatabs(gPredatorData[playerid][ePredatorBoost]);
	gPredatorData[playerid][ePredatorFuel] -= floatabs(gPredatorData[playerid][ePredatorThrustAdd]);
	gPredatorData[playerid][ePredatorFuel] -= floatabs(gPredatorData[playerid][ePredatorPitchAdd]);
	gPredatorData[playerid][ePredatorFuel] -= floatabs(gPredatorData[playerid][ePredatorYawAdd]);
}

CalculatePredatorNextPos(playerid) {
	PositionFromOffset(
		.input_x = gPredatorData[playerid][ePredatorFromX],
		.input_y = gPredatorData[playerid][ePredatorFromY],
		.input_z = gPredatorData[playerid][ePredatorFromZ],
		.input_rx = 0.0,
		.input_ry = gPredatorData[playerid][ePredatorPitch] + 270, // pitch = y
		.input_rz = -gPredatorData[playerid][ePredatorYaw] + 270, // yaw = z
		.offset_x = -(PREDATOR_MOVE_DISTANCE * gPredatorData[playerid][ePredatorBoost]),
		.offset_y = 0.0,
		.offset_z = 0.0,
		.ret_x = gPredatorData[playerid][ePredatorToX],
		.ret_y = gPredatorData[playerid][ePredatorToY],
		.ret_z = gPredatorData[playerid][ePredatorToZ]
	);

	CA_RayCastLine(
		.StartX = gPredatorData[playerid][ePredatorFromX],
		.StartY = gPredatorData[playerid][ePredatorFromY],
		.StartZ = gPredatorData[playerid][ePredatorFromZ],
		.EndX = gPredatorData[playerid][ePredatorToX],
		.EndY = gPredatorData[playerid][ePredatorToY],
		.EndZ = gPredatorData[playerid][ePredatorToZ],
		.x = gPredatorData[playerid][ePredatorToX],
		.y = gPredatorData[playerid][ePredatorToY],
		.z = gPredatorData[playerid][ePredatorToZ]
	);
}

CalculatePredatorTarget(playerid) {
	gPredatorData[playerid][ePredatorPrevTargetX] = gPredatorData[playerid][ePredatorTargetX];
	gPredatorData[playerid][ePredatorPrevTargetY] = gPredatorData[playerid][ePredatorTargetY];
	gPredatorData[playerid][ePredatorPrevTargetZ] = gPredatorData[playerid][ePredatorTargetZ];

	PositionFromOffset(
		.input_x = gPredatorData[playerid][ePredatorFromX],
		.input_y = gPredatorData[playerid][ePredatorFromY],
		.input_z = gPredatorData[playerid][ePredatorFromZ],
		.input_rx = 0.0,
		.input_ry = gPredatorData[playerid][ePredatorPitch] + 270, // pitch = y
		.input_rz = -gPredatorData[playerid][ePredatorYaw] + 270, // yaw = z
		.offset_x = -PREDATOR_TARGET_DISTANCE, // default target distance.
		.offset_y = 0.0,
		.offset_z = 0.0,
		.ret_x = gPredatorData[playerid][ePredatorTargetX],
		.ret_y = gPredatorData[playerid][ePredatorTargetY],
		.ret_z = gPredatorData[playerid][ePredatorTargetZ]
	);

	CA_RayCastLine(
		.StartX = gPredatorData[playerid][ePredatorFromX],
		.StartY = gPredatorData[playerid][ePredatorFromY],
		.StartZ = gPredatorData[playerid][ePredatorFromZ],
		.EndX = gPredatorData[playerid][ePredatorTargetX],
		.EndY = gPredatorData[playerid][ePredatorTargetY],
		.EndZ = gPredatorData[playerid][ePredatorTargetZ],
		.x = gPredatorData[playerid][ePredatorTargetX],
		.y = gPredatorData[playerid][ePredatorTargetY],
		.z = gPredatorData[playerid][ePredatorTargetZ]
	);


	new target_vehicleid = GetVehicleInLine(
		.x1 = gPredatorData[playerid][ePredatorFromX],
		.y1 = gPredatorData[playerid][ePredatorFromY],
		.z1 = gPredatorData[playerid][ePredatorFromZ],
		.x2 = gPredatorData[playerid][ePredatorTargetX],
		.y2 = gPredatorData[playerid][ePredatorTargetY],
		.z2 = gPredatorData[playerid][ePredatorTargetZ]
	);

	if( IsValidVehicle(target_vehicleid) ) {
		new Float:vx, Float:vy, Float:vz;

		GetVehiclePos(target_vehicleid, vx, vy, vz);

		gPredatorData[playerid][ePredatorTargetDist] = GetDistanceBetweenPoints3D(gPredatorData[playerid][ePredatorToX], gPredatorData[playerid][ePredatorToY], gPredatorData[playerid][ePredatorToZ], vx, vy, vz);

		// Recalculate the target pos because a vehicle was found between the missile and the target.
		PositionFromOffset(
			.input_x = gPredatorData[playerid][ePredatorFromX],
			.input_y = gPredatorData[playerid][ePredatorFromY],
			.input_z = gPredatorData[playerid][ePredatorFromZ],
			.input_rx = 0.0,
			.input_ry = gPredatorData[playerid][ePredatorPitch] + 270, // pitch = y
			.input_rz = -gPredatorData[playerid][ePredatorYaw] + 270, // yaw = z
			.offset_x = -gPredatorData[playerid][ePredatorTargetDist], // new target distance
			.offset_y = 0.0,
			.offset_z = 0.0,
			.ret_x = gPredatorData[playerid][ePredatorTargetX],
			.ret_y = gPredatorData[playerid][ePredatorTargetY],
			.ret_z = gPredatorData[playerid][ePredatorTargetZ]
		);
	} else {
		gPredatorData[playerid][ePredatorTargetDist] = GetDistanceBetweenPoints3D(gPredatorData[playerid][ePredatorToX], gPredatorData[playerid][ePredatorToY], gPredatorData[playerid][ePredatorToZ], gPredatorData[playerid][ePredatorTargetX], gPredatorData[playerid][ePredatorTargetY], gPredatorData[playerid][ePredatorTargetZ]);
	}
}

CalculatePredatorCamera(playerid) {
	PositionFromOffset(
		.input_x = gPredatorData[playerid][ePredatorFromX],
		.input_y = gPredatorData[playerid][ePredatorFromY],
		.input_z = gPredatorData[playerid][ePredatorFromZ],
		.input_rx = 0.0,
		.input_ry = gPredatorData[playerid][ePredatorPitch] + 270, // pitch = y
		.input_rz = -gPredatorData[playerid][ePredatorYaw] + 270, // yaw = z
		.offset_x = 20.0,
		.offset_y = 5.0,
		.offset_z = -5.0,
		.ret_x = gPredatorData[playerid][ePredatorToCamX],
		.ret_y = gPredatorData[playerid][ePredatorToCamY],
		.ret_z = gPredatorData[playerid][ePredatorToCamZ]
	);
}

ApplyPredatorMovement(playerid) {
	gPredatorData[playerid][ePredatorMoveTimeMS] = MoveObject(
		.objectid = gPredatorData[playerid][ePredatorMissileObject],
		.X = gPredatorData[playerid][ePredatorToX],
		.Y = gPredatorData[playerid][ePredatorToY],
		.Z = gPredatorData[playerid][ePredatorToZ],
		.Speed = gPredatorData[playerid][ePredatorThrust],
		.RotX = 0.0,
		.RotY = gPredatorData[playerid][ePredatorPitch] + 270,
		.RotZ = -gPredatorData[playerid][ePredatorYaw] + 270
	);
}

ApplyPredatorCamera(playerid) {
	InterpolateCameraPos(playerid, gPredatorData[playerid][ePredatorFromCamX], gPredatorData[playerid][ePredatorFromCamY], gPredatorData[playerid][ePredatorFromCamZ], gPredatorData[playerid][ePredatorToCamX], gPredatorData[playerid][ePredatorToCamY], gPredatorData[playerid][ePredatorToCamZ], gPredatorData[playerid][ePredatorMoveTimeMS], CAMERA_MOVE);
	InterpolateCameraLookAt(playerid, gPredatorData[playerid][ePredatorPrevTargetX], gPredatorData[playerid][ePredatorPrevTargetY], gPredatorData[playerid][ePredatorPrevTargetZ], gPredatorData[playerid][ePredatorTargetX], gPredatorData[playerid][ePredatorTargetY], gPredatorData[playerid][ePredatorTargetZ], gPredatorData[playerid][ePredatorMoveTimeMS], CAMERA_MOVE);
}

PlayPredatorMusic(playerid, bool:toggle) {
	PlayerPlaySound(playerid, toggle ? 1068 : 1069, 0.0, 0.0, 0.0);
}

KillPlayersByPredator(predator_playerid, Float:explosion_x, Float:explosion_y, Float:explosion_z) {
	new Float:x, Float:y, Float:z;
	for(new playerid, max_playerid = GetPlayerPoolSize(); playerid <= max_playerid; playerid ++) {
		if( !IsPlayerConnected(playerid) ) {
			continue; // This player is not connected - skip this player.
		}

		if( gPredatorData[playerid][ePredatorState] == PREDATORSTATE_ACTIVE ) {
			x = gSpawnData[playerid][eSpawnX], y = gSpawnData[playerid][eSpawnY], z = gSpawnData[playerid][eSpawnZ];
			// This player is controlling a predator - so we fetch their respawn position.
		} else if( GetPlayerState(playerid) == PLAYER_STATE_SPECTATING ) {
			continue; // This player is spectating for another reason than controlling a predator - skip this player.
		} else {
			GetPlayerPos(playerid, x, y, z); // This player is spawned, fetch their current position.
		}

		new Float:dist = GetDistanceBetweenPoints3D(explosion_x, explosion_y, explosion_z, x, y, z);

		if( dist < PREDATOR_EXPLOSION_RADIUS ) {
			gPredatorData[playerid][ePredatorDamageBy] = predator_playerid;
		}
	}
}

LaunchPredator(playerid, Float:x, Float:y, Float:z) {
	if( gPredatorData[playerid][ePredatorState] != PREDATORSTATE_OFF ) {
		return 0;
	}

	SaveSpawnData(playerid);

	CreatePredator(playerid, x, y, z);

	SetupFade(playerid, .fadeto_opaque = true, .duration_ms = 500);

	gPredatorData[playerid][ePredatorState] ++;
	return 1;
}


forward UpdateExplosionSequence();
public UpdateExplosionSequence() {
	for(new playerid, max_playerid = GetPlayerPoolSize(); playerid <= max_playerid; playerid ++) {
		if( !IsPlayerConnected(playerid)) {
			continue;
		}

		if( gPredatorData[playerid][ePredatorState] <= PREDATORSTATE_ACTIVE ) {
			continue;
		}
		
		if( gPredatorData[playerid][ePredatorExplosionsLeft] <= 0 ) {
			continue;
		}

		CreateExplosion(gPredatorData[playerid][ePredatorToX], gPredatorData[playerid][ePredatorToY], gPredatorData[playerid][ePredatorToZ], 7, PREDATOR_EXPLOSION_RADIUS);
		gPredatorData[playerid][ePredatorExplosionsLeft] --;
	}
}

forward UpdatePredatorState();
public UpdatePredatorState() {
	for(new playerid, max_playerid = GetPlayerPoolSize(); playerid <= max_playerid; playerid ++) {
		if( IsPlayerConnected(playerid) && gPredatorData[playerid][ePredatorState] == PREDATORSTATE_WAIT_EXPLODE && gPredatorData[playerid][ePredatorExplosionsLeft] <= 0 ) {
			gPredatorData[playerid][ePredatorState] = PREDATORSTATE_OFF;
		}
	}
}

//------------------------------------------------------------------------------
// Replacement Actor

CreatePlayerReplacementActor(playerid) {
	gPredatorData[playerid][ePredatorReplacementActor] = CreateActor(gSpawnData[playerid][eSpawnSkin], gSpawnData[playerid][eSpawnX], gSpawnData[playerid][eSpawnY], gSpawnData[playerid][eSpawnZ], gSpawnData[playerid][eSpawnA]);
	SetActorInvulnerable(gPredatorData[playerid][ePredatorReplacementActor], false);
}

DestroyPlayerReplacementActor(playerid) {
	DestroyActor( gPredatorData[playerid][ePredatorReplacementActor] );
}

GetActorPlayerReplacement(actorid) {
	for(new playerid, max_playerid = GetPlayerPoolSize(); playerid <= max_playerid; playerid ++) {
		if( !IsPlayerConnected(playerid) ) {
			continue;
		}

		if( gPredatorData[playerid][ePredatorState] != PREDATORSTATE_ACTIVE ) {
			continue;
		}

		if( actorid == gPredatorData[playerid][ePredatorReplacementActor] ) {
			return playerid;
		}
	}
	return INVALID_PLAYER_ID;
}

//------------------------------------------------------------------------------
// Fade Methods

CreateFadeTextdraw() {
	gFadeTD =
	TextDrawCreate(1.0, 1.0, "_");
	TextDrawLetterSize(gFadeTD, 0.0, 50.0);
	TextDrawUseBox(gFadeTD, 1);
	TextDrawBoxColor(gFadeTD, 255);
	TextDrawTextSize(gFadeTD, 640.0, 0.0);
	TextDrawSetSelectable(gFadeTD, 0);
}

DestroyFadeTextdraw() {
	TextDrawDestroy(gFadeTD);
}

CalculateFadeProgress(playerid) {
	gFadeData[playerid][eFadePassedTime] = GetTickCount() - gFadeData[playerid][eFadeStartTick];
	gFadeData[playerid][eFadeProgress] = Float:gFadeData[playerid][eFadePassedTime] / Float:gFadeData[playerid][eFadeDuration];
	FloatClamp(gFadeData[playerid][eFadeProgress], 0.0, 1.0);

	switch( gFadeData[playerid][eFadeState] ) {
		case FADESTATE_TO_OPAQUE: {
			gFadeData[playerid][eFadeAlpha] = floatround(gFadeData[playerid][eFadeProgress] * 0xFF, floatround_ceil);
		}
		case FADESTATE_TO_TRANSP: {
			gFadeData[playerid][eFadeAlpha] = 0xFF - floatround(gFadeData[playerid][eFadeProgress] * 0xFF, floatround_ceil);
		}
	}
	clamp(gFadeData[playerid][eFadeAlpha], 0x0, 0xFF);
}

ApplyFadeAlpha(playerid, alpha) {
	if( alpha == 0x0 ) {
		TextDrawHideForPlayer(playerid, gFadeTD);
	} else {
		TextDrawBoxColor(gFadeTD, alpha );
		TextDrawShowForPlayer(playerid, gFadeTD);
	}
}

SetupFade(playerid, bool:fadeto_opaque, duration_ms) {
	gFadeData[playerid][eFadeDuration] = duration_ms;
	clamp(gFadeData[playerid][eFadeDuration], PREDATOR_FADE_TIME_MIN, PREDATOR_FADE_TIME_MAX);

	gFadeData[playerid][eFadeStartTick] = GetTickCount();
	gFadeData[playerid][eFadeEndTick] = gFadeData[playerid][eFadeStartTick] + gFadeData[playerid][eFadeDuration];

	gFadeData[playerid][eFadeState] = fadeto_opaque ? FADESTATE_TO_OPAQUE : FADESTATE_TO_TRANSP;
	return 1;
}

forward UpdatePredatorFade();
public UpdatePredatorFade() {
	for(new playerid, max_playerid = GetPlayerPoolSize(); playerid <= max_playerid; playerid ++) {
		if( IsPlayerConnected(playerid) && gFadeData[playerid][eFadeState] != FADESTATE_OFF ) {
			CalculateFadeProgress(playerid);
			ApplyFadeAlpha(playerid, gFadeData[playerid][eFadeAlpha]);

			if( gFadeData[playerid][eFadePassedTime] > gFadeData[playerid][eFadeDuration] ) {
				switch(gPredatorData[playerid][ePredatorState]) {
					case PREDATORSTATE_INTRO: {
						TogglePlayerSpectating(playerid, true);

						gPredatorData[playerid][ePredatorState] ++;
					}
					case PREDATORSTATE_OUTRO: {
						gPredatorData[playerid][ePredatorState] ++;
					}
				}
				gFadeData[playerid][eFadeState] = FADESTATE_OFF;
			}
		}
	}
}

//------------------------------------------------------------------------------
// Spawn Data Methods

IsSeatTaken(vehicleid, seatid) {
	for(new playerid, max_playerid = GetPlayerPoolSize(); playerid <= max_playerid; playerid ++) {
		if( IsPlayerConnected(playerid) && GetPlayerVehicleID(playerid) == vehicleid && GetPlayerVehicleSeat(playerid) == seatid) {
			return 1;
		}
	}
	return 0;
}

SaveSpawnData(playerid) {
	gSpawnData[playerid][eSpawnSkin] = GetPlayerSkin(playerid);
	gSpawnData[playerid][eSpawnInterior] = GetPlayerInterior(playerid);
	gSpawnData[playerid][eSpawnWorld] = GetPlayerVirtualWorld(playerid);
	GetPlayerHealth(playerid, gSpawnData[playerid][eSpawnHealth]);
	GetPlayerArmour(playerid, gSpawnData[playerid][eSpawnArmour]);
	gSpawnData[playerid][eSpawnMoney] = GetPlayerMoney(playerid);

	for(new s; s < 13; s ++) {
		GetPlayerWeaponData(playerid, s, gSpawnData[playerid][eSpawnWeaponData][s], gSpawnData[playerid][eSpawnAmmoData][s]);
	}

	gSpawnData[playerid][eSpawnVehicleID] = GetPlayerVehicleID(playerid);
	if( gSpawnData[playerid][eSpawnVehicleID] ) {
		gSpawnData[playerid][eSpawnVehicleSeat] = GetPlayerVehicleSeat(playerid);

		GetVehiclePos(gSpawnData[playerid][eSpawnVehicleID], gSpawnData[playerid][eSpawnX], gSpawnData[playerid][eSpawnY], gSpawnData[playerid][eSpawnZ]);
		GetVehicleZAngle(gSpawnData[playerid][eSpawnVehicleID], gSpawnData[playerid][eSpawnA]);
	} else {
		GetPlayerPos(playerid, gSpawnData[playerid][eSpawnX], gSpawnData[playerid][eSpawnY], gSpawnData[playerid][eSpawnZ]);
		GetPlayerFacingAngle(playerid, gSpawnData[playerid][eSpawnA]);
	}
}

ApplySpawnData(playerid) {
	SetPlayerSkin(playerid, gSpawnData[playerid][eSpawnSkin]);
	SetPlayerInterior(playerid, gSpawnData[playerid][eSpawnInterior]);
	SetPlayerVirtualWorld(playerid, gSpawnData[playerid][eSpawnWorld]);
	SetPlayerHealth(playerid, gSpawnData[playerid][eSpawnHealth]);
	SetPlayerArmour(playerid, gSpawnData[playerid][eSpawnArmour]);

	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, gSpawnData[playerid][eSpawnMoney]);

	if( IsValidVehicle(gSpawnData[playerid][eSpawnVehicleID]) && !IsSeatTaken(gSpawnData[playerid][eSpawnVehicleID], gSpawnData[playerid][eSpawnVehicleSeat]) ) {
		PutPlayerInVehicle(playerid, gSpawnData[playerid][eSpawnVehicleID], gSpawnData[playerid][eSpawnVehicleSeat]);
	} else {
		SetPlayerPos(playerid, gSpawnData[playerid][eSpawnX], gSpawnData[playerid][eSpawnY], gSpawnData[playerid][eSpawnZ]);
		SetPlayerFacingAngle(playerid, gSpawnData[playerid][eSpawnA]);
	}
	SetCameraBehindPlayer(playerid);
}

//------------------------------------------------------------------------------
// Graphical User Interface Methods

CreateGUIGlobalTextdraws() {
	gGUIGTD[eGTDGUIDataBG] =
	TextDrawCreate			(320.0, 320.0, "_");
	TextDrawAlignment		(gGUIGTD[eGTDGUIDataBG], 2);
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataBG], 0.0, 11.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataBG], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataBG], 100);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataBG], 630.0, 240.0);

	gGUIGTD[eGTDGUIDataCaption] =
	TextDrawCreate			(200.0, 318.0, "Predator Data");
	TextDrawBackgroundColor	(gGUIGTD[eGTDGUIDataCaption], 255);
	TextDrawFont			(gGUIGTD[eGTDGUIDataCaption], 2);
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataCaption], 0.2, 1.0);
	TextDrawColor			(gGUIGTD[eGTDGUIDataCaption], -1);
	TextDrawSetOutline		(gGUIGTD[eGTDGUIDataCaption], 0);
	TextDrawSetProportional	(gGUIGTD[eGTDGUIDataCaption], 1);
	TextDrawSetShadow		(gGUIGTD[eGTDGUIDataCaption], 1);

	gGUIGTD[eGTDGUIDataTotThrustBG] =
	TextDrawCreate			(202.0, 332.0, "_");
	TextDrawBackgroundColor	(gGUIGTD[eGTDGUIDataTotThrustBG], 0);
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataTotThrustBG], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataTotThrustBG], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataTotThrustBG], -206);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataTotThrustBG], 438.0, 0.0);

	gGUIGTD[eGTDGUIDataTotThrustBar] =
	TextDrawCreate			(202.0, 332.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataTotThrustBar], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataTotThrustBar], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataTotThrustBar], -1);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataTotThrustBar], 200.0, 0.0);

	// Thrust Add
	gGUIGTD[eGTDGUIDataAddThrustBG] =
	TextDrawCreate			(202.0, 344.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataAddThrustBG], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataAddThrustBG], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataAddThrustBG], -206);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataAddThrustBG], 438.0, 0.0);

	gGUIGTD[eGTDGUIDataAddThrustNeg] =
	TextDrawCreate			(321.0, 344.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataAddThrustNeg], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataAddThrustNeg], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataAddThrustNeg], -16777166);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataAddThrustNeg], 199.0, 0.0);

	gGUIGTD[eGTDGUIDataAddThrustPos] =
	TextDrawCreate			(321.0, 344.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataAddThrustPos], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataAddThrustPos], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataAddThrustPos], 16711730);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataAddThrustPos], 438.0, 0.0);

	gGUIGTD[eGTDGUIDataAddThrustBar] =
	TextDrawCreate			(321.0, 344.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataAddThrustBar], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataAddThrustBar], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataAddThrustBar], -1);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataAddThrustBar], 319.0, 0.0);

	// Pitch
	gGUIGTD[eGTDGUIDataTotPitchBG] =
	TextDrawCreate			(202.0, 356.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataTotPitchBG], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataTotPitchBG], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataTotPitchBG], -206);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataTotPitchBG], 438.0, 0.0);

	gGUIGTD[eGTDGUIDataTotPitchBar] =
	TextDrawCreate			(202.0, 356.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataTotPitchBar], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataTotPitchBar], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataTotPitchBar], -1);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataTotPitchBar], 200.0, 0.0);

	// Pitch Add
	gGUIGTD[eGTDGUIDataAddPitchBG] =
	TextDrawCreate			(202.0, 368.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataAddPitchBG], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataAddPitchBG], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataAddPitchBG], -206);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataAddPitchBG], 438.0, 0.0);

	gGUIGTD[eGTDGUIDataAddPitchNeg] =
	TextDrawCreate			(321.0, 368.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataAddPitchNeg], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataAddPitchNeg], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataAddPitchNeg], -16777166);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataAddPitchNeg], 199.0, 0.0);

	gGUIGTD[eGTDGUIDataAddPitchPos] =
	TextDrawCreate			(321.0, 368.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataAddPitchPos], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataAddPitchPos], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataAddPitchPos], 16711730);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataAddPitchPos], 438.000000, 0.000000);

	gGUIGTD[eGTDGUIDataAddPitchBar] =
	TextDrawCreate			(321.0, 368.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataAddPitchBar], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataAddPitchBar], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataAddPitchBar], -1);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataAddPitchBar], 319.000000, 0.000000);

	// Yaw Total
	gGUIGTD[eGTDGUIDataTotYawBG] =
	TextDrawCreate			(202.0, 380.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataTotYawBG], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataTotYawBG], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataTotYawBG], -206);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataTotYawBG], 438.0, 0.0);

	gGUIGTD[eGTDGUIDataTotYawBar] =
	TextDrawCreate			(202.0, 380.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataTotYawBar], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataTotYawBar], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataTotYawBar], -1);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataTotYawBar], 200.0, 0.0);

	// Yaw Add
	gGUIGTD[eGTDGUIDataAddYawBG] =
	TextDrawCreate			(202.0, 392.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataAddYawBG], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataAddYawBG], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataAddYawBG], -206);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataAddYawBG], 438.0, 0.0);

	gGUIGTD[eGTDGUIDataAddYawNeg] =
	TextDrawCreate			(321.0, 392.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataAddYawNeg], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataAddYawNeg], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataAddYawNeg], -16777166);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataAddYawNeg], 199.0, 0.0);

	gGUIGTD[eGTDGUIDataAddYawPos] =
	TextDrawCreate			(321.0, 392.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataAddYawPos], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataAddYawPos], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataAddYawPos], 16711730);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataAddYawPos], 438.0, 0.0);

	gGUIGTD[eGTDGUIDataAddYawBar] =
	TextDrawCreate			(321.0, 392.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataAddYawBar], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataAddYawBar], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataAddYawBar], -1);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataAddYawBar], 319.0, 0.0);

	// Total Fuel
	gGUIGTD[eGTDGUIDataTotFuelBG] =
	TextDrawCreate			(202.0, 404.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataTotFuelBG], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataTotFuelBG], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataTotFuelBG], -206);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataTotFuelBG], 438.0, 0.0);

	gGUIGTD[eGTDGUIDataTotFuelBar] =
	TextDrawCreate			(202.0, 404.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataTotFuelBar], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataTotFuelBar], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataTotFuelBar], -1);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataTotFuelBar], 200.0, 0.0);

	// Total Distance
	gGUIGTD[eGTDGUIDataTotDistBG] =
	TextDrawCreate			(202.0, 416.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataTotDistBG], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataTotDistBG], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataTotDistBG], -206);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataTotDistBG], 438.0, 0.0);

	gGUIGTD[eGTDGUIDataTotDistBar] =
	TextDrawCreate			(202.0, 416.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIDataTotDistBar], 0.0, 0.7);
	TextDrawUseBox			(gGUIGTD[eGTDGUIDataTotDistBar], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIDataTotDistBar], -1);
	TextDrawTextSize		(gGUIGTD[eGTDGUIDataTotDistBar], 200.0, 0.0);

	gGUIGTD[eGTDGUIKeyBG] =
	TextDrawCreate			(498.0, 11.0, "_");
	TextDrawLetterSize		(gGUIGTD[eGTDGUIKeyBG], 0.0, 9.5);
	TextDrawUseBox			(gGUIGTD[eGTDGUIKeyBG], 1);
	TextDrawBoxColor		(gGUIGTD[eGTDGUIKeyBG], 50);
	TextDrawTextSize		(gGUIGTD[eGTDGUIKeyBG], 630.0, 0.0);

	gGUIGTD[eGTDGUIKeyCaption] =
	TextDrawCreate			(499.0, 9.0, "keystrokes");
	TextDrawBackgroundColor	(gGUIGTD[eGTDGUIKeyCaption], 255);
	TextDrawFont			(gGUIGTD[eGTDGUIKeyCaption], 2);
	TextDrawLetterSize		(gGUIGTD[eGTDGUIKeyCaption], 0.2, 1.0);
	TextDrawColor			(gGUIGTD[eGTDGUIKeyCaption], -1);
	TextDrawSetOutline		(gGUIGTD[eGTDGUIKeyCaption], 0);
	TextDrawSetProportional	(gGUIGTD[eGTDGUIKeyCaption], 1);
	TextDrawSetShadow		(gGUIGTD[eGTDGUIKeyCaption], 1);

	for(new key, Float:y, str_l[20], str_r[30]; key < MAX_GUI_KEYS; key++) {
		y = 22.0 + (key * 13.0);

		switch(key) {
			case GUI_KEY_THRUST: {
				str_l = "Thrust++";
				str_r = "SPACE";
			}
			case GUI_KEY_PITCH_ADD: {
				str_l = "Pitch++";
				str_r = "~k~~GO_FORWARD~";
			}
			case GUI_KEY_PITCH_SUB: {
				str_l = "Pitch--";
				str_r = "~k~~GO_BACK~";
			}
			case GUI_KEY_YAW_ADD: {
				str_l = "Yaw++";
				str_r = "~k~~GO_RIGHT~";
			}
			case GUI_KEY_YAW_SUB: {
				str_l = "Yaw--";
				str_r = "~k~~GO_LEFT~";
			}
			case GUI_KEY_DESTROY: {
				str_l = "Destroy";
				str_r = "~k~~VEHICLE_ENTER_EXIT~";
			}
		}

		gGUIGTD[eGTDGUIKeyL][key] =
		TextDrawCreate			(498.0, y, str_l);
		TextDrawBackgroundColor	(gGUIGTD[eGTDGUIKeyL][key], 0);
		TextDrawFont			(gGUIGTD[eGTDGUIKeyL][key], 2);
		TextDrawLetterSize		(gGUIGTD[eGTDGUIKeyL][key], 0.2, 1.0);
		TextDrawColor			(gGUIGTD[eGTDGUIKeyL][key], 255);
		TextDrawSetOutline		(gGUIGTD[eGTDGUIKeyL][key], 0);
		TextDrawSetProportional	(gGUIGTD[eGTDGUIKeyL][key], 1);
		TextDrawSetShadow		(gGUIGTD[eGTDGUIKeyL][key], 1);
		TextDrawUseBox			(gGUIGTD[eGTDGUIKeyL][key], 1);
		TextDrawBoxColor		(gGUIGTD[eGTDGUIKeyL][key], -206);
		TextDrawTextSize		(gGUIGTD[eGTDGUIKeyL][key], 556.0, 0.0);

		gGUIGTD[eGTDGUIKeyR][key] =
		TextDrawCreate			(559.0, y, str_r);
		TextDrawBackgroundColor	(gGUIGTD[eGTDGUIKeyR][key], 0);
		TextDrawFont			(gGUIGTD[eGTDGUIKeyR][key], 2);
		TextDrawLetterSize		(gGUIGTD[eGTDGUIKeyR][key], 0.2, 1.0);
		TextDrawColor			(gGUIGTD[eGTDGUIKeyR][key], 255);
		TextDrawSetOutline		(gGUIGTD[eGTDGUIKeyR][key], 0);
		TextDrawSetProportional	(gGUIGTD[eGTDGUIKeyR][key], 1);
		TextDrawSetShadow		(gGUIGTD[eGTDGUIKeyR][key], 1);
		TextDrawUseBox			(gGUIGTD[eGTDGUIKeyR][key], 1);
		TextDrawBoxColor		(gGUIGTD[eGTDGUIKeyR][key], -206);
		TextDrawTextSize		(gGUIGTD[eGTDGUIKeyR][key], 630.0, 0.0);
	}
}

DestroyGUIGlobalTextdraws() {
	for(new gtd; gtd < MAX_GUI_GLOBAL_TEXTDRAWS; gtd ++) {
		TextDrawDestroy(gGUIGTD[gtd]);
	}
}

CreateGUIPlayerTextdraws(playerid) {
	gGUIPTD[playerid][ePTDGUITotThrustText] =
	CreatePlayerTextDraw			(playerid, 320.0, 330.0, "thrust");
	PlayerTextDrawAlignment			(playerid, gGUIPTD[playerid][ePTDGUITotThrustText], 2);
	PlayerTextDrawBackgroundColor	(playerid, gGUIPTD[playerid][ePTDGUITotThrustText], 0);
	PlayerTextDrawFont				(playerid, gGUIPTD[playerid][ePTDGUITotThrustText], 2);
	PlayerTextDrawLetterSize		(playerid, gGUIPTD[playerid][ePTDGUITotThrustText], 0.21, 1.0);
	PlayerTextDrawColor				(playerid, gGUIPTD[playerid][ePTDGUITotThrustText], 255);
	PlayerTextDrawSetOutline		(playerid, gGUIPTD[playerid][ePTDGUITotThrustText], 0);
	PlayerTextDrawSetProportional	(playerid, gGUIPTD[playerid][ePTDGUITotThrustText], 1);
	PlayerTextDrawSetShadow			(playerid, gGUIPTD[playerid][ePTDGUITotThrustText], 1);
	PlayerTextDrawUseBox			(playerid, gGUIPTD[playerid][ePTDGUITotThrustText], 1);
	PlayerTextDrawBoxColor			(playerid, gGUIPTD[playerid][ePTDGUITotThrustText], 0);
	PlayerTextDrawTextSize			(playerid, gGUIPTD[playerid][ePTDGUITotThrustText], 0.0, 236.0);

	gGUIPTD[playerid][ePTDGUIAddThrustText] =
	CreatePlayerTextDraw			(playerid, 320.0, 342.0, "+thrust");
	PlayerTextDrawAlignment			(playerid, gGUIPTD[playerid][ePTDGUIAddThrustText], 2);
	PlayerTextDrawBackgroundColor	(playerid, gGUIPTD[playerid][ePTDGUIAddThrustText], 0);
	PlayerTextDrawFont				(playerid, gGUIPTD[playerid][ePTDGUIAddThrustText], 2);
	PlayerTextDrawLetterSize		(playerid, gGUIPTD[playerid][ePTDGUIAddThrustText], 0.21, 1.0);
	PlayerTextDrawColor				(playerid, gGUIPTD[playerid][ePTDGUIAddThrustText], 255);
	PlayerTextDrawSetOutline		(playerid, gGUIPTD[playerid][ePTDGUIAddThrustText], 0);
	PlayerTextDrawSetProportional	(playerid, gGUIPTD[playerid][ePTDGUIAddThrustText], 1);
	PlayerTextDrawSetShadow			(playerid, gGUIPTD[playerid][ePTDGUIAddThrustText], 1);
	PlayerTextDrawUseBox			(playerid, gGUIPTD[playerid][ePTDGUIAddThrustText], 1);
	PlayerTextDrawBoxColor			(playerid, gGUIPTD[playerid][ePTDGUIAddThrustText], 0);
	PlayerTextDrawTextSize			(playerid, gGUIPTD[playerid][ePTDGUIAddThrustText], 0.0, 236.0);

	gGUIPTD[playerid][ePTDGUITotPitchText] =
	CreatePlayerTextDraw			(playerid, 320.0, 354.0, "pitch");
	PlayerTextDrawAlignment			(playerid, gGUIPTD[playerid][ePTDGUITotPitchText], 2);
	PlayerTextDrawBackgroundColor	(playerid, gGUIPTD[playerid][ePTDGUITotPitchText], 0);
	PlayerTextDrawFont				(playerid, gGUIPTD[playerid][ePTDGUITotPitchText], 2);
	PlayerTextDrawLetterSize		(playerid, gGUIPTD[playerid][ePTDGUITotPitchText], 0.21, 1.0);
	PlayerTextDrawColor				(playerid, gGUIPTD[playerid][ePTDGUITotPitchText], 255);
	PlayerTextDrawSetOutline		(playerid, gGUIPTD[playerid][ePTDGUITotPitchText], 0);
	PlayerTextDrawSetProportional	(playerid, gGUIPTD[playerid][ePTDGUITotPitchText], 1);
	PlayerTextDrawSetShadow			(playerid, gGUIPTD[playerid][ePTDGUITotPitchText], 1);
	PlayerTextDrawUseBox			(playerid, gGUIPTD[playerid][ePTDGUITotPitchText], 1);
	PlayerTextDrawBoxColor			(playerid, gGUIPTD[playerid][ePTDGUITotPitchText], 0);
	PlayerTextDrawTextSize			(playerid, gGUIPTD[playerid][ePTDGUITotPitchText], 0.0, 236.0);

	gGUIPTD[playerid][ePTDGUIAddPitchText] =
	CreatePlayerTextDraw			(playerid, 320.0, 366.0, "+pitch");
	PlayerTextDrawAlignment			(playerid, gGUIPTD[playerid][ePTDGUIAddPitchText], 2);
	PlayerTextDrawBackgroundColor	(playerid, gGUIPTD[playerid][ePTDGUIAddPitchText], 0);
	PlayerTextDrawFont				(playerid, gGUIPTD[playerid][ePTDGUIAddPitchText], 2);
	PlayerTextDrawLetterSize		(playerid, gGUIPTD[playerid][ePTDGUIAddPitchText], 0.21, 1.0);
	PlayerTextDrawColor				(playerid, gGUIPTD[playerid][ePTDGUIAddPitchText], 255);
	PlayerTextDrawSetOutline		(playerid, gGUIPTD[playerid][ePTDGUIAddPitchText], 0);
	PlayerTextDrawSetProportional	(playerid, gGUIPTD[playerid][ePTDGUIAddPitchText], 1);
	PlayerTextDrawSetShadow			(playerid, gGUIPTD[playerid][ePTDGUIAddPitchText], 1);
	PlayerTextDrawUseBox			(playerid, gGUIPTD[playerid][ePTDGUIAddPitchText], 1);
	PlayerTextDrawBoxColor			(playerid, gGUIPTD[playerid][ePTDGUIAddPitchText], 0);
	PlayerTextDrawTextSize			(playerid, gGUIPTD[playerid][ePTDGUIAddPitchText], 0.0, 236.0);

	gGUIPTD[playerid][ePTDGUITotYawText] =
	CreatePlayerTextDraw			(playerid, 320.0, 378.0, "yaw");
	PlayerTextDrawAlignment			(playerid, gGUIPTD[playerid][ePTDGUITotYawText], 2);
	PlayerTextDrawBackgroundColor	(playerid, gGUIPTD[playerid][ePTDGUITotYawText], 0);
	PlayerTextDrawFont				(playerid, gGUIPTD[playerid][ePTDGUITotYawText], 2);
	PlayerTextDrawLetterSize		(playerid, gGUIPTD[playerid][ePTDGUITotYawText], 0.21, 1.0);
	PlayerTextDrawColor				(playerid, gGUIPTD[playerid][ePTDGUITotYawText], 255);
	PlayerTextDrawSetOutline		(playerid, gGUIPTD[playerid][ePTDGUITotYawText], 0);
	PlayerTextDrawSetProportional	(playerid, gGUIPTD[playerid][ePTDGUITotYawText], 1);
	PlayerTextDrawSetShadow			(playerid, gGUIPTD[playerid][ePTDGUITotYawText], 1);
	PlayerTextDrawUseBox			(playerid, gGUIPTD[playerid][ePTDGUITotYawText], 1);
	PlayerTextDrawBoxColor			(playerid, gGUIPTD[playerid][ePTDGUITotYawText], 0);
	PlayerTextDrawTextSize			(playerid, gGUIPTD[playerid][ePTDGUITotYawText], 0.0, 236.0);

	gGUIPTD[playerid][ePTDGUIAddYawText] =
	CreatePlayerTextDraw			(playerid, 320.0, 390.0, "+yaw");
	PlayerTextDrawAlignment			(playerid, gGUIPTD[playerid][ePTDGUIAddYawText], 2);
	PlayerTextDrawBackgroundColor	(playerid, gGUIPTD[playerid][ePTDGUIAddYawText], 0);
	PlayerTextDrawFont				(playerid, gGUIPTD[playerid][ePTDGUIAddYawText], 2);
	PlayerTextDrawLetterSize		(playerid, gGUIPTD[playerid][ePTDGUIAddYawText], 0.21, 1.0);
	PlayerTextDrawColor				(playerid, gGUIPTD[playerid][ePTDGUIAddYawText], 255);
	PlayerTextDrawSetOutline		(playerid, gGUIPTD[playerid][ePTDGUIAddYawText], 0);
	PlayerTextDrawSetProportional	(playerid, gGUIPTD[playerid][ePTDGUIAddYawText], 1);
	PlayerTextDrawSetShadow			(playerid, gGUIPTD[playerid][ePTDGUIAddYawText], 1);
	PlayerTextDrawUseBox			(playerid, gGUIPTD[playerid][ePTDGUIAddYawText], 1);
	PlayerTextDrawBoxColor			(playerid, gGUIPTD[playerid][ePTDGUIAddYawText], 0);
	PlayerTextDrawTextSize			(playerid, gGUIPTD[playerid][ePTDGUIAddYawText], 0.0, 236.0);

	gGUIPTD[playerid][ePTDGUITotFuelText] =
	CreatePlayerTextDraw			(playerid, 320.0, 402.0, "fuel");
	PlayerTextDrawAlignment			(playerid, gGUIPTD[playerid][ePTDGUITotFuelText], 2);
	PlayerTextDrawBackgroundColor	(playerid, gGUIPTD[playerid][ePTDGUITotFuelText], 0);
	PlayerTextDrawFont				(playerid, gGUIPTD[playerid][ePTDGUITotFuelText], 2);
	PlayerTextDrawLetterSize		(playerid, gGUIPTD[playerid][ePTDGUITotFuelText], 0.21, 1.0);
	PlayerTextDrawColor				(playerid, gGUIPTD[playerid][ePTDGUITotFuelText], 255);
	PlayerTextDrawSetOutline		(playerid, gGUIPTD[playerid][ePTDGUITotFuelText], 0);
	PlayerTextDrawSetProportional	(playerid, gGUIPTD[playerid][ePTDGUITotFuelText], 1);
	PlayerTextDrawSetShadow			(playerid, gGUIPTD[playerid][ePTDGUITotFuelText], 1);
	PlayerTextDrawUseBox			(playerid, gGUIPTD[playerid][ePTDGUITotFuelText], 1);
	PlayerTextDrawBoxColor			(playerid, gGUIPTD[playerid][ePTDGUITotFuelText], 0);
	PlayerTextDrawTextSize			(playerid, gGUIPTD[playerid][ePTDGUITotFuelText], 0.0, 236.0);

	gGUIPTD[playerid][ePTDGUITotDistText] =
	CreatePlayerTextDraw			(playerid, 320.0, 414.0, "target distance");
	PlayerTextDrawAlignment			(playerid, gGUIPTD[playerid][ePTDGUITotDistText], 2);
	PlayerTextDrawBackgroundColor	(playerid, gGUIPTD[playerid][ePTDGUITotDistText], 0);
	PlayerTextDrawFont				(playerid, gGUIPTD[playerid][ePTDGUITotDistText], 2);
	PlayerTextDrawLetterSize		(playerid, gGUIPTD[playerid][ePTDGUITotDistText], 0.21, 1.0);
	PlayerTextDrawColor				(playerid, gGUIPTD[playerid][ePTDGUITotDistText], 255);
	PlayerTextDrawSetOutline		(playerid, gGUIPTD[playerid][ePTDGUITotDistText], 0);
	PlayerTextDrawSetProportional	(playerid, gGUIPTD[playerid][ePTDGUITotDistText], 1);
	PlayerTextDrawSetShadow			(playerid, gGUIPTD[playerid][ePTDGUITotDistText], 1);
	PlayerTextDrawUseBox			(playerid, gGUIPTD[playerid][ePTDGUITotDistText], 1);
	PlayerTextDrawBoxColor			(playerid, gGUIPTD[playerid][ePTDGUITotDistText], 0);
	PlayerTextDrawTextSize			(playerid, gGUIPTD[playerid][ePTDGUITotDistText], 0.0, 236.0);
}

DestroyGUIPlayerTextdraws(playerid) {
	for(new ptd; ptd < MAX_GUI_PLAYER_TEXTDRAWS; ptd ++) {
		PlayerTextDrawDestroy(playerid, gGUIPTD[playerid][ptd]);
	}
}

ShowGUI(playerid) {
	CreateGUIPlayerTextdraws(playerid);

	RefreshGUI(playerid);

	for(new gtd; gtd < MAX_GUI_GLOBAL_TEXTDRAWS; gtd ++) {
		TextDrawShowForPlayer(playerid, gGUIGTD[gtd]);
	}

	for(new ptd; ptd < MAX_GUI_PLAYER_TEXTDRAWS; ptd ++) {
		PlayerTextDrawShow(playerid, gGUIPTD[playerid][ptd]);
	}
}

HideGUI(playerid) {
	DestroyGUIPlayerTextdraws(playerid);

	for(new gtd; gtd < MAX_GUI_GLOBAL_TEXTDRAWS; gtd ++) {
		TextDrawHideForPlayer(playerid, gGUIGTD[gtd]);
	}
}

RefreshGUI(playerid) {
	// Total Thrust Bar
	new Float:thrust_tot_percent = (gPredatorData[playerid][ePredatorThrust] - PREDATOR_THRUST_TOT_MIN) / (PREDATOR_THRUST_TOT_MAX - PREDATOR_THRUST_TOT_MIN);
	FloatClamp(thrust_tot_percent, 0.0, 1.0);
	TextDrawTextSize(gGUIGTD[eGTDGUIDataTotThrustBar], 200.0 + (thrust_tot_percent * 238.0), 0.0);
	TextDrawShowForPlayer(playerid, gGUIGTD[eGTDGUIDataTotThrustBar]);

	// Total Thrust Text
	format(gGUIString, sizeof gGUIString, "thrust %.2f", gPredatorData[playerid][ePredatorThrust]);
	PlayerTextDrawSetString(playerid, gGUIPTD[playerid][ePTDGUITotThrustText], gGUIString);

	// Add Thrust Bar
	new Float:thrust_add_percent = gPredatorData[playerid][ePredatorThrustAdd] / PREDATOR_THRUST_ADD_MAX;
	FloatClamp(thrust_add_percent, -1.0, 1.0);
	TextDrawTextSize(gGUIGTD[eGTDGUIDataAddThrustBar], 319.0 + (thrust_add_percent * 119.5), 0.0);
	TextDrawShowForPlayer(playerid, gGUIGTD[eGTDGUIDataAddThrustBar]);

	// Add Thrust Text
	format(gGUIString, sizeof gGUIString, "+thrust %.2f", gPredatorData[playerid][ePredatorThrustAdd]);
	PlayerTextDrawSetString(playerid, gGUIPTD[playerid][ePTDGUIAddThrustText], gGUIString);

	// Total Pitch Bar
	new Float:pitch_percentage = (gPredatorData[playerid][ePredatorPitch] - PREDATOR_PITCH_TOT_MIN) / (PREDATOR_PITCH_TOT_MAX - PREDATOR_PITCH_TOT_MIN);
	FloatClamp(pitch_percentage, 0.0, 1.0);
	TextDrawTextSize(gGUIGTD[eGTDGUIDataTotPitchBar], 200.0 + (pitch_percentage * 238.0), 0.0);
	TextDrawShowForPlayer(playerid, gGUIGTD[eGTDGUIDataTotPitchBar]);

	// Total Pitch Text
	format(gGUIString, sizeof gGUIString, "pitch %.2f", gPredatorData[playerid][ePredatorPitch]);
	PlayerTextDrawSetString(playerid, gGUIPTD[playerid][ePTDGUITotPitchText], gGUIString);

	// Add Pitch Bar
	new Float:pitch_add_percent = gPredatorData[playerid][ePredatorPitchAdd] / PREDATOR_PITCH_ADD_MAX;
	FloatClamp(pitch_add_percent, -1.0, 1.0);
	TextDrawTextSize(gGUIGTD[eGTDGUIDataAddPitchBar], 319.0 + (pitch_add_percent * 119.5), 0.0);
	TextDrawShowForPlayer(playerid, gGUIGTD[eGTDGUIDataAddPitchBar]);

	// Add Pitch Text
	format(gGUIString, sizeof gGUIString, "+pitch %.2f", gPredatorData[playerid][ePredatorPitchAdd]);
	PlayerTextDrawSetString(playerid, gGUIPTD[playerid][ePTDGUIAddPitchText], gGUIString);

	// Total Yaw Bar
	new Float:yaw_percentage = gPredatorData[playerid][ePredatorYaw] / 360;
	FloatClamp(yaw_percentage, 0.0, 1.0);
	TextDrawTextSize(gGUIGTD[eGTDGUIDataTotYawBar], 200.0 + (yaw_percentage * 238.0), 0.0);
	TextDrawShowForPlayer(playerid, gGUIGTD[eGTDGUIDataTotYawBar]);

	// Total Yaw Text
	format(gGUIString, sizeof gGUIString, "yaw %.2f", gPredatorData[playerid][ePredatorYaw]);
	PlayerTextDrawSetString(playerid, gGUIPTD[playerid][ePTDGUITotYawText], gGUIString);

	// Add Yaw Bar
	new Float:yaw_add_percent = gPredatorData[playerid][ePredatorYawAdd] / PREDATOR_YAW_ADD_MAX;
	FloatClamp(yaw_add_percent, -1.0, 1.0);
	TextDrawTextSize(gGUIGTD[eGTDGUIDataAddYawBar], 319.0 + (yaw_add_percent * 119.5), 0.0);
	TextDrawShowForPlayer(playerid, gGUIGTD[eGTDGUIDataAddYawBar]);

	// Add Yaw Text
	format(gGUIString, sizeof gGUIString, "+yaw %.2f", gPredatorData[playerid][ePredatorYawAdd]);
	PlayerTextDrawSetString(playerid, gGUIPTD[playerid][ePTDGUIAddYawText], gGUIString);

	// Total Distance Bar
	new Float:dist_percentage = gPredatorData[playerid][ePredatorTargetDist] / PREDATOR_GUI_DIST_MAX;
	FloatClamp(dist_percentage, 0.0, 1.0);
	TextDrawTextSize(gGUIGTD[eGTDGUIDataTotDistBar], 200.0 + (dist_percentage * 238.0), 0.0);
	TextDrawShowForPlayer(playerid, gGUIGTD[eGTDGUIDataTotDistBar]);

	// Total Distance Text
	if( gPredatorData[playerid][ePredatorTargetDist] > PREDATOR_GUI_DIST_MAX ) {
		format(gGUIString, sizeof gGUIString, "Dist >%.2f", PREDATOR_GUI_DIST_MAX);
	} else {
		format(gGUIString, sizeof gGUIString, "Dist %.2f", gPredatorData[playerid][ePredatorTargetDist]);
	}
	PlayerTextDrawSetString(playerid, gGUIPTD[playerid][ePTDGUITotDistText], gGUIString);

	// Total Fuel Bar
	new Float:fuel_percentage = gPredatorData[playerid][ePredatorFuel] / PREDATOR_FUEL_MAX;
	FloatClamp(fuel_percentage, 0.0, 1.0);
	TextDrawTextSize(gGUIGTD[eGTDGUIDataTotFuelBar], 200.0 + (fuel_percentage * 238.0), 0.0);
	TextDrawShowForPlayer(playerid, gGUIGTD[eGTDGUIDataTotFuelBar]);

	// Total Fuel Text
	format(gGUIString, sizeof gGUIString, "fuel %.2f%%", fuel_percentage * 100);
	PlayerTextDrawSetString(playerid, gGUIPTD[playerid][ePTDGUITotFuelText], gGUIString);
}

//------------------------------------------------------------------------------
// Vehicle Collision Area

GetVehicleInLine(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2) {
	new areas[MAX_VEHICLES], areas_count;
	areas_count = GetDynamicAreasForLine(x1, y1, z1, x2, y2, z2, areas, sizeof areas);

	if( areas_count == 0 ) {
		return INVALID_VEHICLE_ID;
	}

	for(new i = areas_count - 1; i >= 0; i --) {
		/*
			Count backwards because the vehicles are sorted by distance in descending order.
			(The nearest vehicles are found at the end of the array)
		*/

		new attached_vehicleid = Streamer_GetIntData(STREAMER_TYPE_AREA, areas[i], E_STREAMER_ATTACHED_VEHICLE);

		if( IsValidVehicle(attached_vehicleid) && areas[i] == gVehicleColArea[attached_vehicleid-1] ) {
			return attached_vehicleid;
		}
	}

	return INVALID_VEHICLE_ID;
}

InitVehicleCollisionAreaData() {
	for(new v; v < MAX_VEHICLES; v ++) {
		gVehicleColArea[v] = INVALID_STREAMER_ID;
	}
}

DestroyVehicleCollisionAreas() {
	for(new v; v < MAX_VEHICLES; v ++) {
		if( IsValidDynamicArea(gVehicleColArea[v]) ) {
			DestroyDynamicArea(gVehicleColArea[v]);
		}
	}
}

Float:GetVehicleModelSphereSize(modelid) {
	new Float:x, Float:y, Float:z, Float:size;
	GetVehicleModelInfo(modelid, VEHICLE_MODEL_INFO_SIZE, x, y, z);

	size = x;
	if( y > size ) {
		size = y;
	}
	if( z > size ) {
		size = z;
	}
	return size;
}

CreateVehicleCollisionArea(vehicleid) {
	new modelid, Float:size, Float:x, Float:y, Float:z;
	modelid = GetVehicleModel(vehicleid);
	size = GetVehicleModelSphereSize(modelid);
	GetVehiclePos(vehicleid, x, y, z);
	gVehicleColArea[vehicleid-1] = CreateDynamicSphere(x, y, z, size);
	AttachDynamicAreaToVehicle(gVehicleColArea[vehicleid-1], vehicleid);
}

DestroyVehicleCollisionArea(vehicleid) {
	DestroyDynamicArea( gVehicleColArea[vehicleid-1] );
	gVehicleColArea[vehicleid-1] = INVALID_STREAMER_ID;
}

forward UpdateVehicleCollisionAreas();
public UpdateVehicleCollisionAreas() {
	for(new vehicleid = 1, max_vehicleid = GetVehiclePoolSize(); vehicleid <= max_vehicleid; vehicleid ++) {
		if( IsValidVehicle(vehicleid) && !IsValidDynamicArea(gVehicleColArea[vehicleid-1]) ) {
			// Vehicle exists but not its' collision area - create the area.
			CreateVehicleCollisionArea(vehicleid);
		}
		else if( !IsValidVehicle(vehicleid) && IsValidDynamicArea(gVehicleColArea[vehicleid-1]) ) {
			// Vehicle does not exist but its' collision area does - remove the area.
			DestroyVehicleCollisionArea(vehicleid);
		}
	}
}

//------------------------------------------------------------------------------
// Callbacks

public OnGameModeInit() {
	print("Predator FS: OnGameModeInit");
	InitPredator();

	#if defined pred_OnGameModeInit
		pred_OnGameModeInit();
	#endif
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit pred_OnGameModeInit
#if defined pred_OnGameModeInit
	forward pred_OnGameModeInit();
#endif


public OnFilterScriptInit() {
	print("Predator FS: OnFilterScriptInit");
	InitPredator();

	#if defined pred_OnFilterScriptInit
		pred_OnFilterScriptInit();
	#endif
}
#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit pred_OnFilterScriptInit
#if defined pred_OnFilterScriptInit
	forward pred_OnFilterScriptInit();
#endif


public OnGameModeExit() {
	print("Predator FS: OnGameModeExit");
	ExitPredator();

	#if defined pred_OnGameModeExit
		pred_OnGameModeExit();
	#endif
}
#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit pred_OnGameModeExit
#if defined pred_OnGameModeExit
	forward pred_OnGameModeExit();
#endif


public OnFilterScriptExit() {
	print("Predator FS: OnFilterScriptExit");
	ExitPredator();

	#if defined pred_OnFilterScriptExit
		pred_OnFilterScriptExit();
	#endif
}
#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit pred_OnFilterScriptExit
#if defined pred_OnFilterScriptExit
	forward pred_OnFilterScriptExit();
#endif


public OnPlayerSpawn(playerid) {
	if( gPredatorData[playerid][ePredatorState] == PREDATORSTATE_WAIT_SPAWN ) {
		SetupFade(playerid, .fadeto_opaque = false, .duration_ms = 2000);

		gPredatorData[playerid][ePredatorState] ++;

		ApplySpawnData(playerid);
	}

	#if defined pred_OnPlayerSpawn
		return pred_OnPlayerSpawn(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn pred_OnPlayerSpawn
#if defined pred_OnPlayerSpawn
	forward pred_OnPlayerSpawn(playerid);
#endif


public OnPlayerDeath(playerid, killerid, reason) {
	if( gPredatorData[playerid][ePredatorDamageBy] != INVALID_PLAYER_ID ) {
		// This player has been struck by a predator missile recently.

		killerid = gPredatorData[playerid][ePredatorDamageBy]; // the new killerid is the player controlling the missile.
		reason = 51; // the new death reason is 51 (explosion)

		gPredatorData[playerid][ePredatorDamageBy] = INVALID_PLAYER_ID; // reset the damage by missile player
	}

	#if defined pred_OnPlayerDeath
		return pred_OnPlayerDeath(playerid, killerid, reason); // the new values will be passed on to the next callback(s) in the chain.
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath pred_OnPlayerDeath
#if defined pred_OnPlayerDeath
	forward pred_OnPlayerDeath(playerid, killerid, reason);
#endif


public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart) {
	if( gPredatorData[playerid][ePredatorDamageBy] != INVALID_PLAYER_ID ) {
		// This player has been hit by a predator missile recently

		// reason 51 = explosion
		// reason 54 = collision / fall

		if( issuerid == INVALID_PLAYER_ID && (weaponid == 51 || weaponid == 54) ) {
			// This might be predator damage! No action needed here.
		} else {
			// This player has now been damaged by something else than a predator missile - reset their predator damage by player.
			gPredatorData[playerid][ePredatorDamageBy] = INVALID_PLAYER_ID;
		}
	}

	#if defined pred_OnPlayerTakeDamage
		return pred_OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart);
	#else
		return 0;
	#endif
}
#if defined _ALS_OnPlayerTakeDamage
	#undef OnPlayerTakeDamage
#else
	#define _ALS_OnPlayerTakeDamage
#endif
#define OnPlayerTakeDamage pred_OnPlayerTakeDamage
#if defined pred_OnPlayerTakeDamage
	forward pred_OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart);
#endif


public OnPlayerGiveDamageActor(playerid, damaged_actorid, Float:amount, weaponid, bodypart) {
	new damaged_playerid = GetActorPlayerReplacement(damaged_actorid);
	if( IsPlayerConnected(damaged_playerid) ) {
		gPredatorData[damaged_playerid][ePredatorFuel] = 0.0; // missile will cancel because it's out of fuel.
	}

	#if defined pred_OnPlayerGiveDamageActor
		return pred_OnPlayerGiveDamageActor(playerid, damaged_actorid, Float:amount, weaponid, bodypart);
	#else
		return 0;
	#endif
}
#if defined _ALS_OnPlayerGiveDamageActor
	#undef OnPlayerGiveDamageActor
#else
	#define _ALS_OnPlayerGiveDamageActor
#endif
#define OnPlayerGiveDamageActor pred_OnPlayerGiveDamageActor
#if defined pred_OnPlayerGiveDamageActor
	forward pred_OnPlayerGiveDamageActor(playerid, damaged_actorid, Float:amount, weaponid, bodypart);
#endif


public OnPlayerStateChange(playerid, newstate, oldstate) {
	if( gPredatorData[playerid][ePredatorState] == PREDATORSTATE_WAIT_SPEC && newstate == PLAYER_STATE_SPECTATING ) {
		CreatePlayerReplacementActor(playerid);

		DefaultPredatorMovementData(playerid);

		CalculatePredatorMovement(playerid);
		CalculatePredatorNextPos(playerid);
		CalculatePredatorTarget(playerid);
		CalculatePredatorCamera(playerid);

		ApplyPredatorMovement(playerid);
		ApplyPredatorCamera(playerid);

		CreatePredatorTarget(playerid, gPredatorData[playerid][ePredatorTargetX], gPredatorData[playerid][ePredatorTargetY], gPredatorData[playerid][ePredatorTargetZ]);
		ApplyPredatorTargetMovement(playerid);

		PlayPredatorMusic(playerid, .toggle = true);

		SetupFade(playerid, .fadeto_opaque = false, .duration_ms = 1000);

		ShowGUI(playerid);

		gPredatorData[playerid][ePredatorState] ++;
	}

	#if defined pred_OnPlayerStateChange
		pred_OnPlayerStateChange(playerid, newstate, oldstate);
	#endif
}
#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif
#define OnPlayerStateChange pred_OnPlayerStateChange
#if defined pred_OnPlayerStateChange
	forward pred_OnPlayerStateChange(playerid, newstate, oldstate);
#endif


public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if( gPredatorData[playerid][ePredatorState] == PREDATORSTATE_ACTIVE && (newkeys & KEY_SECONDARY_ATTACK) && !(oldkeys & KEY_SECONDARY_ATTACK) ) {
		// Predator is active and destroy button was pressed
		gPredatorData[playerid][ePredatorFuel] = 0.0; // missile will cancel because it's out of fuel.
	}

	#if defined pred_OnPlayerKeyStateChange
		pred_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#endif
}
#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange pred_OnPlayerKeyStateChange
#if defined pred_OnPlayerKeyStateChange
	forward pred_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif


public OnObjectMoved(objectid) {
	for(new playerid, max_playerid = GetPlayerPoolSize(); playerid <= max_playerid; playerid ++) {
		if( !IsPlayerConnected(playerid) ) {
			continue;
		}

		if( gPredatorData[playerid][ePredatorState] != PREDATORSTATE_ACTIVE ) {
			continue;
		}

		if( objectid != gPredatorData[playerid][ePredatorMissileObject] ) {
			continue;
		}

		if( gPredatorData[playerid][ePredatorTargetDist] < 5 || gPredatorData[playerid][ePredatorFuel] <= 0 ) {
			DestroyPlayerReplacementActor(playerid);

			KillPlayersByPredator(
				.predator_playerid = playerid,
				.explosion_x = gPredatorData[playerid][ePredatorToX],
				.explosion_y = gPredatorData[playerid][ePredatorToY],
				.explosion_z = gPredatorData[playerid][ePredatorToZ]
			);

			DestroyPredator(playerid);
			DestroyPredatorTarget(playerid);

			HideGUI(playerid);

			ApplyFadeAlpha(playerid, 0xFF);

			TogglePlayerSpectating(playerid, false);

			gPredatorData[playerid][ePredatorExplosionsLeft] = 5;
			gPredatorData[playerid][ePredatorState] ++;

			PlayPredatorMusic(playerid, .toggle = false);
		} else {
			gPredatorData[playerid][ePredatorFromX] = gPredatorData[playerid][ePredatorToX];
			gPredatorData[playerid][ePredatorFromY] = gPredatorData[playerid][ePredatorToY];
			gPredatorData[playerid][ePredatorFromZ] = gPredatorData[playerid][ePredatorToZ];
			gPredatorData[playerid][ePredatorFromCamX] = gPredatorData[playerid][ePredatorToCamX];
			gPredatorData[playerid][ePredatorFromCamY] = gPredatorData[playerid][ePredatorToCamY];
			gPredatorData[playerid][ePredatorFromCamZ] = gPredatorData[playerid][ePredatorToCamZ];

			CalculatePredatorMovement(playerid);
			CalculatePredatorNextPos(playerid);
			CalculatePredatorTarget(playerid);
			CalculatePredatorCamera(playerid);
			CalculatePredatorFuel(playerid);

			ApplyPredatorMovement(playerid);
			ApplyPredatorCamera(playerid);
			ApplyPredatorTargetMovement(playerid);

			RefreshGUI(playerid);
		}
	}

	#if defined pred_OnObjectMoved
		pred_OnObjectMoved(objectid);
	#endif
}
#if defined _ALS_OnObjectMoved
	#undef OnObjectMoved
#else
	#define _ALS_OnObjectMoved
#endif
#define OnObjectMoved pred_OnObjectMoved
#if defined pred_OnObjectMoved
	forward pred_OnObjectMoved(objectid);
#endif
