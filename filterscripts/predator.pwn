#include <predator>
#tryinclude <zcmd>

public OnPlayerDeath(playerid, killerid, reason) {
	SendDeathMessage(playerid, killerid, reason);
	return 1;
}

#if defined _zcmd_included
CMD:predator(playerid, params[]) {
	new Float:x, Float:y, Float:z;
	
	GetPlayerPos(playerid, x, y, z);
	z += 500.0;
	
	if( LaunchPredator(playerid, x, y, z) ) {
		SendClientMessage(playerid, 0x00FF00FF, "Predator launched.");
	} else {
		SendClientMessage(playerid, 0xFF0000FF, "Predator could not be launched!");
	}
	return 1;
}
#else
public OnPlayerCommandText(playerid, cmdtext[]) {
	if( !strcmp(cmdtext, "/predator", true) ) {
		new Float:x, Float:y, Float:z;

		GetPlayerPos(playerid, x, y, z);
		z += 500.0;

		if( LaunchPredator(playerid, x, y, z) ) {
			SendClientMessage(playerid, 0x00FF00FF, "Predator launched.");
		} else {
			SendClientMessage(playerid, 0xFF0000FF, "Predator could not be launched!");
		}
		return 1;
	}
	return 0;
}
#endif
